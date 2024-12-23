#pragma once
// MESSAGE SCAN_SETTINGS PACKING

#define MAVLINK_MSG_ID_SCAN_SETTINGS 9


typedef struct __mavlink_scan_settings_t {
 float yaw_start; /*< [deg]  Starting yaw angle, relative to the homed position */
 float yaw_stop; /*< [deg]  Ending yaw angle, relative to the homed position*/
 float pitch_start; /*< [deg]  Starting pitch angle, relative to the homed position*/
 float pitch_stop; /*< [deg]  Ending pitch angle, relative to the homed position*/
 float pitch_rest_angle; /*< [deg]  Angle that the pitch to should go to at end of the scan*/
 float point_spacing; /*< [deg]  Spacing between point samples. Smaller spacing leads to denser point clouds */
 float scan_speed; /*< [rpm]  How fast, in RPM to spin the pitch motor*/
 uint16_t scan_stop_reasons; /*<   Bitmask of allowed reasons for the scan to stop. 0 means that no detected errors will stop the scan. */
} mavlink_scan_settings_t;

#define MAVLINK_MSG_ID_SCAN_SETTINGS_LEN 30
#define MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN 30
#define MAVLINK_MSG_ID_9_LEN 30
#define MAVLINK_MSG_ID_9_MIN_LEN 30

