#ifndef _CAN_H
#define _CAN_H
#include "main.h"
#include "canard.h"
#include "canard_internals.h"
#include "string.h"
#include "hyp.msg.BatteryStatus_Hyp.h"
#include "hyp.msg.GetNodeInfor_Hyp.h"
#include "hyp.msg.HeartBeat_Hyp.h"
#include "stdbool.h"
void FDCan_Init(FDCAN_HandleTypeDef* fdcan);
void FDCan_Handle(void);

extern CanardInstance canard;
#endif //_CAN_H
