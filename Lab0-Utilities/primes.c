#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
void primes(){
    int n;
    int p;
    int fd[2];
    int len;
    if((len=read(0,&n,sizeof(int)))<=0||n<=0){
        close(1);
        exit(0);
    }
    printf("prime %d\n",n);
    pipe(fd);
    int pid=fork();
    if(pid>0){
        close(0);
        dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        primes();
    }
    else{
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        while((len=read(0,&p,sizeof(int)))>0&&p>0){
            if(p%n!=0){
                write(1,&p,sizeof(int));
            }
        }
        if(len<=0||p<=0){
            close(1);
            exit(0);
        }
    }      
} 
int main(){
     int fd[2];
     int i;
     pipe(fd);
     int pid=fork();
     if(pid>0){
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);
        for(i=2;i<=35;i++){
            write(1,&i,sizeof(int));
        }
	close(1);
        wait(0);
    }
    else{
        close(0);
        dup(fd[0]);
        close(fd[1]);
        close(fd[0]);
        primes();
    }
    exit(0);
}