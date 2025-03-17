# Kernel Module Project

## Overview
This project implements three kernel modules to demonstrate various Linux kernel programming concepts:
1. A simple module that displays kernel information
2. A module that reports the current value of jiffies
3. A module that calculates elapsed time in seconds

Additionally, a simple file copy utility is included to demonstrate system call tracing.

## Module Design and Functionality

### Simple Module
The simple module provides basic information about the kernel:
- Prints the GOLDEN_RATIO_PRIME constant
- Displays the HZ value (system timer frequency)
- Shows the current jiffies value on load and unload
- Calculates and displays the GCD of 3300 and 24 on unload

### Jiffies Module
The jiffies module creates a proc file that reports the current value of the jiffies counter when read:
- Creates a proc entry named "jiffies"
- Implements a proc_read function to handle read operations
- Safely copies data to user space using copy_to_user

### Seconds Module
The seconds module creates a proc file that reports the elapsed time in seconds since the module was loaded:
- Creates a proc entry named "seconds"
- Stores the initial jiffies value at module load time
- Calculates elapsed seconds by subtracting initial jiffies from current jiffies and dividing by HZ

## Test Cases and Results

### Simple Module Testing


```
$ sudo insmod simple.c
$ sudo rmmod simple.c
$ dmesg
Golden Ratio: 88942315846
```

### Jiffies Module Testing
```
$ sudo insmod jiffies.ko
$ cat /proc/jiffies
Jiffies: 4328744602

$ sleep 5
$ cat /proc/jiffies
Jiffies: 4328745102

$ sudo rmmod jiffies
```

### Seconds Module Testing
```
$ sudo insmod seconds.ko
$ cat /proc/seconds
Elapsed Seconds: 0

$ sleep 10
$ cat /proc/seconds
Elapsed Seconds: 10

$ sleep 20
$ cat /proc/seconds
Elapsed Seconds: 30

$ sudo rmmod seconds
```

### File Copy Utility Testing
```
$ gcc -o filecopy filecopy.c
$ ./filecopy
Usage: ./filecopy destination source

$ ./filecopy existing.txt source.txt
File existing.txt already exists

$ ./filecopy new.txt nonexistent.txt
Cannot access nonexistent.txt

$ ./filecopy new.txt source.txt
$ diff new.txt source.txt

```

## System Call Tracing

I used the `strace` utility to trace system calls made by the file copy program:

```
$ strace ./filecopy new.txt source.txt
execve("./filecopy", ["./filecopy", "new.txt", "source.txt"], 0x7ffe1d33d2c0 /* 51 vars */) = 0
brk(NULL)                               = 0x55a9b744c000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=106094, ...}) = 0
mmap(NULL, 106094, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f7f7d3e5000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\360q\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=2029224, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f7f7d3e3000
mmap(NULL, 2036952, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f7f7d1f2000
mprotect(0x7f7f7d214000, 1847296, PROT_NONE) = 0
mmap(0x7f7f7d214000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x22000) = 0x7f7f7d214000
mmap(0x7f7f7d38c000, 303104, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19a000) = 0x7f7f7d38c000
mmap(0x7f7f7d3d7000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1e5000) = 0x7f7f7d3d7000
mmap(0x7f7f7d3dd000, 13528, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f7f7d3dd000
close(3)                                = 0
arch_prctl(ARCH_SET_FS, 0x7f7f7d3e4540) = 0
mprotect(0x7f7f7d3d7000, 12288, PROT_READ) = 0
mprotect(0x55a9b6b4e000, 4096, PROT_READ) = 0
mprotect(0x7f7f7d429000, 4096, PROT_READ) = 0
munmap(0x7f7f7d3e5000, 106094)          = 0
access("new.txt", F_OK)                 = -1 ENOENT (No such file or directory)
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 0), ...}) = 0
openat(AT_FDCWD, "new.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666) = 3
openat(AT_FDCWD, "source.txt", O_RDONLY) = 4
read(4, "This is a test file.\nIt has some"..., 8192) = 56
write(3, "This is a test file.\nIt has some"..., 56) = 56
read(4, "", 8192)                       = 0
close(3)                                = 0
close(4)                                = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

### Challenges with Tracing:

**Distinguishing Between Library and Direct System Calls**:
   - The C standard library functions as I am use to C++.
   - Tracing shows the actual system calls, not the library functions used in the code
