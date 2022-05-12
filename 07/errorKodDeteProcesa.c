#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int forkujSe(){
	int pid = fork();

	if(pid == 0){
		printf("Poruka od deteta.\n");
	} else {
		int child_status;
		wait(&child_status);
		if(WIFEXITED(child_status)){
			int exit_status = WEXITSTATUS(child_status);
			printf("Status deteta: %i\n", exit_status);
			if(exit_status != 0){
				printf("Doslo je do greske kod deteta...\n");
				exit(exit_status);
			}
		} else {
			printf("Dete nije svojevoljno zavrsilo sa radom [jos uvek]...\n");
		}
		printf("Poruka od roditelja.\n");
		return 1;
	}

	// ovde podesavamo exit status deteta
	_exit(1);
}

int main(){
	printf("Start...\n");
	int rez = forkujSe();
	printf("Gotov... rez = %i\n", rez);

	return 0;
}
