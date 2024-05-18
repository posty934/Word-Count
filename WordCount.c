#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int countCharacters(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    
    int count = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (!isspace(c)) { // Count non-whitespace characters
            count++;
        }
    }
    fclose(file);
    return count;
}

int countWords(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    
    int count = 0;
    bool inWord = false;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (!isspace(c) && c != ',') {
            if (!inWord) {
                count++; // New word encountered (ignoring commas as well)
                inWord = true;
            }
        } else {
            inWord = false; // End of word
        }
    }
    fclose(file);
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c|-w] input_file_name\n", argv[0]);
        return 1;
    }
    
    char param = argv[1][1]; // Extract the parameter (-c or -w)
    const char *filename = argv[2];
    
    if (param == 'c') {
        int characters = countCharacters(filename);
        printf("×Ö·ûÊý: %d\n", characters);
    } else if (param == 'w') {
        int words = countWords(filename);
        printf("µ¥´ÊÊý: %d\n", words);
    } else {
        fprintf(stderr, "Invalid parameter. Use -c for characters or -w for words.\n");
        return 1;
    }
    
    return 0;
}
