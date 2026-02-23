#include <stdio.h>
#include "ti_msp_dl_config.h"

int time_management(void)
{
    SYSCFG_DL_init();
    DL_GPIO_enablePower(GPIOB);
    
    DL_GPIO_initPeripheralInputFunctionFeatures(IOMUX_PINCM49,
        IOMUX_PINCM49_PF_GPIOB_DIO21, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_PULL_UP, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInput(IOMUX_PINCM50);
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_22);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22);

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

    uintptr_t GPIOB_base = 0x400A2000u;

    uintptr_t blue_offset = 0x1214u;
    volatile uint8_t *blue_pin_ptr = (volatile uint8_t *)(GPIOB_base + blue_offset + 2u);

    uint32_t prev = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_21);
    uint32_t start = 0;
    uint32_t stop = 0;
    uint32_t clock_freq = 32000000;
    
    while (1) {
        uint32_t curr = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_21);

        if (!curr && prev) { 
            start = DL_Timer_getTimerCount(TIMG12);
            printf("Button pressed\n");
        }

        if (curr && !prev) {
            stop = DL_Timer_getTimerCount(TIMG12);
            uint32_t duration = stop - start;
            float time_seconds = (float)duration / clock_freq;
            printf("Button held for: %f seconds\n", time_seconds);
        }
        prev = curr;
    }

}
