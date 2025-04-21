# Thread Pool Implementation

This project implements a simple thread pool in C that allows concurrent execution of tasks using worker threads.

## Overview

The thread pool creates a fixed number of worker threads at initialization and manages a task queue. Client code can submit tasks to the pool, which are then executed by available worker threads.

## Implementation Details

### Components

- **Thread Pool**: Manages worker threads and the task queue
- **Task Queue**: A circular buffer that holds tasks waiting to be executed
- **Worker Threads**: Continuously pull tasks from the queue and execute them

## Building and Running

### Compilation

To compile the project, simply use the provided Makefile:

```
make
```

This will generate an executable named `example`.

## Usage

### API

- `void pool_init(void)`: Initialize the thread pool
- `int pool_submit(void (*function)(void *), void *data)`: Submit a task to the pool
- `void pool_shutdown(void)`: Shut down the thread pool

## Example Client

The included client file demonstrates the thread pool in action with three test cases:

1. **Addition**: Adds two integers and prints the result
2. **Subtraction**: Subtracts one integer from another and prints the result
3. **Multiplication**: Multiplies two integers and prints the result

The client initializes the thread pool, submits these three tasks, and then shuts down the pool.

### Sample Output

When running the example program, you'll see output similar to:
```
I add two values 5 and 10 result = 15
I add subtract values 10 and 5 result = 5
I add multiply values 5 and 10 result = 50
```