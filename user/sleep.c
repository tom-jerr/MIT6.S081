#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]){
    if (argc < 2){
        printf("There are too few params!\n");
        exit(1);    //系统级调用；0为正常退出，其余均为异常退出
    }
    else if (argc > 2){
        printf("There are too many params!\n");
        exit(1);
    }
    else{
        if (sleep(atoi(argv[1])) < 0){     //atoi将字符转化为int类型
            printf("Kernel sleep error!\n");
            exit(1);
        }
    }
    exit(0);
}