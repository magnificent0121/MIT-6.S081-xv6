
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	if(argc!=2){
		fprintf(2,"Error! Sleep needs one argunment!\n");
		exit(1);
	}
	int SleepTime = atoi(argv[1]);// 将字符串转为整数
	printf( "nothing happens for a little while\n");
	sleep(SleepTime);
	exit(0);//正常退出
}