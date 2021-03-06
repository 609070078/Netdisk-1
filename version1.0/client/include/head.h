#ifndef __HEAD_H__
#define __HEAD_H__
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/time.h>
#include <strings.h>
#include <syslog.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/epoll.h>
#include <sys/uio.h>
#include <sys/sendfile.h>
#include <libgen.h>

/* #define ARGS_CHECK(argc, val) {\ */
/*     if(argc != val) {\ */
/*         printf("error args\n");\ */
/*         return -1;\ */
/*     }\ */
/* } */

#define ERROR_CHECK(ret, retVal, funcName) {\
    if(ret == retVal) {\
        perror(funcName);\
        return -1;\
    }\
}

#define THREAD_ERROR_CHECK(ret, funcName) {\
    if(ret != 0) {\
        printf("%s:%s\n", funcName, strerror(ret));\
        return -1;\
    }\
}

#define CHILD_THREAD_ERROR_CHECK(ret, funcName) {\
    if(ret != 0) {\
        printf("%s:%s\n", funcName, strerror(ret));\
        return (void*)-1;\
    }\
}

typedef struct {
    char ip[17];
    int port;
}Config_t, *pConfig_t;

typedef struct {
    int dataLen;
    char buf[1000];
}train_t;

enum CMD {
    CD, LS, PUTS, GETS, MKDIR, RM, PWD
};

bool configInfo(pConfig_t);
void setNonBlock(int);
int recvCycle(int, void*, int);
int endRcv(int socketFd);
int login(int socketFd, char* usrname);
int epollInAdd(int epfd, int fd);
int request(int socketFd, char* nowpath, int CMD, char* pathname);
int getsCmd(int socketFd);
int putsCmd(int socketFd, char* pathname);

#endif

