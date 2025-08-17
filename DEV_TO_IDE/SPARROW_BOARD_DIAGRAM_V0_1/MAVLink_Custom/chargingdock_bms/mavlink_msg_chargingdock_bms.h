#pragma once
// MESSAGE chargingdock_bms PACKING

#define MAVLINK_MSG_ID_chargingdock_bms 200


typedef struct __mavlink_chargingdock_bms_t {
 float temperature; /*<  Temperature in C*/
 uint16_t voltage; /*<  Voltage mV*/
 int16_t current; /*<  Current mA*/
 uint16_t timeToFull; /*<  Time to full*/
 uint16_t timeToEmpty; /*<  Time to empty*/
 uint8_t button; /*<  Button*/
 uint8_t isCharging; /*<  System in charging mode*/
 uint8_t AdapterPower; /*<  Adapter Power*/
 char name[50]; /*<  Name*/
 uint8_t SOC; /*<  State Of Charge*/
 uint8_t FullCharge; /*<  bit Full Charge from BQ40ZX*/
 uint8_t TurnOffPower; /*<  bit to disable mosfet on BMS*/
} mavlink_chargingdock_bms_t;

#define MAVLINK_MSG_ID_chargingdock_bms_LEN 68
#define MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN 68
#define MAVLINK_MSG_ID_200_LEN 68
#define MAVLINK_MSG_ID_200_MIN_LEN 68

#define MAVLINK_MSG_ID_chargingdock_bms_CRC 133
#define MAVLINK_MSG_ID_200_CRC 133

