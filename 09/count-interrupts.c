#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int c = 0;
int signaled = 0;

void interruptHandler(){
	signaled = 1;
	c++;
}

int main(){
	printf("Start...\n");

	signal(SIGINT, &interruptHandler);

	for(;;){
		if(signaled == 1){
			printf("\nPrimio ctrl+c signal %i puta.\n", c);
			if(c == 4){
				exit(0);
			}
			signaled = 0;
		}
		printf("radi...\n");
		sleep(1);
	}
	
	return 0;
}
