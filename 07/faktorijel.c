#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int racunaj(int pocetno){
	int pid = 0;
	int i = pocetno;
	int ulaz, izlaz;
	printf("%i\n", i);

	while(pid == 0 && i > 1){
		int fd[2];
		if (pipe(fd) == -1){
			perror("");
		}
		pid = fork();
		if (pid != 0){
			ulaz = dup(fd[0]);
		} else {
			izlaz = dup(fd[1]);
			i--;
			printf("%i\n", i);
		}
		close(fd[0]);
		close(fd[1]);
	}

	// sacekaj svu decu
	// da ne bi ostao ziv neki zombi proces
	while(wait(NULL) != -1){
	}
	//printf("%i\n", i);

	if(i == 1){
		close(ulaz);
		printf("Ja sam %i, zapocinjem pisanje..\n", i);
		write(izlaz, &i, sizeof(int));
		close(izlaz);
	} else if(i == pocetno){
		close(izlaz);
		int r = 0;
		read(ulaz, &r, sizeof(int));
		close(ulaz);
		printf("Ja sam %i, procitao sam %i\n", i, r);
		printf("Glavni proces vraca vrednost...\n");
		return r*i;
	} else {
		int tmp = 1;
		read(ulaz, &tmp, sizeof(int));
		close(ulaz);
		printf("Ja sam %i, procitao sam %i\n", i, tmp);
		tmp *= i;
		write(izlaz, &tmp, sizeof(int));
		close(izlaz);
	}
	// ako nije glavna nit,
	// ne vracaj se u glavni program...
	_exit(0);
}

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Expected 1 argument - faktoriel\n");
		exit(-1);
	}
	int x = atoi(argv[1]);
	if(x == 0){
		printf("Error converting to int...\n");
		exit(-1);
	}
	int rez = racunaj(x);
	printf("rez: %i\n", rez);
	return 0;
}
