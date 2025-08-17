/** @file
 *  @brief MAVLink comm protocol generated from tle_messages.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_TLE_MESSAGES_H
#define MAVLINK_TLE_MESSAGES_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_TLE_MESSAGES.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_TLE_MESSAGES_XML_HASH -5692792120971241951

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{200, 0, 20, 20, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_TLE_MESSAGES

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
#include "./mavlink_msg_sensor_data.h"

// base include



#if MAVLINK_TLE_MESSAGES_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_SENSOR_DATA}
# define MAVLINK_MESSAGE_NAMES {{ "SENSOR_DATA", 200 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_TLE_MESSAGES_H
