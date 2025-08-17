/** @file
 *    @brief MAVLink comm protocol testsuite generated from hypmotion_mavlink_custom.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef HYPMOTION_MAVLINK_CUSTOM_TESTSUITE_H
#define HYPMOTION_MAVLINK_CUSTOM_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_chargingdock_bms(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_chargingdock_bms_aes_security(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_boardIO_SOM_Tobufi(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_hypmotion_mavlink_custom(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common(system_id, component_id, last_msg);
    mavlink_test_chargingdock_bms(system_id, component_id, last_msg);
    mavlink_test_chargingdock_bms_aes_security(system_id, component_id, last_msg);
    mavlink_test_boardIO_SOM_Tobufi(system_id, component_id, last_msg);
    mavlink_test_hypmotion_mavlink_custom(system_id, component_id, last_msg);
}
#endif

#include "../common/testsuite.h"
#include "../chargingdock_bms/testsuite.h"
#include "../chargingdock_bms_aes_security/testsuite.h"
#include "../boardIO_SOM_Tobufi/testsuite.h"



static void mavlink_test_hypmotion_mavlink_custom(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // HYPMOTION_MAVLINK_CUSTOM_TESTSUITE_H
