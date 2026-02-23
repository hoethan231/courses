#include <stdio.h>
#include "ti_msp_dl_config.h"

#define QUEUE_SIZE 10

struct record {
    uint32_t timestamp;
    uint8_t state;
};

struct record queue[QUEUE_SIZE];
volatile int read_index = 0;
volatile int write_index = 0;

void GROUP1_IRQHandler(void)
{
    uint32_t interrupt_status = DL_GPIO_getEnabledInterruptStatus(GPIOB, DL_GPIO_PIN_21);

    if ((interrupt_status & DL_GPIO_PIN_21) == DL_GPIO_PIN_21)
    {
        int next_write = (write_index + 1) % QUEUE_SIZE;
        if (next_write == read_index) {
            printf("ERROR: Queue is full!\n");
            DL_GPIO_clearInterruptStatus(GPIOB, DL_GPIO_PIN_21);
            return; 
        }

        queue[write_index].timestamp = DL_Timer_getTimerCount(TIMG12);
        queue[write_index].state = (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_21) & DL_GPIO_PIN_21) ? 1 : 0;
        
        write_index = next_write;
        
        DL_GPIO_clearInterruptStatus(GPIOB, DL_GPIO_PIN_21);
    }
}

int measurement(void)
{
    SYSCFG_DL_init();
    DL_GPIO_enablePower(GPIOB);

    DL_GPIO_initPeripheralInputFunctionFeatures(IOMUX_PINCM49,
        IOMUX_PINCM49_PF_GPIOB_DIO21, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_PULL_UP, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(IOMUX_PINCM50);
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_22);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22);

    DL_GPIO_setUpperPinsPolarity(GPIOB, DL_GPIO_PIN_21_EDGE_RISE_FALL);
    DL_GPIO_clearInterruptStatus(GPIOB, DL_GPIO_PIN_21);
    DL_GPIO_enableInterrupt(GPIOB, DL_GPIO_PIN_21);
    NVIC_EnableIRQ(GPIOB_INT_IRQn);

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
    DL_Timer_enableClock(TIMG12);
    DL_Timer_startCounter(TIMG12);

    uint32_t clock_freq = 32000000;
    uint32_t prev_timestamp = 0;

    while (1) {
        delay_cycles(32000000 / 100);

        while (read_index != write_index) {
            struct record current = queue[read_index];
            
            if (current.state == 1) {
                uint32_t duration = current.timestamp - prev_timestamp;
                float time_ms = (float)duration / clock_freq * 1000.0f;
                printf("Duration: %.2f ms, read_index: %d\n", time_ms, read_index);
            }
            
            prev_timestamp = current.timestamp;
            
            read_index = (read_index + 1) % QUEUE_SIZE;
        }
    }
}