/**
 * ======================================================
 *     PREDEFINE HARDWARE MEMORY ADDRESSES SUCH AS:
 * 
 *      - PERIPHERALS
 *      - RTC MEMORY
 *      - EXTERNAL MEMORY
 * =====================================================
 * 
*/


#include <stdio.h>
#include <stdint.h>


#define __VUINT32 volatile uint32_t
#define __VUINT16 volatile uint16_t
#define __VUINT8 volatile uint8_t

#define __VUINT32_PTR volatile uint32_t*
#define __VUINT16_PTR volatile uint16_t*
#define __VUINT8_PTR volatile uint8_t*


namespace esp32_addr {

  volatile uint32_t* RTC_MEMORY_ADDR[3][2] = {
    // SLOW MEMORY ADDRESS
    {
      (volatile uint32_t*)0x50000000,
      (volatile uint32_t*)0x50001FFF
    },
    // FAST MEMORY ADDRESS (BUS DATA)
    {
      (volatile uint32_t*)0x3FF80000,
      (volatile uint32_t*)0x3FF81FFF
    },
    // CONTROL MEMORY ADDRESS
    {
      (volatile uint32_t*)0x3FF43000,
      (volatile uint32_t*)0x3FF43FFF
    }
  };

  volatile uint32_t* PERIPHERALS_MEMORY_ADDR[2][2] = {
    // GPIO MEMORY ADDRESS
    {
      (volatile uint32_t*)0x3FF44000,
      (volatile uint32_t*)0x3FF44FFF
    },
    // PWM MEMORY ADDRESS
    {
      (volatile uint32_t*)0x3FF59000,
      (volatile uint32_t*)0x3FF59FFF
    }
  };

  volatile uint32_t* EXTERNAL_MEMORY_ADDR[2][2] = {
    // EXTERNAL FLASH MEMORY ADDRESS
    {
      (volatile uint32_t*)0x3F40000, 
      (volatile uint32_t*)0x3F7FFFFF
    }, 
    // EXTERNAL SRAM MEMORY ADDRESS
    {
      (volatile uint32_t*)0x3F80000, 
      (volatile uint32_t*)0x3FBFFFFF
    }
  };

  // SAME ORDER AS 32 BYTES ARRAYS


  volatile uint8_t* RTC_MEMORY_ADDR8[3][2] = {
    {
      (volatile uint8_t*)0x50000000,
      (volatile uint8_t*)0x50001FFF
    },
    {
      (volatile uint8_t*)0x3FF80000,
      (volatile uint8_t*)0x3FF81FFF
    },
    {
      (volatile uint8_t*)0x3FF43000,
      (volatile uint8_t*)0x3FF43FFF
    }
  };

  volatile uint8_t* EXTERNAL_MEMORY_ADDR8[2][2] = {
    {
      (volatile uint8_t*)0x3F40000, 
      (volatile uint8_t*)0x3F7FFFFF
    },
    {
      (volatile uint8_t*)0x3F80000, 
      (volatile uint8_t*)0x3FBFFFFF
    }
  };

  uint32_t __LIMIT_SIZE_RTC = 0x1F40; // 8 kilobytes
  uint32_t __LIMIT_SIZE_EXTERNAL = 0x3D0900; // 4 megabytes

  // include `ESP` before
  uint32_t __Internal_Flash_Size = ESP.getFlashChipSize();
  uint32_t __Sketch_Size = ESP.getSketchSize();
  uint32_t __Free_Sketch_Size = ESP.getFreeSketchSpace();

  __VUINT32_PTR GPIO_ADDR_MEM = (__VUINT32_PTR)PERIPHERALS_MEMORY_ADDR[0][0];
  __VUINT32_PTR GPIO_ENABLE_REG = (__VUINT32_PTR)GPIO_ADDR_MEM;
  __VUINT32_PTR GPIO_OUT_REG = (__VUINT32_PTR)((uint8_t*)GPIO_ADDR_MEM + 0x04);
  __VUINT32_PTR GPIO_IN_REG = (__VUINT32_PTR)((uint8_t*)GPIO_ADDR_MEM + 0x08);

  #define GPIO_DEFAULT_PIN 2

}



namespace RASPERRY_PI_ADDR {
  
  #include <stdio.h>
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>

  #ifdef __linux__
  #include <unistd.h>
  #include <sys/ioctl.h>
  #include <sys/mman.h>
  #endif


  #define BASE_DDR4_RAM_V4 0x00000000
  #define BCM2711_PERI_BASE  0xFFE00000
  #define BASE_GPU_MEM_ADDR 0xC0000000
  #define GPIO_BASE (BCM2711_PERI_BASE + 0x200000)
  #define UART0_BASE (BCM2711_PERI_BASE + 0x201000)
  #define SPIO_BASE (BCM2711_PERI_BASE + 0x204000)
  #define BLOCK_SIZE (4 * 1024)

  int mem_fd = open("/dev/mem", O_RDWR | O_SYNC);

  void* gpio_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
  void* uart0_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, UART0_BASE);
  void* spio_map = mmap(NULL, BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, SPIO_BASE);
  


}





