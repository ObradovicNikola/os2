#include <stdio.h>

int main(int argc, char *argv[]){
	printf("Hello C\n");
	for(int i = 0; i < argc; i++){
		printf("arg %i: %s\n", i, argv[i]);
	}
	return 0;
}
