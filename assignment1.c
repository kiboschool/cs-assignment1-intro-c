#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Declare each of the functions we will be using
bool matchPatternX(const char *arg);
bool matchPatternY(const char *arg);
bool matchPatternZ(const char *arg);

// Entry point into the program.
int main(int argc, char *argv[]) {
    char mode = 'x'; // Default mode
    bool variantOutput = false;

    // Argument parsing
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-v") == 0) {
            variantOutput = true;
        } else if (strcmp(argv[i], "-x") == 0) {
            mode = 'x';
        } else if (strcmp(argv[i], "-y") == 0) {
            mode = 'y';
        } else if (strcmp(argv[i], "-z") == 0) {
            mode = 'z';
        } else {
            // Process non-flag arguments
            bool matches = false;
            switch (mode) {
                case 'x':
                    matches = matchPatternX(argv[i]);
                    if (matches && variantOutput) {
                        // Perform and print conversion (to be implemented)
                    }
                    break;
                case 'y':
                    matches = matchPatternY(argv[i]);
                    if (matches && variantOutput) {
                        // Perform and print conversion (to be implemented)
                    }
                    break;
                case 'z':
                    matches = matchPatternZ(argv[i]);
                    if (matches && variantOutput) {
                        // Perform and print conversion (to be implemented)
                    }
                    break;
            }
            
            if (matches && !variantOutput) {
                printf("match\n");
            }
            else if (!matches) {
                printf("nomatch\n");
            }
        }
    }

    return 0;
}

bool matchPatternX(const char *arg) {
    // Implement pattern matching for -x mode
    return false;
}

bool matchPatternY(const char *arg) {
    // Implement pattern matching for -y mode
    return false;
}

bool matchPatternZ(const char *arg) {
    // Implement pattern matching for -z mode
    return false;
}
