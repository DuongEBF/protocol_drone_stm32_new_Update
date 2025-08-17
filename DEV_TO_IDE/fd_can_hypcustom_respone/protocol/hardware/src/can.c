#include "can.h"
FDCAN_HandleTypeDef* fdcan_src;
uint8_t canard_memory_pool[1024];
CanardInstance canard;
struct hyp_msg_BatteryStatus_Hyp req;

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t filterIndex)
{
	FDCAN_RxHeaderTypeDef rxHeader;
	uint8_t rxData[8];
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

bool should_accept(const CanardInstance* ins, uint64_t* out_sig, uint16_t data_type_id,
                   CanardTransferType transfer_type, uint8_t source_node_id) {
    if (data_type_id == 232 && transfer_type == CanardTransferTypeRequest) {
        *out_sig = HYP_MSG_BATTERYSTATUS_HYP_SIGNATURE;
        return true;
    }
    return false;
}

void on_reception(CanardInstance* ins, CanardRxTransfer* transfer)
{
	if (transfer->data_type_id == 232 && transfer->transfer_type == CanardTransferTypeRequest)
	{
		hyp_msg_BatteryStatus_Hyp_decode(transfer,&req);
		if (strncmp((char*)req.name.data, "Get_batt", req.name.len) == 0)
		{
			struct hyp_msg_BatteryStatus_Hyp value;
			value.current = 4;
			value.voltage = 22;
			value.name.len = strlen("HYPMOTION_BATT1");
			memcpy(value.name.data, "HYPMOTION_BATT1", value.name.len);
			uint8_t buffer[HYP_MSG_BATTERYSTATUS_HYP_MAX_SIZE];
			uint32_t len = hyp_msg_BatteryStatus_Hyp_encode(&value, buffer
#if CANARD_ENABLE_TAO_OPTION
		, true
#endif
		    );
			uint8_t tid = transfer->transfer_id;
			canardRequestOrRespond(&canard, transfer->source_node_id,
					HYP_MSG_BATTERYSTATUS_HYP_SIGNATURE,
					HYP_MSG_BATTERYSTATUS_HYP_ID,
					&tid, CANARD_TRANSFER_PRIORITY_LOW,
					CanardResponse, buffer, len);
		}
	}
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
    if (HAL_FDCAN_ConfigFilter(fdcan_src, &sFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }

    sFilterConfig.IdType = FDCAN_EXTENDED_ID;
    sFilterConfig.FilterIndex = 1;
    sFilterConfig.FilterType = FDCAN_FILTER_MASK;
    sFilterConfig.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
    sFilterConfig.FilterID1 = 0x00000000;
    sFilterConfig.FilterID2 = 0x00000000;
    if (HAL_FDCAN_ConfigFilter(fdcan_src, &sFilterConfig) != HAL_OK)
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
        if ((fdcan_src->Instance->TXFQS & FDCAN_TXFQS_TFQF) == 0) // TX FIFO not full
        {
            txHeader.Identifier = txf->id & 0x1FFFFFFF;
            txHeader.IdType = FDCAN_EXTENDED_ID;
            txHeader.TxFrameType = FDCAN_DATA_FRAME;
            txHeader.DataLength = txf->data_len;
            txHeader.FDFormat = FDCAN_CLASSIC_CAN;
            txHeader.BitRateSwitch = FDCAN_BRS_OFF;
            txHeader.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
            txHeader.MessageMarker = 0;

            if (HAL_FDCAN_AddMessageToTxFifoQ(fdcan_src, &txHeader, (uint8_t*)txf->data) == HAL_OK)
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

void FDCan_Init(FDCAN_HandleTypeDef* fdcan)
{
    fdcan_src = fdcan;

    // Init CAN hardware
    HAL_FDCAN_Start(fdcan_src);
    HAL_FDCAN_ActivateNotification(fdcan_src, FDCAN_IT_RX_FIFO0_NEW_MESSAGE, 0);
    config_fdcan_filter_all();

    // Init libcanard
    canardInit(&canard,
				canard_memory_pool,
				sizeof(canard_memory_pool),
				on_reception,
				should_accept,
				NULL);
    canardSetLocalNodeID(&canard, 11);
}

void FDCan_Handle(void)
{
	FDCan_tx_frame();
}
