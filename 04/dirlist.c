#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

typedef struct
{
	short sorted;
	char *dirs[50];
	int dir_count;
	int starting_with_count;
	char starting_chars[50];
} options;

void dirlist(char *dirname, options opt)
{
	struct dirent **namelist;
	int n;
	if(opt.sorted == 1){
		n = scandir(dirname, &namelist, NULL, alphasort);
	} else {
		n = scandir(dirname, &namelist, NULL, NULL);
	}
	if (n == -1)
	{
		perror("scandir");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++)
	{
		if(opt.starting_with_count > 0){
			int ok = 0;
			int j = 0;
			while(!ok && j < opt.starting_with_count){
				if(namelist[i]->d_name[0] == opt.starting_chars[j]){
					ok = 1;
				}
				j++;
			}
			if(ok){
				printf("%s\n", namelist[i]->d_name);
			}
		} else {
			printf("%s\n", namelist[i]->d_name);
		}
	}

	while (n--)
	{
		free(namelist[n]);
	}
	free(namelist);
}

int main(int argc, char *argv[])
{
	printf("Helou\n");

	// options opt = malloc(sizeof(options));
	options opt;
	opt.sorted = 0;
	opt.dir_count = 0;
	opt.starting_with_count = 0;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "--sort") == 0)
		{
			opt.sorted = 1;
		}
		else if (strncmp(argv[i], "--S", 3) == 0){
			int j = 3;
			char c = argv[i][j];
			
			while(c != '\0'){
				opt.starting_chars[opt.starting_with_count] = c;
				opt.starting_with_count++;
				j++;
				c = argv[i][j];	
			}
		}
		else
		{
			opt.dirs[opt.dir_count] = argv[i];
			opt.dir_count++;
		}
	}

	for (int i = 0; i < opt.dir_count; i++)
	{
		printf("listing --> %s\n", opt.dirs[i]);
		dirlist(opt.dirs[i], opt);
	}
}
