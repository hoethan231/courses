#include "ti_msp_dl_config.h"
#include <stdio.h>
#include <stdlib.h>

#define CRC32_SEED 0xFFFFFFFF
#define MYDATA_LENGTH 10240

uint32_t compute_simple_checksum(uint8_t* data, uint32_t length)
{
    uint32_t sum = 0;

    for (uint32_t i = 0; i < length; i++) {
        uint32_t shift = (i & 3u) * 8u;           
        sum += ((uint32_t)data[i]) << shift;       
    }

    return ~sum; 
}

/* Standard software calculation of CRC32 */
static uint32_t calculateCRC32(uint8_t* data, uint32_t length)
{
    const uint32_t crc32_poly = 0xEDB88320;
    uint32_t ii, jj, byte, crc, mask;
    crc = CRC32_SEED;
    for(ii=0; ii<length; ii++) {
        byte = data[ii];
        crc = crc ^ byte;
        for (jj = 0; jj < 8; jj++) {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (crc32_poly & mask);
        }
    }
    return crc;
}

int sppedup(void)
{
    SYSCFG_DL_init();

    // CRC setup
    DL_CRC_reset(CRC);
    DL_CRC_enablePower(CRC);
    delay_cycles(POWER_STARTUP_DELAY);
    DL_CRC_init(CRC, DL_CRC_32_POLYNOMIAL, DL_CRC_BIT_REVERSED,
        DL_CRC_INPUT_ENDIANESS_LITTLE_ENDIAN, DL_CRC_OUTPUT_BYTESWAP_DISABLED);
    DL_CRC_setSeed32(CRC, CRC32_SEED);

    // Set up to use the 32-bit counter TIMG12
    DL_Timer_enablePower(TIMG12);
    DL_Timer_ClockConfig config;
    config.clockSel = DL_TIMER_CLOCK_BUSCLK;
    config.divideRatio = DL_TIMER_CLOCK_DIVIDE_1;
    config.prescale = 0;
    DL_Timer_setClockConfig(TIMG12, &config);
    DL_Timer_TimerConfig timerConfig;
    timerConfig.timerMode = DL_TIMER_TIMER_MODE_PERIODIC_UP;
    timerConfig.period = -1;
    timerConfig.startTimer = DL_TIMER_START;
    timerConfig.genIntermInt = DL_TIMER_INTERM_INT_DISABLED;
    timerConfig.counterVal = 0;
    DL_Timer_initTimerMode(TIMG12, &timerConfig);

    uint32_t clock_freq = 32000000;

    static uint8_t myData[MYDATA_LENGTH];

    srand(12345);
    for (int i = 0; i < MYDATA_LENGTH; i++) {
        myData[i] = (uint8_t)rand();
    }

    // Simple Checksum
    uint32_t start = DL_Timer_getTimerCount(TIMG12);
    uint32_t sum1 = compute_simple_checksum(myData, MYDATA_LENGTH);
    uint32_t stop = DL_Timer_getTimerCount(TIMG12);
    uint32_t duration1 = stop - start;
    float time1_us = (float)duration1 / clock_freq * 1000000.0f;
    
    // Software CRC32
    start = DL_Timer_getTimerCount(TIMG12);
    uint32_t sum2 = calculateCRC32(myData, MYDATA_LENGTH);
    stop = DL_Timer_getTimerCount(TIMG12);
    uint32_t duration2 = stop - start;
    float time2_us = (float)duration2 / clock_freq * 1000000.0f;
    
    // Hardware CRC32
    DL_CRC_setSeed32(CRC, CRC32_SEED);
    start = DL_Timer_getTimerCount(TIMG12);
    for(int i = 0; i < MYDATA_LENGTH; ++i) {
       DL_CRC_feedData8(CRC, myData[i]);
    }
    uint32_t sum3 = DL_CRC_getResult32(CRC);
    stop = DL_Timer_getTimerCount(TIMG12);
    uint32_t duration3 = stop - start;
    float time3_us = (float)duration3 / clock_freq * 1000000.0f;

    
    printf("Simple Checksum:\n");
    printf("  Time: %.2f us\n", time1_us);
    printf("  Checksum: 0x%08lX\n\n", (unsigned long)sum1);
    
    printf("Software CRC32:\n");
    printf("  Time: %.2f us\n", time2_us);
    printf("  Checksum: 0x%08lX\n\n", (unsigned long)sum2);
    
    printf("Hardware CRC32:\n");
    printf("  Time: %.2f us\n", time3_us);
    printf("  Checksum: 0x%08lX\n\n", (unsigned long)sum3);
    
    // Calculate speedups
    float speedup_hw_vs_sw = time2_us / time3_us;
    float speedup_simple_vs_hw = time1_us / time3_us;
    
    printf("Hardware CRC vs Software CRC speedup: %.2fx\n", speedup_hw_vs_sw);
    printf("Simple Checksum vs Hardware CRC speedup: %.2fx\n", speedup_simple_vs_hw);

    while (1) { }
}