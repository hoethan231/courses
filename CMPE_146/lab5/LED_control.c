#include "ti_msp_dl_config.h"
#include <stdio.h>

#define OSCILLATOR_PINCM  IOMUX_PINCM26
#define OSCILLATOR_GPIO_NUM  DL_GPIO_PIN_9
#define OSCILLATOR_GPIO_PORT  GPIOB

const float system_clk_freq = 32000000;
const static int gen_cycles = 10;
const int calibration_iter = 10; 
float cal_default_frequency;
const float threshold_sensitivity = 0.85;
const float default_sensitivity = 0.9;

const uint32_t LED1_base_address = 0x400A0000;
const uint16_t DOUT3_0_offset = 0x1200;

struct delta_time {
   uint32_t initial_timestamp;
   uint32_t final_timestamp;
};

float gen_chargeDischarge_cycle(int initCycles);

float calibrate_capacitive_touch(int initGenCycles, int initIterations);

int main(void) {
   SYSCFG_DL_init();
   DL_GPIO_enablePower(GPIOB);
   DL_GPIO_enablePower(GPIOA);

   DL_GPIO_initDigitalOutputFeatures(
       IOMUX_PINCM1,
       DL_GPIO_INVERSION_ENABLE,
       DL_GPIO_RESISTOR_NONE,
       DL_GPIO_DRIVE_STRENGTH_LOW,
       DL_GPIO_HIZ_DISABLE
   );
   DL_GPIO_enableOutput(GPIOA, DL_GPIO_PIN_0);
   DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_0);

   DL_GPIO_initDigitalInput(OSCILLATOR_PINCM);
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

   cal_default_frequency = calibrate_capacitive_touch(gen_cycles, calibration_iter);
   printf("Calibrated (default) Frequency: %f Hz\n", cal_default_frequency);

   uint16_t led_state = 0x0;
   float current_frequency, prev_frequency;
   float threshold_frequency = cal_default_frequency * threshold_sensitivity;
   float default_frequency = cal_default_frequency * default_sensitivity;
   volatile uint8_t * p_red_LED1 = (volatile uint8_t *)(LED1_base_address + DOUT3_0_offset + 0);

   while (1) {
       current_frequency = gen_chargeDischarge_cycle(gen_cycles);
       printf("Current Frequency: %f\n", current_frequency);

       if(current_frequency <= threshold_frequency && prev_frequency > default_frequency) led_state = ~led_state;
       prev_frequency = current_frequency;
      
       if (led_state)
           *(p_red_LED1) = 0x1;
       else
           *(p_red_LED1) = 0x0;
   }
}

float gen_chargeDischarge_cycle(int initCycles) {
   DL_GPIO_initDigitalInputFeatures(
       OSCILLATOR_PINCM,
       DL_GPIO_INVERSION_DISABLE,
       DL_GPIO_RESISTOR_PULL_DOWN,
       DL_GPIO_HYSTERESIS_DISABLE,
       DL_GPIO_WAKEUP_DISABLE
   );

   uint8_t count = 0;
   uint32_t current_state, prev_state = 1;
   struct delta_time time;
   float calculated_time;


   time.initial_timestamp = DL_Timer_getTimerCount(TIMG12);


   while (count < initCycles) {
       current_state = DL_GPIO_readPins(OSCILLATOR_GPIO_PORT, OSCILLATOR_GPIO_NUM);

       if (current_state == 0 && prev_state > 0) {
           DL_GPIO_initDigitalInputFeatures(
               OSCILLATOR_PINCM,
               DL_GPIO_INVERSION_DISABLE,
               DL_GPIO_RESISTOR_PULL_UP,
               DL_GPIO_HYSTERESIS_DISABLE,
               DL_GPIO_WAKEUP_DISABLE
           );
       }
       else if (current_state > 0 && prev_state == 0) {
           DL_GPIO_initDigitalInputFeatures(
               OSCILLATOR_PINCM,
               DL_GPIO_INVERSION_DISABLE,
               DL_GPIO_RESISTOR_PULL_DOWN,
               DL_GPIO_HYSTERESIS_DISABLE,
               DL_GPIO_WAKEUP_DISABLE
           );
           ++count;
       }


       prev_state = current_state;
   }

   time.final_timestamp = DL_Timer_getTimerCount(TIMG12);
   calculated_time = (time.final_timestamp - time.initial_timestamp) * (1 / system_clk_freq); 
   calculated_time = initCycles / calculated_time;


   return calculated_time;
}

float calibrate_capacitive_touch(int initGenCycles, int initIterations) {
   float sum_frequency = 0, current_frequency;

   int count = 0;
   while(1) {
       if(count++ == initIterations) break;
       current_frequency = gen_chargeDischarge_cycle(initGenCycles);
       sum_frequency = sum_frequency + current_frequency;
   }

   return sum_frequency / initIterations;
}
