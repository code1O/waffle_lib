#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "__hardware_addr.h"


typedef void (*__sleep_t)(long);

namespace esp32_control {
    using namespace esp32_addr;

    // Handle memory address at Read/Write bus
    template <typename __MEM_T>
    class __memory_RoW_bus {
    private:
        __MEM_T __MEMORY_ADDRESS;
    public:
        __memory_RoW_bus(__MEM_T MEMORY_ADDR): __MEMORY_ADDRESS(MEMORY_ADDR){}

        static void WRITE_GPIO_STATUS(uint8_t status = 0x01, void* sleep_func, long delay_time = 1000L) {
            __sleep_t ptrFuncSleep = (__sleep_t)sleep_func;

            *GPIO_ENABLE_REG |= (1 << GPIO_DEFAULT_PIN);
            status == 0x01? *GPIO_OUT_REG |= (1 << GPIO_DEFAULT_PIN)
                          : *GPIO_OUT_REG &= ~(1 << GPIO_DEFAULT_PIN);
            ptrFuncSleep(delay_time);

        }

        static bool READ_GPIO_STATUS(__VUINT32_PTR* MEM_ADDR) {
            bool status_read = (((*GPIO_IN_REG >> *MEM_ADDR) & 0x01) == 0);
            return status_read;
        }

        // NOTE: add `free()` to this function after using it, for it's using `malloc()`
        static uint8_t READ_BLE_STATUS(uint8_t* report, size_t byte_idx) {
            int bit_idx;
            uint8_t mask_byte = 0x01;

            uint8_t* final_byteArray = (uint8_t*)malloc(8 * sizeof(uint8_t));
            if (final_byteArray == NULL) {
                perror("MALLOC ERROR:");
                return NULL;
            }
            
            // GIVEN AN ARRAY [0x1A, 0x3C, 0x4D, 0xFF, ...] FOR EXAMPLE
            for (bit_idx = 0; bit_idx < 8; bit_idx ++ ){
                final_byteArray[bit_idx] = (report[byte_idx] >> bit_idx) & mask_byte;
            }

            return final_byteArray;
        }

        void writein_memory(__MEM_T New_AddrValue) {
            bool ISGREATER_SIZES = (sizeof(New_AddrValue) > sizeof(__MEMORY_ADDRESS));
            if (!__MEMORY_ADDRESS) perror("Error:");
            __MEM_T current_mem_value = __MEMORY_ADDRESS;

            // In case that the query value is greater than the current value (or viceversa)
            // Then write the current value within the memory address (in other words, do nothing)
            __MEMORY_ADDRESS = ISGREATER_SIZES? current_mem_value : New_AddrValue;
        }

        __MEM_T read_memory() {
            bool ISGREATER_TYPESIZE = (sizeof(__MEMORY_ADDRESS) > sizeof(__MEM_T));
            if (!__MEMORY_ADDRESS) perror("Error:");
            return ISGREATER_TYPESIZE? NULL: __MEMORY_ADDRESS;
        }

    };
}