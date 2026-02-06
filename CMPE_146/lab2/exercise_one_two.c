#include <stdio.h>
#include "ti_msp_dl_config.h"

int exercise_one_two(void)
{
    SYSCFG_DL_init();
    DL_GPIO_enablePower(GPIOB);

    DL_GPIO_initDigitalOutput(IOMUX_PINCM57);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM58);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM50);
        
    DL_GPIO_initDigitalInput(IOMUX_PINCM57);
    DL_GPIO_initDigitalInput(IOMUX_PINCM58);
    DL_GPIO_initDigitalInput(IOMUX_PINCM50);

    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_26);
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_27);
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_22);
    
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_26);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_27);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22);

    volatile uint32_t *data_output_ptr = (volatile uint32_t *) 0x1280;
    volatile uint32_t *GPIOB_ptr = (volatile uint32_t *) 0x400A2000;

    uintptr_t pin_addy = (uintptr_t)data_output_ptr + (uintptr_t)GPIOB_ptr;
    volatile uint32_t *pin_ptr = (volatile uint32_t *)pin_addy;
    
    while (1) {
        *pin_ptr |= (1UL << 22);
        delay_cycles(32000000);
        *pin_ptr &= ~(1UL << 22);
        delay_cycles(32000000);
    }
}
