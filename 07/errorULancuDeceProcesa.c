#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int forkujSe(int pocetno){
	int i = pocetno;

	int pid = 0;
	int pisiRoditelju, citajOdDeteta;
	while(i > 1 && pid == 0){
		int fd[2];
		if(pipe(fd) == -1){
			perror("");
			_exit(1);
		}
		pid = fork();
		if(pid != 0){
			citajOdDeteta = dup(fd[0]);
		} else {
			i--;
			pisiRoditelju = dup(fd[1]);
		}
		close(fd[0]);
		close(fd[1]);
	}

	int child_status;
	wait(&child_status);
	if(WIFEXITED(child_status)){
		int exit_status = WEXITSTATUS(child_status);
		printf("Ja sam %i, moje dete je zavrsilo sa statusom %i\n", i, exit_status);
		if(exit_status != 0){
			printf("Ja sam %i, doslo je do greske sa mojim detetom...\n", i);
			_exit(exit_status);
		}
	} else {
		printf("Dete nije svojevoljno zavrsilo sa radom [jos uvek]...\n");
	}
	
	// if i == 3, _exit(1);
	if(i == 3){
		//close(pisiRoditelju);
		//close(citajOdDeteta);
		_exit(7);
	}

	printf("Ja sam nivo %i\n", i);

	int rez = 1;
	if(i == 1){
		close(citajOdDeteta);
		rez = 1;
		printf("Nivo %i, pisem roditelju %i\n", i, rez);
		write(pisiRoditelju, &rez, sizeof(int));
		close(pisiRoditelju);
	} else if(i == pocetno){
		read(citajOdDeteta, &rez, sizeof(int));
		printf("Nivo %i, procitao od deteta %i, vrazam rez %i\n", i, rez, rez*i);
		close(citajOdDeteta);
		rez *= i;
		return rez;
	} else {
		int read_status = read(citajOdDeteta, &rez, sizeof(int));
		printf("Nivo %i, read status: %i\n", i, read_status);
		close(citajOdDeteta);
		printf("Nivo %i, procitao od deteta %i, pisem roditelju %i\n", i, rez, rez*i);
		rez *= i;
		write(pisiRoditelju, &rez, sizeof(int));
		close(pisiRoditelju);
	}

	_exit(0);
}

int main(){
	printf("Start...\n");

	int rez = forkujSe(5);

	printf("Kraj... rez = %i\n", rez);
}
