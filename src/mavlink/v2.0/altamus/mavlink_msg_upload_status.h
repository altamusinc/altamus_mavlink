#pragma once
// MESSAGE UPLOAD_STATUS PACKING

#define MAVLINK_MSG_ID_UPLOAD_STATUS 14


typedef struct __mavlink_upload_status_t {
 uint32_t start_time_unix; /*<   Time that scan started */
 uint32_t bytes_uploaded; /*<   number of bytes uploaded*/
 uint32_t upload_size; /*< [bytes]  Size of the upload*/
 uint16_t upload_rate; /*< [kBps]  Upload rate in kilobytes per seconds*/
 uint16_t time_remaining; /*< [seconds]  Estimated time remaining, in seconds*/
 uint8_t upload_completion; /*< [%]  Percentage complete of the scan */
} mavlink_upload_status_t;

#define MAVLINK_MSG_ID_UPLOAD_STATUS_LEN 17
#define MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN 17
#define MAVLINK_MSG_ID_14_LEN 17
#define MAVLINK_MSG_ID_14_MIN_LEN 17

#define MAVLINK_MSG_ID_UPLOAD_STATUS_CRC 141
#define MAVLINK_MSG_ID_14_CRC 141



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_UPLOAD_STATUS { \
    14, \
    "UPLOAD_STATUS", \
    6, \
    {  { "start_time_unix", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_upload_status_t, start_time_unix) }, \
         { "upload_completion", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_upload_status_t, upload_completion) }, \
         { "bytes_uploaded", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_upload_status_t, bytes_uploaded) }, \
         { "upload_size", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_upload_status_t, upload_size) }, \
         { "upload_rate", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_upload_status_t, upload_rate) }, \
         { "time_remaining", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_upload_status_t, time_remaining) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_UPLOAD_STATUS { \
    "UPLOAD_STATUS", \
    6, \
    {  { "start_time_unix", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_upload_status_t, start_time_unix) }, \
         { "upload_completion", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_upload_status_t, upload_completion) }, \
         { "bytes_uploaded", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_upload_status_t, bytes_uploaded) }, \
         { "upload_size", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_upload_status_t, upload_size) }, \
         { "upload_rate", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_upload_status_t, upload_rate) }, \
         { "time_remaining", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_upload_status_t, time_remaining) }, \
         } \
}
#endif

