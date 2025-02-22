
/**
 * 
 *  Lexical analyzer for `.htconfig` files
 * Analyze and transform values read from its source by tokenizing first
 * 
 * Analize importants:
 * 
 * - Keywords
 * - Data type
 * - builtin processors
 * 
 * 
*/



#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <errno.h>


typedef enum {
    TOKEN_KEYWORD, TOKEN_IDENTIFIER, TOKEN_TYPE, TOKEN_OPERATOR,
    TOKEN_SYMBOL, TOKEN_UNKNOWN, TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[32];
} Token;

typedef enum {
    TOKEN_FN_KEYWORD, TOKEN_FN_IDENTIFIER,
    TOKEN_FN_CONTENT, TOKEN_FN_EOF
} BlockType;

typedef struct {
    BlockType Type;
    char value[252];
} Block;

const char* keywords[] = {"num", "$", "?", "<?>", "mov", "call", "ret", NULL};
const char* delimiters = " \t\n,(){}[]";

#if defined(__cplusplus)
extern "C" {

    bool IS_KEYWORD(const char* string){
        bool result;
        for (int idx = 0; keywords[idx] != NULL; ++idx){
            result += strcmp(string, keywords[idx]);
        }
        return result;
    }

    uint8_t IS_SYMBOL(char line){
        bool IS_GROUP = (line == '[' || line == ']');
        bool IS_BRACES = (line == '(' || line == ')');
        bool IS_MATRIX = (line == '{' || line == '}');

        uint8_t code = IS_GROUP? 0xb8: 
                       IS_BRACES? 0x51: 
                       IS_MATRIX? 0xf8: 0x00;

        return code;
    }

    /**
     * 
     * A two option return.
     * Search for given values within the `array_ptr`
     * 
     * 
    */
    bool option_depends(char* array_ptr[], int count, ...){
        va_list args;
        va_start(args, count);
        int size_array = sizeof(*array_ptr) / sizeof(array_ptr[0]);
        int idx;
        bool* result;

        for (idx = 0; idx < size_array; idx++) {
            char* depends_element = va_arg(args, char*);
            bool IS_EXPECTED_STRING = (strcmp(array_ptr[idx], depends_element) == 0);
            result[idx] = IS_EXPECTED_STRING;
        }

        va_end(args);
        return result;

    }

    Token CHECK_ISALPHA(Token token, const char** source){
        int idx = 0;
        char buffer[32];
        bool main_condition = (isalpha(**source) || **source == '_');
        bool second_condition = (isalnum(**source) || **source == '_');
        if (!main_condition) perror("Error: not found main condition");

        while (second_condition) buffer[idx++] = *(*source)++;

        buffer[idx] = '\0';
        token.type = IS_KEYWORD(buffer)? TOKEN_KEYWORD: TOKEN_IDENTIFIER;

        strcpy(token.value, buffer);
        return token;
    }

    Token CHECK_ISDIGIT(Token token, const char** source) {
        int idx = 0;
        char buffer[32];
        bool main_condition = isdigit(**source);
        bool second_condition = (isdigit(**source) || **source == '_');

        if (!main_condition) perror("ERROR:");
        while (second_condition) buffer[idx] = *(*source)++;

        buffer[idx] = '\0';
        token.type = TOKEN_TYPE;
        strcpy(token.value, buffer);
        return token;
    }

    Token get_next_token(const char** source) {
        Token token;
        token.type = TOKEN_UNKNOWN;
        token.value[0] = '\0';

        while (isspace(**source)) (*source)++;

        if (**source == '\0') {
            token.type = TOKEN_EOF;
            strcpy(token.value, "EOF");
            return token;
        }

        CHECK_ISALPHA(token, source);
        CHECK_ISDIGIT(token, source);
    }



    void IS_DATATYPE() {}


    
    /**
     * 
     * ARITHMETIC OPERATIONS MADE IN ASSEMBLY
     * 
    */

   void add_two_nums(int fd, int sd);


#endif

#if defined(__cplusplus)
}

#endif
