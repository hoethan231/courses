#include "ti_msp_dl_config.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define FLASH_BASE_ADDRESS  (0x00004000)
#define FLASH_ALIAS_ADDRESS (0x00400000)

volatile DL_FLASHCTL_COMMAND_STATUS gCmdStatus;

int main(void) {
    SYSCFG_DL_init();

    DL_FlashCTL_unprotectSector(FLASHCTL, FLASH_BASE_ADDRESS,
                                DL_FLASHCTL_REGION_SELECT_MAIN);
    gCmdStatus = DL_FlashCTL_eraseMemoryFromRAM(FLASHCTL, FLASH_BASE_ADDRESS,
                                                DL_FLASHCTL_COMMAND_SIZE_SECTOR);
    if (gCmdStatus == DL_FLASHCTL_COMMAND_STATUS_FAILED) {
        __BKPT(0);
    }

    _Alignas(DL_FLASHCTL_SECTOR_SIZE) const uint8_t flash_data[] = {0xff};

    volatile uint8_t *flash_pointer =
        (volatile uint8_t *)(FLASH_BASE_ADDRESS + FLASH_ALIAS_ADDRESS);

    for (int i = 0; i < 8; ++i) {
        uint8_t updated_data = (uint8_t)(flash_data[0] & ~(1u << i));

        DL_FlashCTL_unprotectSector(FLASHCTL, FLASH_BASE_ADDRESS,
                                    DL_FLASHCTL_REGION_SELECT_MAIN);
        gCmdStatus = DL_FlashCTL_programMemoryFromRAM8(FLASHCTL,
                                                       FLASH_BASE_ADDRESS,
                                                       &updated_data);
        if (gCmdStatus == DL_FLASHCTL_COMMAND_STATUS_FAILED) {
            __BKPT(0);
        }

        printf("Flash alias 0x%x contents: %x %x %x %x %x %x %x %x\n",
               FLASH_BASE_ADDRESS + FLASH_ALIAS_ADDRESS,
               flash_pointer[0], flash_pointer[1], flash_pointer[2], flash_pointer[3],
               flash_pointer[4], flash_pointer[5], flash_pointer[6], flash_pointer[7]);
    }
}