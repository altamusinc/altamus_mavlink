#pragma once
// MESSAGE SCAN_STATUS PACKING

#define MAVLINK_MSG_ID_SCAN_STATUS 10


typedef struct __mavlink_scan_status_t {
 uint32_t start_time_unix; /*<   Time that scan started */
 uint16_t time_remaining; /*< [seconds]  Estimated time remaining in the scan, in seconds*/
 uint8_t scan_completion; /*< [%]  Percentage complete of the scan */
} mavlink_scan_status_t;

#define MAVLINK_MSG_ID_SCAN_STATUS_LEN 7
#define MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN 7
#define MAVLINK_MSG_ID_10_LEN 7
#define MAVLINK_MSG_ID_10_MIN_LEN 7

#define MAVLINK_MSG_ID_SCAN_STATUS_CRC 17
#define MAVLINK_MSG_ID_10_CRC 17



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SCAN_STATUS { \
    10, \
    "SCAN_STATUS", \
    3, \
    {  { "start_time_unix", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_scan_status_t, start_time_unix) }, \
         { "scan_completion", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_scan_status_t, scan_completion) }, \
         { "time_remaining", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_scan_status_t, time_remaining) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SCAN_STATUS { \
    "SCAN_STATUS", \
    3, \
    {  { "start_time_unix", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_scan_status_t, start_time_unix) }, \
         { "scan_completion", NULL, MAVLINK_TYPE_UINT8_T, 0, 6, offsetof(mavlink_scan_status_t, scan_completion) }, \
         { "time_remaining", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_scan_status_t, time_remaining) }, \
         } \
}
#endif

/**
 * @brief Pack a scan_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param start_time_unix   Time that scan started 
 * @param scan_completion [%]  Percentage complete of the scan 
 * @param time_remaining [seconds]  Estimated time remaining in the scan, in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t start_time_unix, uint8_t scan_completion, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint16_t(buf, 4, time_remaining);
    _mav_put_uint8_t(buf, 6, scan_completion);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
#else
    mavlink_scan_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.time_remaining = time_remaining;
    packet.scan_completion = scan_completion;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
}

/**
 * @brief Pack a scan_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param start_time_unix   Time that scan started 
 * @param scan_completion [%]  Percentage complete of the scan 
 * @param time_remaining [seconds]  Estimated time remaining in the scan, in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t start_time_unix, uint8_t scan_completion, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint16_t(buf, 4, time_remaining);
    _mav_put_uint8_t(buf, 6, scan_completion);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
#else
    mavlink_scan_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.time_remaining = time_remaining;
    packet.scan_completion = scan_completion;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
#endif
}

/**
 * @brief Pack a scan_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param start_time_unix   Time that scan started 
 * @param scan_completion [%]  Percentage complete of the scan 
 * @param time_remaining [seconds]  Estimated time remaining in the scan, in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t start_time_unix,uint8_t scan_completion,uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint16_t(buf, 4, time_remaining);
    _mav_put_uint8_t(buf, 6, scan_completion);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
#else
    mavlink_scan_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.time_remaining = time_remaining;
    packet.scan_completion = scan_completion;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
}

/**
 * @brief Encode a scan_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param scan_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scan_status_t* scan_status)
{
    return mavlink_msg_scan_status_pack(system_id, component_id, msg, scan_status->start_time_unix, scan_status->scan_completion, scan_status->time_remaining);
}

/**
 * @brief Encode a scan_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param scan_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scan_status_t* scan_status)
{
    return mavlink_msg_scan_status_pack_chan(system_id, component_id, chan, msg, scan_status->start_time_unix, scan_status->scan_completion, scan_status->time_remaining);
}

/**
 * @brief Encode a scan_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param scan_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_scan_status_t* scan_status)
{
    return mavlink_msg_scan_status_pack_status(system_id, component_id, _status, msg,  scan_status->start_time_unix, scan_status->scan_completion, scan_status->time_remaining);
}

/**
 * @brief Send a scan_status message
 * @param chan MAVLink channel to send the message
 *
 * @param start_time_unix   Time that scan started 
 * @param scan_completion [%]  Percentage complete of the scan 
 * @param time_remaining [seconds]  Estimated time remaining in the scan, in seconds
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_scan_status_send(mavlink_channel_t chan, uint32_t start_time_unix, uint8_t scan_completion, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint16_t(buf, 4, time_remaining);
    _mav_put_uint8_t(buf, 6, scan_completion);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_STATUS, buf, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
#else
    mavlink_scan_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.time_remaining = time_remaining;
    packet.scan_completion = scan_completion;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_STATUS, (const char *)&packet, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
#endif
}

/**
 * @brief Send a scan_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_scan_status_send_struct(mavlink_channel_t chan, const mavlink_scan_status_t* scan_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scan_status_send(chan, scan_status->start_time_unix, scan_status->scan_completion, scan_status->time_remaining);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_STATUS, (const char *)scan_status, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SCAN_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_scan_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t start_time_unix, uint8_t scan_completion, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint16_t(buf, 4, time_remaining);
    _mav_put_uint8_t(buf, 6, scan_completion);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_STATUS, buf, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
#else
    mavlink_scan_status_t *packet = (mavlink_scan_status_t *)msgbuf;
    packet->start_time_unix = start_time_unix;
    packet->time_remaining = time_remaining;
    packet->scan_completion = scan_completion;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_STATUS, (const char *)packet, MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN, MAVLINK_MSG_ID_SCAN_STATUS_LEN, MAVLINK_MSG_ID_SCAN_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE SCAN_STATUS UNPACKING


/**
 * @brief Get field start_time_unix from scan_status message
 *
 * @return   Time that scan started 
 */
static inline uint32_t mavlink_msg_scan_status_get_start_time_unix(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field scan_completion from scan_status message
 *
 * @return [%]  Percentage complete of the scan 
 */
static inline uint8_t mavlink_msg_scan_status_get_scan_completion(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  6);
}

/**
 * @brief Get field time_remaining from scan_status message
 *
 * @return [seconds]  Estimated time remaining in the scan, in seconds
 */
static inline uint16_t mavlink_msg_scan_status_get_time_remaining(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Decode a scan_status message into a struct
 *
 * @param msg The message to decode
 * @param scan_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_scan_status_decode(const mavlink_message_t* msg, mavlink_scan_status_t* scan_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    scan_status->start_time_unix = mavlink_msg_scan_status_get_start_time_unix(msg);
    scan_status->time_remaining = mavlink_msg_scan_status_get_time_remaining(msg);
    scan_status->scan_completion = mavlink_msg_scan_status_get_scan_completion(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SCAN_STATUS_LEN? msg->len : MAVLINK_MSG_ID_SCAN_STATUS_LEN;
        memset(scan_status, 0, MAVLINK_MSG_ID_SCAN_STATUS_LEN);
    memcpy(scan_status, _MAV_PAYLOAD(msg), len);
#endif
}
