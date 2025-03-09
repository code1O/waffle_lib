#ifndef SUBNET_H
#define SUBNET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>



#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
    #define USE_VLA 1
    
#else
    #define USE_VLA 0
    #define _countof(_Array) (sizeof(_Array) / sizeof(_Array[0]))

#endif


#if defined(_WIN32) || (_WIN64)
#define USE_PLATFORM 1

#elif defined(__linux__)
#define USE_PLATFORM 2

#else
#define USE_PLATFORM 0

#endif


#if defined(__cplusplus)
extern "C" {

    typedef struct {
        uint32_t network;
        uint32_t broadcast;
        uint32_t first_host;
        uint32_t last_host;
    } Subnet;

    uint32_t netArrayToInt(uint8_t ip[4]) {
        uint32_t first_octets = ((uint32_t)ip[0] << 24) | ((uint32_t)ip[1] << 16);
        uint32_t last_octets = ((uint32_t)ip[2] << 8) | ip[3];
        return first_octets | last_octets;
    }

    int* net_prefixes(int _n_Subnets, uint32_t ip) {
        int bitsBorrow = (int)ceil(log2(_n_Subnets));

        uint32_t __IP_FIRST_OCTET = (ip >> 24) & 0xFF;
        uint32_t range_ips[3][2] = {{0x01, 0x7e}, {0x80, 0xbf}, {0xc0, 0xdf}};

        int __def_prefix_RangeIps[3] = {8, 16, 24};
        int prefix_RangeIP = 0, new_prefix_RangeIp = 0;

        for (int idx = 0; idx < _countof(range_ips); idx++) {
            bool __IS_CLASS_IP = (__IP_FIRST_OCTET >= range_ips[idx][0]) && (__IP_FIRST_OCTET <= range_ips[idx][1]);

            if (__IS_CLASS_IP) {
                prefix_RangeIP = __def_prefix_RangeIps[idx];
                new_prefix_RangeIp = prefix_RangeIP + bitsBorrow;
                break;
            }
        }

        int prefixes[2] = {prefix_RangeIP, new_prefix_RangeIp};

        return prefixes;
    }

    // Storage in the buffer, allowing to be printed in the console
    void assign_buffer(uint32_t ip, char* buffer) {
        uint32_t ip_array[4];
        ip_array[0] = (ip >> 24) & 0xFF;     ip_array[1] = (ip >> 16) & 0xFF;
        ip_array[2] = (ip >> 8) & 0xFF;      ip_array[3] = ip & 0xFF;

        #if USE_VLA
        sprintf_s(buffer, (unsigned)_countof(buffer), "%u.%u.%u.%u",
                  ip_array[0], ip_array[1], ip_array[2], ip_array[3]
                );
        
        #else
        sprintf(buffer, "%u.%u.%u.%u", ip_array[0], ip_array[1], ip_array[2], ip_array[3]);

        #endif
        
    }

    void apply_subnet(uint32_t baseIP, int original_prefix, int new_prefix, const char* interface_name) {
        uint32_t baseMask = 0xFFFFFFFF << (32 - original_prefix);
        uint32_t newMask = 0xFFFFFFFF << (32 - new_prefix);
        
        uint32_t subnetNetwork = 0x00000000, subnetBroadcast = 0x00000000;

        int numSubnets = 1 << (new_prefix - original_prefix);

        #if USE_VLA
        Subnet __subnet[numSubnets];
        #else
        Subnet *__subnet = (Subnet *)malloc(numSubnets * sizeof(Subnet));
        #endif

        char IP_ADDRESS[64], SUBNET_MASK[64];
        char GATEWAY_FIRSTHOST[64], GATEWAY_LASTHOST[64];
        char cmd[256];
    
        #if USE_PLATFORM == 1
            const char* _str_cmd = "netsh interface ipv4 add address \"%s\" %s %s";
        #else
            const char* _str_cmd = "sudo ip address add %s dev %s";
        #endif

        for (int idx = 0; idx < numSubnets; idx++) {
            subnetNetwork = (baseIP & baseMask) + (idx << (32 - new_prefix));
            subnetBroadcast = subnetNetwork | (~newMask);

            __subnet[idx].network = subnetNetwork;
            __subnet[idx].broadcast = subnetBroadcast;
            __subnet[idx].first_host = subnetNetwork + 1;
            __subnet[idx].last_host = subnetBroadcast - 1;

            sprintf(IP_ADDRESS, "%u.%u.%u.%u", 
                (subnetNetwork >> 24) & 0xFF, (subnetNetwork >> 16) & 0xFF, 
                (subnetNetwork >> 8) & 0xFF, subnetNetwork & 0xFF
            );

            sprintf(SUBNET_MASK, "%u.%u.%u.%u", 
                (newMask >> 24) & 0xFF, (newMask >> 16) & 0xFF, 
                (newMask >> 8) & 0xFF, newMask & 0xFF
            );

            #if USE_PLATFORM == 1
                sprintf(cmd, _str_cmd, interface_name, IP_ADDRESS, SUBNET_MASK);
            #else
                sprintf(cmd, _str_cmd, IP_ADDRESS, interface_name);
            #endif

            system(cmd);
        }

        #if !USE_VLA
        free(__subnet);
        #endif
    }

}
#endif

#endif