/**
 * @brief Pack a upload_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param start_time_unix   Time that scan started 
 * @param upload_completion [%]  Percentage complete of the scan 
 * @param bytes_uploaded   number of bytes uploaded
 * @param upload_size [bytes]  Size of the upload
 * @param upload_rate [kBps]  Upload rate in kilobytes per seconds
 * @param time_remaining [seconds]  Estimated time remaining, in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_upload_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t start_time_unix, uint8_t upload_completion, uint32_t bytes_uploaded, uint32_t upload_size, uint16_t upload_rate, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_UPLOAD_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint32_t(buf, 4, bytes_uploaded);
    _mav_put_uint32_t(buf, 8, upload_size);
    _mav_put_uint16_t(buf, 12, upload_rate);
    _mav_put_uint16_t(buf, 14, time_remaining);
    _mav_put_uint8_t(buf, 16, upload_completion);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
#else
    mavlink_upload_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.bytes_uploaded = bytes_uploaded;
    packet.upload_size = upload_size;
    packet.upload_rate = upload_rate;
    packet.time_remaining = time_remaining;
    packet.upload_completion = upload_completion;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_UPLOAD_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
}

/**
 * @brief Pack a upload_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param start_time_unix   Time that scan started 
 * @param upload_completion [%]  Percentage complete of the scan 
 * @param bytes_uploaded   number of bytes uploaded
 * @param upload_size [bytes]  Size of the upload
 * @param upload_rate [kBps]  Upload rate in kilobytes per seconds
 * @param time_remaining [seconds]  Estimated time remaining, in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_upload_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t start_time_unix, uint8_t upload_completion, uint32_t bytes_uploaded, uint32_t upload_size, uint16_t upload_rate, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_UPLOAD_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint32_t(buf, 4, bytes_uploaded);
    _mav_put_uint32_t(buf, 8, upload_size);
    _mav_put_uint16_t(buf, 12, upload_rate);
    _mav_put_uint16_t(buf, 14, time_remaining);
    _mav_put_uint8_t(buf, 16, upload_completion);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
#else
    mavlink_upload_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.bytes_uploaded = bytes_uploaded;
    packet.upload_size = upload_size;
    packet.upload_rate = upload_rate;
    packet.time_remaining = time_remaining;
    packet.upload_completion = upload_completion;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_UPLOAD_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
#endif
}

/**
 * @brief Pack a upload_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param start_time_unix   Time that scan started 
 * @param upload_completion [%]  Percentage complete of the scan 
 * @param bytes_uploaded   number of bytes uploaded
 * @param upload_size [bytes]  Size of the upload
 * @param upload_rate [kBps]  Upload rate in kilobytes per seconds
 * @param time_remaining [seconds]  Estimated time remaining, in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_upload_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t start_time_unix,uint8_t upload_completion,uint32_t bytes_uploaded,uint32_t upload_size,uint16_t upload_rate,uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_UPLOAD_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint32_t(buf, 4, bytes_uploaded);
    _mav_put_uint32_t(buf, 8, upload_size);
    _mav_put_uint16_t(buf, 12, upload_rate);
    _mav_put_uint16_t(buf, 14, time_remaining);
    _mav_put_uint8_t(buf, 16, upload_completion);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
#else
    mavlink_upload_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.bytes_uploaded = bytes_uploaded;
    packet.upload_size = upload_size;
    packet.upload_rate = upload_rate;
    packet.time_remaining = time_remaining;
    packet.upload_completion = upload_completion;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_UPLOAD_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
}

/**
 * @brief Encode a upload_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param upload_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_upload_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_upload_status_t* upload_status)
{
    return mavlink_msg_upload_status_pack(system_id, component_id, msg, upload_status->start_time_unix, upload_status->upload_completion, upload_status->bytes_uploaded, upload_status->upload_size, upload_status->upload_rate, upload_status->time_remaining);
}

/**
 * @brief Encode a upload_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param upload_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_upload_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_upload_status_t* upload_status)
{
    return mavlink_msg_upload_status_pack_chan(system_id, component_id, chan, msg, upload_status->start_time_unix, upload_status->upload_completion, upload_status->bytes_uploaded, upload_status->upload_size, upload_status->upload_rate, upload_status->time_remaining);
}

/**
 * @brief Encode a upload_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param upload_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_upload_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_upload_status_t* upload_status)
{
    return mavlink_msg_upload_status_pack_status(system_id, component_id, _status, msg,  upload_status->start_time_unix, upload_status->upload_completion, upload_status->bytes_uploaded, upload_status->upload_size, upload_status->upload_rate, upload_status->time_remaining);
}

/**
 * @brief Send a upload_status message
 * @param chan MAVLink channel to send the message
 *
 * @param start_time_unix   Time that scan started 
 * @param upload_completion [%]  Percentage complete of the scan 
 * @param bytes_uploaded   number of bytes uploaded
 * @param upload_size [bytes]  Size of the upload
 * @param upload_rate [kBps]  Upload rate in kilobytes per seconds
 * @param time_remaining [seconds]  Estimated time remaining, in seconds
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_upload_status_send(mavlink_channel_t chan, uint32_t start_time_unix, uint8_t upload_completion, uint32_t bytes_uploaded, uint32_t upload_size, uint16_t upload_rate, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_UPLOAD_STATUS_LEN];
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint32_t(buf, 4, bytes_uploaded);
    _mav_put_uint32_t(buf, 8, upload_size);
    _mav_put_uint16_t(buf, 12, upload_rate);
    _mav_put_uint16_t(buf, 14, time_remaining);
    _mav_put_uint8_t(buf, 16, upload_completion);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UPLOAD_STATUS, buf, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
#else
    mavlink_upload_status_t packet;
    packet.start_time_unix = start_time_unix;
    packet.bytes_uploaded = bytes_uploaded;
    packet.upload_size = upload_size;
    packet.upload_rate = upload_rate;
    packet.time_remaining = time_remaining;
    packet.upload_completion = upload_completion;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UPLOAD_STATUS, (const char *)&packet, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
#endif
}

/**
 * @brief Send a upload_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_upload_status_send_struct(mavlink_channel_t chan, const mavlink_upload_status_t* upload_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_upload_status_send(chan, upload_status->start_time_unix, upload_status->upload_completion, upload_status->bytes_uploaded, upload_status->upload_size, upload_status->upload_rate, upload_status->time_remaining);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UPLOAD_STATUS, (const char *)upload_status, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_UPLOAD_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_upload_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t start_time_unix, uint8_t upload_completion, uint32_t bytes_uploaded, uint32_t upload_size, uint16_t upload_rate, uint16_t time_remaining)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, start_time_unix);
    _mav_put_uint32_t(buf, 4, bytes_uploaded);
    _mav_put_uint32_t(buf, 8, upload_size);
    _mav_put_uint16_t(buf, 12, upload_rate);
    _mav_put_uint16_t(buf, 14, time_remaining);
    _mav_put_uint8_t(buf, 16, upload_completion);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UPLOAD_STATUS, buf, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
#else
    mavlink_upload_status_t *packet = (mavlink_upload_status_t *)msgbuf;
    packet->start_time_unix = start_time_unix;
    packet->bytes_uploaded = bytes_uploaded;
    packet->upload_size = upload_size;
    packet->upload_rate = upload_rate;
    packet->time_remaining = time_remaining;
    packet->upload_completion = upload_completion;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_UPLOAD_STATUS, (const char *)packet, MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN, MAVLINK_MSG_ID_UPLOAD_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE UPLOAD_STATUS UNPACKING


/**
 * @brief Get field start_time_unix from upload_status message
 *
 * @return   Time that scan started 
 */
