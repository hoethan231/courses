CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: officeHours.o
	$(CC) $(CFLAGS) -o example officeHours.o $(PTHREADS)

clean:
	rm -rf *.o
	rm -rf example