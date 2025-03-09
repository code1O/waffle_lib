
/**
 *  ===================================================
 *       Lexical analyzer for `.htconfig` files
 *       Analyze and transform values read 
 *       From its source by tokenizing first
 * 
 *       Analize importants:
 * 
 *       - Keywords
 *       - Data type
 *       - builtin processors
 *  ===================================================
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
const char* type_str[] = {"KEYWORD", "IDENTIFIER", "TYPE", "OPERATOR", "SYMBOL", "UNKNOWN", "EOF"};
const char* delimiters = " \t\n,(){}[]";


// ===========================================================
//                      WEB DATATYPES
// ===========================================================


typedef struct {
    int protocol;
    char* addr;
    unsigned short port;
} *net_sockaddr_in;

#define TCP_PROTOCOL 0x06
#define UDP_PROTOCOL 0x11

bool __NET_INADDR_ANY = false;


// ===========================================================
//                  BUILTIN VARIABLES
// ===========================================================

typedef int                         __IPPROTOCOL;
typedef unsigned short              __HOSTPORT;
typedef char*                       __NET_ADDR;

typedef char*                       __HTML_TITLE;
typedef char*                       __HTML_ROUTES[];
typedef bool                        __HTML_DARKTHEME[];



// ===========================================================
//                  LEXER ANALYZER
// ===========================================================

#if defined(__cplusplus)
extern "C" {

    bool IS_KEYWORD(const char* string){
        bool result;
        for (int idx = 0; keywords[idx] != NULL; ++idx){
            result += strcmp(string, keywords[idx]);
        }
        return result;
    }

    // Return a `uint8_t` code if matches symbol with the given character
    //
    // - `Matrix symbol`: 0xb8
    //
    // - `Parenthesees symbol`: 0x51
    //
    // - `Array symbol`: 0xf8
    //
    //
    uint8_t IS_SYMBOL(char line){
        bool IS_MATRIX = (line == '[' || line == ']');
        bool IS_PARENTHESES = (line == '(' || line == ')');
        bool IS_ARRAY = (line == '{' || line == '}');

        uint8_t code = IS_MATRIX? 0xb8: 
                       IS_PARENTHESES? 0x51: 
                       IS_ARRAY? 0xf8: 0x00;

        return code;
    }

    // Return a `uint8_t` code if matches assembly keyword / processer with the given string
    //
    // - `mov`: 0x04
    //
    // - `ret`: 0x08
    //
    // - `call`: 0x10
    //
    // - `#` (processer): 0x18
    //
    uint8_t IS_ASSEMBLY_PROCESSER(Token token) {
        const char* processer[] = {"mov", "ret", "call"};
        const uint8_t hex_array[] = {0x04, 0x08, 0x10};

        int idx;
        const int length_array = sizeof(processer) / sizeof(processer[0]);

        if (token.type != TOKEN_IDENTIFIER) return 0x00;

        for (idx = 0; idx < length_array; idx ++) {
            bool is_processer = strcmp(token.value, processer[idx]) == 0;
            if (is_processer) return hex_array[idx];
        }

        if (strcmp(token.value, "#") == 0) return 0x18;

        return 0x00;

    }

    uint8_t IS_PROCESSER(char line) {
        char* processer[] = {""};
        int length_array = sizeof(processer) / sizeof(processer[0]);

    }

    //
    // Search for given values within the `array_ptr`
    // Then, set a `true` value for the given elements
    // 
    // ```c
    // char* array_ptr[] = {"/", "/HelloWorld", "/Oother"};
    /// bool is_option = option_depends(array_ptr, 2, "/", "/Oother");
    // ```
    //
    // NOTE: ADD `free()` after using it!
    //
    //
    bool* option_depends(char* array_ptr[], int count, ...){
        va_list args;
        va_start(args, count);

        int size_array = sizeof(array_ptr) / sizeof(array_ptr[0]);
        if (size_array <= 0 || count <= 0) return NULL;

        int idx;
        bool* result = (bool*)calloc(size_array, sizeof(bool));

        for (idx = 0; idx < size_array; idx++) {
            char* depends_element = va_arg(args, char*);
            bool IS_EXPECTED_STRING = (strcmp(array_ptr[idx], depends_element) == 0);
            result[idx] = IS_EXPECTED_STRING;
        }

        va_end(args);
        return result;

    }

    // 
    // Execute a function only for the given values from an array
    // 
    // ```c
    // char* array_ptr[] = {"1", "150", "320", "5"};
    // void* result_option = (void*)option_fn(array_ptr, 2, "150", "5");
    // ```
    //
    //
    void option_fn(char* array_ptr[], void* fn, int count, ...) {
        va_list args;
        va_start(args, count);
        int size_array = sizeof(*array_ptr) / sizeof(array_ptr[0]);
        int idx;

    }

    Token CHECK_ISALPHA(Token token, const char** source){
        int idx = 0;
        char buffer[32];
        bool main_condition = (isalpha(**source) || **source == '_');
        bool second_condition = (isalnum(**source) || **source == '_');
        if (!main_condition) perror("Error:");

        while (second_condition) buffer[idx++] = *(*source)++;

        buffer[idx] = '\0';
        token.type = IS_KEYWORD(buffer)? TOKEN_KEYWORD: TOKEN_IDENTIFIER;

        strcpy_s(token.value, sizeof(token.value), buffer);
        return token;
    }

    Token CHECK_ISDIGIT(Token token, const char** source) {
        int idx = 0;
        char buffer[32];
        bool main_condition = isdigit(**source);
        bool second_condition = (isdigit(**source) || **source == '_');

        if (!main_condition) printf("%s", "The given data isn't a digit type");

        while (second_condition) buffer[idx] = *(*source)++;

        buffer[idx] = '\0';
        token.type = TOKEN_TYPE;

        strcpy_s(token.value, sizeof(token.value), buffer);
        return token;
    }

    Token get_next_token(const char** source) {
        Token token;
        token.type = TOKEN_UNKNOWN;
        token.value[0] = '\0';

        while (isspace(**source)) (*source)++;

        if (**source == '\0') {
            token.type = TOKEN_EOF;

            strcpy_s(token.value, sizeof(token.value), "EOF");
            return token;
        }

        CHECK_ISALPHA(token, source);
        CHECK_ISDIGIT(token, source);
    }


    Token check_builtinTypes(Token token, const char* source) {
        do {
            token = get_next_token(&source);
            
        } while (token.type != TOKEN_EOF);
    }



#endif

#if defined(__cplusplus)
}

#endif
