#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 200
#define WORD_SIZE 20

void checkNumberOfArguments(int argc, char* file_name);
void openAndCreateFiles(char* file_name);
void getUserInput(FILE* file, FILE* tempFile, char file_name[], char tempFile_name[]);
void readLines(FILE* file, FILE* tempFile, char file_name[], char tempFile_name[], char* oldWord, char* newWord);
int replaceWords(char* buffer, char* oldWord, char* newWord);

int main(int argc, char *argv[]) {

    char* file_name = argv[1];
    checkNumberOfArguments(argc, file_name);

    return 0;
}

void checkNumberOfArguments(int argc, char* file_name) {
    // Checks to see if the number of arguments is the expected number
    if (argc == 1) {
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    }
    printf("\n");
    openAndCreateFiles(file_name);
}

void openAndCreateFiles(char* file_name) {
    // Opens the input file and creates a temporary file
    FILE *file = fopen(file_name, "r");
    char tempFile_name[] = "temp.txt";
    FILE *tempFile = fopen(tempFile_name, "w");
    if (file == NULL || tempFile == NULL) {
        printf("\nCannot open the file");
        exit(EXIT_SUCCESS);
    }
    getUserInput(file, tempFile, file_name, tempFile_name);
}

void getUserInput(FILE* file, FILE* tempFile, char file_name[], char tempFile_name[]) {
    // Asks the user for the old word and the new word
    char oldWord[WORD_SIZE];
    char newWord[WORD_SIZE];
    printf("Enter word to replace:");
    scanf("%s", oldWord);
    printf("Replace '%s' with:", oldWord);
    scanf(" %s", newWord);
    readLines(file, tempFile, file_name, tempFile_name, oldWord, newWord);
}

void readLines(FILE* file, FILE* tempFile, char file_name[], char tempFile_name[], char* oldWord, char* newWord) {
    // Reads each line from the input file
    char buffer[BUFFER_SIZE];
    int wordCount = 0;
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        wordCount += replaceWords(buffer, oldWord, newWord);
        fputs(buffer, tempFile);
    }
    fclose(file);
    fclose(tempFile);
    remove(file_name);
    rename(tempFile_name, file_name);
    if (wordCount == 0) {
        printf("\nCould not find '%s'", oldWord);
        exit(EXIT_SUCCESS);
    }
    printf("\nSuccessfully replaced all occurrences of '%s' with '%s'", oldWord, newWord);
}

int replaceWords(char* buffer, char* oldWord, char* newWord) {
    // Finds occurrences of oldWord and replaces it with newWord
    char *ptr;
    char temp[BUFFER_SIZE];
    int index;
    int wordCount = 0;
    int wordLength = strlen(oldWord);

    if (!strcmp(oldWord, newWord)) {
        printf("\nOld word is the same as new word");
        exit(EXIT_SUCCESS);
    }
    if ((ptr = strstr(buffer, oldWord)) != NULL) {
        strcpy(temp, buffer);
        index = ptr - buffer;
        buffer[index] = '\0';
        strcat(buffer, newWord);
        strcat(buffer, temp + index + wordLength);
        wordCount++;
    }
    return wordCount;
}
