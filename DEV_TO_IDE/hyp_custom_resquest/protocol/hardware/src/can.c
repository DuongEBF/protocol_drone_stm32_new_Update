#include "can.h"
uint16_t v;
int16_t i;
uint8_t heartbeat_transfer_id = 0;
uint8_t batteryinfo_transfer_id = 0;
hyp_can_packet_t* hyp_handle;
//----------------------driver_read-------------------//
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    if (hyp_handle->hyp_can_GetRxMessage(hcan, CAN_RX_FIFO0, &hyp_handle->rxHeader, hyp_handle->rxData) == HAL_OK)
    {
        hyp_handle->frame.id = hyp_handle->rxHeader.ExtId;
        if (hyp_handle->rxHeader.IDE == CAN_ID_EXT)
        	hyp_handle->frame.id |= (1UL << 31);

        hyp_handle->frame.data_len = hyp_handle->rxHeader.DLC;
        memcpy(hyp_handle->frame.data, hyp_handle->rxData, hyp_handle->rxHeader.DLC);
        hyp_handle->frame.iface_id = 0;

        hyp_handle->hyp_canardHandleRxframe(&hyp_handle->canard, &hyp_handle->frame, HAL_GetTick() * 1000ULL);
    }
}

bool should_accept(const CanardInstance* ins, uint64_t* out_sig, uint16_t data_type_id,
                   CanardTransferType transfer_type, uint8_t source_node_id)
{
    if (data_type_id == 232 && transfer_type == CanardTransferTypeResponse)
    {
        *out_sig = HYP_MSG_BATTERYSTATUS_HYP_SIGNATURE;
        return true;
    }
    return false;
}

void on_reception(CanardInstance* ins, CanardRxTransfer* transfer)
{
	if (transfer->data_type_id == 232 && transfer->transfer_type == CanardTransferTypeResponse)
	{
		struct hyp_msg_BatteryStatus_Hyp resp;
		hyp_msg_BatteryStatus_Hyp_decode(transfer, &resp);
		char buff_resp[50] = {0};
		memcpy(buff_resp, resp.name.data, resp.name.len);
		if(strcmp(buff_resp, "HYPMOTION_BATT1") == 0)
		{
			v = resp.voltage;
			i = resp.current;
		}
	}
}
static void send_heartbeat(CanardInstance* ins, uint8_t* transfer_id, uint32_t uptime_sec)
{
	struct hyp_msg_HeartBeat_Hyp hb;
    hb.uptime_sec = uptime_sec;
    hb.health = HYP_MSG_HEARTBEAT_HYP_HEALTH_OK;
    hb.mode = HYP_MSG_HEARTBEAT_HYP_MODE_OPERATIONAL;
    hb.sub_mode = 0;
    hb.vendor_specific_status_code = 0;
    uint8_t buff[HYP_MSG_HEARTBEAT_HYP_MAX_SIZE];
    uint32_t len = hyp_msg_HeartBeat_Hyp_encode(&hb, buff
#if CANARD_ENABLE_TAO_OPTION
        , true
#endif
    );
    hyp_handle->hyp_canardBroadcast(
									ins,
									HYP_MSG_HEARTBEAT_HYP_SIGNATURE,
									HYP_MSG_HEARTBEAT_HYP_ID,
									transfer_id,
									CANARD_TRANSFER_PRIORITY_LOW,
									buff,
									len
    );
}

