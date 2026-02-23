#include <stdio.h>
#include "ti_msp_dl_config.h"

int main(void)
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

    uintptr_t GPIOB_base = 0x400A2000u;

    uintptr_t blue_offset = 0x1214u;
    volatile uint8_t *blue_pin_ptr = (volatile uint8_t *)(GPIOB_base + blue_offset + 2u);

    uintptr_t swt_offset = 0x1314u;
    volatile uint8_t *swt_pin_ptr = (volatile uint8_t *)(GPIOB_base + swt_offset + 1u);

    bool led_state = false;
    uint8_t prev = 1;
    while (1) {
        uint8_t curr = *swt_pin_ptr;

        if (curr && !prev) { led_state = !led_state; }
        
        prev = curr;
        if (led_state) {
            *blue_pin_ptr = 0x01;
        } else {
            *blue_pin_ptr = 0x00;
        }
        
    }

}
