#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/sysmacros.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

void listDir(const char *dirname){
  printf("\n=== %s ===\n", dirname);	
  DIR *dir = opendir(dirname);
  if(dir == NULL){
    perror("");
    return;
  }

  int res;
  struct dirent *entry = readdir(dir);
  printf("Permissions, hard links, byte size, access time, filename\n");
  while(entry != NULL){
    struct stat stats;
    
    char *filepath = malloc(sizeof(char) * 100);
    filepath = strcpy(filepath, dirname);    
    strcat(filepath, "/");
    strcat(filepath, entry->d_name);
    if (lstat(filepath, &stats) == -1) {
      perror("lstat");
      exit(EXIT_FAILURE);
    }
    switch(stats.st_mode & S_IFMT) {
      case S_IFDIR:  printf("d");              break; 
      case S_IFLNK:  printf("l");		break;
      case S_IFREG:  printf("-");		break;
      default:       printf("?");		break;
    }
    
    //printf("%o ", (stats.st_mode / 8) % 8) ;
        
    printf("%c", (stats.st_mode & S_IRUSR)? 'r':'-');    
    printf("%c", (stats.st_mode & S_IWUSR)? 'w':'-');    
    printf("%c", (stats.st_mode & S_IXUSR)? 'x':'-');    
    
    printf("%c", (stats.st_mode & S_IRGRP)? 'r':'-');    
    printf("%c", (stats.st_mode & S_IWGRP)? 'w':'-');    
    printf("%c", (stats.st_mode & S_IXGRP)? 'x':'-');    
    
    printf("%c", (stats.st_mode & S_IROTH)? 'r':'-');    
    printf("%c", (stats.st_mode & S_IWOTH)? 'w':'-');    
    printf("%c", (stats.st_mode & S_IXOTH)? 'x':'-');    
    
    printf(" %ju ", (uintmax_t) stats.st_nlink);

    printf("%8jd ", (intmax_t) stats.st_size);

    // struct tm *lcltime = localtime(stats.st_atim.tv_sec);
    // printf("%i-%i-%i %i:%i ", lcltime->tm_year+1900, 1, 1, 1, 1);
    char *timestring = ctime(&stats.st_atime);
    timestring[strlen(timestring) - 2] = '\0';
    printf("%s ", timestring);

    printf("%s\n", entry->d_name);

    entry = readdir(dir); 
  }

  res = closedir(dir);
  if(res == 1){
    perror("");
  }
}

int main(int argc, char *argv[]){
  printf("Helou\n\n");

  if(argc < 2){
    printf("Excpected at least 1 argument...\n");
  } else {
    for(int i = 1; i < argc; i++){
      listDir(argv[i]);
    }
  }

  return 0;
}
