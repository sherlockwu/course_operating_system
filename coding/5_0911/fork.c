#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    // print something
    printf("Good Morning, this is process %d\n", getpid());

    // fork
    int rc = fork();

    // facing different process
    if (rc < 0){
        // fail
        fprintf(stderr, "Fail to fork a new process");
        exit(1);
    }
    if (rc ==0){
        // child process
        //prnt
        printf("Hello, this is child process: %d\n", getpid());
    } else{
        // parent
        // print itself and child
        printf("Hello, this is process %d, parent of process %d\n", getpid(), rc);

    }
    return 0;
}
