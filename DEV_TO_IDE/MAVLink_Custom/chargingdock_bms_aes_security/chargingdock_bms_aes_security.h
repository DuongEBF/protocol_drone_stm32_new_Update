/** @file
 *  @brief MAVLink comm protocol generated from chargingdock_bms_aes_security.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_CHARGINGDOCK_BMS_AES_SECURITY_H
#define MAVLINK_CHARGINGDOCK_BMS_AES_SECURITY_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_CHARGINGDOCK_BMS_AES_SECURITY.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_CHARGINGDOCK_BMS_AES_SECURITY_XML_HASH -2088667205435760217

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{201, 174, 128, 128, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_CHARGINGDOCK_BMS_AES_SECURITY

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
#include "./mavlink_msg_chargingdock_bms_aes_security.h"

// base include



#if MAVLINK_CHARGINGDOCK_BMS_AES_SECURITY_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_CHARGINGDOCK_BMS_AES_SECURITY}
# define MAVLINK_MESSAGE_NAMES {{ "CHARGINGDOCK_BMS_AES_SECURITY", 201 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_CHARGINGDOCK_BMS_AES_SECURITY_H