#define MAVLINK_MSG_ID_SCAN_SETTINGS_CRC 92
#define MAVLINK_MSG_ID_9_CRC 92



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SCAN_SETTINGS { \
    9, \
    "SCAN_SETTINGS", \
    8, \
    {  { "yaw_start", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_scan_settings_t, yaw_start) }, \
         { "yaw_stop", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_scan_settings_t, yaw_stop) }, \
         { "pitch_start", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_scan_settings_t, pitch_start) }, \
         { "pitch_stop", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_scan_settings_t, pitch_stop) }, \
         { "pitch_rest_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_scan_settings_t, pitch_rest_angle) }, \
         { "point_spacing", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_scan_settings_t, point_spacing) }, \
         { "scan_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_scan_settings_t, scan_speed) }, \
         { "scan_stop_reasons", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_scan_settings_t, scan_stop_reasons) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SCAN_SETTINGS { \
    "SCAN_SETTINGS", \
    8, \
    {  { "yaw_start", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_scan_settings_t, yaw_start) }, \
         { "yaw_stop", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_scan_settings_t, yaw_stop) }, \
         { "pitch_start", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_scan_settings_t, pitch_start) }, \
         { "pitch_stop", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_scan_settings_t, pitch_stop) }, \
         { "pitch_rest_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_scan_settings_t, pitch_rest_angle) }, \
         { "point_spacing", NULL, MAVLINK_TYPE_FLOAT, 0, 20, offsetof(mavlink_scan_settings_t, point_spacing) }, \
         { "scan_speed", NULL, MAVLINK_TYPE_FLOAT, 0, 24, offsetof(mavlink_scan_settings_t, scan_speed) }, \
         { "scan_stop_reasons", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_scan_settings_t, scan_stop_reasons) }, \
         } \
}
#endif

/**
 * @brief Pack a scan_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param yaw_start [deg]  Starting yaw angle, relative to the homed position 
 * @param yaw_stop [deg]  Ending yaw angle, relative to the homed position
 * @param pitch_start [deg]  Starting pitch angle, relative to the homed position
 * @param pitch_stop [deg]  Ending pitch angle, relative to the homed position
 * @param pitch_rest_angle [deg]  Angle that the pitch to should go to at end of the scan
 * @param point_spacing [deg]  Spacing between point samples. Smaller spacing leads to denser point clouds 
 * @param scan_speed [rpm]  How fast, in RPM to spin the pitch motor
 * @param scan_stop_reasons   Bitmask of allowed reasons for the scan to stop. 0 means that no detected errors will stop the scan. 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_settings_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float yaw_start, float yaw_stop, float pitch_start, float pitch_stop, float pitch_rest_angle, float point_spacing, float scan_speed, uint16_t scan_stop_reasons)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_SETTINGS_LEN];
    _mav_put_float(buf, 0, yaw_start);
    _mav_put_float(buf, 4, yaw_stop);
    _mav_put_float(buf, 8, pitch_start);
    _mav_put_float(buf, 12, pitch_stop);
    _mav_put_float(buf, 16, pitch_rest_angle);
    _mav_put_float(buf, 20, point_spacing);
    _mav_put_float(buf, 24, scan_speed);
    _mav_put_uint16_t(buf, 28, scan_stop_reasons);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
#else
    mavlink_scan_settings_t packet;
    packet.yaw_start = yaw_start;
    packet.yaw_stop = yaw_stop;
    packet.pitch_start = pitch_start;
    packet.pitch_stop = pitch_stop;
    packet.pitch_rest_angle = pitch_rest_angle;
    packet.point_spacing = point_spacing;
    packet.scan_speed = scan_speed;
    packet.scan_stop_reasons = scan_stop_reasons;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_SETTINGS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
}

/**
 * @brief Pack a scan_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param yaw_start [deg]  Starting yaw angle, relative to the homed position 
 * @param yaw_stop [deg]  Ending yaw angle, relative to the homed position
 * @param pitch_start [deg]  Starting pitch angle, relative to the homed position
 * @param pitch_stop [deg]  Ending pitch angle, relative to the homed position
 * @param pitch_rest_angle [deg]  Angle that the pitch to should go to at end of the scan
 * @param point_spacing [deg]  Spacing between point samples. Smaller spacing leads to denser point clouds 
 * @param scan_speed [rpm]  How fast, in RPM to spin the pitch motor
 * @param scan_stop_reasons   Bitmask of allowed reasons for the scan to stop. 0 means that no detected errors will stop the scan. 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_settings_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float yaw_start, float yaw_stop, float pitch_start, float pitch_stop, float pitch_rest_angle, float point_spacing, float scan_speed, uint16_t scan_stop_reasons)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_SETTINGS_LEN];
    _mav_put_float(buf, 0, yaw_start);
    _mav_put_float(buf, 4, yaw_stop);
    _mav_put_float(buf, 8, pitch_start);
    _mav_put_float(buf, 12, pitch_stop);
    _mav_put_float(buf, 16, pitch_rest_angle);
    _mav_put_float(buf, 20, point_spacing);
    _mav_put_float(buf, 24, scan_speed);
    _mav_put_uint16_t(buf, 28, scan_stop_reasons);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
#else
    mavlink_scan_settings_t packet;
    packet.yaw_start = yaw_start;
    packet.yaw_stop = yaw_stop;
    packet.pitch_start = pitch_start;
    packet.pitch_stop = pitch_stop;
    packet.pitch_rest_angle = pitch_rest_angle;
    packet.point_spacing = point_spacing;
    packet.scan_speed = scan_speed;
    packet.scan_stop_reasons = scan_stop_reasons;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_SETTINGS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
#endif
}

/**
 * @brief Pack a scan_settings message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param yaw_start [deg]  Starting yaw angle, relative to the homed position 
 * @param yaw_stop [deg]  Ending yaw angle, relative to the homed position
 * @param pitch_start [deg]  Starting pitch angle, relative to the homed position
 * @param pitch_stop [deg]  Ending pitch angle, relative to the homed position
 * @param pitch_rest_angle [deg]  Angle that the pitch to should go to at end of the scan
 * @param point_spacing [deg]  Spacing between point samples. Smaller spacing leads to denser point clouds 
 * @param scan_speed [rpm]  How fast, in RPM to spin the pitch motor
 * @param scan_stop_reasons   Bitmask of allowed reasons for the scan to stop. 0 means that no detected errors will stop the scan. 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_scan_settings_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float yaw_start,float yaw_stop,float pitch_start,float pitch_stop,float pitch_rest_angle,float point_spacing,float scan_speed,uint16_t scan_stop_reasons)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_SETTINGS_LEN];
    _mav_put_float(buf, 0, yaw_start);
    _mav_put_float(buf, 4, yaw_stop);
    _mav_put_float(buf, 8, pitch_start);
    _mav_put_float(buf, 12, pitch_stop);
    _mav_put_float(buf, 16, pitch_rest_angle);
    _mav_put_float(buf, 20, point_spacing);
    _mav_put_float(buf, 24, scan_speed);
    _mav_put_uint16_t(buf, 28, scan_stop_reasons);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
#else
    mavlink_scan_settings_t packet;
    packet.yaw_start = yaw_start;
    packet.yaw_stop = yaw_stop;
    packet.pitch_start = pitch_start;
    packet.pitch_stop = pitch_stop;
    packet.pitch_rest_angle = pitch_rest_angle;
    packet.point_spacing = point_spacing;
    packet.scan_speed = scan_speed;
    packet.scan_stop_reasons = scan_stop_reasons;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SCAN_SETTINGS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
}

/**
 * @brief Encode a scan_settings struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param scan_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_settings_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_scan_settings_t* scan_settings)
{
    return mavlink_msg_scan_settings_pack(system_id, component_id, msg, scan_settings->yaw_start, scan_settings->yaw_stop, scan_settings->pitch_start, scan_settings->pitch_stop, scan_settings->pitch_rest_angle, scan_settings->point_spacing, scan_settings->scan_speed, scan_settings->scan_stop_reasons);
}

/**
 * @brief Encode a scan_settings struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param scan_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_settings_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_scan_settings_t* scan_settings)
{
    return mavlink_msg_scan_settings_pack_chan(system_id, component_id, chan, msg, scan_settings->yaw_start, scan_settings->yaw_stop, scan_settings->pitch_start, scan_settings->pitch_stop, scan_settings->pitch_rest_angle, scan_settings->point_spacing, scan_settings->scan_speed, scan_settings->scan_stop_reasons);
}

/**
 * @brief Encode a scan_settings struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param scan_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_scan_settings_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_scan_settings_t* scan_settings)
{
    return mavlink_msg_scan_settings_pack_status(system_id, component_id, _status, msg,  scan_settings->yaw_start, scan_settings->yaw_stop, scan_settings->pitch_start, scan_settings->pitch_stop, scan_settings->pitch_rest_angle, scan_settings->point_spacing, scan_settings->scan_speed, scan_settings->scan_stop_reasons);
}

/**
 * @brief Send a scan_settings message
 * @param chan MAVLink channel to send the message
 *
 * @param yaw_start [deg]  Starting yaw angle, relative to the homed position 
 * @param yaw_stop [deg]  Ending yaw angle, relative to the homed position
 * @param pitch_start [deg]  Starting pitch angle, relative to the homed position
 * @param pitch_stop [deg]  Ending pitch angle, relative to the homed position
 * @param pitch_rest_angle [deg]  Angle that the pitch to should go to at end of the scan
 * @param point_spacing [deg]  Spacing between point samples. Smaller spacing leads to denser point clouds 
 * @param scan_speed [rpm]  How fast, in RPM to spin the pitch motor
 * @param scan_stop_reasons   Bitmask of allowed reasons for the scan to stop. 0 means that no detected errors will stop the scan. 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_scan_settings_send(mavlink_channel_t chan, float yaw_start, float yaw_stop, float pitch_start, float pitch_stop, float pitch_rest_angle, float point_spacing, float scan_speed, uint16_t scan_stop_reasons)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SCAN_SETTINGS_LEN];
    _mav_put_float(buf, 0, yaw_start);
    _mav_put_float(buf, 4, yaw_stop);
    _mav_put_float(buf, 8, pitch_start);
    _mav_put_float(buf, 12, pitch_stop);
    _mav_put_float(buf, 16, pitch_rest_angle);
    _mav_put_float(buf, 20, point_spacing);
    _mav_put_float(buf, 24, scan_speed);
    _mav_put_uint16_t(buf, 28, scan_stop_reasons);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_SETTINGS, buf, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
#else
    mavlink_scan_settings_t packet;
    packet.yaw_start = yaw_start;
    packet.yaw_stop = yaw_stop;
    packet.pitch_start = pitch_start;
    packet.pitch_stop = pitch_stop;
    packet.pitch_rest_angle = pitch_rest_angle;
    packet.point_spacing = point_spacing;
    packet.scan_speed = scan_speed;
    packet.scan_stop_reasons = scan_stop_reasons;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_SETTINGS, (const char *)&packet, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
#endif
}

/**
 * @brief Send a scan_settings message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_scan_settings_send_struct(mavlink_channel_t chan, const mavlink_scan_settings_t* scan_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_scan_settings_send(chan, scan_settings->yaw_start, scan_settings->yaw_stop, scan_settings->pitch_start, scan_settings->pitch_stop, scan_settings->pitch_rest_angle, scan_settings->point_spacing, scan_settings->scan_speed, scan_settings->scan_stop_reasons);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_SETTINGS, (const char *)scan_settings, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SCAN_SETTINGS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_scan_settings_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float yaw_start, float yaw_stop, float pitch_start, float pitch_stop, float pitch_rest_angle, float point_spacing, float scan_speed, uint16_t scan_stop_reasons)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, yaw_start);
    _mav_put_float(buf, 4, yaw_stop);
    _mav_put_float(buf, 8, pitch_start);
    _mav_put_float(buf, 12, pitch_stop);
    _mav_put_float(buf, 16, pitch_rest_angle);
    _mav_put_float(buf, 20, point_spacing);
    _mav_put_float(buf, 24, scan_speed);
    _mav_put_uint16_t(buf, 28, scan_stop_reasons);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_SETTINGS, buf, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
#else
    mavlink_scan_settings_t *packet = (mavlink_scan_settings_t *)msgbuf;
    packet->yaw_start = yaw_start;
    packet->yaw_stop = yaw_stop;
    packet->pitch_start = pitch_start;
    packet->pitch_stop = pitch_stop;
    packet->pitch_rest_angle = pitch_rest_angle;
    packet->point_spacing = point_spacing;
    packet->scan_speed = scan_speed;
    packet->scan_stop_reasons = scan_stop_reasons;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SCAN_SETTINGS, (const char *)packet, MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN, MAVLINK_MSG_ID_SCAN_SETTINGS_CRC);
#endif
}
#endif

#endif

// MESSAGE SCAN_SETTINGS UNPACKING


/**
 * @brief Get field yaw_start from scan_settings message
 *
 * @return [deg]  Starting yaw angle, relative to the homed position 
 */
static inline float mavlink_msg_scan_settings_get_yaw_start(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field yaw_stop from scan_settings message
 *
 * @return [deg]  Ending yaw angle, relative to the homed position
 */
static inline float mavlink_msg_scan_settings_get_yaw_stop(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field pitch_start from scan_settings message
 *
 * @return [deg]  Starting pitch angle, relative to the homed position
 */
static inline float mavlink_msg_scan_settings_get_pitch_start(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field pitch_stop from scan_settings message
 *
 * @return [deg]  Ending pitch angle, relative to the homed position
 */
static inline float mavlink_msg_scan_settings_get_pitch_stop(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field pitch_rest_angle from scan_settings message
 *
 * @return [deg]  Angle that the pitch to should go to at end of the scan
 */
static inline float mavlink_msg_scan_settings_get_pitch_rest_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field point_spacing from scan_settings message
 *
 * @return [deg]  Spacing between point samples. Smaller spacing leads to denser point clouds 
 */
static inline float mavlink_msg_scan_settings_get_point_spacing(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  20);
}

/**
 * @brief Get field scan_speed from scan_settings message
 *
 * @return [rpm]  How fast, in RPM to spin the pitch motor
 */
static inline float mavlink_msg_scan_settings_get_scan_speed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  24);
}

/**
 * @brief Get field scan_stop_reasons from scan_settings message
 *
 * @return   Bitmask of allowed reasons for the scan to stop. 0 means that no detected errors will stop the scan. 
 */
static inline uint16_t mavlink_msg_scan_settings_get_scan_stop_reasons(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  28);
}

/**
 * @brief Decode a scan_settings message into a struct
 *
 * @param msg The message to decode
 * @param scan_settings C-struct to decode the message contents into
 */
static inline void mavlink_msg_scan_settings_decode(const mavlink_message_t* msg, mavlink_scan_settings_t* scan_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    scan_settings->yaw_start = mavlink_msg_scan_settings_get_yaw_start(msg);
    scan_settings->yaw_stop = mavlink_msg_scan_settings_get_yaw_stop(msg);
    scan_settings->pitch_start = mavlink_msg_scan_settings_get_pitch_start(msg);
    scan_settings->pitch_stop = mavlink_msg_scan_settings_get_pitch_stop(msg);
    scan_settings->pitch_rest_angle = mavlink_msg_scan_settings_get_pitch_rest_angle(msg);
    scan_settings->point_spacing = mavlink_msg_scan_settings_get_point_spacing(msg);
    scan_settings->scan_speed = mavlink_msg_scan_settings_get_scan_speed(msg);
    scan_settings->scan_stop_reasons = mavlink_msg_scan_settings_get_scan_stop_reasons(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SCAN_SETTINGS_LEN? msg->len : MAVLINK_MSG_ID_SCAN_SETTINGS_LEN;
        memset(scan_settings, 0, MAVLINK_MSG_ID_SCAN_SETTINGS_LEN);
    memcpy(scan_settings, _MAV_PAYLOAD(msg), len);
#endif
}
