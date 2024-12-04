// myshell program
/*
    Files & directories commands
    - ls
    - cd use : chdir()
    - pwd use : getcwd()
    - cat
*/

// execution of a program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#define MAX_LINE 80 /* The maximum length command (terminal's default size)*/

int main()
{

    while(1) {

        //prompt
        printf("myshell> ");
        {
            //read command
            char *args[MAX_LINE/2 + 1]; /* command line arguments */
            char input[MAX_LINE]; 
            fgets(input, MAX_LINE, stdin); // char *fgets(char *str, int n, FILE *stream);
            printf("input: %s\n", input);
            input[strlen(input) - 1] = '\0'; // remove newline character
            char *token = strtok(input, " \n\t"); //parsing the input string
            printf("token %s\n", token);
            int i = 0;

           
            while (token != NULL) {
                args[i++] = token;
                token = strtok(NULL, " \n\t");
                printf("token %s\n", token);
            }
            args[i] = NULL;

            if (i == 0) {
                continue;
            }
            //exit command
            if (strcmp(args[0], "exit") == 0) {
                printf("Goodbye~\n");
                exit(0);
            }
            else if (strcmp(args[0], "cd") == 0) {
                chdir(args[1]);
            }
            else if (strcmp(args[0], "pwd") == 0) {
                getcwd(input, MAX_LINE);
                printf("Current working dir: %s\n", input);
            }
                
                
            // //cat command from cat_command.c
            // if (strcmp(args[0], "cat") == 0) {
            //     if (i < 2) {
            //         fprintf(stderr, "Usage: cat <file1> [file2 ...]\n");
            //         continue;
            //     }
            //     for (int j = 1; j < i; j++) {
            //         cat_file(args[j]);
            //     }
            // }

            // //ls command from ls_command.c
            // else if (strcmp(args[0], "ls") == 0) {
            //     FILE *fp;
            //     char path[1035];
            //     char command[50];
            //     const char *dir = (i > 1) ? args[1] : ".";
            //     snprintf(command, sizeof(command), "ls %s", dir);
            //     fp = popen(command, "r");
            //     if (fp == NULL) {
            //         perror("popen");
            //         return EXIT_FAILURE;
            //     }
            //     while (fgets(path, sizeof(path), fp) != NULL) {
            //         printf("%s", path);
            //     }
            //     pclose(fp);
            // }
            
            // //execute command from exec_command.c
            // else {
            //     args[i] = NULL;
            //     exec_command(args[0], args);
            // }
        }
    }
}