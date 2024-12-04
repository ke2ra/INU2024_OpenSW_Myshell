#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ls_command.h"
#include "cat_command.h"

#define MAX_LINE 80 /* The maximum length command (terminal's default size)*/

int main()
{
    while (1)
    {
        // prompt
        printf("myshell> ");
        {
            // read command
            char *args[MAX_LINE / 2 + 1]; /* command line arguments */
            char input[MAX_LINE];
            fgets(input, MAX_LINE, stdin); // char *fgets(char *str, int n, FILE *stream);
            printf("input: %s\n", input);
            input[strlen(input) - 1] = '\0'; // remove newline character
            char *token = strtok(input, " \n\t"); // parsing the input string
            printf("token %s\n", token);
            int i = 0;

            while (token != NULL)
            {
                args[i++] = token;
                token = strtok(NULL, " \n\t");
                printf("token %s\n", token);
            }
            args[i] = NULL;

            if (i == 0)
            {
                continue;
            }
            // exit command
            if (strcmp(args[0], "exit") == 0)
            {
                printf("Goodbye~\n");
                exit(0);
            }
            else if (strcmp(args[0], "cd") == 0)
            {
                chdir(args[1]);
            }
            else if (strcmp(args[0], "pwd") == 0)
            {
                getcwd(input, MAX_LINE);
                printf("Current working dir: %s\n", input);
            }
            else if (strcmp(args[0], "ls") == 0)
            {
                my_ls();
            }
            else if (strcmp(args[0], "cat") == 0)
            {
                if (i != 2)
                {
                    fprintf(stderr, "Usage: cat <file>\n");
                    continue;
                }
                cat_file(args[1]);
            }
            else
            {
                if (access(args[0], X_OK) == 0)
                {
                    pid_t pid = fork();

                    if (pid < 0)
                    {
                        // fork 실패
                        perror("fork failed");
                    }
                    else if (pid == 0)
                    {
                        // 자식 프로세스에서 명령어 실행
                        if (execvp(args[0], args) == -1)
                        {
                            // 명령어 실행 실패
                            perror("exec failed");
                            exit(EXIT_FAILURE);
                        }
                    }
                    else
                    {
                        // 부모 프로세스에서 자식 프로세스 대기
                        int status;
                        waitpid(pid, &status, 0);
                    }
                }
                else
                {
                    // 명령어가 존재하지 않거나 실행 불가한 경우
                    printf("Command not found: %s\n", args[0]);
                }
            }
        }
    }
}
