#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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
        // print
        printf("Hello, this is child process: %d\n", (int)getpid());
        // redirection
        close(STDOUT_FILENO);
        open("./exe.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
        // exec
            // set arguments
            char *myargs[3];
            myargs[0] = strdup("wc");
            myargs[1] = strdup("fork.c");
            myargs[2] = NULL;

            // call
            execvp(myargs[0], myargs);
        // print
        printf("You shouldn't see this");
    } else{
        // parent
        int wc = wait(NULL);
        // print itself and child
        printf("Hello, this is process %d, parent of process %d\n", (int)getpid(), rc);

    }
    return 0;
}