static inline uint32_t mavlink_msg_upload_status_get_start_time_unix(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field upload_completion from upload_status message
 *
 * @return [%]  Percentage complete of the scan 
 */
static inline uint8_t mavlink_msg_upload_status_get_upload_completion(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field bytes_uploaded from upload_status message
 *
 * @return   number of bytes uploaded
 */
static inline uint32_t mavlink_msg_upload_status_get_bytes_uploaded(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field upload_size from upload_status message
 *
 * @return [bytes]  Size of the upload
 */
static inline uint32_t mavlink_msg_upload_status_get_upload_size(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field upload_rate from upload_status message
 *
 * @return [kBps]  Upload rate in kilobytes per seconds
 */
static inline uint16_t mavlink_msg_upload_status_get_upload_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field time_remaining from upload_status message
 *
 * @return [seconds]  Estimated time remaining, in seconds
 */
static inline uint16_t mavlink_msg_upload_status_get_time_remaining(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Decode a upload_status message into a struct
 *
 * @param msg The message to decode
 * @param upload_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_upload_status_decode(const mavlink_message_t* msg, mavlink_upload_status_t* upload_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    upload_status->start_time_unix = mavlink_msg_upload_status_get_start_time_unix(msg);
    upload_status->bytes_uploaded = mavlink_msg_upload_status_get_bytes_uploaded(msg);
    upload_status->upload_size = mavlink_msg_upload_status_get_upload_size(msg);
    upload_status->upload_rate = mavlink_msg_upload_status_get_upload_rate(msg);
    upload_status->time_remaining = mavlink_msg_upload_status_get_time_remaining(msg);
    upload_status->upload_completion = mavlink_msg_upload_status_get_upload_completion(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_UPLOAD_STATUS_LEN? msg->len : MAVLINK_MSG_ID_UPLOAD_STATUS_LEN;
        memset(upload_status, 0, MAVLINK_MSG_ID_UPLOAD_STATUS_LEN);
    memcpy(upload_status, _MAV_PAYLOAD(msg), len);
#endif
}
