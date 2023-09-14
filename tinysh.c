#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to implement the setenv command
int my_setenv(const char *variable, const char *value, int overwrite) {
    if (variable == NULL || value == NULL) {
        fprintf(stderr, "setenv: Invalid arguments\n");
        return -1; // Failure
    }

    // Use the setenv function to set or modify the environment variable
    if (setenv(variable, value, overwrite) != 0) {
        perror("setenv");
        return -1; // Failure
    }

    return 0; // Success
}

// Function to implement the unsetenv command
int my_unsetenv(const char *variable) {
    if (variable == NULL) {
        fprintf(stderr, "unsetenv: Invalid argument\n");
        return -1; // Failure
    }

    // Use the unsetenv function to remove the environment variable
    if (unsetenv(variable) != 0) {
        perror("unsetenv");
        return -1; // Failure
    }

    return 0; // Success
}

int main(int argc, char *argv[]) {
    if (argc == 3 && strcmp(argv[1], "setenv") == 0) {
        return my_setenv(argv[2], argv[3], 1);
    } else if (argc == 2 && strcmp(argv[1], "unsetenv") == 0) {
        return my_unsetenv(argv[2]);
    } else {
        fprintf(stderr, "Usage: %s [setenv VARIABLE VALUE | unsetenv VARIABLE]\n", argv[0]);
        return -1; // Failure
    }
}
