#pragma once
// MESSAGE SCAN_RESULT_INFO PACKING

#define MAVLINK_MSG_ID_SCAN_RESULT_INFO 21


typedef struct __mavlink_scan_result_info_t {
 uint64_t start_time_unix; /*<   Unix start time*/
 uint64_t end_time_unix; /*<   Unix end time*/
 uint32_t num_points; /*<   Number of points*/
 uint32_t file_size_bytes; /*<   Size of the resulting .bin file*/
 uint32_t scan_duration; /*< [seconds]  Duration of the scan, in seconds*/
 uint16_t scan_stop_reason; /*<   Reason for the scan stopping*/
 uint16_t scan_start_reason; /*<   Reason for scan starting*/
 uint8_t type; /*<   What type of info this is, estimated or actual*/
} mavlink_scan_result_info_t;

#define MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN 33
#define MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN 33
#define MAVLINK_MSG_ID_21_LEN 33
#define MAVLINK_MSG_ID_21_MIN_LEN 33

#define MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC 31
#define MAVLINK_MSG_ID_21_CRC 31



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SCAN_RESULT_INFO { \
    21, \
    "SCAN_RESULT_INFO", \
    8, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_scan_result_info_t, type) }, \
         { "num_points", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_scan_result_info_t, num_points) }, \
         { "file_size_bytes", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_scan_result_info_t, file_size_bytes) }, \
         { "start_time_unix", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_scan_result_info_t, start_time_unix) }, \
         { "end_time_unix", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_scan_result_info_t, end_time_unix) }, \
         { "scan_duration", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_scan_result_info_t, scan_duration) }, \
         { "scan_stop_reason", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_scan_result_info_t, scan_stop_reason) }, \
         { "scan_start_reason", NULL, MAVLINK_TYPE_UINT16_T, 0, 30, offsetof(mavlink_scan_result_info_t, scan_start_reason) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SCAN_RESULT_INFO { \
    "SCAN_RESULT_INFO", \
    8, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 32, offsetof(mavlink_scan_result_info_t, type) }, \
         { "num_points", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_scan_result_info_t, num_points) }, \
         { "file_size_bytes", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_scan_result_info_t, file_size_bytes) }, \
         { "start_time_unix", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_scan_result_info_t, start_time_unix) }, \
         { "end_time_unix", NULL, MAVLINK_TYPE_UINT64_T, 0, 8, offsetof(mavlink_scan_result_info_t, end_time_unix) }, \
         { "scan_duration", NULL, MAVLINK_TYPE_UINT32_T, 0, 24, offsetof(mavlink_scan_result_info_t, scan_duration) }, \
         { "scan_stop_reason", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_scan_result_info_t, scan_stop_reason) }, \
         { "scan_start_reason", NULL, MAVLINK_TYPE_UINT16_T, 0, 30, offsetof(mavlink_scan_result_info_t, scan_start_reason) }, \
         } \
}
#endif

