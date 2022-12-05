#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    char buf[32];
    int n;
    char* args[MAXARG];
    int numArg;
    for (int i = 1; i < argc; i++)
        args[i - 1] = argv[i];
    numArg = argc - 1;
    char* p = buf;
    //从标准输入中读取
    while ((n = read(0, p, 1)) > 0){
        if (*p == '\n'){
            *p = 0;
            int pid = fork();
            if (pid < 0){
                printf("fork err\n");
                exit(1);
            }
            else if (pid == 0){
                args[numArg] = buf;
                exec(args[0], args);
                exit(0);
            }
            else wait(0);
            //重新将指针移回到数组头部
            p = buf;
        }
        else p++;
    }
    exit(0);
}