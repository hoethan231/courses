CC = gcc
CFLAGS = -Wall -Wextra -g

all: allocator

allocator: contiguous_mem.c
	$(CC) $(CFLAGS) contiguous_mem.c -o allocator

clean:
	rm -f allocator