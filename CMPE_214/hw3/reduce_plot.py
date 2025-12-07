import subprocess, json, os
import matplotlib.pyplot as plt

def compile_cuda(src="reduce_bench.cu", out="reduce_bench", arch="sm_70"):
    cmd = ["nvcc","-O3",f"-arch={arch}",src,"-o",out]
    print("Compiling:", " ".join(cmd))
    subprocess.run(cmd, check=True)
    return f"./{out}"

def run(exe, N, mode, blocks, tpb, iters):
    # mode: 0=CPU, 1=gpu-naive, 2=gpu-optimized
    p = subprocess.run([exe, str(N), str(mode), str(blocks), str(tpb), str(iters)],
                       capture_output=True, text=True, check=True)
    line = p.stdout.strip().splitlines()[-1]
    return json.loads(line)

def sweep(exe, N, mode, grids, tpbs, iters):
    rows = []
    for g in grids:
        for t in tpbs:
            try:
                rows.append(run(exe, N, mode, g, t, iters))
            except subprocess.CalledProcessError as e:
                print("fail:", e.stderr)
    return rows

def plot_mode(rows, title):
    tpb_groups = {}
    for r in rows:
        key = r["TPB"]
        tpb_groups.setdefault(key, []).append((r["Blocks"], r["Best_ms"]))
    for k in tpb_groups:
        tpb_groups[k].sort()
    plt.figure()
    for tpb, series in sorted(tpb_groups.items()):
        xs = [x for x,_ in series]
        ys = [y for _,y in series]
        plt.plot(xs, ys, marker="o", label=f"TPB {tpb}")
    plt.xscale("log", base=2)
    plt.xlabel("Blocks")
    plt.ylabel("Best kernel time (ms)")
    plt.title(title)
    plt.grid(True, which="both")
    plt.legend()

def plot_cpu(cpu_ms, grids):
    plt.figure()
    xs = grids
    ys = [cpu_ms] * len(xs)
    plt.plot(xs, ys, linestyle="--", marker="o", color="black", label="CPU serial")
    plt.xscale("log", base=2)
    plt.xlabel("Blocks")
    plt.ylabel("CPU time (ms)")
    plt.title("CPU Reduction: time vs blocks")
    plt.grid(True, which="both")
    plt.legend()

def main():
    arch = "sm_70"
    exe  = compile_cuda(arch=arch)

    N = 16777216
    grids = [1,2,4,8,16,32,64,128]
    tpbs  = [32,64,128,256,512,1024]
    iters = int(os.environ.get("ITERS","7"))

    cpu_row = run(exe, N, 0, 1, 1, iters)
    cpu_ms = cpu_row["Best_ms"]
    plot_cpu(cpu_ms, grids)

    naive_rows = sweep(exe, N, 1, grids, tpbs, iters)
    plot_mode(naive_rows, "Naïve GPU Reduction: time vs blocks")

    opt_rows = sweep(exe, N, 2, grids, tpbs, iters)
    plot_mode(opt_rows, "Optimized GPU Reduction: time vs blocks")

    plt.show()

if __name__ == "__main__":
    main()
