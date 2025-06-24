#pragma once
// MESSAGE SCAN_TRANSFORM PACKING

#define MAVLINK_MSG_ID_SCAN_TRANSFORM 22


typedef struct __mavlink_scan_transform_t {
 float roll_offset; /*< [degrees] */
 float pitch_offset; /*< [degrees] */
 float pitch_scale; /*< [%] */
 float yaw_scale; /*< [%] */
} mavlink_scan_transform_t;

#define MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN 16
#define MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN 16
#define MAVLINK_MSG_ID_22_LEN 16
#define MAVLINK_MSG_ID_22_MIN_LEN 16

#define MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC 140
#define MAVLINK_MSG_ID_22_CRC 140



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SCAN_TRANSFORM { \
    22, \
    "SCAN_TRANSFORM", \
    4, \
    {  { "roll_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_scan_transform_t, roll_offset) }, \
         { "pitch_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_scan_transform_t, pitch_offset) }, \
         { "pitch_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_scan_transform_t, pitch_scale) }, \
         { "yaw_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_scan_transform_t, yaw_scale) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SCAN_TRANSFORM { \
    "SCAN_TRANSFORM", \
    4, \
    {  { "roll_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_scan_transform_t, roll_offset) }, \
         { "pitch_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_scan_transform_t, pitch_offset) }, \
         { "pitch_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_scan_transform_t, pitch_scale) }, \
         { "yaw_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_scan_transform_t, yaw_scale) }, \
         } \
}
#endif

/**
 * @brief Pack a scan_transform message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll_offset [degrees] 
 * @param pitch_offset [degrees] 
 * @param pitch_scale [%] 
 * @param yaw_scale [%] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_transform_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
#else
    mavlink_scan_transform_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_TRANSFORM;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
}

/**
 * @brief Pack a scan_transform message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll_offset [degrees] 
 * @param pitch_offset [degrees] 
 * @param pitch_scale [%] 
 * @param yaw_scale [%] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_transform_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
#else
    mavlink_scan_transform_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_TRANSFORM;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
#endif
}

/**
 * @brief Pack a scan_transform message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll_offset [degrees] 
 * @param pitch_offset [degrees] 
 * @param pitch_scale [%] 
 * @param yaw_scale [%] 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_transform_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll_offset,float pitch_offset,float pitch_scale,float yaw_scale)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
#else
    mavlink_scan_transform_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_TRANSFORM;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
}

/**
 * @brief Encode a scan_transform struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param scan_transform C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_transform_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scan_transform_t* scan_transform)
{
    return mavlink_msg_scan_transform_pack(system_id, component_id, msg, scan_transform->roll_offset, scan_transform->pitch_offset, scan_transform->pitch_scale, scan_transform->yaw_scale);
}

/**
 * @brief Encode a scan_transform struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param scan_transform C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_transform_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scan_transform_t* scan_transform)
{
    return mavlink_msg_scan_transform_pack_chan(system_id, component_id, chan, msg, scan_transform->roll_offset, scan_transform->pitch_offset, scan_transform->pitch_scale, scan_transform->yaw_scale);
}

/**
 * @brief Encode a scan_transform struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param scan_transform C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_transform_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_scan_transform_t* scan_transform)
{
    return mavlink_msg_scan_transform_pack_status(system_id, component_id, _status, msg,  scan_transform->roll_offset, scan_transform->pitch_offset, scan_transform->pitch_scale, scan_transform->yaw_scale);
}

/**
 * @brief Send a scan_transform message
 * @param chan MAVLink channel to send the message
 *
 * @param roll_offset [degrees] 
 * @param pitch_offset [degrees] 
 * @param pitch_scale [%] 
 * @param yaw_scale [%] 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_scan_transform_send(mavlink_channel_t chan, float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_TRANSFORM, buf, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
#else
    mavlink_scan_transform_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_TRANSFORM, (const char *)&packet, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
#endif
}

/**
 * @brief Send a scan_transform message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_scan_transform_send_struct(mavlink_channel_t chan, const mavlink_scan_transform_t* scan_transform)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scan_transform_send(chan, scan_transform->roll_offset, scan_transform->pitch_offset, scan_transform->pitch_scale, scan_transform->yaw_scale);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_TRANSFORM, (const char *)scan_transform, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
#endif
}

#if MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_scan_transform_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_TRANSFORM, buf, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
#else
    mavlink_scan_transform_t *packet = (mavlink_scan_transform_t *)msgbuf;
    packet->roll_offset = roll_offset;
    packet->pitch_offset = pitch_offset;
    packet->pitch_scale = pitch_scale;
    packet->yaw_scale = yaw_scale;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_TRANSFORM, (const char *)packet, MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN, MAVLINK_MSG_ID_SCAN_TRANSFORM_CRC);
#endif
}
#endif

#endif

// MESSAGE SCAN_TRANSFORM UNPACKING


/**
 * @brief Get field roll_offset from scan_transform message
 *
 * @return [degrees] 
 */
static inline float mavlink_msg_scan_transform_get_roll_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch_offset from scan_transform message
 *
 * @return [degrees] 
 */
static inline float mavlink_msg_scan_transform_get_pitch_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field pitch_scale from scan_transform message
 *
 * @return [%] 
 */
static inline float mavlink_msg_scan_transform_get_pitch_scale(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field yaw_scale from scan_transform message
 *
 * @return [%] 
 */
static inline float mavlink_msg_scan_transform_get_yaw_scale(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a scan_transform message into a struct
 *
 * @param msg The message to decode
 * @param scan_transform C-struct to decode the message contents into
 */
static inline void mavlink_msg_scan_transform_decode(const mavlink_message_t* msg, mavlink_scan_transform_t* scan_transform)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    scan_transform->roll_offset = mavlink_msg_scan_transform_get_roll_offset(msg);
    scan_transform->pitch_offset = mavlink_msg_scan_transform_get_pitch_offset(msg);
    scan_transform->pitch_scale = mavlink_msg_scan_transform_get_pitch_scale(msg);
    scan_transform->yaw_scale = mavlink_msg_scan_transform_get_yaw_scale(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN? msg->len : MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN;
        memset(scan_transform, 0, MAVLINK_MSG_ID_SCAN_TRANSFORM_LEN);
    memcpy(scan_transform, _MAV_PAYLOAD(msg), len);
#endif
}
