#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
int main(int argc,char *argv[]){
    if((argc != 3) || strcmp(argv[1],"--help") == 0){
        printf("%s src-file nwe-file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int inputfd,outputfd,openFlags;
    char buf[1024];

    mode_t fileperms;
    ssize_t numRead;

    inputfd = open(argv[1],O_RDONLY);
    if(inputfd == -1){
        printf("%s:%s\n",argv[1],strerror(errno));
        exit(EXIT_FAILURE);
    }

    openFlags = O_CREAT | O_WRONLY | O_TRUNC | O_EXCL;
    fileperms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

    outputfd = open(argv[2], openFlags, fileperms);
    if(outputfd == -1){
        printf("%s:%s\n",argv[2],strerror(errno));
        exit(EXIT_FAILURE);
    }

    while((numRead = read(inputfd, buf, 1024)) > 0){
        if(write(outputfd, buf, numRead) != numRead){
            printf("%s\n",strerror(0));
            exit(EXIT_FAILURE);
        }
    }

    if(numRead == -1){
        printf("%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(close(inputfd)==-1){
        printf("%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(close(outputfd)==-1){
        printf("%s\n",strerror(errno));
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}