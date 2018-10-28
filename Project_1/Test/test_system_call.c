#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#define NR_setflag 355

long sys_caller( int flag ){
	pid_t current_pid = getpid();
	printf("%d\n", current_pid );
	return syscall(NR_setflag,current_pid,flag);
}



int main(int argc, char** argv){
	if ( argc < 2 || argc > 3 ){
		printf("%s\n", "You should give me exactly 1 command-line parameters!\n\
	Program will be terminated.");
			return 0;
	}
	long return_value = -5;
	int flag = atoi(argv[1]);
	return_value = sys_caller(flag);

	if(return_value == 0){
		printf("System call works without error.\n");
	}else{
		printf("There is error with error value %s\n", strerror(errno));
	}

	return 0;
}