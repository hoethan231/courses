// #include "ti_msp_dl_config.h"
// #include <stdio.h>

// #define OSCILLATOR_PINCM  IOMUX_PINCM26
// #define OSCILLATOR_GPIO_NUM  DL_GPIO_PIN_9
// #define OSCILLATOR_GPIO_PORT  GPIOB

// const float system_clk_freq = 32000000;

// struct delta_time {
//    uint32_t initial_timestamp;
//    uint32_t final_timestamp;
// };

// float gen_chargeDischarge_cycle(int initCycles);

// int main(void) {
//    SYSCFG_DL_init();

//    DL_GPIO_enablePower(GPIOB);
//    DL_GPIO_initDigitalInput(IOMUX_PINCM49);
//    DL_GPIO_initPeripheralInputFunctionFeatures(
//        IOMUX_PINCM49,
//        IOMUX_PINCM49_PF_GPIOB_DIO21,
//        DL_GPIO_INVERSION_DISABLE,
//        DL_GPIO_RESISTOR_PULL_UP,
//        DL_GPIO_HYSTERESIS_DISABLE,
//        DL_GPIO_WAKEUP_DISABLE
//    );

//    DL_GPIO_initDigitalInput(OSCILLATOR_PINCM);
//    DL_Timer_enablePower(TIMG12);
//    DL_Timer_ClockConfig config;
//    config.clockSel = DL_TIMER_CLOCK_BUSCLK;
//    config.divideRatio = DL_TIMER_CLOCK_DIVIDE_1;
//    config.prescale = 0;
//    DL_Timer_setClockConfig(TIMG12, &config);
//    DL_Timer_TimerConfig timerConfig;
//    timerConfig.timerMode = DL_TIMER_TIMER_MODE_PERIODIC_UP;
//    timerConfig.period = -1;
//    timerConfig.startTimer = DL_TIMER_START;
//    timerConfig.genIntermInt = DL_TIMER_INTERM_INT_DISABLED;
//    timerConfig.counterVal = 0;
//    DL_Timer_initTimerMode(TIMG12, &timerConfig);

//    float measured_freq;
//    int target_cycles = 10;

//    while (1) {
//        measured_freq = gen_chargeDischarge_cycle(target_cycles);
//        printf("%f Hz\n", measured_freq);
//        delay_cycles(system_clk_freq / 10);
//    }

//    return 0;
// }

// float gen_chargeDischarge_cycle(int initCycles) {
//    DL_GPIO_initDigitalInputFeatures(
//        OSCILLATOR_PINCM,
//        DL_GPIO_INVERSION_DISABLE,
//        DL_GPIO_RESISTOR_PULL_DOWN, 
//        DL_GPIO_HYSTERESIS_DISABLE,
//        DL_GPIO_WAKEUP_DISABLE
//    );


//    uint8_t count = 0;
//    uint32_t current_state, prev_state = 1;
//    struct delta_time time;
//    float calculated_time;

//    time.initial_timestamp = DL_Timer_getTimerCount(TIMG12);


//    while (count < initCycles) {
//        current_state = DL_GPIO_readPins(OSCILLATOR_GPIO_PORT, OSCILLATOR_GPIO_NUM);


//        if (current_state == 0 && prev_state > 0) {
//            DL_GPIO_initDigitalInputFeatures(
//                OSCILLATOR_PINCM,
//                DL_GPIO_INVERSION_DISABLE,
//                DL_GPIO_RESISTOR_PULL_UP,
//                DL_GPIO_HYSTERESIS_DISABLE,
//                DL_GPIO_WAKEUP_DISABLE
//            );
//        }
//        else if (current_state > 0 && prev_state == 0) {
//            DL_GPIO_initDigitalInputFeatures(
//                OSCILLATOR_PINCM,
//                DL_GPIO_INVERSION_DISABLE,
//                DL_GPIO_RESISTOR_PULL_DOWN, 
//                DL_GPIO_HYSTERESIS_DISABLE,
//                DL_GPIO_WAKEUP_DISABLE
//            );
//            ++count;
//        }


//        prev_state = current_state;
//    }
//    time.final_timestamp = DL_Timer_getTimerCount(TIMG12);

//    calculated_time = (time.final_timestamp - time.initial_timestamp) * (1 / system_clk_freq);
//    calculated_time = initCycles / calculated_time;

//    return calculated_time;
// }
