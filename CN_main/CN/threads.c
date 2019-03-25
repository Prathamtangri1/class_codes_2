#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5   

void* func1(void* threadid) {
    long tid;
    tid = (long)threadid;
    printf("Thread id: %d\n", tid);
    pthread_exit(NULL);
}

int main(){
    pthread_t threads[NUM_THREADS];
    int rc, i;

    for(int i = 0 ; i < NUM_THREADS ; i++) {
        printf("Creating Thread: %d\n", i);
        rc = pthread_create(&threads[i], NULL, func1, (void*)i);

        if(rc) {
            printf("Error creating thread: %d %d\n", rc, i);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
