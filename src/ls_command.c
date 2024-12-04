#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    char path[1035];
    char command[50];

    // Use current directory if no directory is specified
    const char *dir = (argc > 1) ? argv[1] : ".";

    // Create the command to list directory contents
    snprintf(command, sizeof(command), "ls %s", dir);

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        perror("popen");
        return EXIT_FAILURE;
    }

    // Read the output a line at a time and print it
    while (fgets(path, sizeof(path), fp) != NULL) {
        printf("%s", path);
    }

    // Close the command
    pclose(fp);

    return EXIT_SUCCESS;
}