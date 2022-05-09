#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    printf("sadrzaj trenutnog direktorijuma:\n");

    int n = fork();
    if (n == 0){
    	execl("/bin/ls", "/bin/ls", "-g", "-G", NULL);
	fflush(stdout);
    }
    wait(NULL);

    printf("kraj ispisa\n");

    return 0;
}
