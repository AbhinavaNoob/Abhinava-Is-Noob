#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <string.h> // For usleep

void displayBootSequence(void) {
    const char *steps[] = {
        "[DONE] Initializing hardware components",
        "[DONE] Scanning for storage devices",
        "[DONE] Loading kernel modules",
        "[DONE] Checking disk integrity",
        "[DONE] Verifying file system",
        "[DONE] Mounting root filesystem",
        "[DONE] Starting network manager",
        "[DONE] Configuring network interfaces",
        "[DONE] Starting process scheduler",
        "[DONE] Initializing subsystems",
        "[DONE] Loading user environment",
        "[DONE] Setting up display manager"
    };

    int num_steps = sizeof(steps) / sizeof(steps[0]);
    for (int i = 0; i < num_steps; i++) {
        printf("%s\n", steps[i]);
        usleep(500000);  // 500 milliseconds delay
    }
    printf("\nBoot sequence complete. Starting OS...\n");
    usleep(2000000);  // 2 seconds delay
}

void OS(void) {
    char cwd[1024];
    char *user = getenv("USER");
    char hostname[1024];

    // Clear the screen for UNIX
    system("clear");

    printf("Type \"help\" to get all the commands\n");

    char input[57];

    // Get current working directory
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        // Get the hostname
        if (gethostname(hostname, sizeof(hostname)) == 0) {
            char *dir_name = strrchr(cwd, '/');
            dir_name = (dir_name != NULL) ? dir_name + 1 : cwd;
        } else {
            perror("gethostname() error");
        }
    } else {
        perror("getcwd() error");
    }

    while (1) {
        char *dir_name = strrchr(cwd, '/');
        dir_name = (dir_name != NULL) ? dir_name + 1 : cwd;

        printf("\n%s: ", dir_name);
        scanf("%56s", input);  // Prevent buffer overflow

        if (strcmp(input, "ls") == 0 || strcmp(input, "mkdir") == 0 || strcmp(input, "help") == 0 || 
            strcmp(input, "clear") == 0 || strcmp(input, "exit") == 0 || strcmp(input, "echo") == 0 || 
            strcmp(input, "cd") == 0) {
            
            if (strcmp(input, "ls") == 0) {
                system("ls");
            }
            if (strcmp(input, "mkdir") == 0) {
                char dirname[50];
                printf("");
                scanf("%49s", dirname);
                char cmd[60];
                snprintf(cmd, sizeof(cmd), "mkdir %s", dirname);
                system(cmd);
            }
            if (strcmp(input, "help") == 0) {
                printf("\nCommands:\n");
                printf("mkdir <dirname>: Create a directory\n");
                printf("ls: List directories/files\n");
                printf("clear: Clear the terminal screen\n");
                printf("exit: Exit the shell\n");
                printf("echo <text>: Echoes the input text\n");
            }
            if (strcmp(input, "clear") == 0) {
                system("clear");  // For UNIX
            }
            if (strcmp(input, "exit") == 0) {
                break;
            }
            if (strcmp(input, "echo") == 0) {
                char echo[50];
                printf("");
                scanf("%49s", echo);
                char cmd[60];
                snprintf(cmd, sizeof(cmd), "echo %s", echo);
                system(cmd);
            }
            if (strcmp(input, "cd") == 0) {
                char dir[50];
                printf("");
                scanf("%49s", dir);
                if (chdir(dir) == 0) {
                    if (getcwd(cwd, sizeof(cwd)) != NULL) {
                        printf("Directory changed to %s\n", cwd);
                    } else {
                        perror("Error getting current working directory");
                    }
                } else {
                    perror("Error changing directory");
                }
            }
        } else {
            printf("OS: command not found\n");
        }
    }
}

int main() {
    system("clear");
    printf("Booting into OS...\n\n");

    displayBootSequence();  // Show the boot sequence

    system("clear");
    printf(
        " ██████╗   ██████╗ ███████╗\n"
        "██╔════╝  ██╔═══██╗██╔════╝\n"
        "██║       ██║   ██║███████╗\n"
        "██║       ██║   ██║╚════██║\n"
        "╚██████╗  ╚██████╔╝███████║\n"
        "╚═════╝    ╚═════╝ ╚══════╝\n    An OS made in C\n\n");

        sleep(2);

    OS();

    return 0;
}