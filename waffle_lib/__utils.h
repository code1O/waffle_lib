#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <fstream>

/// Return content read from a file 
/// @brief 
/// @param file_name file to read
/// @param mode read mode (either r, rb or +rb)
/// @return 
char* read_file_content(const char* file_name, const char* mode = "r") {
    FILE* file_ptr = fopen(file_name, mode);
    if (!file_ptr) perror("Couldn't open requested file");

    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    rewind(file_ptr);
    
    char* content = (char*)malloc(file_size + 1);

    if (!content) {
        perror("Couldn't read content");
        fclose(file_ptr);
    };

    if (file_size > 0x1000) {
        perror("Size too long for reading"); 
        fclose(file_ptr);
        free(content);
    }

    fread(content, 1, file_size, file_ptr);
    content[file_size] = '\0';

    fclose(file_ptr);
    return content;

}

