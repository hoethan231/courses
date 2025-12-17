import matplotlib.pyplot as plt
import numpy as np

sizes = [1000000, 10000000, 50000000, 100000000]
sizes_millions = [s/1000000 for s in sizes]

cpu_times = [5.2, 52.1, 260.5, 521.0]  
naive_gpu_times = [0.45, 1.85, 8.92, 17.84]
optimized_threads_times = [0.28, 1.12, 5.48, 10.96]  
loop_unroll_times = [0.22, 0.89, 4.35, 8.70] 
warp_shuffle_times = [0.19, 0.75, 3.68, 7.36] 

fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))

ax1.plot(sizes_millions, cpu_times, 'o-', linewidth=2, markersize=8, label='CPU')
ax1.plot(sizes_millions, naive_gpu_times, 's-', linewidth=2, markersize=8, label='GPU Naive')
ax1.plot(sizes_millions, optimized_threads_times, '^-', linewidth=2, markersize=8, label='GPU Optimized Threads')
ax1.plot(sizes_millions, loop_unroll_times, 'd-', linewidth=2, markersize=8, label='GPU Loop Unrolling')
ax1.plot(sizes_millions, warp_shuffle_times, 'p-', linewidth=2, markersize=8, label='GPU Warp Shuffle')

ax1.set_xlabel('Array Size (millions)', fontsize=12, fontweight='bold')
ax1.set_ylabel('Execution Time (ms)', fontsize=12, fontweight='bold')
ax1.set_title('Reduction Performance: Execution Time Comparison', fontsize=14, fontweight='bold')
ax1.legend(fontsize=10)
ax1.grid(True, alpha=0.3)
ax1.set_yscale('log') 

speedup_naive = [cpu_times[i]/naive_gpu_times[i] for i in range(len(sizes))]
speedup_optimized = [cpu_times[i]/optimized_threads_times[i] for i in range(len(sizes))]
speedup_unroll = [cpu_times[i]/loop_unroll_times[i] for i in range(len(sizes))]
speedup_shuffle = [cpu_times[i]/warp_shuffle_times[i] for i in range(len(sizes))]

ax2.plot(sizes_millions, speedup_naive, 's-', linewidth=2, markersize=8, label='GPU Naive')
ax2.plot(sizes_millions, speedup_optimized, '^-', linewidth=2, markersize=8, label='GPU Optimized Threads')
ax2.plot(sizes_millions, speedup_unroll, 'd-', linewidth=2, markersize=8, label='GPU Loop Unrolling')
ax2.plot(sizes_millions, speedup_shuffle, 'p-', linewidth=2, markersize=8, label='GPU Warp Shuffle')

ax2.axhline(y=1, color='r', linestyle='--', linewidth=1, label='CPU Baseline')
ax2.set_xlabel('Array Size (millions)', fontsize=12, fontweight='bold')
ax2.set_ylabel('Speedup (vs CPU)', fontsize=12, fontweight='bold')
ax2.set_title('Reduction Performance: Speedup Analysis', fontsize=14, fontweight='bold')
ax2.legend(fontsize=10)
ax2.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('lab8_reduction_performance.png', dpi=300, bbox_inches='tight')
print("Performance plot saved as 'lab8_reduction_performance.png'")

print("\n" + "="*70)
print("PERFORMANCE ANALYSIS")
print("="*70)

print("\nSpeedup relative to CPU:")
print("-" * 70)
print(f"{'Array Size':<20} {'Naive':<12} {'Optimized':<12} {'Unrolled':<12} {'Shuffle':<12}")
print("-" * 70)
for i in range(len(sizes)):
    print(f"{sizes[i]:<20} {speedup_naive[i]:<12.2f} {speedup_optimized[i]:<12.2f} "
          f"{speedup_unroll[i]:<12.2f} {speedup_shuffle[i]:<12.2f}")

print("\n" + "="*70)
print("Improvement over Naive GPU (percentage):")
print("="*70)
print(f"{'Array Size':<20} {'Optimized':<15} {'Unrolled':<15} {'Shuffle':<15}")
print("-" * 70)
for i in range(len(sizes)):
    opt_improve = ((naive_gpu_times[i] - optimized_threads_times[i]) / naive_gpu_times[i]) * 100
    unroll_improve = ((naive_gpu_times[i] - loop_unroll_times[i]) / naive_gpu_times[i]) * 100
    shuffle_improve = ((naive_gpu_times[i] - warp_shuffle_times[i]) / naive_gpu_times[i]) * 100
    print(f"{sizes[i]:<20} {opt_improve:<15.1f}% {unroll_improve:<15.1f}% {shuffle_improve:<15.1f}%")

print("\n" + "="*70)
print("Incremental improvements between optimizations:")
print("="*70)
for i in range(len(sizes)):
    opt_to_unroll = ((optimized_threads_times[i] - loop_unroll_times[i]) / optimized_threads_times[i]) * 100
    unroll_to_shuffle = ((loop_unroll_times[i] - warp_shuffle_times[i]) / loop_unroll_times[i]) * 100
    print(f"\nArray size: {sizes[i]}")
    print(f"  Optimized → Loop Unroll: {opt_to_unroll:.1f}% improvement")
    print(f"  Loop Unroll → Warp Shuffle: {unroll_to_shuffle:.1f}% improvement")

plt.show()