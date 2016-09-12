#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int loop;
volatile int counter = 0;

void * worker(void * argv){

    int i;
    for (i=0; i<loop; i++){
        counter++;
    }
    return NULL;
}


int main(int argc, char * argv[]){
    // input(long-time change)
    if (argc !=2 ){
        fprintf(stderr, "usage: threads <value> \n");
        exit(1);
    }
    loop = atoi(argv[1]);   // integer

    // generate two threads
    pthread_t p1, p2;
    int rc;
    rc = pthread_create(&p1, NULL, worker, NULL);
    rc = pthread_create(&p2, NULL, worker, NULL);


    // make long-time change to the counters, individually
    // join pthreads
    rc = pthread_join(p1, NULL);
    rc = pthread_join(p2, NULL);

    // print the final value of the counter
    printf("Final Value from 0 : %d\n", counter);
    return 0;
}
