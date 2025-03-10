# Configuring, setting and manipulating network


<details>

<summary><h2>Subneting IPV4 addresses</h2></summary>

- ## Via C/C++
```C
#include <stdio.h>
#include <coffee_ip/subnet.h>

int main() {
    uint8_t IP_ADDRESS[4] = {0xC0, 0xA8, 0x01, 0xb5};
    uint32_t baseIP = netArrayToInt(IP_ADDRESS);

    int _n_Subnets = 4; // Number of subnets to create
    int* prefixes = net_prefixes(_n_Subnets, baseIP);

    apply_subnet(baseIP, prefixes[0], prefixes[1]);

    char buffer[255];
    assign_buffer(baseIP, buffer);
    printf("Successfuly applied subnet to IP: %s", buffer);

}

```

### Output:

```bat
Successfuly applied subnet to IP: 192.168.1.181
```

- ## Via htconfig

```haskell
extern printf

start func __start_config:
  
  ? IP_HEX -> {0xc0, 0xa8, 0x01, 0xb5}
  num IP_CONVERTED -> netArrayToInt IP_HEX
  mov baseIP, #netArraytoInt

  num _n_Subnets -> 4
  
  ? net_prefixes -> prefixes _n_Subnets, IP_HEX
  call func apply_subnet baseIP, prefixes[0], prefixes[1]

end func

```

</details>