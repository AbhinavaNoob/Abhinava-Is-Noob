#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

void terminal()
{
    char command[256];
    char cwd[1024];
    const char *ver = "v1.0.0";

    while (1)
    {
        getcwd(cwd, sizeof(cwd));
        printf("%s > ", basename(cwd));

        scanf(" %[^\n]", command);

        if (strcmp(command, "exit") == 0)
        {
            printf("Exiting CLI OS\n");
                for (int i = 0; i < 14; i++)
                {
                    printf(".");
                    usleep(100000);
                    fflush(stdout);
                }
                printf("\n");
            break;
        }
        else if (strcmp(command, "help") == 0)
        {
            printf("                      CLI_OS UNIX\n");
            printf(" CLI_OS is a simple command line interface operating system.\n");
            printf("Commands:\n");
            printf("help - Display help message\n");
            printf("exit - Exit CLI_OS (you may use control+C to quit)\n");
            printf("CLIver - Display the current version.\n");
            printf("cd - Change directory\n");
            printf("then basically it is your terminal command.\n");
        }
        else if (strcmp(command, "CLIver") == 0)
        {
            printf("Current version: %s\n", ver);
        }
        else if (strncmp(command, "cd ", 3) == 0)
        {
            char *path = command + 3;
            if (chdir(path) != 0)
            {
                perror("cd failed");
            }
        }
        else
        {
            system(command);
        }
    }
}
int main()
{
    system("clear");
    printf("CLI_OS UNIX isn't for windows, windows version is currently going on.\n");
    sleep(3);
    
    system("clear");
    printf("       CLI OS\n");
    printf("      booting!\n");

    for (int i = 0; i < 20; i++)
    {
        printf(".");
        usleep(100000);
        fflush(stdout);
    }
    printf("\n");
    sleep(3);
    system("clear");

    terminal();

    return 0;
}