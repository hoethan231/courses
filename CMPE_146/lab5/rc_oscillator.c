// #include "ti_msp_dl_config.h"
// #include <stdio.h>

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

//    DL_GPIO_initDigitalInput(IOMUX_PINCM26);
//    DL_GPIO_initDigitalInputFeatures(
//        IOMUX_PINCM26,
//        DL_GPIO_INVERSION_DISABLE,
//        DL_GPIO_RESISTOR_PULL_DOWN,
//        DL_GPIO_HYSTERESIS_DISABLE,
//        DL_GPIO_WAKEUP_DISABLE
//    );


//    uint8_t count = 0, oscillation_cycles = 100;
//    uint32_t current_state, prev_state = 1;


//    while (count < oscillation_cycles) {
//        current_state = DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_9);

//        if (current_state == 0 && prev_state > 0) {
//            printf("0");
//            DL_GPIO_initDigitalInputFeatures(
//                IOMUX_PINCM26,
//                DL_GPIO_INVERSION_DISABLE,
//                DL_GPIO_RESISTOR_PULL_UP,
//                DL_GPIO_HYSTERESIS_DISABLE,
//                DL_GPIO_WAKEUP_DISABLE
//            );
//        }
//        else if (current_state > 0 && prev_state == 0) {
//            printf("1");
//            DL_GPIO_initDigitalInputFeatures(
//                IOMUX_PINCM26,
//                DL_GPIO_INVERSION_DISABLE,
//                DL_GPIO_RESISTOR_PULL_DOWN,
//                DL_GPIO_HYSTERESIS_DISABLE,
//                DL_GPIO_WAKEUP_DISABLE
//            );
//            ++count;
//        }

//        prev_state = current_state;
//    }

//    return 0;
// }
