#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("Hello world!\n");
	
	if(argc < 3){
	  printf("Excpecting 2 arguments...\n");
	  printf("Usage: mksub parrentFolder childFolder\n");
	  return 1;
	}

	int res = mkdir(argv[1], 0755);
	if (res == -1){
	   //error
           printf("mkdir() failed\n");
	   perror("");
	   return 1;
	} else {
	  printf("Dir %s created successfully.\n", argv[1]);
	}
	
	
	res = chdir(argv[1]);
	if (res == -1){
	   //error
           printf("chdir() failed\n");
	   perror("");
	   return 1;
	} else {
	  printf("Dir changed successfully.\n");
	}

	res = mkdir(argv[2], 0755);
	if (res == -1){
	   //error
           printf("mkdir() failed\n");
	   perror("");
	} else {
	  printf("Dir %s/%s created successfully.\n", argv[1], argv[2]);
	}
	
	return 0;
}
