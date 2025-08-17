/*
 * mavlink_from_tobufi.h
 *
 *  Created on: Aug 13, 2025
 *      Author: duong
 */

#ifndef MAVLINK_FROM_TOBUFI_H_
#define MAVLINK_FROM_TOBUFI_H_
#include "../../MAVLink_Custom/hypmotion_mavlink_custom/mavlink.h"
typedef struct
{
	mavlink_message_t rx_msg;
	mavlink_status_t status;
	mavlink_chargingdock_bms_t char_infor;
}mavlink_from_tobufi_t;
void mavlink_process_tbf(mavlink_from_tobufi_t* char_infor);
void mavlink_init_tbf(void);
#endif /* MAVLINK_FROM_TOBUFI_H_ */
