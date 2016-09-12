#include <stdio.h>
#include "common.h"
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char * argv[]){
    // input
    if (argc != 2){
        printf(stderr, "usage: cpu <string> \n");
        exit(1);   //?
    }

    char * string_output;
    string_output = argv[1];



    // print
    while(1){
        // Spin
        Spin(1);
        // Output
        printf("%s\n", string_output);
    }

    return 0;
}
