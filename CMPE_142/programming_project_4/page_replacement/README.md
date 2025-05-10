# Page Replacement Algorithm Simulator

This program implements and compares three page replacement algorithms: FIFO (First-In-First-Out), LRU (Least Recently Used), and OPT (Optimal), as described in Section 10.4 of the textbook.

## Overview

The program generates a random page-reference string with page numbers ranging from 0 to 9, applies this reference string to each page replacement algorithm, and records the number of page faults incurred by each algorithm.

## Implementation Details

### Page Replacement Algorithms

1. **FIFO (First-In-First-Out)**
   - Replaces the page that has been in memory the longest
   - Maintains a queue to track the order of page arrivals
   - Simple to implement but may suffer from Belady's anomaly

2. **LRU (Least Recently Used)**
   - Replaces the page that has not been used for the longest period of time
   - Requires tracking when each page was last accessed
   - Generally performs better than FIFO but is more complex to implement

3. **OPT (Optimal)**
   - Replaces the page that will not be used for the longest period of time in the future
   - Requires future knowledge of the reference string
   - Provides the theoretical minimum number of page faults
   - Not practically implementable in real systems but useful as a benchmark

### Implementation Features

- Random generation of page-reference strings
- Detailed visualization of the first 20 page references for each algorithm
- Comprehensive comparison of page fault rates
- Support for configurable number of page frames

## Compilation

To compile the program, use:

```
make
```

## Running the Program

Run the program by specifying the number of page frames:

```
./page_replacement <number_of_frames>
```

Example:
```
./page_replacement 3
```

This will run the simulation with 3 page frames.

## Output

The program produces output in the following format:

1. The randomly generated page-reference string
2. For each algorithm (FIFO, LRU, OPT):
   - Visualization of the first 20 page references
   - Total number of page faults
3. A summary comparison of all three algorithms:
   - Number of page faults
   - Page fault rate

## Sample Output

```
Generated Page Reference String:
3 2 1 0 4 5 2 6 7 0 1 3 5 4 2 1 0 6 7 8 
...

Running FIFO Page Replacement Algorithm:
Reference  0: Page 3 loaded into frame. Frames: [ 3*, -, -]  [Page Fault]
Reference  1: Page 2 loaded into frame. Frames: [ 3,  2*, -]  [Page Fault]
...
FIFO Total Page Faults: 65

Running LRU Page Replacement Algorithm:
Reference  0: Page 3 loaded into frame. Frames: [ 3*, -, -]  [Page Fault]
Reference  1: Page 2 loaded into frame. Frames: [ 3,  2*, -]  [Page Fault]
...
LRU Total Page Faults: 59

Running Optimal Page Replacement Algorithm:
Reference  0: Page 3 loaded into frame. Frames: [ 3*, -, -]  [Page Fault]
Reference  1: Page 2 loaded into frame. Frames: [ 3,  2*, -]  [Page Fault]
...
Optimal Total Page Faults: 48

Page Replacement Algorithm Comparison:
===================================
Number of frames: 3
Reference string length: 100

Algorithm        Page Faults     Fault Rate
---------------------------------------
FIFO             65              65.00%
LRU              59              59.00%
OPT              48              48.00%
```

## Analysis

The program demonstrates the theoretical advantages of the different page replacement algorithms:
- OPT generally performs the best (lowest page fault rate) as it has perfect knowledge of future page references
- LRU typically performs better than FIFO as it makes use of temporal locality
- The performance gap between algorithms tends to vary based on the reference string pattern and number of frames

By comparing these algorithms on the same reference string, the program helps illustrate the core concepts of virtual memory management and page replacement policies.