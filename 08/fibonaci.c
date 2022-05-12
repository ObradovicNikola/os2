#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define POTREBNO_DECE 2

int fibonaci(int pocetno){
	if(pocetno == 0) return 0;
	if(pocetno == 1) return 1;
	
	int maxdubina = pocetno;
	int i = pocetno; // dubina
	int brdece = 0;
	int pisiDetetu, citajOdDeteta;
	int pisiRoditelju, citajOdRoditelja;


	int fd[2];
	int fd2[2];
	while(i > 1 && brdece < POTREBNO_DECE){
		if(brdece == 0){
			if(pipe(fd) == -1){
				perror("");
				exit(1);
				// sta ako se zapravo desi error,
				// onda ce se ugasiti samo child proces npr.
			}
			if(pipe(fd2) == -1){
				perror("");
				exit(1);
			}
		}
		int pid = fork();
		if(pid != 0){
			//printf("Racunam f(%i)...\n", i);
			if(brdece == 0) {
				citajOdDeteta = dup(fd[0]);
				pisiDetetu = dup(fd2[1]);
			}
			brdece++;
		} else {
			i--;
			brdece = 0;
			//printf("dete, dubina %i\n", i);
			pisiRoditelju = dup(fd[1]);
			citajOdRoditelja = dup(fd2[0]);
		}
		if(pid == 0 && brdece > 1){
			close(fd[0]);
			close(fd[1]);
			close(fd2[0]);
			close(fd2[1]);
		}
	}

	//printf("%i\n", i);
	
	if (i == 1){
		//printf("I'm bottom process.\n");
		int task = 0;
		int rez = 0;
		read(citajOdRoditelja, &task, sizeof(int));
		printf("Nivo %i, taking task %i\n", i, task);
		if(task == 1) rez = 1;
		else rez = 0;
		
		printf("nivo - %i, zadatak %i, vracam rez %i\n", i, task, rez);
		write(pisiRoditelju, &rez, sizeof(int));
	} else if(i == pocetno){
		//printf("I'm top process.\n");
		int rez = 999;
		int task = i-1;
		printf("Nivo %i, adding task %i and %i\n", i, task, task-1);
		write(pisiDetetu, &task, sizeof(int));
		task--;
		//printf("Adding task %i\n", task);
		write(pisiDetetu, &task, sizeof(int));

		int rez2 = 0;
		read(citajOdDeteta, &rez, sizeof(int));
		read(citajOdDeteta, &rez2, sizeof(int));
		printf("Nivo - %i, uzimam rezultate %i i %i\n", i, rez, rez2);
		rez += rez2;

		close(pisiDetetu);
		close(citajOdDeteta);
		close(pisiRoditelju);
		close(citajOdRoditelja);
		return rez;
	} else {
		int task = 0;
		read(citajOdRoditelja, &task, sizeof(int));
		//printf("Taking task %i\n", task);
		int tmp = task;

		tmp--;
		write(pisiDetetu, &tmp, sizeof(int));
		tmp--;
		write(pisiDetetu, &tmp, sizeof(int));

		while(wait(NULL) != -1){}
		int rez1 = 0, rez2 = 0;
		read(citajOdDeteta, &rez1, sizeof(int));
		read(citajOdDeteta, &rez2, sizeof(int));
		printf("nivo - %i, zadatak %i, uzimam od deteta %i i %i\n", i, task, rez1, rez2);
		rez1 = rez1+rez2;
		if(task==1) rez1 = 1;
		write(pisiRoditelju, &rez1, sizeof(int));
	}
	
	close(pisiDetetu);
	close(citajOdDeteta);
	close(pisiRoditelju);
	close(citajOdRoditelja);
	
	while(wait(NULL) != -1){}
	_exit(0);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Excpected 1 argument - fibonaci\n");
		return 1;
	}

	int x = atoi(argv[1]);
	if(x == 0){
		printf("Error converting to int...\n");
	}

	int rez = fibonaci(x);
	printf("rez = %i\n", rez);

	return 0;	
}