static void send_batteryinfo_request(CanardInstance* ins, uint8_t* transfer_id, uint8_t node_id)
{
	struct hyp_msg_BatteryStatus_Hyp msg;
	memset(&msg, 0, sizeof(msg));

	msg.name.len = strlen("Get_batt");
	memcpy(msg.name.data, "Get_batt", msg.name.len);

	uint8_t buffer[HYP_MSG_BATTERYSTATUS_HYP_MAX_SIZE];
	uint32_t len = hyp_msg_BatteryStatus_Hyp_encode(&msg, buffer
#if CANARD_ENABLE_TAO_OPTION
        , true
#endif
    );
	hyp_handle->hyp_canardRequestOrRespond(
											ins,
											node_id,
											HYP_MSG_BATTERYSTATUS_HYP_SIGNATURE,
											HYP_MSG_BATTERYSTATUS_HYP_ID,
											transfer_id,
											CANARD_TRANSFER_PRIORITY_LOW,
											CanardRequest,
											buffer,
											len
	);
}
//-------------driver_send---------------//
static void tx_frame(void)
{
	hyp_handle->txf = NULL;
	while ((hyp_handle->txf = hyp_handle->hyp_canardPeekTxQueue(&hyp_handle->canard)) != NULL)
	{
		if (hyp_handle->hyp_can_GetTxMailboxesFreeLevel(hyp_handle->can_src) > 0)
		{
			memset(&hyp_handle->txHeader, 0, sizeof(hyp_handle->txHeader));
			hyp_handle->txHeader.IDE = CAN_ID_EXT;
			hyp_handle->txHeader.ExtId = hyp_handle->txf->id & 0x1FFFFFFF;
			hyp_handle->txHeader.RTR = CAN_RTR_DATA;
			hyp_handle->txHeader.DLC = hyp_handle->txf->data_len;
			hyp_handle->txHeader.TransmitGlobalTime = DISABLE;

			uint32_t txMailbox;
			if (hyp_handle->hyp_can_AddTxMessage(hyp_handle->can_src, &hyp_handle->txHeader, (uint8_t*)hyp_handle->txf->data, &txMailbox) == HAL_OK)
			{
					hyp_handle->hyp_canardPopTxQueue(&hyp_handle->canard);
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
	hyp_handle->sFilterConfig.FilterBank = 0;
	hyp_handle->sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
	hyp_handle->sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
	hyp_handle->sFilterConfig.FilterIdHigh = 0;
	hyp_handle->sFilterConfig.FilterIdLow  = 0;
	hyp_handle->sFilterConfig.FilterMaskIdHigh = 0;
	hyp_handle->sFilterConfig.FilterMaskIdLow  = 0;
	hyp_handle->sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	hyp_handle->sFilterConfig.FilterActivation = ENABLE;
	hyp_handle->hyp_can_ConfigFilter(hyp_handle->can_src, &hyp_handle->sFilterConfig);
}
void Can_Init(CAN_HandleTypeDef* hcan, hyp_can_packet_t* hyp_can)
{
	hyp_handle = hyp_can;
	hyp_handle->can_src = hcan;
	hyp_handle->hyp_can_GetRxMessage =             HAL_CAN_GetRxMessage;
	hyp_handle->hyp_canardHandleRxframe =          canardHandleRxFrame;
	hyp_handle->hyp_can_Start =                    HAL_CAN_Start;
	hyp_handle->hyp_can_ActivateNotification =     HAL_CAN_ActivateNotification;
	hyp_handle->hyp_canardInit =                   canardInit;
	hyp_handle->hyp_canardSetLocalNodeID =         canardSetLocalNodeID;
	hyp_handle->hyp_can_ConfigFilter =             HAL_CAN_ConfigFilter;
	hyp_handle->hyp_canardPeekTxQueue =            canardPeekTxQueue;
	hyp_handle->hyp_can_GetTxMailboxesFreeLevel =  HAL_CAN_GetTxMailboxesFreeLevel;
	hyp_handle->hyp_can_AddTxMessage =             HAL_CAN_AddTxMessage;
	hyp_handle->hyp_canardPopTxQueue =             canardPopTxQueue;
	hyp_handle->hyp_canardBroadcast = 			   canardBroadcast;
	hyp_handle->hyp_canardRequestOrRespond =       canardRequestOrRespond;


	hyp_handle->hyp_can_Start(hyp_handle->can_src);
	hyp_handle->hyp_can_ActivateNotification(hyp_handle->can_src, CAN_IT_RX_FIFO0_MSG_PENDING);
	hyp_handle->hyp_canardInit(&hyp_handle->canard,
							hyp_handle->canard_memory_pool,
							sizeof(hyp_handle->canard_memory_pool),
							on_reception,
							should_accept,
							NULL);
	hyp_handle->hyp_canardSetLocalNodeID(&hyp_handle->canard, 15);
	config_filter();
}


void Can_Handle(void)
{
	static uint32_t last_heartbeat_tick = 0;
	static uint32_t last_battinfo_tick = 0;
	if (HAL_GetTick() - last_heartbeat_tick >= 1000)
	{
		last_heartbeat_tick = HAL_GetTick();
		send_heartbeat(&hyp_handle->canard, &heartbeat_transfer_id, HAL_GetTick()/1000);
	}
	if (HAL_GetTick() - last_battinfo_tick >= 100)
	{
		last_battinfo_tick = HAL_GetTick();
		send_batteryinfo_request(&hyp_handle->canard, &batteryinfo_transfer_id, 11);
	}
	tx_frame();
}
