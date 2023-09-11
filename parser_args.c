#include "shell.h"

void parser(char *std_input, char **argv, int *argc)
{
        char *token = strtok(std_input, " ");
        int max_args = 10;  // Maximum number of arguments
        int arg_index = 0;  // Index for argv

        if (token == NULL) {
                // No input, nothing to return
                return;
        }

        // Dynamically allocate memory for argv
        argv[arg_index] = _strdup(token);
        arg_index++;
        (*argc)++;

        while (token != NULL && *argc < max_args) {
                token = strtok(NULL, " ");
                if (token != NULL) {
                        // Dynamically allocate memory for the next argument
                        argv[arg_index] = _strdup(token);
                        arg_index++;
                        (*argc)++;
                }
        }

        argv[arg_index] = NULL; // Null-terminate args
}

