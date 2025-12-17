import subprocess, json, os
import matplotlib.pyplot as plt

def compile_cuda(src="mm_bench.cu", out="mm_bench", arch="sm_75"):
    cmd = ["nvcc","-O3",f"-arch={arch}",src,"-o",out]
    print("Compiling:", " ".join(cmd))
    subprocess.run(cmd, check=True)
    return f"./{out}"

def run_once(exe, N, mode, tile, iters):
    # mode: 0=cpu-naive, 1=cpu-opt, 2=gpu-naive, 3=gpu-tiled
    p = subprocess.run(
        [exe, str(N), str(mode), str(tile), str(iters)],
        capture_output=True, text=True, check=True
    )
    line = p.stdout.strip().splitlines()[-1]
    return json.loads(line)

def main():
    arch = os.environ.get("CUDA_ARCH", "sm_75")
    exe  = compile_cuda(arch=arch)

    sizes = [1 << k for k in range(1, 14)]

    tile  = 16 
    iters = int(os.environ.get("ITERS", "5"))

    cpu_naive_times = []
    cpu_opt_times   = []
    gpu_naive_times = []
    gpu_tiled_times = []

    for N in sizes:
        print(f"N = {N}")

        # CPU naive
        r0 = run_once(exe, N, 0, tile, iters)
        cpu_naive_times.append(r0["Ms"])
        print("  CPU naive:", r0)

        # CPU optimized
        r1 = run_once(exe, N, 1, tile, iters)
        cpu_opt_times.append(r1["Ms"])
        print("  CPU opt:  ", r1)

        # GPU naive
        r2 = run_once(exe, N, 2, tile, iters)
        gpu_naive_times.append(r2["Ms"])
        print("  GPU naive:", r2)

        # GPU tiled
        r3 = run_once(exe, N, 3, tile, iters)
        gpu_tiled_times.append(r3["Ms"])
        print("  GPU tiled:", r3)

    plt.figure()
    plt.plot(sizes, cpu_naive_times, marker="o", label="CPU naive")
    plt.plot(sizes, cpu_opt_times, marker="o", label="CPU optimized")
    plt.xlabel("Matrix size N (N x N)")
    plt.ylabel("Time (ms)")
    plt.title("CPU Matrix Multiplication: naive vs optimized")
    plt.grid(True)
    plt.legend()

    plt.figure()
    plt.plot(sizes, cpu_opt_times,   marker="o", label="CPU optimized")
    plt.plot(sizes, gpu_naive_times, marker="o", label="GPU naive")
    plt.plot(sizes, gpu_tiled_times, marker="o", label="GPU tiled (shared mem)")
    plt.xlabel("Matrix size N (N x N)")
    plt.ylabel("Time (ms)")
    plt.title("CPU vs GPU Matrix Multiplication")
    plt.grid(True)
    plt.legend()

    plt.show()

if __name__ == "__main__":
    main()
