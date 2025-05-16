#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1024

// Function to convert a string to uppercase
void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (isalpha((unsigned char)str[i])) {
            str[i] = toupper((unsigned char)str[i]);
        }
    }
}

// Function to convert a string to lowercase
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        if (isalpha((unsigned char)str[i])) {
            str[i] = tolower((unsigned char)str[i]);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <source_file> <short_lines_file> <long_lines_file>\n", argv[0]);
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) {
        perror("Error opening source file");
        return 1;
    }

    FILE *short_file = fopen(argv[2], "w");
    if (!short_file) {
        perror("Error opening short lines file");
        fclose(src);
        return 1;
    }

    FILE *long_file = fopen(argv[3], "w");
    if (!long_file) {
        perror("Error opening long lines file");
        fclose(src);
        fclose(short_file);
        return 1;
    }

    char line[MAX_LINE];
    int short_count = 0;
    int long_count = 0;

    while (fgets(line, MAX_LINE, src)) {
        // Remove newline for accurate length check
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }

        if (len < 20) {
            to_uppercase(line);
            fprintf(short_file, "%s\n", line);
            short_count++;
        } else {
            to_lowercase(line);
            fprintf(long_file, "%s\n", line);
            long_count++;
        }
    }

    fclose(src);
    fclose(short_file);
    fclose(long_file);

    printf("Wrote %d short lines to %s\n", short_count, argv[2]);
    printf("Wrote %d long lines to %s\n", long_count, argv[3]);

    return 0;
}
