#include "ti_msp_dl_config.h"
#include <stdio.h>
#include <stdlib.h>

uint32_t compute_simple_checksum(uint8_t* data, uint32_t length)
{
    uint32_t sum = 0;

    for (uint32_t i = 0; i < length; i++) {
        uint32_t shift = (i & 3u) * 8u;           
        sum += ((uint32_t)data[i]) << shift;       
    }

    return ~sum; 
}

int simple_checksum(void)
{
    SYSCFG_DL_init();

    static uint8_t myData[10240];

    srand(12345);
    for (int i = 0; i < 10240; i++) {
        myData[i] = (uint8_t)rand();
    }

    printf("First four bytes: 0x%02X 0x%02X 0x%02X 0x%02X\n",
           myData[0], myData[1], myData[2], myData[3]);

    printf("Last four bytes : 0x%02X 0x%02X 0x%02X 0x%02X\n",
           myData[10236], myData[10237], myData[10238], myData[10239]);

    uint32_t sum = compute_simple_checksum(myData, 10240);
    printf("Simple checksum = 0x%08lX\n", (unsigned long)sum);

    while (1) { }
}