/**
 * @brief Pack a scan_result_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type   What type of info this is, estimated or actual
 * @param num_points   Number of points
 * @param file_size_bytes   Size of the resulting .bin file
 * @param start_time_unix   Unix start time
 * @param end_time_unix   Unix end time
 * @param scan_duration [seconds]  Duration of the scan, in seconds
 * @param scan_stop_reason   Reason for the scan stopping
 * @param scan_start_reason   Reason for scan starting
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_result_info_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t type, uint32_t num_points, uint32_t file_size_bytes, uint64_t start_time_unix, uint64_t end_time_unix, uint32_t scan_duration, uint16_t scan_stop_reason, uint16_t scan_start_reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN];
    _mav_put_uint64_t(buf, 0, start_time_unix);
    _mav_put_uint64_t(buf, 8, end_time_unix);
    _mav_put_uint32_t(buf, 16, num_points);
    _mav_put_uint32_t(buf, 20, file_size_bytes);
    _mav_put_uint32_t(buf, 24, scan_duration);
    _mav_put_uint16_t(buf, 28, scan_stop_reason);
    _mav_put_uint16_t(buf, 30, scan_start_reason);
    _mav_put_uint8_t(buf, 32, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
#else
    mavlink_scan_result_info_t packet;
    packet.start_time_unix = start_time_unix;
    packet.end_time_unix = end_time_unix;
    packet.num_points = num_points;
    packet.file_size_bytes = file_size_bytes;
    packet.scan_duration = scan_duration;
    packet.scan_stop_reason = scan_stop_reason;
    packet.scan_start_reason = scan_start_reason;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_RESULT_INFO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
}

/**
 * @brief Pack a scan_result_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param type   What type of info this is, estimated or actual
 * @param num_points   Number of points
 * @param file_size_bytes   Size of the resulting .bin file
 * @param start_time_unix   Unix start time
 * @param end_time_unix   Unix end time
 * @param scan_duration [seconds]  Duration of the scan, in seconds
 * @param scan_stop_reason   Reason for the scan stopping
 * @param scan_start_reason   Reason for scan starting
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_result_info_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t type, uint32_t num_points, uint32_t file_size_bytes, uint64_t start_time_unix, uint64_t end_time_unix, uint32_t scan_duration, uint16_t scan_stop_reason, uint16_t scan_start_reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN];
    _mav_put_uint64_t(buf, 0, start_time_unix);
    _mav_put_uint64_t(buf, 8, end_time_unix);
    _mav_put_uint32_t(buf, 16, num_points);
    _mav_put_uint32_t(buf, 20, file_size_bytes);
    _mav_put_uint32_t(buf, 24, scan_duration);
    _mav_put_uint16_t(buf, 28, scan_stop_reason);
    _mav_put_uint16_t(buf, 30, scan_start_reason);
    _mav_put_uint8_t(buf, 32, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
#else
    mavlink_scan_result_info_t packet;
    packet.start_time_unix = start_time_unix;
    packet.end_time_unix = end_time_unix;
    packet.num_points = num_points;
    packet.file_size_bytes = file_size_bytes;
    packet.scan_duration = scan_duration;
    packet.scan_stop_reason = scan_stop_reason;
    packet.scan_start_reason = scan_start_reason;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_RESULT_INFO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
#endif
}

/**
 * @brief Pack a scan_result_info message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param type   What type of info this is, estimated or actual
 * @param num_points   Number of points
 * @param file_size_bytes   Size of the resulting .bin file
 * @param start_time_unix   Unix start time
 * @param end_time_unix   Unix end time
 * @param scan_duration [seconds]  Duration of the scan, in seconds
 * @param scan_stop_reason   Reason for the scan stopping
 * @param scan_start_reason   Reason for scan starting
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_result_info_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t type,uint32_t num_points,uint32_t file_size_bytes,uint64_t start_time_unix,uint64_t end_time_unix,uint32_t scan_duration,uint16_t scan_stop_reason,uint16_t scan_start_reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN];
    _mav_put_uint64_t(buf, 0, start_time_unix);
    _mav_put_uint64_t(buf, 8, end_time_unix);
    _mav_put_uint32_t(buf, 16, num_points);
    _mav_put_uint32_t(buf, 20, file_size_bytes);
    _mav_put_uint32_t(buf, 24, scan_duration);
    _mav_put_uint16_t(buf, 28, scan_stop_reason);
    _mav_put_uint16_t(buf, 30, scan_start_reason);
    _mav_put_uint8_t(buf, 32, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
#else
    mavlink_scan_result_info_t packet;
    packet.start_time_unix = start_time_unix;
    packet.end_time_unix = end_time_unix;
    packet.num_points = num_points;
    packet.file_size_bytes = file_size_bytes;
    packet.scan_duration = scan_duration;
    packet.scan_stop_reason = scan_stop_reason;
    packet.scan_start_reason = scan_start_reason;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_RESULT_INFO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
}

/**
 * @brief Encode a scan_result_info struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param scan_result_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_result_info_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scan_result_info_t* scan_result_info)
{
    return mavlink_msg_scan_result_info_pack(system_id, component_id, msg, scan_result_info->type, scan_result_info->num_points, scan_result_info->file_size_bytes, scan_result_info->start_time_unix, scan_result_info->end_time_unix, scan_result_info->scan_duration, scan_result_info->scan_stop_reason, scan_result_info->scan_start_reason);
}

/**
 * @brief Encode a scan_result_info struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param scan_result_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_result_info_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scan_result_info_t* scan_result_info)
{
    return mavlink_msg_scan_result_info_pack_chan(system_id, component_id, chan, msg, scan_result_info->type, scan_result_info->num_points, scan_result_info->file_size_bytes, scan_result_info->start_time_unix, scan_result_info->end_time_unix, scan_result_info->scan_duration, scan_result_info->scan_stop_reason, scan_result_info->scan_start_reason);
}

/**
 * @brief Encode a scan_result_info struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param scan_result_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_result_info_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_scan_result_info_t* scan_result_info)
{
    return mavlink_msg_scan_result_info_pack_status(system_id, component_id, _status, msg,  scan_result_info->type, scan_result_info->num_points, scan_result_info->file_size_bytes, scan_result_info->start_time_unix, scan_result_info->end_time_unix, scan_result_info->scan_duration, scan_result_info->scan_stop_reason, scan_result_info->scan_start_reason);
}

/**
 * @brief Send a scan_result_info message
 * @param chan MAVLink channel to send the message
 *
 * @param type   What type of info this is, estimated or actual
 * @param num_points   Number of points
 * @param file_size_bytes   Size of the resulting .bin file
 * @param start_time_unix   Unix start time
 * @param end_time_unix   Unix end time
 * @param scan_duration [seconds]  Duration of the scan, in seconds
 * @param scan_stop_reason   Reason for the scan stopping
 * @param scan_start_reason   Reason for scan starting
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_scan_result_info_send(mavlink_channel_t chan, uint8_t type, uint32_t num_points, uint32_t file_size_bytes, uint64_t start_time_unix, uint64_t end_time_unix, uint32_t scan_duration, uint16_t scan_stop_reason, uint16_t scan_start_reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN];
    _mav_put_uint64_t(buf, 0, start_time_unix);
    _mav_put_uint64_t(buf, 8, end_time_unix);
    _mav_put_uint32_t(buf, 16, num_points);
    _mav_put_uint32_t(buf, 20, file_size_bytes);
    _mav_put_uint32_t(buf, 24, scan_duration);
    _mav_put_uint16_t(buf, 28, scan_stop_reason);
    _mav_put_uint16_t(buf, 30, scan_start_reason);
    _mav_put_uint8_t(buf, 32, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_RESULT_INFO, buf, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
#else
    mavlink_scan_result_info_t packet;
    packet.start_time_unix = start_time_unix;
    packet.end_time_unix = end_time_unix;
    packet.num_points = num_points;
    packet.file_size_bytes = file_size_bytes;
    packet.scan_duration = scan_duration;
    packet.scan_stop_reason = scan_stop_reason;
    packet.scan_start_reason = scan_start_reason;
    packet.type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_RESULT_INFO, (const char *)&packet, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
#endif
}

/**
 * @brief Send a scan_result_info message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_scan_result_info_send_struct(mavlink_channel_t chan, const mavlink_scan_result_info_t* scan_result_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scan_result_info_send(chan, scan_result_info->type, scan_result_info->num_points, scan_result_info->file_size_bytes, scan_result_info->start_time_unix, scan_result_info->end_time_unix, scan_result_info->scan_duration, scan_result_info->scan_stop_reason, scan_result_info->scan_start_reason);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_RESULT_INFO, (const char *)scan_result_info, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
#endif
}

#if MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_scan_result_info_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t type, uint32_t num_points, uint32_t file_size_bytes, uint64_t start_time_unix, uint64_t end_time_unix, uint32_t scan_duration, uint16_t scan_stop_reason, uint16_t scan_start_reason)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, start_time_unix);
    _mav_put_uint64_t(buf, 8, end_time_unix);
    _mav_put_uint32_t(buf, 16, num_points);
    _mav_put_uint32_t(buf, 20, file_size_bytes);
    _mav_put_uint32_t(buf, 24, scan_duration);
    _mav_put_uint16_t(buf, 28, scan_stop_reason);
    _mav_put_uint16_t(buf, 30, scan_start_reason);
    _mav_put_uint8_t(buf, 32, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_RESULT_INFO, buf, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
#else
    mavlink_scan_result_info_t *packet = (mavlink_scan_result_info_t *)msgbuf;
    packet->start_time_unix = start_time_unix;
    packet->end_time_unix = end_time_unix;
    packet->num_points = num_points;
    packet->file_size_bytes = file_size_bytes;
    packet->scan_duration = scan_duration;
    packet->scan_stop_reason = scan_stop_reason;
    packet->scan_start_reason = scan_start_reason;
    packet->type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_RESULT_INFO, (const char *)packet, MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN, MAVLINK_MSG_ID_SCAN_RESULT_INFO_CRC);
#endif
}
#endif

#endif

// MESSAGE SCAN_RESULT_INFO UNPACKING


/**
 * @brief Get field type from scan_result_info message
 *
 * @return   What type of info this is, estimated or actual
 */
