#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

const char *progName;

void errMsg(const char *operation, const char *fileName)
{
  fprintf(stderr, "%s: error %s %s: %s\n",
          progName, operation, fileName, strerror(errno));
  exit(EXIT_FAILURE);
}

int main(int argc, const char *argv[])
{
    if (argc > 1) {
        fprintf(stderr, "Aufruf: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char dirname[] = ".";

    DIR *directory = opendir(dirname);

    if(directory == NULL) {
        printf("Error:opening directory: %s\n", dirname);
        exit(EXIT_FAILURE);
    }

    for(; ;) {
        errno = 0;

        struct dirent *dirp = readdir(directory);
        if(dirp == NULL) break;

        struct stat filestat;

        int stat_err = stat(dirp->d_name, &filestat);
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

        printf("%ld Bytes %s %s %s\n", filestat.st_size, typ, time, dirp->d_name);
    }

    if(errno != 0) {
        printf("Error: reading directory (%s)", dirname);
    }

    if (closedir(directory) == -1) {
        errMsg("closing directory", dirname);
    }

    exit(EXIT_SUCCESS);
}
