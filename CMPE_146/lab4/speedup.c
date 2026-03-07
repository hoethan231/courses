#include "ti_msp_dl_config.h"
#include <stdio.h>
#include <stdlib.h>

#define CRC32_SEED      0xFFFFFFFF
#define MYDATA_LENGTH   10240
#define DMA_CH0_CHAN_ID (0)

const float_t system_clk_freq = 32000000;
static uint8_t myData[MYDATA_LENGTH];
volatile bool dma_done;

static const DL_DMA_Config gDMA_CH0Config = {
    .transferMode  = DL_DMA_SINGLE_BLOCK_TRANSFER_MODE,
    .extendedMode  = DL_DMA_NORMAL_MODE,
    .destIncrement = DL_DMA_ADDR_UNCHANGED,
    .srcIncrement  = DL_DMA_ADDR_INCREMENT,
    .destWidth     = DL_DMA_WIDTH_BYTE,
    .srcWidth      = DL_DMA_WIDTH_BYTE,
    .trigger       = DMA_SOFTWARE_TRIG,
    .triggerType   = DL_DMA_TRIGGER_TYPE_EXTERNAL,
};

void DMA_IRQHandler(void) {
    switch (DL_DMA_getPendingInterrupt(DMA)) {
        case DL_DMA_EVENT_IIDX_DMACH0:
            dma_done = true;
            break;
        default:
            break;
    }
}

uint8_t checkAdditionOverflowThree(uint8_t a, uint8_t b, uint8_t c) {
    uint8_t limit    = 255;
    uint8_t a_b_sum  = a + b;
    if (a > (limit - b))       return 1;
    if (a_b_sum > (limit - c)) return 0x01;
    return 0x0;
}

uint32_t compute_simple_checksum(uint8_t *data, uint32_t length) {
    uint32_t sum = 0x00000000;
    uint8_t *sum_ptr = (uint8_t *)&sum;
    uint8_t  byte_count = 0;
    uint8_t  overflow_arr[4] = {0, 0, 0, 0};

    for (int i = 0; i < length; ++i) {
        switch (byte_count) {
            case 0: {
                uint8_t overflow = checkAdditionOverflowThree(sum_ptr[byte_count], data[i], overflow_arr[0]);
                overflow_arr[1]       = overflow;
                sum_ptr[byte_count]   = sum_ptr[byte_count] + data[i] + overflow_arr[0];
                break;
            }
            case 1: {
                uint8_t overflow = checkAdditionOverflowThree(sum_ptr[byte_count], data[i], overflow_arr[1]);
                overflow_arr[2]       = overflow;
                sum_ptr[byte_count]   = sum_ptr[byte_count] + data[i] + overflow_arr[1];
                break;
            }
            case 2: {
                uint8_t overflow = checkAdditionOverflowThree(sum_ptr[byte_count], data[i], overflow_arr[2]);
                overflow_arr[3]       = overflow;
                sum_ptr[byte_count]   = sum_ptr[byte_count] + data[i] + overflow_arr[2];
                break;
            }
            case 3: {
                uint8_t overflow = checkAdditionOverflowThree(sum_ptr[byte_count], data[i], overflow_arr[3]);
                sum_ptr[byte_count]   = sum_ptr[byte_count] + data[i] + overflow_arr[3];
                break;
            }
        }
        byte_count = (byte_count + 1) % 4;
    }
    return ~sum;
}

static uint32_t calculateCRC32(uint8_t *data, uint32_t length) {
    const uint32_t crc32_poly = 0xEDB88320;
    uint32_t ii, jj, byte, crc, mask;
    crc = CRC32_SEED;
    for (ii = 0; ii < length; ii++) {
        byte = data[ii];
        crc  = crc ^ byte;
        for (jj = 0; jj < 8; jj++) {
            mask = -(crc & 1);
            crc  = (crc >> 1) ^ (crc32_poly & mask);
        }
    }
    return crc;
}

