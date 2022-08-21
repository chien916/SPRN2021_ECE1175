#include <stdio.h>
#include <pthread.h>
#include <sched.h>
#include <unistd.h>

// Define the mutex as global variable
pthread_t thread1, thread2, thread3;
pthread_mutex_t lock;
pthread_mutexattr_t attributes;
int policy = SCHED_RR;


void *function1() {
    printf("Thread 1 - Try to lock\n");
    pthread_mutex_lock(&lock);
    printf("Thread 1 - Mutex locked \n");
    printf("Thread 1 ----TO DO----\n");
    for (unsigned int i = 0; i < 599999999; i++) {}
    printf("Thread 1 - Mutex unlocked\n");
    pthread_mutex_unlock(&lock);
}

void *function2() {
    printf("Thread 2 - Try to lock\n");
    pthread_mutex_lock(&lock);
    printf("Thread 2 had the lock \n");
    printf("Thread 2 ----TO DO----\n");
    for (unsigned int i = 0; i < 599999999; i++) {}
    printf("Thread 2 - Mutex unlocked\n");
    pthread_mutex_unlock(&lock);
}

void *function3() {
    printf("Thread 3 - Try to lock\n");
    pthread_mutex_lock(&lock);
    printf("Thread 3 had the lock \n");
    printf("Thread 3 ----TO DO----\n");
    for (unsigned long i = 0; i < 5999999999; i++) {}
    printf("Thread 3 - Mutex unlocked\n");
    pthread_mutex_unlock(&lock);
}

int main() {
    //Create mutex and initialize it.
    pthread_mutexattr_setprotocol(&attributes, PTHREAD_PRIO_INHERIT);
    pthread_mutex_init(&lock, &attributes);

    struct sched_param param_main;
    param_main.sched_priority = 90;
    pthread_setschedparam(pthread_self(), policy, &param_main);


    struct sched_param param_3;
    param_3.sched_priority = 4;
    printf("Thread 3 released with priority of %d\n", param_3.sched_priority);
    pthread_create(&thread3, NULL, function3, NULL);
    pthread_setschedparam(thread3, policy, &param_3);
    sleep(1);


    struct sched_param param_1;
    param_1.sched_priority = 10;
    printf("Thread 1 released with priority of %d\n", param_1.sched_priority);
    pthread_create(&thread1, NULL, function1, NULL);
    pthread_setschedparam(thread1, policy, &param_1);
    sleep(1);


    struct sched_param param_2;
    param_2.sched_priority = 7;
    printf("Thread 2 released with priority of %d\n", param_2.sched_priority);
    pthread_create(&thread2, NULL, function2, NULL);
    pthread_setschedparam(thread2, policy, &param_2);
    sleep(1);

    pthread_join(thread3, NULL);sleep(1);
    pthread_join(thread1, NULL);sleep(1);
    pthread_join(thread2, NULL);sleep(1);
    //Waiting for thread to complete

//    pthread_join(thread3, NULL);
//    pthread_join(thread1, NULL);

    return 0;
}