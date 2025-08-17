/*
 * can.h
 *
 *  Created on: Aug 6, 2025
 *      Author: duong
 */

#ifndef CAN_H_
#define CAN_H_
#include "main.h"
#include "canard.h"
#include "canard_internals.h"
#include "hyp.aes.Encryption_Hyp.h"
#include "hyp.msg.BatteryStatus_Hyp.h"
#include "string.h"
#include "aes.h"
#include <stdio.h>
void can_init(CAN_HandleTypeDef* hcan1);
void can_handle(void);

#endif /* CAN_H_ */
