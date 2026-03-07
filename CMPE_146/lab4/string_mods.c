#include "ti_msp_dl_config.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

char* string1 = "xyz123";
char  string2[] = "xyz123";

void main(void) {
    SYSCFG_DL_init();

    printf("Initial string1: %s\n", string1);
    printf("Initial string2: %s\n", string2);

    string1[0] = '0';
    string2[0] = '0';

    printf("After modify - string1: %s\n", string1);
    printf("After modify - string2: %s\n", string2);
}