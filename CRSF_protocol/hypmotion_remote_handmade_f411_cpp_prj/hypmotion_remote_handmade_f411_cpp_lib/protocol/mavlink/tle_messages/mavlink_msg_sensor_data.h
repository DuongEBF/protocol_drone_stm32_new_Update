#pragma once
// MESSAGE SENSOR_DATA PACKING

#define MAVLINK_MSG_ID_SENSOR_DATA 200


typedef struct __mavlink_sensor_data_t {
 float Bx_mT; /*<  
                
            */
 float By_mT; /*<  
                
            */
 float Bz_mT; /*<  
                
            */
 float phi; /*<  
                
            */
 float theta; /*<  
                
            */
} mavlink_sensor_data_t;

#define MAVLINK_MSG_ID_SENSOR_DATA_LEN 20
#define MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN 20
#define MAVLINK_MSG_ID_200_LEN 20
#define MAVLINK_MSG_ID_200_MIN_LEN 20

#define MAVLINK_MSG_ID_SENSOR_DATA_CRC 0
#define MAVLINK_MSG_ID_200_CRC 0



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SENSOR_DATA { \
    200, \
    "SENSOR_DATA", \
    5, \
    {  { "Bx_mT", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_sensor_data_t, Bx_mT) }, \
         { "By_mT", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_sensor_data_t, By_mT) }, \
         { "Bz_mT", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_sensor_data_t, Bz_mT) }, \
         { "phi", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_sensor_data_t, phi) }, \
         { "theta", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_sensor_data_t, theta) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SENSOR_DATA { \
    "SENSOR_DATA", \
    5, \
    {  { "Bx_mT", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_sensor_data_t, Bx_mT) }, \
         { "By_mT", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_sensor_data_t, By_mT) }, \
         { "Bz_mT", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_sensor_data_t, Bz_mT) }, \
         { "phi", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_sensor_data_t, phi) }, \
         { "theta", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_sensor_data_t, theta) }, \
         } \
}
#endif

