/*
 * can.c
 *
 *  Created on: Aug 6, 2025
 *      Author: duong
 */
#include "can.h"
CAN_HandleTypeDef* can;
uint8_t canard_memory_pool[2048];
CanardInstance canard;
#define STRUCT_SIZE 68
#define BLOCK_SIZE 16
#define PADDED_SIZE (((STRUCT_SIZE + BLOCK_SIZE - 1) / BLOCK_SIZE) * BLOCK_SIZE)  //80byte
const uint8_t key[16] = {
    0x2b, 0x7e, 0x15, 0x16,
    0x28, 0xae, 0xd2, 0xa6,
    0xab, 0xf7, 0x05, 0x03,
    0x2b, 0x7e, 0x15, 0x16
};

struct AES_ctx ctx;
struct hyp_msg_BatteryStatus_Hyp batt_transmit;
int ret;
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxHeaderTypeDef rxHeader;
    uint8_t rxData[8];
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK) {
        CanardCANFrame frame;
        frame.id = rxHeader.ExtId;
        if (rxHeader.IDE == CAN_ID_EXT)
            frame.id |= (1UL << 31);

        frame.data_len = rxHeader.DLC;
        memcpy(frame.data, rxData, rxHeader.DLC);
        frame.iface_id = 0;

        canardHandleRxFrame(&canard, &frame, HAL_GetTick() * 1000ULL);
    }
}
void tx_frame(void)
{
	CanardCANFrame* txf = NULL;
	while ((txf = canardPeekTxQueue(&canard)) != NULL)
	{
			if (HAL_CAN_GetTxMailboxesFreeLevel(can) > 0)
			{
					CAN_TxHeaderTypeDef txHeader;
					memset(&txHeader, 0, sizeof(txHeader));
					txHeader.IDE = CAN_ID_EXT;
					txHeader.ExtId = txf->id & 0x1FFFFFFF;
					txHeader.RTR = CAN_RTR_DATA;
					txHeader.DLC = txf->data_len;
					txHeader.TransmitGlobalTime = DISABLE;

					uint32_t txMailbox;
					if (HAL_CAN_AddTxMessage(can, &txHeader, (uint8_t*)txf->data, &txMailbox) == HAL_OK)
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
	HAL_Delay(1);
}
static void config_filter(void)
{
		//------------filer-------------//
	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterBank = 0;
	sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterIdHigh = 0;
	sFilterConfig.FilterIdLow  = 0;
	sFilterConfig.FilterMaskIdHigh = 0;
	sFilterConfig.FilterMaskIdLow  = 0;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	sFilterConfig.FilterActivation = ENABLE;
	HAL_CAN_ConfigFilter(can, &sFilterConfig);
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
				break;
			}
		}
	}
}

static void send_payload_batt_aes(CanardInstance *ins)
{
	struct hyp_aes_Encryption_Hyp cryp;
	uint8_t data[PADDED_SIZE] = {0};

	batt_transmit.current = 2;
	batt_transmit.voltage = 24;
	batt_transmit.state_of_charge_percent = 77;
	batt_transmit.name.len = strlen("HYPMOTION_PACK1");
	memcpy(batt_transmit.name.data, "HYPMOTION_PACK1", batt_transmit.name.len);
	memcpy(data, &batt_transmit, STRUCT_SIZE);

	for (int i = 0; i < PADDED_SIZE; i += BLOCK_SIZE)
	{
	    AES_ECB_encrypt(&ctx, data + i);
	}
	memcpy(cryp.payload_ciphertext_tiny, data, PADDED_SIZE);
	uint8_t buff[HYP_AES_ENCRYPTION_HYP_MAX_SIZE];
	uint32_t len = hyp_aes_Encryption_Hyp_encode(&cryp, buff);
	static uint8_t trans_id = 0;
	ret = canardBroadcast(ins,
					HYP_AES_ENCRYPTION_HYP_SIGNATURE,
					HYP_AES_ENCRYPTION_HYP_ID,
					&trans_id,
					CANARD_TRANSFER_PRIORITY_LOW,
					buff,
					len);
}


void can_init(CAN_HandleTypeDef* hcan1)
{
	can = hcan1;
	HAL_CAN_Start(can);
	HAL_CAN_ActivateNotification(can, CAN_IT_RX_FIFO0_MSG_PENDING);
	canardInit(&canard,
				canard_memory_pool,
				sizeof(canard_memory_pool),
				on_reception,
				should_accept,
				NULL);
	canardSetLocalNodeID(&canard, 15);
	config_filter();
	AES_init_ctx(&ctx, key);
}
void can_handle(void)
{
	static uint32_t last_send = 0;
	if(HAL_GetTick() - last_send > 100)
	{
		send_payload_batt_aes(&canard);
		last_send = HAL_GetTick();
	}
	tx_frame();
}


