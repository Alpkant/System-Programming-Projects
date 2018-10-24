#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#define NR_setflag 355

long sys_caller( int flag ){
	pid_t current_pid = getpid();
	printf("%d\n", current_pid );
	return syscall(NR_setflag,current_pid,flag);
}



int main(int argc, char** argv){
	long return_value = -5;
	int flag = atoi(argv[1]);
	printf("AHA FLAG %d\n",flag);
	return_value = sys_caller(flag);

	if(return_value == 0){
		printf("System call works without error.\n");
	}else{
		printf("There is error with error value %ld\n", return_value);
	}

	return 0;
}