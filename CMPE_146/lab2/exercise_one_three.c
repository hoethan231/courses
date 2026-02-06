#include <stdio.h>
#include "ti_msp_dl_config.h"

int exercise_one_three(void)
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

    uintptr_t GPIOB_base = 0x400A2000u;
    uintptr_t offset = 0x1214u;
    uintptr_t pin_addy = GPIOB_base + offset;

    volatile uint8_t *pin_ptr = (volatile uint8_t *)(pin_addy + 2u);

    printf("Alias Address: 0x%08X", pin_addy);

    uint8_t state = 0;
    while (1) {
        state ^= 1u;
        *pin_ptr = state;
        delay_cycles(32000000);
    }

}
