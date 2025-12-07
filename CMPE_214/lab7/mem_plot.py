import subprocess, json, math
import matplotlib.pyplot as plt
import os
from collections import defaultdict

def compile_cuda(source="mem_bench.cu", out="mem_bench", arch="sm_70"):
    cmd = ["nvcc", "-O3", f"-arch={arch}", source, "-o", out]
    print("Compiling:", " ".join(cmd))
    subprocess.run(cmd, check=True)
    return f"./{out}"

def run_once(exe, bytes_per_array, mode, iters=10, block=256):
    result = subprocess.run([exe, str(bytes_per_array), str(mode), str(iters), str(block)],
                            capture_output=True, text=True, check=True)
    line = result.stdout.strip().splitlines()[-1]
    return json.loads(line)

def sweep(exe, sizes, modes, iters=10):
    rows = []
    for m in modes:
        for b in sizes:
            try:
                data = run_once(exe, b, m, iters=iters)
                rows.append(data)
                print(data)
            except subprocess.CalledProcessError as e:
                print("Failed for size", b, "mode", m, "stderr:", e.stderr)
    return rows

def to_series(rows, xkey, ykey, groupkey="Mode"):
    groups = defaultdict(list)
    for r in rows:
        groups[r[groupkey]].append((r[xkey], r[ykey]))
    for k in groups:
        groups[k] = sorted(groups[k], key=lambda t: t[0])
    return groups

def plot_series(series_dict, x_label, y_label, title, logx=True):
    plt.figure()
    for name, series in series_dict.items():
        if not series: 
            continue
        xs, ys = zip(*series)
        plt.plot(xs, ys, marker="o", label=name)
    if logx:
        plt.xscale("log", base=2)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)
    plt.grid(True, which="both")
    plt.legend()

def main():
    arch = os.environ.get("CUDA_ARCH", "sm_70")
    exe = compile_cuda(arch=arch)

    # 32 B up to 2 GiB
    sizes = [1<<p for p in range(5, 32)]

    modes = [
        0,  # pageable+memcpy
        1,  # pinned+memcpy
        2,  # uvm-nohint
        3,  # uvm-accessed
        4,  # uvm-preferred
    ]

    iters = int(os.environ.get("ITERS", "10"))
    rows = sweep(exe, sizes, modes, iters=iters)

    s1 = to_series(rows, xkey="Bytes", ykey="Total_ms")
    plot_series(s1, "Bytes per array", "Total_ms", "Total time vs size (min over runs)")
    plt.show()

if __name__ == "__main__":
    main()