#define MAVLINK_MSG_chargingdock_bms_FIELD_NAME_LEN 50

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_chargingdock_bms { \
    200, \
    "chargingdock_bms", \
    12, \
    {  { "button", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_chargingdock_bms_t, button) }, \
         { "isCharging", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_chargingdock_bms_t, isCharging) }, \
         { "temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_chargingdock_bms_t, temperature) }, \
         { "voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_chargingdock_bms_t, voltage) }, \
         { "current", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_chargingdock_bms_t, current) }, \
         { "timeToFull", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_chargingdock_bms_t, timeToFull) }, \
         { "timeToEmpty", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_chargingdock_bms_t, timeToEmpty) }, \
         { "AdapterPower", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_chargingdock_bms_t, AdapterPower) }, \
         { "name", NULL, MAVLINK_TYPE_CHAR, 50, 15, offsetof(mavlink_chargingdock_bms_t, name) }, \
         { "SOC", NULL, MAVLINK_TYPE_UINT8_T, 0, 65, offsetof(mavlink_chargingdock_bms_t, SOC) }, \
         { "FullCharge", NULL, MAVLINK_TYPE_UINT8_T, 0, 66, offsetof(mavlink_chargingdock_bms_t, FullCharge) }, \
         { "TurnOffPower", NULL, MAVLINK_TYPE_UINT8_T, 0, 67, offsetof(mavlink_chargingdock_bms_t, TurnOffPower) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_chargingdock_bms { \
    "chargingdock_bms", \
    12, \
    {  { "button", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_chargingdock_bms_t, button) }, \
         { "isCharging", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_chargingdock_bms_t, isCharging) }, \
         { "temperature", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_chargingdock_bms_t, temperature) }, \
         { "voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_chargingdock_bms_t, voltage) }, \
         { "current", NULL, MAVLINK_TYPE_INT16_T, 0, 6, offsetof(mavlink_chargingdock_bms_t, current) }, \
         { "timeToFull", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_chargingdock_bms_t, timeToFull) }, \
         { "timeToEmpty", NULL, MAVLINK_TYPE_UINT16_T, 0, 10, offsetof(mavlink_chargingdock_bms_t, timeToEmpty) }, \
         { "AdapterPower", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_chargingdock_bms_t, AdapterPower) }, \
         { "name", NULL, MAVLINK_TYPE_CHAR, 50, 15, offsetof(mavlink_chargingdock_bms_t, name) }, \
         { "SOC", NULL, MAVLINK_TYPE_UINT8_T, 0, 65, offsetof(mavlink_chargingdock_bms_t, SOC) }, \
         { "FullCharge", NULL, MAVLINK_TYPE_UINT8_T, 0, 66, offsetof(mavlink_chargingdock_bms_t, FullCharge) }, \
         { "TurnOffPower", NULL, MAVLINK_TYPE_UINT8_T, 0, 67, offsetof(mavlink_chargingdock_bms_t, TurnOffPower) }, \
         } \
}
#endif

/**
 * @brief Pack a chargingdock_bms message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param button  Button
 * @param isCharging  System in charging mode
 * @param temperature  Temperature in C
 * @param voltage  Voltage mV
 * @param current  Current mA
 * @param timeToFull  Time to full
 * @param timeToEmpty  Time to empty
 * @param AdapterPower  Adapter Power
 * @param name  Name
 * @param SOC  State Of Charge
 * @param FullCharge  bit Full Charge from BQ40ZX
 * @param TurnOffPower  bit to disable mosfet on BMS
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_chargingdock_bms_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t button, uint8_t isCharging, float temperature, uint16_t voltage, int16_t current, uint16_t timeToFull, uint16_t timeToEmpty, uint8_t AdapterPower, const char *name, uint8_t SOC, uint8_t FullCharge, uint8_t TurnOffPower)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_chargingdock_bms_LEN];
    _mav_put_float(buf, 0, temperature);
    _mav_put_uint16_t(buf, 4, voltage);
    _mav_put_int16_t(buf, 6, current);
    _mav_put_uint16_t(buf, 8, timeToFull);
    _mav_put_uint16_t(buf, 10, timeToEmpty);
    _mav_put_uint8_t(buf, 12, button);
    _mav_put_uint8_t(buf, 13, isCharging);
    _mav_put_uint8_t(buf, 14, AdapterPower);
    _mav_put_uint8_t(buf, 65, SOC);
    _mav_put_uint8_t(buf, 66, FullCharge);
    _mav_put_uint8_t(buf, 67, TurnOffPower);
    _mav_put_char_array(buf, 15, name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_chargingdock_bms_LEN);
#else
    mavlink_chargingdock_bms_t packet;
    packet.temperature = temperature;
    packet.voltage = voltage;
    packet.current = current;
    packet.timeToFull = timeToFull;
    packet.timeToEmpty = timeToEmpty;
    packet.button = button;
    packet.isCharging = isCharging;
    packet.AdapterPower = AdapterPower;
    packet.SOC = SOC;
    packet.FullCharge = FullCharge;
    packet.TurnOffPower = TurnOffPower;
    mav_array_memcpy(packet.name, name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_chargingdock_bms_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_chargingdock_bms;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
}

/**
 * @brief Pack a chargingdock_bms message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param button  Button
 * @param isCharging  System in charging mode
 * @param temperature  Temperature in C
 * @param voltage  Voltage mV
 * @param current  Current mA
 * @param timeToFull  Time to full
 * @param timeToEmpty  Time to empty
 * @param AdapterPower  Adapter Power
 * @param name  Name
 * @param SOC  State Of Charge
 * @param FullCharge  bit Full Charge from BQ40ZX
 * @param TurnOffPower  bit to disable mosfet on BMS
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_chargingdock_bms_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t button, uint8_t isCharging, float temperature, uint16_t voltage, int16_t current, uint16_t timeToFull, uint16_t timeToEmpty, uint8_t AdapterPower, const char *name, uint8_t SOC, uint8_t FullCharge, uint8_t TurnOffPower)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_chargingdock_bms_LEN];
    _mav_put_float(buf, 0, temperature);
    _mav_put_uint16_t(buf, 4, voltage);
    _mav_put_int16_t(buf, 6, current);
    _mav_put_uint16_t(buf, 8, timeToFull);
    _mav_put_uint16_t(buf, 10, timeToEmpty);
    _mav_put_uint8_t(buf, 12, button);
    _mav_put_uint8_t(buf, 13, isCharging);
    _mav_put_uint8_t(buf, 14, AdapterPower);
    _mav_put_uint8_t(buf, 65, SOC);
    _mav_put_uint8_t(buf, 66, FullCharge);
    _mav_put_uint8_t(buf, 67, TurnOffPower);
    _mav_put_char_array(buf, 15, name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_chargingdock_bms_LEN);
#else
    mavlink_chargingdock_bms_t packet;
    packet.temperature = temperature;
    packet.voltage = voltage;
    packet.current = current;
    packet.timeToFull = timeToFull;
    packet.timeToEmpty = timeToEmpty;
    packet.button = button;
    packet.isCharging = isCharging;
    packet.AdapterPower = AdapterPower;
    packet.SOC = SOC;
    packet.FullCharge = FullCharge;
    packet.TurnOffPower = TurnOffPower;
    mav_array_memcpy(packet.name, name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_chargingdock_bms_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_chargingdock_bms;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN);
#endif
}

/**
 * @brief Pack a chargingdock_bms message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param button  Button
 * @param isCharging  System in charging mode
 * @param temperature  Temperature in C
 * @param voltage  Voltage mV
 * @param current  Current mA
 * @param timeToFull  Time to full
 * @param timeToEmpty  Time to empty
 * @param AdapterPower  Adapter Power
 * @param name  Name
 * @param SOC  State Of Charge
 * @param FullCharge  bit Full Charge from BQ40ZX
 * @param TurnOffPower  bit to disable mosfet on BMS
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_chargingdock_bms_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t button,uint8_t isCharging,float temperature,uint16_t voltage,int16_t current,uint16_t timeToFull,uint16_t timeToEmpty,uint8_t AdapterPower,const char *name,uint8_t SOC,uint8_t FullCharge,uint8_t TurnOffPower)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_chargingdock_bms_LEN];
    _mav_put_float(buf, 0, temperature);
    _mav_put_uint16_t(buf, 4, voltage);
    _mav_put_int16_t(buf, 6, current);
    _mav_put_uint16_t(buf, 8, timeToFull);
    _mav_put_uint16_t(buf, 10, timeToEmpty);
    _mav_put_uint8_t(buf, 12, button);
    _mav_put_uint8_t(buf, 13, isCharging);
    _mav_put_uint8_t(buf, 14, AdapterPower);
    _mav_put_uint8_t(buf, 65, SOC);
    _mav_put_uint8_t(buf, 66, FullCharge);
    _mav_put_uint8_t(buf, 67, TurnOffPower);
    _mav_put_char_array(buf, 15, name, 50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_chargingdock_bms_LEN);
#else
    mavlink_chargingdock_bms_t packet;
    packet.temperature = temperature;
    packet.voltage = voltage;
    packet.current = current;
    packet.timeToFull = timeToFull;
    packet.timeToEmpty = timeToEmpty;
    packet.button = button;
    packet.isCharging = isCharging;
    packet.AdapterPower = AdapterPower;
    packet.SOC = SOC;
    packet.FullCharge = FullCharge;
    packet.TurnOffPower = TurnOffPower;
    mav_array_memcpy(packet.name, name, sizeof(char)*50);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_chargingdock_bms_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_chargingdock_bms;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
}

/**
 * @brief Encode a chargingdock_bms struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param chargingdock_bms C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_chargingdock_bms_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_chargingdock_bms_t* chargingdock_bms)
{
    return mavlink_msg_chargingdock_bms_pack(system_id, component_id, msg, chargingdock_bms->button, chargingdock_bms->isCharging, chargingdock_bms->temperature, chargingdock_bms->voltage, chargingdock_bms->current, chargingdock_bms->timeToFull, chargingdock_bms->timeToEmpty, chargingdock_bms->AdapterPower, chargingdock_bms->name, chargingdock_bms->SOC, chargingdock_bms->FullCharge, chargingdock_bms->TurnOffPower);
}

/**
 * @brief Encode a chargingdock_bms struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param chargingdock_bms C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_chargingdock_bms_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_chargingdock_bms_t* chargingdock_bms)
{
    return mavlink_msg_chargingdock_bms_pack_chan(system_id, component_id, chan, msg, chargingdock_bms->button, chargingdock_bms->isCharging, chargingdock_bms->temperature, chargingdock_bms->voltage, chargingdock_bms->current, chargingdock_bms->timeToFull, chargingdock_bms->timeToEmpty, chargingdock_bms->AdapterPower, chargingdock_bms->name, chargingdock_bms->SOC, chargingdock_bms->FullCharge, chargingdock_bms->TurnOffPower);
}

/**
 * @brief Encode a chargingdock_bms struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param chargingdock_bms C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_chargingdock_bms_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_chargingdock_bms_t* chargingdock_bms)
{
    return mavlink_msg_chargingdock_bms_pack_status(system_id, component_id, _status, msg,  chargingdock_bms->button, chargingdock_bms->isCharging, chargingdock_bms->temperature, chargingdock_bms->voltage, chargingdock_bms->current, chargingdock_bms->timeToFull, chargingdock_bms->timeToEmpty, chargingdock_bms->AdapterPower, chargingdock_bms->name, chargingdock_bms->SOC, chargingdock_bms->FullCharge, chargingdock_bms->TurnOffPower);
}

/**
 * @brief Send a chargingdock_bms message
 * @param chan MAVLink channel to send the message
 *
 * @param button  Button
 * @param isCharging  System in charging mode
 * @param temperature  Temperature in C
 * @param voltage  Voltage mV
 * @param current  Current mA
 * @param timeToFull  Time to full
 * @param timeToEmpty  Time to empty
 * @param AdapterPower  Adapter Power
 * @param name  Name
 * @param SOC  State Of Charge
 * @param FullCharge  bit Full Charge from BQ40ZX
 * @param TurnOffPower  bit to disable mosfet on BMS
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_chargingdock_bms_send(mavlink_channel_t chan, uint8_t button, uint8_t isCharging, float temperature, uint16_t voltage, int16_t current, uint16_t timeToFull, uint16_t timeToEmpty, uint8_t AdapterPower, const char *name, uint8_t SOC, uint8_t FullCharge, uint8_t TurnOffPower)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_chargingdock_bms_LEN];
    _mav_put_float(buf, 0, temperature);
    _mav_put_uint16_t(buf, 4, voltage);
    _mav_put_int16_t(buf, 6, current);
    _mav_put_uint16_t(buf, 8, timeToFull);
    _mav_put_uint16_t(buf, 10, timeToEmpty);
    _mav_put_uint8_t(buf, 12, button);
    _mav_put_uint8_t(buf, 13, isCharging);
    _mav_put_uint8_t(buf, 14, AdapterPower);
    _mav_put_uint8_t(buf, 65, SOC);
    _mav_put_uint8_t(buf, 66, FullCharge);
    _mav_put_uint8_t(buf, 67, TurnOffPower);
    _mav_put_char_array(buf, 15, name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_chargingdock_bms, buf, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
#else
    mavlink_chargingdock_bms_t packet;
    packet.temperature = temperature;
    packet.voltage = voltage;
    packet.current = current;
    packet.timeToFull = timeToFull;
    packet.timeToEmpty = timeToEmpty;
    packet.button = button;
    packet.isCharging = isCharging;
    packet.AdapterPower = AdapterPower;
    packet.SOC = SOC;
    packet.FullCharge = FullCharge;
    packet.TurnOffPower = TurnOffPower;
    mav_array_memcpy(packet.name, name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_chargingdock_bms, (const char *)&packet, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
#endif
}

/**
 * @brief Send a chargingdock_bms message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_chargingdock_bms_send_struct(mavlink_channel_t chan, const mavlink_chargingdock_bms_t* chargingdock_bms)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_chargingdock_bms_send(chan, chargingdock_bms->button, chargingdock_bms->isCharging, chargingdock_bms->temperature, chargingdock_bms->voltage, chargingdock_bms->current, chargingdock_bms->timeToFull, chargingdock_bms->timeToEmpty, chargingdock_bms->AdapterPower, chargingdock_bms->name, chargingdock_bms->SOC, chargingdock_bms->FullCharge, chargingdock_bms->TurnOffPower);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_chargingdock_bms, (const char *)chargingdock_bms, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
#endif
}

#if MAVLINK_MSG_ID_chargingdock_bms_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_chargingdock_bms_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t button, uint8_t isCharging, float temperature, uint16_t voltage, int16_t current, uint16_t timeToFull, uint16_t timeToEmpty, uint8_t AdapterPower, const char *name, uint8_t SOC, uint8_t FullCharge, uint8_t TurnOffPower)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, temperature);
    _mav_put_uint16_t(buf, 4, voltage);
    _mav_put_int16_t(buf, 6, current);
    _mav_put_uint16_t(buf, 8, timeToFull);
    _mav_put_uint16_t(buf, 10, timeToEmpty);
    _mav_put_uint8_t(buf, 12, button);
    _mav_put_uint8_t(buf, 13, isCharging);
    _mav_put_uint8_t(buf, 14, AdapterPower);
    _mav_put_uint8_t(buf, 65, SOC);
    _mav_put_uint8_t(buf, 66, FullCharge);
    _mav_put_uint8_t(buf, 67, TurnOffPower);
    _mav_put_char_array(buf, 15, name, 50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_chargingdock_bms, buf, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
#else
    mavlink_chargingdock_bms_t *packet = (mavlink_chargingdock_bms_t *)msgbuf;
    packet->temperature = temperature;
    packet->voltage = voltage;
    packet->current = current;
    packet->timeToFull = timeToFull;
    packet->timeToEmpty = timeToEmpty;
    packet->button = button;
    packet->isCharging = isCharging;
    packet->AdapterPower = AdapterPower;
    packet->SOC = SOC;
    packet->FullCharge = FullCharge;
    packet->TurnOffPower = TurnOffPower;
    mav_array_memcpy(packet->name, name, sizeof(char)*50);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_chargingdock_bms, (const char *)packet, MAVLINK_MSG_ID_chargingdock_bms_MIN_LEN, MAVLINK_MSG_ID_chargingdock_bms_LEN, MAVLINK_MSG_ID_chargingdock_bms_CRC);
#endif
}
#endif

#endif

// MESSAGE chargingdock_bms UNPACKING


/**
 * @brief Get field button from chargingdock_bms message
 *
 * @return  Button
 */
static inline uint8_t mavlink_msg_chargingdock_bms_get_button(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field isCharging from chargingdock_bms message
 *
 * @return  System in charging mode
 */
static inline uint8_t mavlink_msg_chargingdock_bms_get_isCharging(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field temperature from chargingdock_bms message
 *
 * @return  Temperature in C
 */
static inline float mavlink_msg_chargingdock_bms_get_temperature(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field voltage from chargingdock_bms message
 *
 * @return  Voltage mV
 */
static inline uint16_t mavlink_msg_chargingdock_bms_get_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field current from chargingdock_bms message
 *
 * @return  Current mA
 */
static inline int16_t mavlink_msg_chargingdock_bms_get_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  6);
}

/**
 * @brief Get field timeToFull from chargingdock_bms message
 *
 * @return  Time to full
 */
static inline uint16_t mavlink_msg_chargingdock_bms_get_timeToFull(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field timeToEmpty from chargingdock_bms message
 *
 * @return  Time to empty
 */
static inline uint16_t mavlink_msg_chargingdock_bms_get_timeToEmpty(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  10);
}

/**
 * @brief Get field AdapterPower from chargingdock_bms message
 *
 * @return  Adapter Power
 */
static inline uint8_t mavlink_msg_chargingdock_bms_get_AdapterPower(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Get field name from chargingdock_bms message
 *
 * @return  Name
 */
static inline uint16_t mavlink_msg_chargingdock_bms_get_name(const mavlink_message_t* msg, char *name)
{
    return _MAV_RETURN_char_array(msg, name, 50,  15);
}

/**
 * @brief Get field SOC from chargingdock_bms message
 *
 * @return  State Of Charge
 */
static inline uint8_t mavlink_msg_chargingdock_bms_get_SOC(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  65);
}

/**
 * @brief Get field FullCharge from chargingdock_bms message
 *
 * @return  bit Full Charge from BQ40ZX
 */
static inline uint8_t mavlink_msg_chargingdock_bms_get_FullCharge(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  66);
}

/**
 * @brief Get field TurnOffPower from chargingdock_bms message
 *
 * @return  bit to disable mosfet on BMS
 */
static inline uint8_t mavlink_msg_chargingdock_bms_get_TurnOffPower(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  67);
}

