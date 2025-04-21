# Sleeping TA Problem Implementation

This project implements the classic "Sleeping Teaching Assistant" synchronization problem using POSIX threads, semaphores, and mutex locks.

## Overview

The problem involves coordinating multiple student threads and a TA thread. Students alternate between programming and seeking help from the TA. The TA can help only one student at a time, and there are a limited number of chairs in the hallway for waiting students.

## Implementation Details

### Components

- **TA Thread**: Sleeps when no students are waiting, helps students one by one when available
- **Student Threads**: Alternate between programming and seeking help from the TA
- **Waiting Area**: Limited number of chairs where students can wait their turn

### Synchronization Mechanisms

- **Semaphores**: Control access to the TA and coordinate student-TA interactions
- **Mutex Lock**: Protects access to the shared waiting queue data structure
- **Condition Variables**: Used for thread signaling and coordination

## Synchronization Details

The code uses three semaphores:
- `ta_sleep`: Controls when the TA sleeps/wakes up
- `student_ready`: Signals a student that the TA is ready to help
- `ta_helping`: Student signals they're ready to be helped by the TA

A mutex lock protects the waiting queue:
- `seats`: Ensures atomic operations on the waiting counter

### Compilation

To compile the project, use:

```
make
```

### Running

Execute the compiled program:

```
./example
```

## Sample Output

When running the program, you'll see output similar to:

```
Student 2: Needs help
Student 2: is getting help
TA: starting helping student 2
TA: finished helping student 2
TA: Going to sleep!
Student 2: Needs help
Student 2: is getting help
TA: starting helping student 2
Student 0: Needs help
Student 3: Needs help
Student 4: Needs help
Student 1: Needs help
Student 1: will come back later
TA: finished helping student 2
TA: 3 students left, next!
Student 0: is getting help
```
Here we can see that after three students: 0, 3, 4 are in the seats outside so student 1 had to come back later
