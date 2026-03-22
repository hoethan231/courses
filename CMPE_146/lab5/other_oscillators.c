// #include "ti_msp_dl_config.h"
// #include <stdio.h>

// #define GPIO_OSCILLATOR_ARR_SIZE 4
// #define OSCILLATOR_GPIO_PORT  GPIOB
// #define GEN_CYCLES 10

// static const uint32_t OSCILLATOR_PINCM_ARR[] = { 
//    IOMUX_PINCM18, 
//    IOMUX_PINCM26,
//    IOMUX_PINCM28, 
//    IOMUX_PINCM49 
// };
// static const uint32_t OSCILLATOR_GPIO_NUM_ARR[] = { 
//    DL_GPIO_PIN_5,
//    DL_GPIO_PIN_9,
//    DL_GPIO_PIN_11,
//    DL_GPIO_PIN_21
// };
// static const char * OSCILLATOR_PINS_NAME[] = {
//    "PB5",
//    "PB9",
//    "PB11",
//    "PB21"
// };

// const float system_clk_freq = 32000000;

// struct delta_time {
//    uint32_t initial_timestamp;
//    uint32_t final_timestamp;
// };

// float gen_chargeDischarge_cycle(int initCycles, uint32_t initPINCM, uint32_t initGPIONum, GPIO_Regs * initGPIOPort);

// void initialize_oscillator_pins(const uint32_t * initPinList, uint32_t initSize, GPIO_Regs * initGPIOPort);

// void setup_timer();

// int main(void) {
//    SYSCFG_DL_init();

//    initialize_oscillator_pins(OSCILLATOR_PINCM_ARR, GPIO_OSCILLATOR_ARR_SIZE, OSCILLATOR_GPIO_PORT);

//    setup_timer();

//    float measured_freq;

//    while (1) {
//        for(int i = 0; i < GPIO_OSCILLATOR_ARR_SIZE; ++i) {
//            measured_freq = gen_chargeDischarge_cycle(GEN_CYCLES, OSCILLATOR_PINCM_ARR[i], OSCILLATOR_GPIO_NUM_ARR[i], OSCILLATOR_GPIO_PORT);
//            printf("GPIO %s Freq: %f Hz\t", OSCILLATOR_PINS_NAME[i], measured_freq);
//        }
//        printf("\n");

//        delay_cycles(system_clk_freq / 10);
//    }

//    return 0;
// }

// float gen_chargeDischarge_cycle(int initCycles, uint32_t initPINCM, uint32_t initGPIONum, GPIO_Regs * initGPIOPort) {
//    DL_GPIO_initDigitalInputFeatures(
//        initPINCM,
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
//        current_state = DL_GPIO_readPins(initGPIOPort, initGPIONum);

//        if (current_state == 0 && prev_state > 0) {
//            DL_GPIO_initDigitalInputFeatures(
//                initPINCM,
//                DL_GPIO_INVERSION_DISABLE,
//                DL_GPIO_RESISTOR_PULL_UP,
//                DL_GPIO_HYSTERESIS_DISABLE,
//                DL_GPIO_WAKEUP_DISABLE
//            );
//        }
//        else if (current_state > 0 && prev_state == 0) {
//            DL_GPIO_initDigitalInputFeatures(
//                initPINCM,
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

// void setup_timer() {
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
// }

// void initialize_oscillator_pins(const uint32_t * initPinList, uint32_t initSize, GPIO_Regs * initGPIOPort) {
//    DL_GPIO_enablePower(initGPIOPort);

//    for(int i = 0; i < initSize; ++i)
//        DL_GPIO_initDigitalInput(initPinList[i]);
// }