/**
 * @brief Decode a chargingdock_bms message into a struct
 *
 * @param msg The message to decode
 * @param chargingdock_bms C-struct to decode the message contents into
 */
static inline void mavlink_msg_chargingdock_bms_decode(const mavlink_message_t* msg, mavlink_chargingdock_bms_t* chargingdock_bms)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    chargingdock_bms->temperature = mavlink_msg_chargingdock_bms_get_temperature(msg);
    chargingdock_bms->voltage = mavlink_msg_chargingdock_bms_get_voltage(msg);
    chargingdock_bms->current = mavlink_msg_chargingdock_bms_get_current(msg);
    chargingdock_bms->timeToFull = mavlink_msg_chargingdock_bms_get_timeToFull(msg);
    chargingdock_bms->timeToEmpty = mavlink_msg_chargingdock_bms_get_timeToEmpty(msg);
    chargingdock_bms->button = mavlink_msg_chargingdock_bms_get_button(msg);
    chargingdock_bms->isCharging = mavlink_msg_chargingdock_bms_get_isCharging(msg);
    chargingdock_bms->AdapterPower = mavlink_msg_chargingdock_bms_get_AdapterPower(msg);
    mavlink_msg_chargingdock_bms_get_name(msg, chargingdock_bms->name);
    chargingdock_bms->SOC = mavlink_msg_chargingdock_bms_get_SOC(msg);
    chargingdock_bms->FullCharge = mavlink_msg_chargingdock_bms_get_FullCharge(msg);
    chargingdock_bms->TurnOffPower = mavlink_msg_chargingdock_bms_get_TurnOffPower(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_chargingdock_bms_LEN? msg->len : MAVLINK_MSG_ID_chargingdock_bms_LEN;
        memset(chargingdock_bms, 0, MAVLINK_MSG_ID_chargingdock_bms_LEN);
    memcpy(chargingdock_bms, _MAV_PAYLOAD(msg), len);
#endif
}
