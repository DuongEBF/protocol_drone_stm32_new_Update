#pragma once
// MESSAGE CHARGINGDOCK_BMS_AES_SECURITY PACKING

#define MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY 201


typedef struct __mavlink_chargingdock_bms_aes_security_t {
 uint8_t payload_encrypted[128]; /*<  Encrypted payload*/
} mavlink_chargingdock_bms_aes_security_t;

#define MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN 128
#define MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN 128
#define MAVLINK_MSG_ID_201_LEN 128
#define MAVLINK_MSG_ID_201_MIN_LEN 128

#define MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC 174
#define MAVLINK_MSG_ID_201_CRC 174

#define MAVLINK_MSG_CHARGINGDOCK_BMS_AES_SECURITY_FIELD_PAYLOAD_ENCRYPTED_LEN 128

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_CHARGINGDOCK_BMS_AES_SECURITY { \
    201, \
    "CHARGINGDOCK_BMS_AES_SECURITY", \
    1, \
    {  { "payload_encrypted", NULL, MAVLINK_TYPE_UINT8_T, 128, 0, offsetof(mavlink_chargingdock_bms_aes_security_t, payload_encrypted) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_CHARGINGDOCK_BMS_AES_SECURITY { \
    "CHARGINGDOCK_BMS_AES_SECURITY", \
    1, \
    {  { "payload_encrypted", NULL, MAVLINK_TYPE_UINT8_T, 128, 0, offsetof(mavlink_chargingdock_bms_aes_security_t, payload_encrypted) }, \
         } \
}
#endif

/**
 * @brief Pack a chargingdock_bms_aes_security message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param payload_encrypted  Encrypted payload
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_chargingdock_bms_aes_security_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint8_t *payload_encrypted)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN];

    _mav_put_uint8_t_array(buf, 0, payload_encrypted, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
#else
    mavlink_chargingdock_bms_aes_security_t packet;

    mav_array_memcpy(packet.payload_encrypted, payload_encrypted, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
}

/**
 * @brief Pack a chargingdock_bms_aes_security message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param payload_encrypted  Encrypted payload
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_chargingdock_bms_aes_security_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint8_t *payload_encrypted)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN];

    _mav_put_uint8_t_array(buf, 0, payload_encrypted, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
#else
    mavlink_chargingdock_bms_aes_security_t packet;

    mav_array_memcpy(packet.payload_encrypted, payload_encrypted, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
#endif
}

/**
 * @brief Pack a chargingdock_bms_aes_security message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param payload_encrypted  Encrypted payload
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_chargingdock_bms_aes_security_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint8_t *payload_encrypted)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN];

    _mav_put_uint8_t_array(buf, 0, payload_encrypted, 128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
#else
    mavlink_chargingdock_bms_aes_security_t packet;

    mav_array_memcpy(packet.payload_encrypted, payload_encrypted, sizeof(uint8_t)*128);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
}

/**
 * @brief Encode a chargingdock_bms_aes_security struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param chargingdock_bms_aes_security C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_chargingdock_bms_aes_security_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_chargingdock_bms_aes_security_t* chargingdock_bms_aes_security)
{
    return mavlink_msg_chargingdock_bms_aes_security_pack(system_id, component_id, msg, chargingdock_bms_aes_security->payload_encrypted);
}

/**
 * @brief Encode a chargingdock_bms_aes_security struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param chargingdock_bms_aes_security C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_chargingdock_bms_aes_security_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_chargingdock_bms_aes_security_t* chargingdock_bms_aes_security)
{
    return mavlink_msg_chargingdock_bms_aes_security_pack_chan(system_id, component_id, chan, msg, chargingdock_bms_aes_security->payload_encrypted);
}

/**
 * @brief Encode a chargingdock_bms_aes_security struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param chargingdock_bms_aes_security C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_chargingdock_bms_aes_security_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_chargingdock_bms_aes_security_t* chargingdock_bms_aes_security)
{
    return mavlink_msg_chargingdock_bms_aes_security_pack_status(system_id, component_id, _status, msg,  chargingdock_bms_aes_security->payload_encrypted);
}

/**
 * @brief Send a chargingdock_bms_aes_security message
 * @param chan MAVLink channel to send the message
 *
 * @param payload_encrypted  Encrypted payload
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_chargingdock_bms_aes_security_send(mavlink_channel_t chan, const uint8_t *payload_encrypted)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN];

    _mav_put_uint8_t_array(buf, 0, payload_encrypted, 128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY, buf, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
#else
    mavlink_chargingdock_bms_aes_security_t packet;

    mav_array_memcpy(packet.payload_encrypted, payload_encrypted, sizeof(uint8_t)*128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY, (const char *)&packet, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
#endif
}

/**
 * @brief Send a chargingdock_bms_aes_security message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_chargingdock_bms_aes_security_send_struct(mavlink_channel_t chan, const mavlink_chargingdock_bms_aes_security_t* chargingdock_bms_aes_security)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_chargingdock_bms_aes_security_send(chan, chargingdock_bms_aes_security->payload_encrypted);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY, (const char *)chargingdock_bms_aes_security, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
#endif
}

#if MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_chargingdock_bms_aes_security_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint8_t *payload_encrypted)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_uint8_t_array(buf, 0, payload_encrypted, 128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY, buf, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
#else
    mavlink_chargingdock_bms_aes_security_t *packet = (mavlink_chargingdock_bms_aes_security_t *)msgbuf;

    mav_array_memcpy(packet->payload_encrypted, payload_encrypted, sizeof(uint8_t)*128);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY, (const char *)packet, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_MIN_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_CRC);
#endif
}
#endif

#endif

// MESSAGE CHARGINGDOCK_BMS_AES_SECURITY UNPACKING


/**
 * @brief Get field payload_encrypted from chargingdock_bms_aes_security message
 *
 * @return  Encrypted payload
 */
static inline uint16_t mavlink_msg_chargingdock_bms_aes_security_get_payload_encrypted(const mavlink_message_t* msg, uint8_t *payload_encrypted)
{
    return _MAV_RETURN_uint8_t_array(msg, payload_encrypted, 128,  0);
}

/**
 * @brief Decode a chargingdock_bms_aes_security message into a struct
 *
 * @param msg The message to decode
 * @param chargingdock_bms_aes_security C-struct to decode the message contents into
 */
static inline void mavlink_msg_chargingdock_bms_aes_security_decode(const mavlink_message_t* msg, mavlink_chargingdock_bms_aes_security_t* chargingdock_bms_aes_security)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_chargingdock_bms_aes_security_get_payload_encrypted(msg, chargingdock_bms_aes_security->payload_encrypted);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN? msg->len : MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN;
        memset(chargingdock_bms_aes_security, 0, MAVLINK_MSG_ID_CHARGINGDOCK_BMS_AES_SECURITY_LEN);
    memcpy(chargingdock_bms_aes_security, _MAV_PAYLOAD(msg), len);
#endif
}
