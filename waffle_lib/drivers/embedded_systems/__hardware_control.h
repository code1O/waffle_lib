#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include "__hardware_addr.h"

using namespace esp32_addr;
namespace esp32_control {
    // Handle memory addresses at Read/Write bus
    class __memory_RoW_bus {
    private:
        __VUINT32_PTR __MEMORY_ADDRESS;
    public:
        __memory_RoW_bus(__VUINT32_PTR MEMORY_ADDR): __MEMORY_ADDRESS(MEMORY_ADDR) {}

        static void WRITE_GPIO_STATUS(uint8_t status = 0x01, long delay_time = 1000L) {
        *GPIO_ENABLE_REG |= (1 << GPIO_DEFAULT_PIN);

        status == 0x01? 
        *GPIO_OUT_REG |= (1 << GPIO_DEFAULT_PIN)
        : *GPIO_OUT_REG &= ~(1 << GPIO_DEFAULT_PIN);

        }

        static bool READ_GPIO_STATUS(__VUINT32_PTR MEM_ADDR) {
        uint8_t mask_byte = 0x01;
        int status_read = (*GPIO_IN_REG >> *MEM_ADDR)& mask_byte;
        return status_read == 0? false: true;
        }

        static void READ_BLE_STATUS(uint8_t* report) {
        uint8_t mask_bye = 0xFF;

        }
    };
}