#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

void faktorijel(int initial){
	int n = initial;
	bool wantChild = true;

	while(n > 1 && wantChild){
		int pid = fork();
		if (pid == -1){
			perror("");
			exit(-1);
		}
		if (pid > 0){
			wantChild = false;
		} else {
			n--;
		}
	}
	printf("%d ", n);
}

int main(){
	unsigned int n = 0;
	printf("Unesite neki pozitivan broj: ");
	scanf("%u", &n);
	if(n == 0 || n == 1){
		printf("Faktorijel je 1\n");
	} else {
		faktorijel(n);	
	
	}
	while(wait(NULL) != -1){
	}

	printf("Kraj...\n");
	return 0;
}
