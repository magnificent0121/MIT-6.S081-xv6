#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    int fd1[2];
    int fd2[2];
    char Buffer[1]={' '};
       //char Buffer[1];
    int t1=pipe(fd1);
    int t2=pipe(fd2);
    if (t1==-1||t2==-1){
        fprintf(2,"Pipe Create Failed!\n");
        exit(1);
    }
    int pid=fork();
    if(pid<0){
        fprintf(2,"Fork Failed!\n");
        exit(1);
    }
    if(pid>0){//父进程
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1],Buffer,sizeof(Buffer));
        read(fd2[0],Buffer,sizeof(Buffer));
        printf("%d: received pong\n",getpid());
        close(fd1[1]);
        close(fd2[0]);
        wait(0);//等待子进程结束
        exit(0);
    }
    else{
        close(fd1[1]);
        close(fd2[0]);
        read(fd1[0],Buffer,sizeof(Buffer));
        write(fd2[1],Buffer,sizeof(Buffer));
        printf("%d: received ping\n",getpid());
        close(fd1[0]);
        close(fd2[1]);
        exit(0);
    }
}