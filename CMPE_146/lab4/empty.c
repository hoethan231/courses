#include "ti_msp_dl_config.h"

#define DMA_CH0_CHAN_ID (0)

void DMA_IRQHandler(void) {
    switch (DL_DMA_getPendingInterrupt(DMA)) {
        case DL_DMA_EVENT_IIDX_DMACH0:
            dma_done = true;
            break;
        default:
            break;
    }
}

uint32_t compute_hardware_crc(uint8_t* data, uint32_t length)
{
    DL_CRC_setSeed32(CRC, CRC32_SEED);
    
    for(int i = 0; i < length; ++i) {
        DL_CRC_feedData8(CRC, data[i]);
    }
    
    return DL_CRC_getResult32(CRC);
}

int main(void) {
    SYSCFG_DL_init();

    static const DL_DMA_Config gDMA_CH0Config = {
        .transferMode = DL_DMA_SINGLE_BLOCK_TRANSFER_MODE,
        .extendedMode = DL_DMA_NORMAL_MODE,
        .destIncrement = DL_DMA_ADDR_UNCHANGED,
        .srcIncrement = DL_DMA_ADDR_INCREMENT,
        .destWidth = DL_DMA_WIDTH_BYTE,
        .srcWidth = DL_DMA_WIDTH_BYTE,
        .trigger = DMA_SOFTWARE_TRIG,
        .triggerType = DL_DMA_TRIGGER_TYPE_EXTERNAL,
    };
    DL_DMA_clearInterruptStatus(DMA, DL_DMA_INTERRUPT_CHANNEL0);
    DL_DMA_enableInterrupt(DMA, DL_DMA_INTERRUPT_CHANNEL0);
    DL_DMA_initChannel(DMA, DMA_CH0_CHAN_ID , (DL_DMA_Config *) &gDMA_CH0Config);
    NVIC_EnableIRQ(DMA_INT_IRQn);

    DL_DMA_setSrcAddr(DMA, DMA_CH0_CHAN_ID, (uint32_t)&myData[0]);
    DL_DMA_setDestAddr(DMA, DMA_CH0_CHAN_ID, DL_CRC_getCRCINAddr(CRC));
    DL_DMA_setTransferSize(DMA, DMA_CH0_CHAN_ID, DATA_SIZE);
    DL_DMA_enableChannel(DMA, DMA_CH0_CHAN_ID);
    DL_CRC_setSeed32(CRC, CRC32_SEED);
    dma_done = false;
    DL_DMA_startTransfer(DMA, DMA_CH0_CHAN_ID);

    volatile bool dma_done;

    while (1) {
    }
}
