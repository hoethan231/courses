#include <stdio.h>
#include "ti_msp_dl_config.h"

static volatile bool led_state = false;

int control(void)
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

    DL_GPIO_setUpperPinsPolarity(GPIOB, DL_GPIO_PIN_21_EDGE_RISE_FALL);
    DL_GPIO_clearInterruptStatus(GPIOB, DL_GPIO_PIN_21);
    DL_GPIO_enableInterrupt(GPIOB, DL_GPIO_PIN_21);
    NVIC_EnableIRQ(GPIOB_INT_IRQn);

    while (1) { }
}

void GROUP1_IRQHandler(void)
{
    uint32_t interrupt_status = DL_GPIO_getEnabledInterruptStatus(GPIOB, DL_GPIO_PIN_21);

    if ((interrupt_status & DL_GPIO_PIN_21) == DL_GPIO_PIN_21)
    {
        if (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_21) & DL_GPIO_PIN_21)
        {
            led_state = !led_state;

            if (led_state) {
                DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_22);
            }
            else {
                DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_22);
            }
        }
        DL_GPIO_clearInterruptStatus(GPIOB, DL_GPIO_PIN_21);
    }
}