#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

void my_ls(void) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    } else {
        while ((entry = readdir(dir)) != NULL) {
            struct stat statbuf;
            // 파일의 정보를 가져와서 저장합니다.
            if (stat(entry->d_name, &statbuf) == 0) {
                // 디렉토리인지 확인합니다.
                if (S_ISDIR(statbuf.st_mode)) {
                    printf("%s/\n", entry->d_name);
                } else {
                    printf("%s\n", entry->d_name);
                }
            } else {
                perror("stat");
            }
        }
        closedir(dir);
    }
}
