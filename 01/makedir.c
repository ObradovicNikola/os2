#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(){
	printf("Hello world!\n");
	
	int res = mkdir("os2", 0755);
	if (res == -1){
	   //error
	   int errsv = errno;
           printf("mkdir() failed\n");
           // if (errsv == ...) { ... }
	   perror("");
	} else {
	  printf("Dir os2 created successfully.\n");
	}
	
	return 0;
}