static inline uint8_t mavlink_msg_scan_result_info_get_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  32);
}

/**
 * @brief Get field num_points from scan_result_info message
 *
 * @return   Number of points
 */
static inline uint32_t mavlink_msg_scan_result_info_get_num_points(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field file_size_bytes from scan_result_info message
 *
 * @return   Size of the resulting .bin file
 */
static inline uint32_t mavlink_msg_scan_result_info_get_file_size_bytes(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field start_time_unix from scan_result_info message
 *
 * @return   Unix start time
 */
static inline uint64_t mavlink_msg_scan_result_info_get_start_time_unix(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field end_time_unix from scan_result_info message
 *
 * @return   Unix end time
 */
static inline uint64_t mavlink_msg_scan_result_info_get_end_time_unix(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  8);
}

/**
 * @brief Get field scan_duration from scan_result_info message
 *
 * @return [seconds]  Duration of the scan, in seconds
 */
static inline uint32_t mavlink_msg_scan_result_info_get_scan_duration(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  24);
}

/**
 * @brief Get field scan_stop_reason from scan_result_info message
 *
 * @return   Reason for the scan stopping
 */
static inline uint16_t mavlink_msg_scan_result_info_get_scan_stop_reason(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  28);
}

/**
 * @brief Get field scan_start_reason from scan_result_info message
 *
 * @return   Reason for scan starting
 */
