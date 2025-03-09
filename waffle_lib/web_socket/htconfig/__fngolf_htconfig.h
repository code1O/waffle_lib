#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>

#include "__lexergolf_htconfig.h"

#if defined (__cplusplus)

extern "C" {

    Token SET_NETDATA(Token token, const char* source) {
        net_sockaddr_in net_data;
        
        do {
            token = get_next_token(&source);
            long number;
            uint8_t symbol = IS_SYMBOL(*token.value);

            if (symbol == 0xb8) {
                int idx = 0;
                char* get_array = strtok(token.value, ",");
            }
            

        } while (token.type != TOKEN_EOF);
    }


    
    /**
     * 
     * ARITHMETIC OPERATIONS MADE IN ASSEMBLY
     * 
    */
    

    int add_two_nums(int fd, int sd);
}

#endif