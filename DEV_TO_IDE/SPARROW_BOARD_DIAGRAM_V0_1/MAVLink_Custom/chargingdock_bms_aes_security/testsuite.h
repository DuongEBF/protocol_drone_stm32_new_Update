/** @file
 *    @brief MAVLink comm protocol testsuite generated from chargingdock_bms_aes_security.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef CHARGINGDOCK_BMS_AES_SECURITY_TESTSUITE_H
#define CHARGINGDOCK_BMS_AES_SECURITY_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_chargingdock_bms_aes_security(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_chargingdock_bms_aes_security(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_chargingdock_bms_aes_security(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_chargingdock_bms_aes_security_t packet_in = {
        { 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132 }
    };
    mavlink_chargingdock_bms_aes_security_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.payload_encrypted, packet_in.payload_encrypted, sizeof(uint8_t)*128);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_aes_security_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_chargingdock_bms_aes_security_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_aes_security_pack(system_id, component_id, &msg , packet1.payload_encrypted );
    mavlink_msg_chargingdock_bms_aes_security_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_aes_security_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.payload_encrypted );
    mavlink_msg_chargingdock_bms_aes_security_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_chargingdock_bms_aes_security_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_aes_security_send(MAVLINK_COMM_1 , packet1.payload_encrypted );
    mavlink_msg_chargingdock_bms_aes_security_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("CHARGINGDOCK_BMS_AES_SECURITY") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY) != NULL);
#endif
}

static void mavlink_test_chargingdock_bms_aes_security(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_chargingdock_bms_aes_security(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // CHARGINGDOCK_BMS_AES_SECURITY_TESTSUITE_H