static inline uint16_t mavlink_msg_scan_result_info_get_scan_start_reason(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  30);
}

/**
 * @brief Decode a scan_result_info message into a struct
 *
 * @param msg The message to decode
 * @param scan_result_info C-struct to decode the message contents into
 */
static inline void mavlink_msg_scan_result_info_decode(const mavlink_message_t* msg, mavlink_scan_result_info_t* scan_result_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    scan_result_info->start_time_unix = mavlink_msg_scan_result_info_get_start_time_unix(msg);
    scan_result_info->end_time_unix = mavlink_msg_scan_result_info_get_end_time_unix(msg);
    scan_result_info->num_points = mavlink_msg_scan_result_info_get_num_points(msg);
    scan_result_info->file_size_bytes = mavlink_msg_scan_result_info_get_file_size_bytes(msg);
    scan_result_info->scan_duration = mavlink_msg_scan_result_info_get_scan_duration(msg);
    scan_result_info->scan_stop_reason = mavlink_msg_scan_result_info_get_scan_stop_reason(msg);
    scan_result_info->scan_start_reason = mavlink_msg_scan_result_info_get_scan_start_reason(msg);
    scan_result_info->type = mavlink_msg_scan_result_info_get_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN? msg->len : MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN;
        memset(scan_result_info, 0, MAVLINK_MSG_ID_SCAN_RESULT_INFO_LEN);
    memcpy(scan_result_info, _MAV_PAYLOAD(msg), len);
#endif
}
