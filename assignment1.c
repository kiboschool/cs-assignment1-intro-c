#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Declare each of the functions we will be using
bool matchPatternX(const char *arg);
bool matchPatternY(const char *arg);
bool matchPatternZ(const char *arg);
void printVariantX(const char *arg);
void printVariantY(const char *arg);
void printVariantZ(const char *arg);

bool isPrime(int number);

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
                        printVariantX(argv[i]);
                    }
                    break;
                case 'y':
                    matches = matchPatternY(argv[i]);
                    if (matches && variantOutput) {
                        printVariantY(argv[i]);
                    }
                    break;
                case 'z':
                    matches = matchPatternZ(argv[i]);
                    if (matches && variantOutput) {
                        printVariantZ(argv[i]);
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
    int len = strlen(arg);

    for (int i = 0; i < len; i++) {
        if (i % 2 == 0 && !isdigit(arg[i])) return false;
        if (i % 2 == 1 && !isalpha(arg[i])) return false;
    }
    return true;
}

bool matchPatternY(const char *arg) {
    // Implement pattern matching for -y mode
    int sum = 0;
    for (int i = 0; arg[i] != '\0'; i++) {
        sum += (int)arg[i];
    }
    return isPrime(sum);
}

bool isPrime(int number) {
    if (number <= 1) return false; // 0 and 1 are not prime numbers
    if (number <= 3) return true;  // 2 and 3 are prime numbers

    // Check if number is even, avoiding modulo
    if ((number & 1) == 0) return false;

    // Check for prime without using multiplication or division
    for (int i = 5; i <= number >> 1; i += 2) {
        int product = 0;
        int count = 0;
        // Replicating division: product + i <= number
        while (product <= number) {
            product += i;
            count++;
            if (product == number) {
                // If the division is perfect, number is not prime
                return false;
            }
        }
    }
    return true;
}

bool matchPatternZ(const char *arg) {
    // Implement pattern matching for -z mode
    if (*arg == '\0') {
        return false; // Empty string is not a valid expression
    }

    bool lastWasOperator = true; // Start assuming the last character was an operator

    for (const char *p = arg; *p; p++) {
        if (isdigit(*p)) {
            lastWasOperator = false; // Digit found, so the last character is not an operator
        } else if (*p == '+' || *p == '-' || *p == '*' || *p == '/') {
            if (lastWasOperator) {
                return false; // Two operators in a row are not allowed
            }
            lastWasOperator = true; // Operator found, setting flag
        } else {
            return false; // Invalid character found
        }
    }

    return !lastWasOperator;
}

void printVariantX(const char *arg) {
    for (const char *p = arg; *p; p++) {
        if (isalpha(*p)) {
            printf("%d", *p);  // Print ASCII value of the letter
        } else if (isdigit(*p)) {
            printf("%c", *p);  // Print the digit itself
        }

        if (*(p+1) != '\0') {
            printf("-");  // Add a hyphen between elements, but not at the end
        }
    }
    printf("\n");  // New line at the end of the output
}

void printVariantY(const char *arg) {
    for (const char *p = arg; *p; p++) {
        printf("%02x", (unsigned char)*p);  // Print ASCII value in hexadecimal

        if (*(p + 1) != '\0') {
            printf("-");  // Add a hyphen between elements, but not at the end
        }
    }
    printf("\n");  // New line at the end of the output
}

void printVariantZ(const char *arg) {
    int plusCount = 0, minusCount = 0, multiplyCount = 0, divideCount = 0;

    for (int i = 0; arg[i] != '\0'; i++) {
        switch (arg[i]) {
            case '+':
                plusCount++;
                break;
            case '-':
                minusCount++;
                break;
            case '*':
                multiplyCount++;
                break;
            case '/':
                divideCount++;
                break;
            default:
                // If it's not an operator, do nothing
                break;
        }
    }

    printf("%d%d%d%d\n", plusCount, minusCount, multiplyCount, divideCount);
}