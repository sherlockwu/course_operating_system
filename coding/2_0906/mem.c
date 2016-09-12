#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <assert.h>
#include "common.h"

int main(){
    //allocate a mem address
    int * p = malloc(sizeof(int));
    assert(p!= NULL);
    *p = 0;

    //output PID mem
    printf("Process %d, address of p : %08x \n", getpid(), (unsigned) p);

    //output real-time value in this address
    while(1){
        Spin(1);
        // p++
        *p = *p + 1;
        // output
        printf("(%d) p : %d \n", getpid(), *p);
    }
    return 0;
}
