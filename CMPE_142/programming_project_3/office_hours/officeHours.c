#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define CHAIRS 3
#define STUDENTS 5

int queue = 0;              // How many students are waiting outside
int current_student = -1;   // Who is currently being helped

sem_t TA_sleep;             // TA can sleep while this is locked
sem_t TA_helping;           // So other students can't enter the office
sem_t student_ready;        // So the TA can signal the student in
pthread_mutex_t seats;      // To access critical section of queue/chairs outside

void random_sleep(int seconds) {
    sleep(rand() % seconds + 1);
}


void *handle_ta(void *param) {

    while (1) {
        sem_wait(&TA_sleep);                                            // Sleeping until students come

        pthread_mutex_lock(&seats);
        if (queue > 0) {
            queue--;
            pthread_mutex_unlock(&seats);

            sem_post(&student_ready);                                   // Let the student in
            sem_wait(&TA_helping);                                      // Lock the TA
            
            printf("TA: starting helping student %d\n", current_student);
            random_sleep(10);                                           // Random working time
            printf("TA: finished helping student %d\n", current_student);
            
            pthread_mutex_lock(&seats);
            if (queue == 0) {
                printf("TA: Going to sleep!\n");
            } else {
                printf("TA: %d students left, next!\n", queue);
            }
            pthread_mutex_unlock(&seats);
        } else {
            pthread_mutex_unlock(&seats);
        }
    }
    return NULL;
}

void *handle_student(void *param) {
    int id = *((int *)param);

    while (1) {
        random_sleep(10);                                                // Student Programming
        printf("Student %d: Needs help\n", id);

        pthread_mutex_lock(&seats);
        if (queue < CHAIRS) {
            // Add a student if theres room
            queue++;                                                     
            pthread_mutex_unlock(&seats);

            sem_post(&TA_sleep);
            sem_wait(&student_ready);

            pthread_mutex_lock(&seats);
            current_student = id;
            pthread_mutex_unlock(&seats);

            printf("Student %d: is getting help\n", id);
            sem_post(&TA_helping);
        } else {
            // When there are no seats avaible
            printf("Student %d: will come back later\n", id);
            pthread_mutex_unlock(&seats);
        }
        random_sleep(5); // Goes back to programing
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    
    // Initializing the semaphores and mutexes
    sem_init(&TA_sleep, 0, 0);
    sem_init(&TA_helping, 0, 0);
    sem_init(&student_ready, 0, 0);
    pthread_mutex_init(&seats, NULL);

    // Creating TA and student threads
    pthread_t ta_thread;
    pthread_create(&ta_thread, NULL, handle_ta, NULL);

    pthread_t student_threads[STUDENTS];
    int student_ids[STUDENTS];

    for (int i=0; i<STUDENTS; i++) {
        student_ids[i] = i;
        pthread_create(&student_threads[i], NULL, handle_student, &student_ids[i]);
    }

    for (int i = 0; i < STUDENTS; i++) {
        pthread_join(student_threads[i], NULL);
    }
    
    return 0;
}