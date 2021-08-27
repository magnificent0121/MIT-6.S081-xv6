#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int i,j,pid,len;
    int first_blank;
    char args[MAXARG][32];
    char *p[MAXARG];
    char buf;

    if(argc<2){
        fprintf(2,"too few parameters!\n");
        exit(0);
    }
    while(1){
        i=0;
        first_blank=0;
        memset(args,0,MAXARG*32);

        for(j=1;j<argc;j++){
            strcpy(args[i++],argv[j]);
        }
        j=0;
        while(i<MAXARG-1){
            if((len=read(0,&buf,1))<=0){
                wait(0);
                exit(0);
            }
            if(buf=='\n'){
                break;
            }
            else if(buf==' '){
                if(first_blank){
                    i++;
                    j=0;
                    first_blank=0;
                }
                continue;
            }
            args[i][j++]=buf;
            first_blank=1;
        }
        for(i=0;i<MAXARG-1;i++){
            p[i]=args[i];
        }
        p[MAXARG-1]=0;
        if((pid=fork())==0){
            exec(argv[1],p);
            exit(0);
        }
    }
    exit(0);
}