#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "error_functions.h"

int main(int argc, char *argv[]){
    if(argc < 3 || strcmp(argv[1],"--help") == 0){
        usageErr("%s file1 file2 [-a]\n", argv[0]);
    }

    char para;
    _Bool ifa = 0;
    while((para = getopt(argc, argv, "a"))!=-1){
        switch (para){
            case 'a':{
                ifa = 1;
            }break;
            default:{
                printf("error opterr: %d\n", opterr);
                break;
            }
        }    
    }
    char * file1 = NULL;
    char * file2 = NULL;
        // 收集文件路径参数
    for (int i = optind; i < argc; ++i) {
        if (!file1) {
            file1 = argv[i];
        } else if (!file2) {
            file2 = argv[i];
        } else {
            usageErr("Too many file arguments.\n");
            return 1;
        }
    }


    int fd1,fd2;
    fd1 = open(file1,O_RDONLY);
    if(fd1 == -1){
        errExit("open %s", argv[1]);
    }

    int openFlags = O_RDWR | O_CREAT;
    if(ifa) openFlags |= O_APPEND;

    fd2 = open(file2, openFlags,  S_IRUSR | S_IWUSR | S_IRGRP | S_IRGRP | S_IROTH | S_IWOTH);
    if(fd2 == -1){
        errExit("open %s", argv[1]);
    }


    char buf[1024];
    int numRead;
    while((numRead = read(fd1, buf, 1024)) > 0){
        if(write(fd2, buf, numRead) != numRead){
            errExit("write");
        }
    }
    exit(EXIT_SUCCESS);
}
