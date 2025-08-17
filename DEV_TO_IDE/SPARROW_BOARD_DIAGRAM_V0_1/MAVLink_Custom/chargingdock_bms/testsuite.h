/** @file
 *    @brief MAVLink comm protocol testsuite generated from chargingdock_bms.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef CHARGINGDOCK_BMS_TESTSUITE_H
#define CHARGINGDOCK_BMS_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL

static void mavlink_test_chargingdock_bms(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{

    mavlink_test_chargingdock_bms(system_id, component_id, last_msg);
}
#endif




static void mavlink_test_chargingdock_bms(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_chargingdock_bms >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_chargingdock_bms_t packet_in = {
        17.0,17443,17547,17651,17755,41,108,175,"PQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKL",8,75,142
    };
    mavlink_chargingdock_bms_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.temperature = packet_in.temperature;
        packet1.voltage = packet_in.voltage;
        packet1.current = packet_in.current;
        packet1.timeToFull = packet_in.timeToFull;
        packet1.timeToEmpty = packet_in.timeToEmpty;
        packet1.button = packet_in.button;
        packet1.isCharging = packet_in.isCharging;
        packet1.AdapterPower = packet_in.AdapterPower;
        packet1.SOC = packet_in.SOC;
        packet1.FullCharge = packet_in.FullCharge;
        packet1.TurnOffPower = packet_in.TurnOffPower;
        
        mav_array_memcpy(packet1.name, packet_in.name, sizeof(char)*50);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_chargingdock_bms_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_pack(system_id, component_id, &msg , packet1.button , packet1.isCharging , packet1.temperature , packet1.voltage , packet1.current , packet1.timeToFull , packet1.timeToEmpty , packet1.AdapterPower , packet1.name , packet1.SOC , packet1.FullCharge , packet1.TurnOffPower );
    mavlink_msg_chargingdock_bms_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.button , packet1.isCharging , packet1.temperature , packet1.voltage , packet1.current , packet1.timeToFull , packet1.timeToEmpty , packet1.AdapterPower , packet1.name , packet1.SOC , packet1.FullCharge , packet1.TurnOffPower );
    mavlink_msg_chargingdock_bms_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_chargingdock_bms_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_chargingdock_bms_send(MAVLINK_COMM_1 , packet1.button , packet1.isCharging , packet1.temperature , packet1.voltage , packet1.current , packet1.timeToFull , packet1.timeToEmpty , packet1.AdapterPower , packet1.name , packet1.SOC , packet1.FullCharge , packet1.TurnOffPower );
    mavlink_msg_chargingdock_bms_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("chargingdock_bms") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_chargingdock_bms) != NULL);
#endif
}

static void mavlink_test_chargingdock_bms(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_chargingdock_bms(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // CHARGINGDOCK_BMS_TESTSUITE_H
