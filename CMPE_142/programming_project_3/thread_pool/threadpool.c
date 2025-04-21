/**
 * Implementation of thread pool.
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include "threadpool.h"

#define QUEUE_SIZE 10
#define NUMBER_OF_THREADS 3

#define TRUE 1

int keep_running = 1;

typedef struct 
{
    void (*function)(void *p);
    void *data;
} task;

// My queue class
typedef struct {
    task tasks[QUEUE_SIZE];
    int front;
    int rear;
    int count;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} task_queue;

task_queue queue;

pthread_t bees[NUMBER_OF_THREADS];

int enqueue(task t) {
    // Lock and wait while queue is being accessed by other threads
    pthread_mutex_lock(&queue.lock);
    while (queue.count == QUEUE_SIZE) {
        pthread_cond_wait(&queue.not_full, &queue.lock);
    }

    // Adds task to queue and moves rear pointer
    queue.tasks[queue.rear] = t;
    queue.rear = (queue.rear + 1) % QUEUE_SIZE;
    queue.count++;

    // Releases locks
    pthread_cond_signal(&queue.not_empty);
    pthread_mutex_unlock(&queue.lock);
    return 0;
}

task dequeue() {
    // Locks mutex again
    pthread_mutex_lock(&queue.lock);
    while (queue.count == 0) {
        pthread_cond_wait(&queue.not_empty, &queue.lock);
    }

    // Pops task from queue and iterates front pointer
    task t = queue.tasks[queue.front];
    queue.front = (queue.front + 1) % QUEUE_SIZE;
    queue.count--;

    // Opens mutex
    pthread_cond_signal(&queue.not_full);
    pthread_mutex_unlock(&queue.lock);
    return t;
}

// the worker thread in the thread pool
void *worker(void *param) {
    // Continues poping tasks from pop
    while (keep_running) {
        task t = dequeue();
        t.function(t.data);
    }
    return NULL;
}

/**
 * Submits work to the pool.
 */
int pool_submit(void (*somefunction)(void *), void *p) {
    task t;
    t.function = somefunction;
    t.data = p;
    return enqueue(t);
}


// initialize the thread pool
void pool_init(void) {
    queue.front = queue.rear = queue.count = 0;
    pthread_mutex_init(&queue.lock, NULL);
    pthread_cond_init(&queue.not_empty, NULL);
    pthread_cond_init(&queue.not_full, NULL);

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_create(&bees[i], NULL, worker, NULL);
    }
}

// shutdown the thread pool
void pool_shutdown(void) {
    keep_running = 0;

    // Stop the bees
    pthread_mutex_lock(&queue.lock);
    pthread_cond_broadcast(&queue.not_empty);
    pthread_mutex_unlock(&queue.lock);

    // Initializes all the threads
    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        pthread_join(bees[i], NULL);
    }

    // Deletes mutex and semaphores
    pthread_mutex_destroy(&queue.lock);
    pthread_cond_destroy(&queue.not_empty);
    pthread_cond_destroy(&queue.not_full);
}
