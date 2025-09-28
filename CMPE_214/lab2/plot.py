import json
import subprocess
import matplotlib.pyplot as plt

def compile_cuda(source="vecadd.cu", out="vecadd", arch="sm_70"):
    cmd = ["nvcc", "-O3", f"-arch={arch}", source, "-o", out]
    print("Compiling:", " ".join(cmd))
    subprocess.run(cmd, check=True)
    return f"./{out}"

def run_one(exe, N, blocks, tpb, iters=30):
    try:
        result = subprocess.run(
            [exe, str(N), str(blocks), str(tpb), str(iters)],
            capture_output=True, text=True, check=True
        )
        line = result.stdout.strip().splitlines()[-1]
        return json.loads(line)
    except subprocess.CalledProcessError as e:
        print("Run failed:", e, e.stderr)
    return None

POW2 = [1,2,4,8,16,32,64,128,256,512,1024]

def sweep_threads_per_block(exe, N, blocks_choices, tpb_choices=POW2, metric="Kernel_ms"):
    """
    Vary the thread per block.
    """
    out = {}
    for b in blocks_choices:
        series = []
        for t in tpb_choices:
            d = run_one(exe, N, b, t)
            if d: series.append((t, d[metric]))
        out[b] = series
    return out

def sweep_blocks(exe, N, tpb_choices, blocks_choices=POW2, metric="Kernel_ms"):
    """
    Vary the blocks
    """
    out = {}
    for t in tpb_choices:
        series = []
        for b in blocks_choices:
            d = run_one(exe, N, b, t)
            if d: series.append((b, d[metric]))
        out[t] = series
    return out

def sweep_fixed_total_threads(exe, N, totals, metric="Kernel_ms"):
    """
    Keeping the total number of threads fixed, but varying the tpb and blocks
    """
    out = {}
    for total in totals:
        series = []
        for t in POW2:
            b = total // t
            if b in POW2:
                d = run_one(exe, N, b, t)
                if d: series.append((t, d[metric]))
        out[total] = series
    return out

def plot_series_dict(series_dict, x_label, y_label, title):
    plt.figure()
    for key, series in series_dict.items():
        if not series: 
            continue
        xs, ys = zip(*series)
        plt.plot(xs, ys, marker="o", label=str(key))
    plt.xscale("log", base=2)
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)
    plt.legend()
    plt.grid(True, which="both")

def main():
    N = 1 << 20   # A lot of elements to test
    iters = 20
    arch = "sm_70"

    exe = compile_cuda(arch=arch)

    metric = "Kernal_ms"
    q1 = sweep_threads_per_block(exe, N, POW2, metric=metric)
    plot_series_dict(q1, "Threads per block", f"{metric}", f"Q1: {metric} vs TPB (blocks fixed) @ N={N}")

    q2 = sweep_blocks(exe, N, POW2, metric=metric)
    plot_series_dict(q2, "Blocks", f"{metric}", f"Q2: {metric} vs Blocks (TPB fixed) @ N={N}")

    q3 = sweep_fixed_total_threads(exe, N, POW2, metric=metric)
    plot_series_dict(q3, "Threads per block (blocks = total/tpb)", f"{metric}",
                     f"Q3: {metric} vs TPB (Total threads fixed) @ N={N}")

    plt.show()
