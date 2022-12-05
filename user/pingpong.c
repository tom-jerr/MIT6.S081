#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    int fp[2], cp[2];
    if (pipe(fp) < 0 || pipe(cp) < 0){
        printf("kernel pipe error!\n");
        exit(1);
    }
    int pid = fork();
    if (pid < 0){
        printf("fork error!\n");
        exit(1);
    }
    else if (pid == 0){
        close(cp[0]); 
        close(fp[1]);
        char buf;
        if (read(fp[0], &buf, 1)){
            printf("%d: received p%cng\n",getpid(), buf);
            write(cp[1], "o", 1);
        }
        close(cp[1]);
        close(fp[0]);
    }
    else{
        close(fp[0]); 
        close(cp[1]);
        char buf;
        if (write(fp[1], "i", 1)){
            read(cp[0], &buf, 1);
            printf("%d: received p%cng\n",getpid(), buf);
        }
        close(fp[1]);
        close(cp[0]);
    }
    exit(0);
}