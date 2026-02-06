#include <stdio.h>
#include "ti_msp_dl_config.h"

int exercise_one_one(void)
{
    SYSCFG_DL_init();
    DL_GPIO_enablePower(GPIOB);

    DL_GPIO_initDigitalOutput(IOMUX_PINCM57); // PB26, red LED in LED2
    DL_GPIO_initDigitalOutput(IOMUX_PINCM58); // PB27, green LED in LED2
    DL_GPIO_initDigitalOutput(IOMUX_PINCM50); // PB22, blue LED in LED2
        
    DL_GPIO_initDigitalInput(IOMUX_PINCM57); // PB26, red LED
    DL_GPIO_initDigitalInput(IOMUX_PINCM58); // PB27, green LED
    DL_GPIO_initDigitalInput(IOMUX_PINCM50); // PB22, blue LED

    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_26); // PB26, red LED
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_27); // PB27, green LED
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_22); // PB22, blue LED
    
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_26);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_27);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22);

    while (1) {
        DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_22);
        delay_cycles(32000000);
        DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22);
        delay_cycles(32000000);
    }
}
