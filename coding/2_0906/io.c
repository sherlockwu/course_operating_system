#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    int fd = open("./tmp", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);

    int rc = write(fd, "Hello World! \n", 15);

    close(fd);
    return 0;
}
