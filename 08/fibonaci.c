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


	while(i > 1 && brdece < POTREBNO_DECE){
		int fd[2];
		int fd2[2];
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
		close(fd[0]);
		close(fd[1]);
		close(fd2[0]);
		close(fd2[1]);
	}

	printf("%i\n", i);
	
	if (i == 1){
		printf("I'm bottom process.\n");
		int task = 0;
		int rez = 0;
		read(citajOdRoditelja, &task, sizeof(int));
		if(task == 1) rez = 1;
		else rez = 0;
		
		write(pisiRoditelju, &rez, sizeof(int));
	} else if(i == pocetno){
		printf("I'm top process.\n");
		int rez = 999;
		int task = i-1;
		printf("Adding task %i\n", task);
		write(pisiDetetu, &task, sizeof(int));
		task--;
		printf("Adding task %i\n", task);
		write(pisiDetetu, &task, sizeof(int));

		//while(wait(NULL) != -1){}
		int rez2 = 0;
		read(citajOdDeteta, &rez, sizeof(int));
		read(citajOdDeteta, &rez2, sizeof(int));
		rez += rez2;

		close(pisiDetetu);
		close(citajOdDeteta);
		close(pisiRoditelju);
		close(citajOdRoditelja);
		return rez;
	} else {
		int task = 0;
		read(citajOdRoditelja, &task, sizeof(int));
		printf("Taking task %i\n", task);

		task--;
		write(pisiDetetu, &task, sizeof(int));
		task--;
		write(pisiDetetu, &task, sizeof(int));

		int rez1 = 0, rez2 = 0;
		read(citajOdDeteta, &rez1, sizeof(int));
		read(citajOdDeteta, &rez2, sizeof(int));
		task = rez1+rez2;
		write(pisiRoditelju, &task, sizeof(int));
	}
	
	close(pisiDetetu);
	close(citajOdDeteta);
	close(pisiRoditelju);
	close(citajOdRoditelja);
	
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
