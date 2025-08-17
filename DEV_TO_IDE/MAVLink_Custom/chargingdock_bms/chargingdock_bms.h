/** @file
 *  @brief MAVLink comm protocol generated from chargingdock_bms.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_CHARGINGDOCK_BMS_H
#define MAVLINK_CHARGINGDOCK_BMS_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_CHARGINGDOCK_BMS.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_CHARGINGDOCK_BMS_XML_HASH 721286532428912526

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{200, 133, 68, 68, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_CHARGINGDOCK_BMS

// ENUM DEFINITIONS



// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 2
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_chargingdock_bms.h"

// base include



#if MAVLINK_CHARGINGDOCK_BMS_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_chargingdock_bms}
# define MAVLINK_MESSAGE_NAMES {{ "chargingdock_bms", 200 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_CHARGINGDOCK_BMS_H