int main(void) {
    SYSCFG_DL_init();

    // CRC setup
    DL_CRC_reset(CRC);
    DL_CRC_enablePower(CRC);
    delay_cycles(POWER_STARTUP_DELAY);
    DL_CRC_init(CRC, DL_CRC_32_POLYNOMIAL, DL_CRC_BIT_REVERSED,
                DL_CRC_INPUT_ENDIANESS_LITTLE_ENDIAN,
                DL_CRC_OUTPUT_BYTESWAP_DISABLED);
    DL_CRC_setSeed32(CRC, CRC32_SEED);

    // DMA setup
    DL_DMA_clearInterruptStatus(DMA, DL_DMA_INTERRUPT_CHANNEL0);
    DL_DMA_enableInterrupt(DMA, DL_DMA_INTERRUPT_CHANNEL0);
    DL_DMA_initChannel(DMA, DMA_CH0_CHAN_ID, (DL_DMA_Config *)&gDMA_CH0Config);
    NVIC_EnableIRQ(DMA_INT_IRQn);

    // Timer setup (TIMG12 as 32-bit up counter)
    DL_Timer_enablePower(TIMG12);
    DL_Timer_ClockConfig config;
    config.clockSel    = DL_TIMER_CLOCK_BUSCLK;
    config.divideRatio = DL_TIMER_CLOCK_DIVIDE_1;
    config.prescale    = 0;
    DL_Timer_setClockConfig(TIMG12, &config);

    DL_Timer_TimerConfig timerConfig;
    timerConfig.timerMode    = DL_TIMER_TIMER_MODE_PERIODIC_UP;
    timerConfig.period       = -1;
    timerConfig.startTimer   = DL_TIMER_START;
    timerConfig.genIntermInt = DL_TIMER_INTERM_INT_DISABLED;
    timerConfig.counterVal   = 0;
    DL_Timer_initTimerMode(TIMG12, &timerConfig);

    srand(12345);
    for (int i = 0; i < MYDATA_LENGTH; ++i)
        myData[i] = rand();

    // Print first and last 4 bytes to verify data
    printf("Sample[0]:     0x%0.2x\n", myData[0]);
    printf("Sample[1]:     0x%0.2x\n", myData[1]);
    printf("Sample[2]:     0x%0.2x\n", myData[2]);
    printf("Sample[3]:     0x%0.2x\n", myData[3]);
    printf("Sample[10236]: 0x%0.2x\n", myData[10236]);
    printf("Sample[10237]: 0x%0.2x\n", myData[10237]);
    printf("Sample[10238]: 0x%0.2x\n", myData[10238]);
    printf("Sample[10239]: 0x%0.2x\n", myData[10239]);

    uint32_t initial_value, final_value, checksumResultHardware, checksumResultDMA;
    float_t  hw_time, dma_time;

    // Hardware Method
    initial_value = DL_Timer_getTimerCount(TIMG12);
    for (int i = 0; i < MYDATA_LENGTH; ++i)
        DL_CRC_feedData8(CRC, myData[i]);
    checksumResultHardware = DL_CRC_getResult32(CRC);
    final_value = DL_Timer_getTimerCount(TIMG12);
    hw_time = (final_value - initial_value) * (1 / system_clk_freq) * 100000;
    printf("HW CRC Time: %f us\tHW CRC Checksum: 0x%x\n", hw_time, checksumResultHardware);

    // DMA Method
    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t)&myData[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, DL_CRC_getCRCINAddr(CRC));
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, MYDATA_LENGTH);
    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
    DL_CRC_setSeed32(CRC, CRC32_SEED);
    dma_done = false;
    initial_value = DL_Timer_getTimerCount(TIMG12);
    DL_DMA_startTransfer(DMA, DMA_CH0_CHAN_ID);
    while (!dma_done) {}
    final_value    = DL_Timer_getTimerCount(TIMG12);
    checksumResultDMA = DL_CRC_getResult32(CRC);
    dma_time = (final_value - initial_value) * (1 / system_clk_freq) * 100000;
    printf("DMA CRC Time: %f us\tDMA CRC Checksum: 0x%x\n", dma_time, checksumResultDMA);

    printf("Speedup Ratio: %f\n", hw_time / dma_time);

    return 0;
}