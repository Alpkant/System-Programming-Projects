#include <stdio.h>
#include <sys/resource.h>
#include <string.h>
#define NR_setflag 355

int which = PRIO_PROCESS;

void check_if_test_successful(int flag,int nice,int fork_value){
	if(flag == 0 && fork_value == 0){
		printf("Test is successful! \n");
		return;
	}

	if(flag == 1 && nice <= 10 && fork_value == 0 ){
		printf("Test is successful! \n");
		return;
	}

	if(flag == 1 && nice > 10 && fork_value == -1 ){
		printf("Test is successful! \n");
		return;
	}	
	printf("Test is failed! \n");
	return;
}

int main( int argc, char** argv ){
	if ( argc < 2 || argc > 4 ){
		printf("%s\n", "You should give me exactly 1 command-line parameters!\n\
Program will be terminated.");
		return 0;
	}
	printf("argv[1] flag argument: %d\n", atoi(argv[1]));
	printf("argv[2] nice value argument : %d\n", atoi(argv[2]));
	int flag = atoi(argv[1]);
	int nice_val = atoi(argv[2]);
	id_t pid = getpid();
	id_t p_pid = getppid();
	setpriority(which, pid, nice_val);
	printf("Main process pid: %d ppid: %d \n", pid,p_pid);
	int systemcall_return = syscall(NR_setflag,pid,flag);

	if(systemcall_return == 0){
		printf("System call works without error.\n");
	}else{
		printf("Error is :  %s\n", strerror(systemcall_return));
		return;
	}
	getchar();	
	int fork_value = fork();
	pid = getpid();
	p_pid = getppid();
	if(fork_value == 0){ // Child process
		printf("Child process pid:%d ppid:%d\n",pid,p_pid);
		check_if_test_successful(flag,nice_val,fork_value);
		getchar();
	}else if (fork_value == -1){ // Fork error so parent process
		printf("There was a fork error %s \nParent process pid:%d ppid:%d\n",strerror(fork_value),pid,p_pid);
		check_if_test_successful(flag,nice_val,fork_value);
		getchar();
	}else{ // Parent process
		printf("Parent process pid:%d ppid:%d\n",pid,p_pid);
		getchar();
	}





	
	return 0;
}