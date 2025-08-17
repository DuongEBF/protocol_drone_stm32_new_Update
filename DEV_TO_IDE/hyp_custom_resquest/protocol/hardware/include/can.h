#ifndef _CAN_H
#define _CAN_H
#include "main.h"
#include "canard.h"
#include "canard_internals.h"
#include "string.h"
#include "hyp.msg.BatteryStatus_Hyp.h"
#include "hyp.msg.GetNodeInfor_Hyp.h"
#include "hyp.msg.HeartBeat_Hyp.h"
#define MEMORY_MAX_SIZE   1024
typedef struct
{
	//can_driver
	CAN_HandleTypeDef*     can_src;
	uint8_t                rxData[8];
	CAN_RxHeaderTypeDef    rxHeader;
	CAN_TxHeaderTypeDef    txHeader;
	CAN_FilterTypeDef 	   sFilterConfig;
	HAL_StatusTypeDef      (*hyp_can_GetRxMessage)(CAN_HandleTypeDef *hcan, uint32_t RxFifo,
            									   CAN_RxHeaderTypeDef *pHeader, uint8_t aData[]);
	HAL_StatusTypeDef      (*hyp_can_Start)(CAN_HandleTypeDef *hcan);
	HAL_StatusTypeDef      (*hyp_can_ActivateNotification)(CAN_HandleTypeDef *hcan, uint32_t ActiveITs);
	HAL_StatusTypeDef      (*hyp_can_ConfigFilter)(CAN_HandleTypeDef *hcan, const CAN_FilterTypeDef *sFilterConfig);
	uint32_t               (*hyp_can_GetTxMailboxesFreeLevel)(const CAN_HandleTypeDef *hcan);
	HAL_StatusTypeDef      (*hyp_can_AddTxMessage)(CAN_HandleTypeDef *hcan, const CAN_TxHeaderTypeDef *pHeader,
            										const uint8_t aData[], uint32_t *pTxMailbox);






	//canard_middleware
	CanardCANFrame*        txf;
	CanardCANFrame         frame;
	int16_t                (*hyp_canardHandleRxframe)(CanardInstance* ins, const CanardCANFrame* frame, uint64_t timestamp_usec);
	uint8_t                canard_memory_pool[MEMORY_MAX_SIZE];
	CanardInstance         canard;

	void                   (*hyp_canardInit)(CanardInstance* out_ins,
											void* mem_arena,
											size_t mem_arena_size,
											CanardOnTransferReception on_reception,
											CanardShouldAcceptTransfer should_accept,
											void* user_reference);
	void                   (*hyp_canardSetLocalNodeID)(CanardInstance* ins, uint8_t self_node_id);
	CanardCANFrame*        (*hyp_canardPeekTxQueue)(const CanardInstance* ins);
	void                   (*hyp_canardPopTxQueue)(CanardInstance* ins);
	int16_t                (*hyp_canardBroadcast)(CanardInstance* ins,
													uint64_t data_type_signature,
													uint16_t data_type_id,
													uint8_t* inout_transfer_id,
													uint8_t priority,
													const void* payload,
													uint16_t payload_len);
	int16_t                (*hyp_canardRequestOrRespond)(CanardInstance* ins,
														uint8_t destination_node_id,
														uint64_t data_type_signature,
														uint16_t data_type_id,
														uint8_t* inout_transfer_id,
														uint8_t priority,
														CanardRequestResponse kind,
														const void* payload,
														uint16_t payload_len);
}hyp_can_packet_t;
void Can_Init(CAN_HandleTypeDef* hcan, hyp_can_packet_t* hyp_can);
void Can_Handle(void);
extern uint16_t v;
extern int16_t i;
#endif //_CAN_H
