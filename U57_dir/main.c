#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <limits.h>

const char *progName;

void errMsg(const char *operation, const char *fileName)
{
  fprintf(stderr, "%s: error %s %s: %s\n",
          progName, operation, fileName, strerror(errno));
  exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[])
{   
    progName = argv[0];
    const char *dirname = (argc == 2) ? argv[1] : ".";

    DIR *directory = opendir(dirname);
    if(directory == NULL) {
        printf("Error:opening directory: %s\n", dirname);
        exit(EXIT_FAILURE);
    }

    size_t dirnameLen = strlen(dirname);
    if(dirnameLen + 2 > PATH_MAX) {
        printf("%s: Verzeichnisname zu lang!\n", dirname);
        exit(EXIT_FAILURE);
    }
    char filename[PATH_MAX];
    strcpy(filename, dirname);
    strcat(filename, "/");
    char *nameBeg = &(filename[dirnameLen + 1]); 

    for(; ;) {
        errno = 0;
        
        struct dirent *dirp = readdir(directory);
        if(dirp == NULL) break;

        if (dirnameLen + 1 + strlen(dirp->d_name) + 1 >= PATH_MAX) {
            printf("'%s/%s' ist zu lang!\n", dirname, dirp->d_name);
            continue;  
        }

        strcpy(nameBeg, dirp->d_name);

        struct stat filestat;

        int stat_err = stat(filename, &filestat);
        if(stat_err != 0) {
            printf("Error: getting File-Information! Dir:%s", dirname);
            exit(EXIT_FAILURE);
        }

        char typ;

        if(S_ISREG(filestat.st_mode) == 1) {
            typ = 'f';
        } else if(S_ISDIR(filestat.st_mode) == 1) {
            typ = 'd';
        } else {
            typ = '?';
        }

        char *time = ctime(&filestat.st_mtime);
        *(strchr(time, '\n')) = '\0';

        printf("%10ld Bytes %c %s %s\n", filestat.st_size, typ, time, dirp->d_name);
    }
    
    if(errno != 0) {
        printf("Error: reading directory (%s)", dirname);
    }
    
    if (closedir(directory) == -1) {
        errMsg("closing directory", dirname);
    }

    exit(EXIT_SUCCESS);
}