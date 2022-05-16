#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
	
	printf("Starting...\n");
	
	signal(SIGINT, SIG_IGN);

	sleep(4);

	return 0;
}
