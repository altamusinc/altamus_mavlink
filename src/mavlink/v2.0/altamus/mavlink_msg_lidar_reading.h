#pragma once
// MESSAGE LIDAR_READING PACKING

#define MAVLINK_MSG_ID_LIDAR_READING 1


typedef struct __mavlink_lidar_reading_t {
 uint64_t readings[31]; /*<  */
} mavlink_lidar_reading_t;

#define MAVLINK_MSG_ID_LIDAR_READING_LEN 248
#define MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN 248
#define MAVLINK_MSG_ID_1_LEN 248
#define MAVLINK_MSG_ID_1_MIN_LEN 248

#define MAVLINK_MSG_ID_LIDAR_READING_CRC 125
#define MAVLINK_MSG_ID_1_CRC 125

#define MAVLINK_MSG_LIDAR_READING_FIELD_READINGS_LEN 31

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LIDAR_READING { \
    1, \
    "LIDAR_READING", \
    1, \
    {  { "readings", NULL, MAVLINK_TYPE_UINT64_T, 31, 0, offsetof(mavlink_lidar_reading_t, readings) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LIDAR_READING { \
    "LIDAR_READING", \
    1, \
    {  { "readings", NULL, MAVLINK_TYPE_UINT64_T, 31, 0, offsetof(mavlink_lidar_reading_t, readings) }, \
         } \
}
#endif

/**
 * @brief Pack a lidar_reading message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param readings  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_reading_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint64_t *readings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_READING_LEN];

    _mav_put_uint64_t_array(buf, 0, readings, 31);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_READING_LEN);
#else
    mavlink_lidar_reading_t packet;

    mav_array_memcpy(packet.readings, readings, sizeof(uint64_t)*31);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_READING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR_READING;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
}

/**
 * @brief Pack a lidar_reading message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param readings  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_reading_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint64_t *readings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_READING_LEN];

    _mav_put_uint64_t_array(buf, 0, readings, 31);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_READING_LEN);
#else
    mavlink_lidar_reading_t packet;

    mav_array_memcpy(packet.readings, readings, sizeof(uint64_t)*31);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_READING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR_READING;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN);
#endif
}

/**
 * @brief Pack a lidar_reading message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param readings  
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_reading_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint64_t *readings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_READING_LEN];

    _mav_put_uint64_t_array(buf, 0, readings, 31);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_READING_LEN);
#else
    mavlink_lidar_reading_t packet;

    mav_array_memcpy(packet.readings, readings, sizeof(uint64_t)*31);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_READING_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR_READING;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
}

/**
 * @brief Encode a lidar_reading struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param lidar_reading C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_reading_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_lidar_reading_t* lidar_reading)
{
    return mavlink_msg_lidar_reading_pack(system_id, component_id, msg, lidar_reading->readings);
}

/**
 * @brief Encode a lidar_reading struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lidar_reading C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_reading_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_lidar_reading_t* lidar_reading)
{
    return mavlink_msg_lidar_reading_pack_chan(system_id, component_id, chan, msg, lidar_reading->readings);
}

/**
 * @brief Encode a lidar_reading struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param lidar_reading C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_reading_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_lidar_reading_t* lidar_reading)
{
    return mavlink_msg_lidar_reading_pack_status(system_id, component_id, _status, msg,  lidar_reading->readings);
}

/**
 * @brief Send a lidar_reading message
 * @param chan MAVLink channel to send the message
 *
 * @param readings  
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_lidar_reading_send(mavlink_channel_t chan, const uint64_t *readings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_READING_LEN];

    _mav_put_uint64_t_array(buf, 0, readings, 31);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_READING, buf, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
#else
    mavlink_lidar_reading_t packet;

    mav_array_memcpy(packet.readings, readings, sizeof(uint64_t)*31);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_READING, (const char *)&packet, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
#endif
}

/**
 * @brief Send a lidar_reading message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_lidar_reading_send_struct(mavlink_channel_t chan, const mavlink_lidar_reading_t* lidar_reading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_lidar_reading_send(chan, lidar_reading->readings);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_READING, (const char *)lidar_reading, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
#endif
}

#if MAVLINK_MSG_ID_LIDAR_READING_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_lidar_reading_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint64_t *readings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_uint64_t_array(buf, 0, readings, 31);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_READING, buf, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
#else
    mavlink_lidar_reading_t *packet = (mavlink_lidar_reading_t *)msgbuf;

    mav_array_memcpy(packet->readings, readings, sizeof(uint64_t)*31);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_READING, (const char *)packet, MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN, MAVLINK_MSG_ID_LIDAR_READING_LEN, MAVLINK_MSG_ID_LIDAR_READING_CRC);
#endif
}
#endif

#endif

// MESSAGE LIDAR_READING UNPACKING


/**
 * @brief Get field readings from lidar_reading message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_lidar_reading_get_readings(const mavlink_message_t* msg, uint64_t *readings)
{
    return _MAV_RETURN_uint64_t_array(msg, readings, 31,  0);
}

/**
 * @brief Decode a lidar_reading message into a struct
 *
 * @param msg The message to decode
 * @param lidar_reading C-struct to decode the message contents into
 */
static inline void mavlink_msg_lidar_reading_decode(const mavlink_message_t* msg, mavlink_lidar_reading_t* lidar_reading)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_lidar_reading_get_readings(msg, lidar_reading->readings);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LIDAR_READING_LEN? msg->len : MAVLINK_MSG_ID_LIDAR_READING_LEN;
        memset(lidar_reading, 0, MAVLINK_MSG_ID_LIDAR_READING_LEN);
    memcpy(lidar_reading, _MAV_PAYLOAD(msg), len);
#endif
}
