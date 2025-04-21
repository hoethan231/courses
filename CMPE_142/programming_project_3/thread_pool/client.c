/**
 * Example client program that uses thread pool.
 */

#include <stdio.h>
#include <unistd.h>
#include "threadpool.h"

struct data
{
    int a;
    int b;
};

void add(void *param)
{
    struct data *temp;
    temp = (struct data*)param;

    printf("I add two values %d and %d result = %d\n",temp->a, temp->b, temp->a + temp->b);
}

void sub(void *param)
{
    struct data *temp;
    temp = (struct data*)param;

    printf("I add subtract values %d and %d result = %d\n",temp->a, temp->b, temp->a - temp->b);
}

void mul(void *param)
{
    struct data *temp;
    temp = (struct data*)param;

    printf("I add multiply values %d and %d result = %d\n",temp->a, temp->b, temp->a * temp->b);
}

int main(void)
{
    // create some work to do
    struct data work1;
    struct data work2;
    struct data work3;

    work1.a = 5;
    work2.a = 10;
    work3.a = 5;
    work1.b = 10;
    work2.b = 5;
    work3.b = 10;

    // initialize the thread pool
    pool_init();

    // submit the work to the queue
    pool_submit(&add,&work1);
    pool_submit(&sub,&work2);
    pool_submit(&mul,&work3);

    // may be helpful 
    // sleep(3);

    pool_shutdown();

    return 0;
}