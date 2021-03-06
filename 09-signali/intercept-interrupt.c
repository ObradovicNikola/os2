#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void ctrap(int sig)
{
    puts("Ctrl-C intercepted!");
    //getchar();
    /* restore the default */
    (void)signal(SIGINT, SIG_DFL);
}

int main()
{
    char a = 0;

    /* intercept Ctrl+C */
    (void)signal(SIGINT, ctrap);

    for (;;)
    {
        printf("%d\n", a);
	sleep(1);
        a++;
    }

    return (0);
}
