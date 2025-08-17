/*
 * can.c
 *
 *  Created on: Aug 6, 2025
 *      Author: duong
 */
#include "can.h"
uint8_t canard_memory_pool[2048];
CanardInstance canard;
FDCAN_HandleTypeDef* hfdcan;

#define STRUCT_SIZE 68
#define BLOCK_SIZE 16
#define PADDED_SIZE (((STRUCT_SIZE + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE) //80byte


const uint8_t key[16] = {
    0x2b, 0x7e, 0x15, 0x16,
    0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x05, 0x03,
    0x2b, 0x7e, 0x15, 0x16
};
//const uint8_t key[16] = {
//    0x2b, 0x7e, 0x15, 0x16,
//    0x28, 0xae, 0xd2, 0xa6,
//    0xab, 0xf7, 0x05, 0x03,
//    0x1b, 0x7e, 0x15, 0x16
//};
struct AES_ctx ctx;
struct hyp_msg_BatteryStatus_Hyp batt_infor;
uint32_t count = 0;


void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t filterIndex)
{
	FDCAN_RxHeaderTypeDef rxHeader;
	uint8_t rxData[8];
	count++;
	if (HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &rxHeader, rxData) != HAL_OK)
			return;
	CanardCANFrame frame;
	frame.id = rxHeader.Identifier;
	if (rxHeader.IdType == FDCAN_EXTENDED_ID)
			frame.id |= (1UL << 31); // set extended bit
	frame.data_len = rxHeader.DataLength;
	if (frame.data_len > 8) frame.data_len = 8;

	memcpy(frame.data, rxData, frame.data_len);
	frame.iface_id = 0;

	canardHandleRxFrame(&canard, &frame, HAL_GetTick() * 1000ULL);
}

static void config_fdcan_filter_all(void)
{
    FDCAN_FilterTypeDef sFilterConfig;

    sFilterConfig.IdType = FDCAN_STANDARD_ID;
    sFilterConfig.FilterIndex = 0;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x000;
    sFilterConfig.FilterID2 = 0x000;
    if (HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    sFilterConfig.IdType = FDCAN_EXTENDED_ID;
    sFilterConfig.FilterIndex = 1;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x00000000;
    sFilterConfig.FilterID2 = 0x00000000;
    if (HAL_FDCAN_ConfigFilter(hfdcan, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

static void FDCan_tx_frame(void)
{
    const CanardCANFrame* txf;
    while ((txf = canardPeekTxQueue(&canard)) != NULL)
    {
    	FDCAN_TxHeaderTypeDef txHeader;
        if ((hfdcan->Instance->TXFQS & FDCAN_TXFQS_TFQF) == 0) // TX FIFO not full
        {
            txHeader.Identifier = txf->id & 0x1FFFFFFF;
            txHeader.IdType = FDCAN_EXTENDED_ID;
            txHeader.TxFrameType = FDCAN_DATA_FRAME;
            txHeader.DataLength = txf->data_len;
            txHeader.FDFormat = FDCAN_CLASSIC_CAN;
            txHeader.BitRateSwitch = FDCAN_BRS_OFF;
            txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
            txHeader.MessageMarker = 0;

            if (HAL_FDCAN_AddMessageToTxFifoQ(hfdcan, &txHeader, (uint8_t*)txf->data) == HAL_OK)
            {
                canardPopTxQueue(&canard);
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}

static void handle_AES_Allocation(CanardInstance *ins, CanardRxTransfer *transfer)
{
	uint8_t data[PADDED_SIZE] = {0};
	struct hyp_aes_Encryption_Hyp pkt;
	hyp_aes_Encryption_Hyp_decode(transfer, &pkt);


	memcpy(data, pkt.payload_ciphertext_tiny, PADDED_SIZE);
	for (int i = 0; i < PADDED_SIZE; i += BLOCK_SIZE)
	{
	    AES_ECB_decrypt(&ctx, data + i);
	}
	memcpy(&batt_infor, data, STRUCT_SIZE);
	if (batt_infor.name.len == strlen("HYPMOTION_PACK1") &&
		memcmp(batt_infor.name.data, "HYPMOTION_PACK1", batt_infor.name.len) == 0)
	{
	}
}



static bool should_accept(const CanardInstance *ins, uint64_t *out_data_type_signature,
								uint16_t data_type_id,
                                CanardTransferType transfer_type,
                                uint8_t source_node_id)
{
	if (transfer_type == CanardTransferTypeBroadcast)
	{
		switch (data_type_id)
		{
		 // see if we want to handle a specific broadcast packet
			case HYP_AES_ENCRYPTION_HYP_ID:
			{
				*out_data_type_signature = HYP_AES_ENCRYPTION_HYP_SIGNATURE;
				return true;
			}
		}
	}
    // we don't want any other messages
    return false;
}
static void on_reception(CanardInstance *ins, CanardRxTransfer *transfer)
{
	if (transfer->transfer_type == CanardTransferTypeBroadcast)
	{
		switch (transfer->data_type_id)
		{
			case HYP_AES_ENCRYPTION_HYP_ID:
			{
				handle_AES_Allocation(ins, transfer);
				break;
			}
		}
	}
}
void fdcan_init(FDCAN_HandleTypeDef* hfdcan1)
{
	hfdcan = hfdcan1;
    // Init CAN hardware
    HAL_FDCAN_Start(hfdcan);
    HAL_FDCAN_ActivateNotification(hfdcan, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
    config_fdcan_filter_all();

    // Init libcanard
    canardInit(&canard,
				canard_memory_pool,
				sizeof(canard_memory_pool),
				on_reception,
				should_accept,
				NULL);
    canardSetLocalNodeID(&canard, 11);
    AES_init_ctx(&ctx, key);
}


void fdcan_handle(void)
{
	FDCan_tx_frame();
}
