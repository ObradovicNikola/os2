#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

typedef struct Options{
  int showHidden;
  int showRecursive;
} options;

void printDirContents(char *dirname, const options *opt, const char *curr_dir){
  DIR *dir = opendir(dirname);
  if(dir == NULL){
    printf("Failed to open %s dir...\n", dirname);
    perror("");
    return;
  }
  struct dirent *dirdata = readdir(dir);
  while(dirdata != NULL){
    // hide hidden files by default
    if(opt->showHidden == 1 || dirdata->d_name[0] != '.'){
      if(strcmp(dirdata->d_name, ".") != 0 && strcmp(dirdata->d_name, "..") != 0){
        if(dirdata->d_type == DT_DIR){
          printf("d");
        } else if(dirdata->d_type == DT_REG){
          printf("f");
        } else printf("?");
	struct stat *stats = malloc(sizeof(struct stat));
	char *pathname = malloc(sizeof(char) * 100);
	strcpy(pathname, curr_dir);
	strcat(pathname, "/");
	strcat(pathname, dirdata->d_name);
	int res = stat(pathname, stats);
	printf(" %ju", (uintmax_t)stats->st_nlink);
        printf(" %s\n", dirdata->d_name);
      
        if(opt->showRecursive && dirdata->d_type == DT_DIR){
          printDirContents(dirdata->d_name, opt, pathname);
        }
      }
    }
    dirdata = readdir(dir);
  }
  closedir(dir);
}

int main(int argc, char *argv[]){
  printf("Hello 02\n");
  
  options *opt = malloc(sizeof(options));
  opt->showHidden = 0;
  opt->showRecursive = 0;
  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-r") == 0){
      opt->showRecursive = 1;
    }
    
    else if(strcmp(argv[i], "-a") == 0){
      opt->showHidden = 1;
    }
  }

  for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "-r") != 0 && strcmp(argv[i], "-a") != 0){
      printDirContents(argv[i], opt, argv[i]);
    }
  }

  return 0;
}
