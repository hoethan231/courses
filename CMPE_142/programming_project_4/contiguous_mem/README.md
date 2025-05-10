# Contiguous Memory Allocator Implementation

This project implements a memory allocator that manages a contiguous region of memory using different allocation strategies as described in Section 9.2 of the textbook.

## Overview

The program simulates memory allocation and deallocation in an operating system by maintaining a list of allocated and free memory blocks. It supports multiple memory allocation strategies and provides features for memory compaction and status reporting.

## Implementation Details

### Components

- **Memory Blocks**: Tracks both allocated and free regions of memory
- **Process Management**: Associates memory regions with specific processes
- **Allocation Strategies**: Implements First-Fit, Best-Fit, and Worst-Fit algorithms
- **Memory Compaction**: Consolidates fragmented free memory into one contiguous block

### Key Features

- **Memory Request (RQ)**: Allocates memory to processes using one of three strategies
- **Memory Release (RL)**: Frees memory associated with a process
- **Memory Compaction (C)**: Defragments memory by moving allocated blocks
- **Status Report (STAT)**: Displays the current state of memory allocation

## Memory Allocation Strategies

The allocator supports three different strategies:

- **First-Fit (F)**: Allocates the first hole that is big enough
- **Best-Fit (B)**: Allocates the smallest hole that is big enough
- **Worst-Fit (W)**: Allocates the largest hole available

## Memory Management

When memory is released, the program automatically merges adjacent free blocks to minimize fragmentation. The compaction feature moves all allocated blocks to the beginning of memory and consolidates all free space into a single hole.

### Compilation

To compile the project, use:

```
make
```

### Running

Execute the program with the initial memory size as a parameter:

```
./allocator 1048576
```

This initializes the allocator with 1MB of memory.

## Commands

The program supports the following commands:

- **RQ \<process_id\> \<size\> \<algorithm\>**: Request memory allocation
  - Example: `RQ P0 40000 W` (Allocate 40000 bytes to process P0 using Worst-Fit)
  - Algorithm options: F (First-Fit), B (Best-Fit), W (Worst-Fit)

- **RL \<process_id\>**: Release memory allocated to a process
  - Example: `RL P0` (Free memory allocated to process P0)

- **C**: Compact memory by moving allocated blocks together
  - Combines all free blocks into one large hole

- **STAT**: Display the current memory allocation status
  - Shows which addresses are allocated to which processes

- **X**: Exit the program

## Sample Output

When running the program, you'll see output similar to:

```
Memory initialized with 1048576 bytes
allocator> RQ P0 100000 F
Successfully allocated 100000 bytes to process P0
allocator> RQ P1 200000 B
Successfully allocated 200000 bytes to process P1
allocator> STAT

Current memory allocation:
-------------------------
Addresses [0:99999] Process P0
Addresses [100000:299999] Process P1
Addresses [300000:1048575] Unused
-------------------------
allocator> RL P0
Memory allocated to process P0 has been released
allocator> STAT

Current memory allocation:
-------------------------
Addresses [0:99999] Unused
Addresses [100000:299999] Process P1
Addresses [300000:1048575] Unused
-------------------------
allocator> C
Moved process P1 from addresses [100000:299999] to [0:199999]
Compaction completed. All free memory consolidated at addresses [200000:1048575]
allocator> STAT

Current memory allocation:
-------------------------
Addresses [0:199999] Process P1
Addresses [200000:1048575] Unused
-------------------------
```

This example demonstrates how the program allocates memory to processes, releases memory, compacts the memory space, and provides status reports.