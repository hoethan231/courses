#include "ti_msp_dl_config.h"
#include <stdio.h>
#include <stdlib.h>

#define CRC32_SEED 0xFFFFFFFF

uint32_t compute_simple_checksum(uint8_t* data, uint32_t length)
{
    uint32_t sum = 0;

    for (uint32_t i = 0; i < length; i++) {
        uint32_t shift = (i & 3u) * 8u;           
        sum += ((uint32_t)data[i]) << shift;       
    }

    return ~sum; 
}

uint32_t compute_hardware_crc(uint8_t* data, uint32_t length)
{
    DL_CRC_setSeed32(CRC, CRC32_SEED);
    
    for(int i = 0; i < length; ++i) {
        DL_CRC_feedData8(CRC, data[i]);
    }
    
    return DL_CRC_getResult32(CRC);
}

int main(void)
{
    SYSCFG_DL_init();

    // CRC setup
    DL_CRC_reset(CRC);
    DL_CRC_enablePower(CRC);
    delay_cycles(POWER_STARTUP_DELAY);
    DL_CRC_init(CRC, DL_CRC_32_POLYNOMIAL, DL_CRC_BIT_REVERSED,
        DL_CRC_INPUT_ENDIANESS_LITTLE_ENDIAN, DL_CRC_OUTPUT_BYTESWAP_DISABLED);

    static uint8_t myData[10240];

    srand(12345);
    for (int i = 0; i < 10240; i++) {
        myData[i] = (uint8_t)rand();
    }

    printf("Original Checksum\n");
    uint32_t simple_checksum_1 = compute_simple_checksum(myData, 10240);
    uint32_t hardware_crc_1 = compute_hardware_crc(myData, 10240);
    
    printf("  Simple Checksum: 0x%08lX\n", (unsigned long)simple_checksum_1);
    printf("  Hardware CRC32:  0x%08lX\n\n", (unsigned long)hardware_crc_1);

    printf("Corrupt Bit 0 of myData[2496]\n");
    printf("  Original myData[2496]: 0x%02X\n", myData[2496]);
    myData[2496] ^= 0x01;
    printf("  Modified myData[2496]: 0x%02X\n", myData[2496]);
    
    uint32_t simple_checksum_2 = compute_simple_checksum(myData, 10240);
    uint32_t hardware_crc_2 = compute_hardware_crc(myData, 10240);
    
    printf("  Simple Checksum: 0x%08lX\n", (unsigned long)simple_checksum_2);
    printf("  Hardware CRC32:  0x%08lX\n\n", (unsigned long)hardware_crc_2);

    printf("Corrupted myData[2496] AND myData[8864]\n");
    printf("  Original myData[8864]: 0x%02X\n", myData[8864]);
    myData[8864] ^= 0x01;
    printf("  Modified myData[8864]: 0x%02X\n", myData[8864]);
    
    uint32_t simple_checksum_3 = compute_simple_checksum(myData, 10240);
    uint32_t hardware_crc_3 = compute_hardware_crc(myData, 10240);
    
    printf("  Simple Checksum: 0x%08lX\n", (unsigned long)simple_checksum_3);
    printf("  Hardware CRC32:  0x%08lX\n\n", (unsigned long)hardware_crc_3);

    printf("Simple Checksum changes:\n");
    printf("  Original -> 1 bit flip:  0x%08lX -> 0x%08lX\n", 
           (unsigned long)simple_checksum_1, (unsigned long)simple_checksum_2);
    printf("  1 bit flip -> 2 bit flip: 0x%08lX -> 0x%08lX\n\n", 
           (unsigned long)simple_checksum_2, (unsigned long)simple_checksum_3);
    
    printf("Hardware CRC32 changes:\n");
    printf("  Original -> 1 bit flip:  0x%08lX -> 0x%08lX\n", 
           (unsigned long)hardware_crc_1, (unsigned long)hardware_crc_2);
    printf("  1 bit flip -> 2 bit flip: 0x%08lX -> 0x%08lX\n", 
           (unsigned long)hardware_crc_2, (unsigned long)hardware_crc_3);

    while (1) { }
}