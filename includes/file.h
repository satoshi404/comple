#ifndef _FILE_
#define _FILE_
#include <stdio.h>

FILE* open_file(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

char* read_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = (char*) malloc(size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Error allocating memory for file\n");
        exit(EXIT_FAILURE);
    }

    if (fread(buffer, 1, size, file)!= size) {
        fprintf(stderr, "Error reading file\n");
        exit(EXIT_FAILURE);
    }
    buffer[size] = '\0';
    return buffer;
}

void write_file(FILE* file, char* content) {
    if (fwrite(content, 1, strlen(content), file)!= strlen(content)) {
        fprintf(stderr, "Error writing to file\n");
        exit(EXIT_FAILURE);
    }
}
    

void close_file(FILE* file) {
    fclose(file);
}

#endif // _FILE_