/**
 * @brief Pack a sensor_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param Bx_mT  
                
            
 * @param By_mT  
                
            
 * @param Bz_mT  
                
            
 * @param phi  
                
            
 * @param theta  
                
            
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_data_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float Bx_mT, float By_mT, float Bz_mT, float phi, float theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_DATA_LEN];
    _mav_put_float(buf, 0, Bx_mT);
    _mav_put_float(buf, 4, By_mT);
    _mav_put_float(buf, 8, Bz_mT);
    _mav_put_float(buf, 12, phi);
    _mav_put_float(buf, 16, theta);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
#else
    mavlink_sensor_data_t packet;
    packet.Bx_mT = Bx_mT;
    packet.By_mT = By_mT;
    packet.Bz_mT = Bz_mT;
    packet.phi = phi;
    packet.theta = theta;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_DATA;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
}

/**
 * @brief Pack a sensor_data message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param Bx_mT  
                
            
 * @param By_mT  
                
            
 * @param Bz_mT  
                
            
 * @param phi  
                
            
 * @param theta  
                
            
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_data_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float Bx_mT, float By_mT, float Bz_mT, float phi, float theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_DATA_LEN];
    _mav_put_float(buf, 0, Bx_mT);
    _mav_put_float(buf, 4, By_mT);
    _mav_put_float(buf, 8, Bz_mT);
    _mav_put_float(buf, 12, phi);
    _mav_put_float(buf, 16, theta);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
#else
    mavlink_sensor_data_t packet;
    packet.Bx_mT = Bx_mT;
    packet.By_mT = By_mT;
    packet.Bz_mT = Bz_mT;
    packet.phi = phi;
    packet.theta = theta;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_DATA;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
#endif
}

/**
 * @brief Pack a sensor_data message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param Bx_mT  
                
            
 * @param By_mT  
                
            
 * @param Bz_mT  
                
            
 * @param phi  
                
            
 * @param theta  
                
            
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_sensor_data_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float Bx_mT,float By_mT,float Bz_mT,float phi,float theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_DATA_LEN];
    _mav_put_float(buf, 0, Bx_mT);
    _mav_put_float(buf, 4, By_mT);
    _mav_put_float(buf, 8, Bz_mT);
    _mav_put_float(buf, 12, phi);
    _mav_put_float(buf, 16, theta);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
#else
    mavlink_sensor_data_t packet;
    packet.Bx_mT = Bx_mT;
    packet.By_mT = By_mT;
    packet.Bz_mT = Bz_mT;
    packet.phi = phi;
    packet.theta = theta;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SENSOR_DATA;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
}

/**
 * @brief Encode a sensor_data struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param sensor_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_data_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_sensor_data_t* sensor_data)
{
    return mavlink_msg_sensor_data_pack(system_id, component_id, msg, sensor_data->Bx_mT, sensor_data->By_mT, sensor_data->Bz_mT, sensor_data->phi, sensor_data->theta);
}

/**
 * @brief Encode a sensor_data struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param sensor_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_data_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_sensor_data_t* sensor_data)
{
    return mavlink_msg_sensor_data_pack_chan(system_id, component_id, chan, msg, sensor_data->Bx_mT, sensor_data->By_mT, sensor_data->Bz_mT, sensor_data->phi, sensor_data->theta);
}

/**
 * @brief Encode a sensor_data struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param sensor_data C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_sensor_data_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_sensor_data_t* sensor_data)
{
    return mavlink_msg_sensor_data_pack_status(system_id, component_id, _status, msg,  sensor_data->Bx_mT, sensor_data->By_mT, sensor_data->Bz_mT, sensor_data->phi, sensor_data->theta);
}

/**
 * @brief Send a sensor_data message
 * @param chan MAVLink channel to send the message
 *
 * @param Bx_mT  
                
            
 * @param By_mT  
                
            
 * @param Bz_mT  
                
            
 * @param phi  
                
            
 * @param theta  
                
            
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_sensor_data_send(mavlink_channel_t chan, float Bx_mT, float By_mT, float Bz_mT, float phi, float theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SENSOR_DATA_LEN];
    _mav_put_float(buf, 0, Bx_mT);
    _mav_put_float(buf, 4, By_mT);
    _mav_put_float(buf, 8, Bz_mT);
    _mav_put_float(buf, 12, phi);
    _mav_put_float(buf, 16, theta);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_DATA, buf, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
#else
    mavlink_sensor_data_t packet;
    packet.Bx_mT = Bx_mT;
    packet.By_mT = By_mT;
    packet.Bz_mT = Bz_mT;
    packet.phi = phi;
    packet.theta = theta;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_DATA, (const char *)&packet, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
#endif
}

/**
 * @brief Send a sensor_data message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_sensor_data_send_struct(mavlink_channel_t chan, const mavlink_sensor_data_t* sensor_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_sensor_data_send(chan, sensor_data->Bx_mT, sensor_data->By_mT, sensor_data->Bz_mT, sensor_data->phi, sensor_data->theta);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_DATA, (const char *)sensor_data, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
#endif
}

#if MAVLINK_MSG_ID_SENSOR_DATA_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_sensor_data_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float Bx_mT, float By_mT, float Bz_mT, float phi, float theta)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, Bx_mT);
    _mav_put_float(buf, 4, By_mT);
    _mav_put_float(buf, 8, Bz_mT);
    _mav_put_float(buf, 12, phi);
    _mav_put_float(buf, 16, theta);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_DATA, buf, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
#else
    mavlink_sensor_data_t *packet = (mavlink_sensor_data_t *)msgbuf;
    packet->Bx_mT = Bx_mT;
    packet->By_mT = By_mT;
    packet->Bz_mT = Bz_mT;
    packet->phi = phi;
    packet->theta = theta;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SENSOR_DATA, (const char *)packet, MAVLINK_MSG_ID_SENSOR_DATA_MIN_LEN, MAVLINK_MSG_ID_SENSOR_DATA_LEN, MAVLINK_MSG_ID_SENSOR_DATA_CRC);
#endif
}
#endif

#endif

// MESSAGE SENSOR_DATA UNPACKING


/**
 * @brief Get field Bx_mT from sensor_data message
 *
 * @return  
                
            
 */
static inline float mavlink_msg_sensor_data_get_Bx_mT(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field By_mT from sensor_data message
 *
 * @return  
                
            
 */
static inline float mavlink_msg_sensor_data_get_By_mT(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field Bz_mT from sensor_data message
 *
 * @return  
                
            
 */
static inline float mavlink_msg_sensor_data_get_Bz_mT(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field phi from sensor_data message
 *
 * @return  
                
            
 */
static inline float mavlink_msg_sensor_data_get_phi(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field theta from sensor_data message
 *
 * @return  
                
            
 */
static inline float mavlink_msg_sensor_data_get_theta(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Decode a sensor_data message into a struct
 *
 * @param msg The message to decode
 * @param sensor_data C-struct to decode the message contents into
 */
static inline void mavlink_msg_sensor_data_decode(const mavlink_message_t* msg, mavlink_sensor_data_t* sensor_data)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    sensor_data->Bx_mT = mavlink_msg_sensor_data_get_Bx_mT(msg);
    sensor_data->By_mT = mavlink_msg_sensor_data_get_By_mT(msg);
    sensor_data->Bz_mT = mavlink_msg_sensor_data_get_Bz_mT(msg);
    sensor_data->phi = mavlink_msg_sensor_data_get_phi(msg);
    sensor_data->theta = mavlink_msg_sensor_data_get_theta(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SENSOR_DATA_LEN? msg->len : MAVLINK_MSG_ID_SENSOR_DATA_LEN;
        memset(sensor_data, 0, MAVLINK_MSG_ID_SENSOR_DATA_LEN);
    memcpy(sensor_data, _MAV_PAYLOAD(msg), len);
#endif
}
