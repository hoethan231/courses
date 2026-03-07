#include "ti_msp_dl_config.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define FLASH_BASE_ADDRESS  (0x00004000)
#define FLASH_ALIAS_ADDRESS (0x00400000)

static uint8_t final_counter   = 0xF8;
static uint8_t initial_counter = 0xFF;

uint8_t passCounter;

volatile DL_FLASHCTL_COMMAND_STATUS gCmdStatus;

int main(void) {
    SYSCFG_DL_init();

    DL_GPIO_enablePower(GPIOB);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM57);
    DL_GPIO_initDigitalOutput(IOMUX_PINCM58);
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_26);
    DL_GPIO_enableOutput(GPIOB, DL_GPIO_PIN_27);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_26);
    DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_27);

    volatile uint8_t *flash_pointer =
        (volatile uint8_t *)(FLASH_BASE_ADDRESS + FLASH_ALIAS_ADDRESS);
    uint8_t current_count = flash_pointer[0];

    if (current_count > final_counter) {
        int8_t  right_most = current_count & -current_count;
        right_most         = ~right_most;
        uint8_t ram_byte   = current_count & right_most;

        DL_FlashCTL_unprotectSector(FLASHCTL, FLASH_BASE_ADDRESS,
                                    DL_FLASHCTL_REGION_SELECT_MAIN);
        DL_FlashCTL_programMemoryFromRAM8(FLASHCTL, FLASH_BASE_ADDRESS,
                                          &ram_byte);
        passCounter = 0;
    } else {
        passCounter = 1;
    }

    while (1) {
        if (!passCounter)
            DL_GPIO_togglePins(GPIOB, DL_GPIO_PIN_27); // Toggle green LED
        else
            DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_26);    // Toggle red LED
        delay_cycles(32000000);
    }
}