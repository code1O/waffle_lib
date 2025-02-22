#include <stdio.h>
#include <stdint.h>

#define __ARM_MOVE(reg, val) "mov " reg ", #" value "\n"
#define __ARM_ADD(reg, val) "add " reg ", " value

class __STATS {

private:
  
  int (*given_array);

public:
  
  __STATS(int (*array)): given_array(array) {}

  // Return the average value from an array
  // Using assembly form better efficiency performance
  int mean(int N) {
    int idx = 0;
    int result;
    int len_array = sizeof(this->given_array);

    while (len_array > idx) {
        asm volatile (
            "mov ebx, %0\n"
            "mov ecx, %1\n"
            "mov eax, ebx\n"
            :
            : "r" (this->given_array[idx]), "r" (N)
            : "eax", "ebx"
        );
        idx ++;
    }
    return result;
  }

};


