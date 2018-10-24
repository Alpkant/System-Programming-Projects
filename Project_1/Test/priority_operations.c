#include <stdio.h>
#include <sys/resource.h>
#include <string.h>

int which = PRIO_PROCESS;

int main( int argc, char** argv ){
	if ( argc < 2 || argc > 4 ){
		printf("%s\n", "You should give me exactly 1 command-line parameters!\n\
Program will be terminated.");
		return 0;
	}
	printf("argv[1]: %d\n", atoi(argv[1]));
	int priority = atoi(argv[1]);
	
	id_t pid = getpid();

	printf("pid: %d\n", pid);

	int nice_val = getpriority(which, pid);
	printf("First priority: %d\n", nice_val);
	getchar();

	setpriority(which, pid, priority);
	nice_val = getpriority(which, pid);
	printf("Second priority: %d\n", nice_val);

	getchar();

	
	return 0;
}