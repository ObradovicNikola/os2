#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int stanjeDeteta = 0;

void handleSignal(int sig){
	if (sig == SIGUSR1){
		stanjeDeteta = 1;
	} else if(sig == SIGUSR2){
		stanjeDeteta = 0;
	}else if(sig == SIGINT){
		_exit(0);
	}
}

int main(){
	printf("Start...\n");

	int pid = fork();

	if(pid == 0){
		signal(SIGUSR1, &handleSignal);
		signal(SIGUSR2, &handleSignal);
		signal(SIGINT, &handleSignal);
		
		while(1){
			printf("Dete ");
			if(stanjeDeteta == 0){
				printf("spava\n");
			} else {
				printf("radi\n");
			}
			//usleep(200000);
			sleep(1);
		}
	} else {
		signal(SIGCHLD, SIG_IGN);

		sleep(1);
		kill(pid, SIGUSR1);

		sleep(3);
		kill(pid, SIGUSR2);

		sleep(2);
		kill(pid, SIGINT);

		while(wait(NULL) != -1){}

		printf("Roditelj zavrsava...\n");
	}

	return 0;
}
