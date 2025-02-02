#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include "__utils.h"

char* define_tokens[4] = {
    "$", "*", ":", "///", 
};

char* ASSEMBLY_TOKENS[3] = {
    ".global",
    "mov", "#"
};

char* builtin_VarTokens[3] = {
    ".global_title", ".routes",
    ".darktheme", 
};

char* processor_tokens[7] = {
    "include from", "include",
    "__start_config",
    "start_func", "end_func",
    "call", "ret"
};


int num_tokens = (sizeof(define_tokens) + sizeof(builtin_VarTokens) + sizeof(processor_tokens));


void option_depends(char* array_ptr[], int count, ...){
    va_list args;
    va_start(args, count);

    for (int idx = 0; idx < count; idx ++ ){
        array_ptr[idx] = va_arg(args, char*);
    }


    va_end(args);

}

void process_FileConfig(const char* source) {
    char* content = read_file_content(source);
    char* tokenize = strtok(content, "\n");

    for (int idx = 0; idx < num_tokens; ++idx) {
        switch (*tokenize) {

        }
    }
}

