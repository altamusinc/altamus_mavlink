#pragma once
// MESSAGE FACTORY_CALIBRATION PACKING

#define MAVLINK_MSG_ID_FACTORY_CALIBRATION 23


typedef struct __mavlink_factory_calibration_t {
 float roll_offset; /*< [degrees] Offset for the mechanical roll error in the scanner */
 float pitch_offset; /*< [degrees] Offset for the pitch alignement error in the scanner*/
 float pitch_scale; /*< [%] Scale to apply to pitch values*/
 float yaw_scale; /*< [%] Scale to apply to the yaw values*/
 float range_scale; /*< [%] Scale to apply to the range values*/
 uint16_t max_range; /*< [cm] Maximum range to use. Points with distances beyond this range will not be converted to viewable points. If set to UINT16_MAX field is ignored and all values are passed*/
 int16_t pitch_home_offset_steps; /*<  Pitch Motor: Number of steps to move from home position after homing.*/
 uint16_t pitch_current; /*<   Motor current 0-2500 */
 int16_t yaw_home_offset_steps; /*<  Pitch Motor: Number of steps to move from home position after homing.*/
 uint16_t yaw_current; /*<   Motor current 0-2500 */
 uint8_t pitch_enforce_minimum_steps; /*<  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled*/
 uint8_t yaw_enforce_minimum_steps; /*<  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled*/
} mavlink_factory_calibration_t;

#define MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN 32
#define MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN 32
#define MAVLINK_MSG_ID_23_LEN 32
#define MAVLINK_MSG_ID_23_MIN_LEN 32

#define MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC 188
#define MAVLINK_MSG_ID_23_CRC 188



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_FACTORY_CALIBRATION { \
    23, \
    "FACTORY_CALIBRATION", \
    12, \
    {  { "roll_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_factory_calibration_t, roll_offset) }, \
         { "pitch_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_factory_calibration_t, pitch_offset) }, \
         { "pitch_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_factory_calibration_t, pitch_scale) }, \
         { "yaw_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_factory_calibration_t, yaw_scale) }, \
         { "range_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_factory_calibration_t, range_scale) }, \
         { "max_range", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_factory_calibration_t, max_range) }, \
         { "pitch_enforce_minimum_steps", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_factory_calibration_t, pitch_enforce_minimum_steps) }, \
         { "pitch_home_offset_steps", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_factory_calibration_t, pitch_home_offset_steps) }, \
         { "pitch_current", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_factory_calibration_t, pitch_current) }, \
         { "yaw_enforce_minimum_steps", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_factory_calibration_t, yaw_enforce_minimum_steps) }, \
         { "yaw_home_offset_steps", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_factory_calibration_t, yaw_home_offset_steps) }, \
         { "yaw_current", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_factory_calibration_t, yaw_current) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_FACTORY_CALIBRATION { \
    "FACTORY_CALIBRATION", \
    12, \
    {  { "roll_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_factory_calibration_t, roll_offset) }, \
         { "pitch_offset", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_factory_calibration_t, pitch_offset) }, \
         { "pitch_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_factory_calibration_t, pitch_scale) }, \
         { "yaw_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_factory_calibration_t, yaw_scale) }, \
         { "range_scale", NULL, MAVLINK_TYPE_FLOAT, 0, 16, offsetof(mavlink_factory_calibration_t, range_scale) }, \
         { "max_range", NULL, MAVLINK_TYPE_UINT16_T, 0, 20, offsetof(mavlink_factory_calibration_t, max_range) }, \
         { "pitch_enforce_minimum_steps", NULL, MAVLINK_TYPE_UINT8_T, 0, 30, offsetof(mavlink_factory_calibration_t, pitch_enforce_minimum_steps) }, \
         { "pitch_home_offset_steps", NULL, MAVLINK_TYPE_INT16_T, 0, 22, offsetof(mavlink_factory_calibration_t, pitch_home_offset_steps) }, \
         { "pitch_current", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_factory_calibration_t, pitch_current) }, \
         { "yaw_enforce_minimum_steps", NULL, MAVLINK_TYPE_UINT8_T, 0, 31, offsetof(mavlink_factory_calibration_t, yaw_enforce_minimum_steps) }, \
         { "yaw_home_offset_steps", NULL, MAVLINK_TYPE_INT16_T, 0, 26, offsetof(mavlink_factory_calibration_t, yaw_home_offset_steps) }, \
         { "yaw_current", NULL, MAVLINK_TYPE_UINT16_T, 0, 28, offsetof(mavlink_factory_calibration_t, yaw_current) }, \
         } \
}
#endif

/**
 * @brief Pack a factory_calibration message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll_offset [degrees] Offset for the mechanical roll error in the scanner 
 * @param pitch_offset [degrees] Offset for the pitch alignement error in the scanner
 * @param pitch_scale [%] Scale to apply to pitch values
 * @param yaw_scale [%] Scale to apply to the yaw values
 * @param range_scale [%] Scale to apply to the range values
 * @param max_range [cm] Maximum range to use. Points with distances beyond this range will not be converted to viewable points. If set to UINT16_MAX field is ignored and all values are passed
 * @param pitch_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param pitch_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param pitch_current   Motor current 0-2500 
 * @param yaw_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param yaw_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param yaw_current   Motor current 0-2500 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_factory_calibration_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale, float range_scale, uint16_t max_range, uint8_t pitch_enforce_minimum_steps, int16_t pitch_home_offset_steps, uint16_t pitch_current, uint8_t yaw_enforce_minimum_steps, int16_t yaw_home_offset_steps, uint16_t yaw_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);
    _mav_put_float(buf, 16, range_scale);
    _mav_put_uint16_t(buf, 20, max_range);
    _mav_put_int16_t(buf, 22, pitch_home_offset_steps);
    _mav_put_uint16_t(buf, 24, pitch_current);
    _mav_put_int16_t(buf, 26, yaw_home_offset_steps);
    _mav_put_uint16_t(buf, 28, yaw_current);
    _mav_put_uint8_t(buf, 30, pitch_enforce_minimum_steps);
    _mav_put_uint8_t(buf, 31, yaw_enforce_minimum_steps);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
#else
    mavlink_factory_calibration_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;
    packet.range_scale = range_scale;
    packet.max_range = max_range;
    packet.pitch_home_offset_steps = pitch_home_offset_steps;
    packet.pitch_current = pitch_current;
    packet.yaw_home_offset_steps = yaw_home_offset_steps;
    packet.yaw_current = yaw_current;
    packet.pitch_enforce_minimum_steps = pitch_enforce_minimum_steps;
    packet.yaw_enforce_minimum_steps = yaw_enforce_minimum_steps;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FACTORY_CALIBRATION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
}

/**
 * @brief Pack a factory_calibration message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll_offset [degrees] Offset for the mechanical roll error in the scanner 
 * @param pitch_offset [degrees] Offset for the pitch alignement error in the scanner
 * @param pitch_scale [%] Scale to apply to pitch values
 * @param yaw_scale [%] Scale to apply to the yaw values
 * @param range_scale [%] Scale to apply to the range values
 * @param max_range [cm] Maximum range to use. Points with distances beyond this range will not be converted to viewable points. If set to UINT16_MAX field is ignored and all values are passed
 * @param pitch_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param pitch_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param pitch_current   Motor current 0-2500 
 * @param yaw_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param yaw_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param yaw_current   Motor current 0-2500 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_factory_calibration_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale, float range_scale, uint16_t max_range, uint8_t pitch_enforce_minimum_steps, int16_t pitch_home_offset_steps, uint16_t pitch_current, uint8_t yaw_enforce_minimum_steps, int16_t yaw_home_offset_steps, uint16_t yaw_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);
    _mav_put_float(buf, 16, range_scale);
    _mav_put_uint16_t(buf, 20, max_range);
    _mav_put_int16_t(buf, 22, pitch_home_offset_steps);
    _mav_put_uint16_t(buf, 24, pitch_current);
    _mav_put_int16_t(buf, 26, yaw_home_offset_steps);
    _mav_put_uint16_t(buf, 28, yaw_current);
    _mav_put_uint8_t(buf, 30, pitch_enforce_minimum_steps);
    _mav_put_uint8_t(buf, 31, yaw_enforce_minimum_steps);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
#else
    mavlink_factory_calibration_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;
    packet.range_scale = range_scale;
    packet.max_range = max_range;
    packet.pitch_home_offset_steps = pitch_home_offset_steps;
    packet.pitch_current = pitch_current;
    packet.yaw_home_offset_steps = yaw_home_offset_steps;
    packet.yaw_current = yaw_current;
    packet.pitch_enforce_minimum_steps = pitch_enforce_minimum_steps;
    packet.yaw_enforce_minimum_steps = yaw_enforce_minimum_steps;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FACTORY_CALIBRATION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
#endif
}

/**
 * @brief Pack a factory_calibration message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll_offset [degrees] Offset for the mechanical roll error in the scanner 
 * @param pitch_offset [degrees] Offset for the pitch alignement error in the scanner
 * @param pitch_scale [%] Scale to apply to pitch values
 * @param yaw_scale [%] Scale to apply to the yaw values
 * @param range_scale [%] Scale to apply to the range values
 * @param max_range [cm] Maximum range to use. Points with distances beyond this range will not be converted to viewable points. If set to UINT16_MAX field is ignored and all values are passed
 * @param pitch_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param pitch_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param pitch_current   Motor current 0-2500 
 * @param yaw_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param yaw_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param yaw_current   Motor current 0-2500 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_factory_calibration_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll_offset,float pitch_offset,float pitch_scale,float yaw_scale,float range_scale,uint16_t max_range,uint8_t pitch_enforce_minimum_steps,int16_t pitch_home_offset_steps,uint16_t pitch_current,uint8_t yaw_enforce_minimum_steps,int16_t yaw_home_offset_steps,uint16_t yaw_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);
    _mav_put_float(buf, 16, range_scale);
    _mav_put_uint16_t(buf, 20, max_range);
    _mav_put_int16_t(buf, 22, pitch_home_offset_steps);
    _mav_put_uint16_t(buf, 24, pitch_current);
    _mav_put_int16_t(buf, 26, yaw_home_offset_steps);
    _mav_put_uint16_t(buf, 28, yaw_current);
    _mav_put_uint8_t(buf, 30, pitch_enforce_minimum_steps);
    _mav_put_uint8_t(buf, 31, yaw_enforce_minimum_steps);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
#else
    mavlink_factory_calibration_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;
    packet.range_scale = range_scale;
    packet.max_range = max_range;
    packet.pitch_home_offset_steps = pitch_home_offset_steps;
    packet.pitch_current = pitch_current;
    packet.yaw_home_offset_steps = yaw_home_offset_steps;
    packet.yaw_current = yaw_current;
    packet.pitch_enforce_minimum_steps = pitch_enforce_minimum_steps;
    packet.yaw_enforce_minimum_steps = yaw_enforce_minimum_steps;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_FACTORY_CALIBRATION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
}

/**
 * @brief Encode a factory_calibration struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param factory_calibration C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_factory_calibration_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_factory_calibration_t* factory_calibration)
{
    return mavlink_msg_factory_calibration_pack(system_id, component_id, msg, factory_calibration->roll_offset, factory_calibration->pitch_offset, factory_calibration->pitch_scale, factory_calibration->yaw_scale, factory_calibration->range_scale, factory_calibration->max_range, factory_calibration->pitch_enforce_minimum_steps, factory_calibration->pitch_home_offset_steps, factory_calibration->pitch_current, factory_calibration->yaw_enforce_minimum_steps, factory_calibration->yaw_home_offset_steps, factory_calibration->yaw_current);
}

/**
 * @brief Encode a factory_calibration struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param factory_calibration C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_factory_calibration_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_factory_calibration_t* factory_calibration)
{
    return mavlink_msg_factory_calibration_pack_chan(system_id, component_id, chan, msg, factory_calibration->roll_offset, factory_calibration->pitch_offset, factory_calibration->pitch_scale, factory_calibration->yaw_scale, factory_calibration->range_scale, factory_calibration->max_range, factory_calibration->pitch_enforce_minimum_steps, factory_calibration->pitch_home_offset_steps, factory_calibration->pitch_current, factory_calibration->yaw_enforce_minimum_steps, factory_calibration->yaw_home_offset_steps, factory_calibration->yaw_current);
}

/**
 * @brief Encode a factory_calibration struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param factory_calibration C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_factory_calibration_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_factory_calibration_t* factory_calibration)
{
    return mavlink_msg_factory_calibration_pack_status(system_id, component_id, _status, msg,  factory_calibration->roll_offset, factory_calibration->pitch_offset, factory_calibration->pitch_scale, factory_calibration->yaw_scale, factory_calibration->range_scale, factory_calibration->max_range, factory_calibration->pitch_enforce_minimum_steps, factory_calibration->pitch_home_offset_steps, factory_calibration->pitch_current, factory_calibration->yaw_enforce_minimum_steps, factory_calibration->yaw_home_offset_steps, factory_calibration->yaw_current);
}

/**
 * @brief Send a factory_calibration message
 * @param chan MAVLink channel to send the message
 *
 * @param roll_offset [degrees] Offset for the mechanical roll error in the scanner 
 * @param pitch_offset [degrees] Offset for the pitch alignement error in the scanner
 * @param pitch_scale [%] Scale to apply to pitch values
 * @param yaw_scale [%] Scale to apply to the yaw values
 * @param range_scale [%] Scale to apply to the range values
 * @param max_range [cm] Maximum range to use. Points with distances beyond this range will not be converted to viewable points. If set to UINT16_MAX field is ignored and all values are passed
 * @param pitch_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param pitch_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param pitch_current   Motor current 0-2500 
 * @param yaw_enforce_minimum_steps  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 * @param yaw_home_offset_steps  Pitch Motor: Number of steps to move from home position after homing.
 * @param yaw_current   Motor current 0-2500 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_factory_calibration_send(mavlink_channel_t chan, float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale, float range_scale, uint16_t max_range, uint8_t pitch_enforce_minimum_steps, int16_t pitch_home_offset_steps, uint16_t pitch_current, uint8_t yaw_enforce_minimum_steps, int16_t yaw_home_offset_steps, uint16_t yaw_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN];
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);
    _mav_put_float(buf, 16, range_scale);
    _mav_put_uint16_t(buf, 20, max_range);
    _mav_put_int16_t(buf, 22, pitch_home_offset_steps);
    _mav_put_uint16_t(buf, 24, pitch_current);
    _mav_put_int16_t(buf, 26, yaw_home_offset_steps);
    _mav_put_uint16_t(buf, 28, yaw_current);
    _mav_put_uint8_t(buf, 30, pitch_enforce_minimum_steps);
    _mav_put_uint8_t(buf, 31, yaw_enforce_minimum_steps);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FACTORY_CALIBRATION, buf, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
#else
    mavlink_factory_calibration_t packet;
    packet.roll_offset = roll_offset;
    packet.pitch_offset = pitch_offset;
    packet.pitch_scale = pitch_scale;
    packet.yaw_scale = yaw_scale;
    packet.range_scale = range_scale;
    packet.max_range = max_range;
    packet.pitch_home_offset_steps = pitch_home_offset_steps;
    packet.pitch_current = pitch_current;
    packet.yaw_home_offset_steps = yaw_home_offset_steps;
    packet.yaw_current = yaw_current;
    packet.pitch_enforce_minimum_steps = pitch_enforce_minimum_steps;
    packet.yaw_enforce_minimum_steps = yaw_enforce_minimum_steps;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FACTORY_CALIBRATION, (const char *)&packet, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
#endif
}

/**
 * @brief Send a factory_calibration message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_factory_calibration_send_struct(mavlink_channel_t chan, const mavlink_factory_calibration_t* factory_calibration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_factory_calibration_send(chan, factory_calibration->roll_offset, factory_calibration->pitch_offset, factory_calibration->pitch_scale, factory_calibration->yaw_scale, factory_calibration->range_scale, factory_calibration->max_range, factory_calibration->pitch_enforce_minimum_steps, factory_calibration->pitch_home_offset_steps, factory_calibration->pitch_current, factory_calibration->yaw_enforce_minimum_steps, factory_calibration->yaw_home_offset_steps, factory_calibration->yaw_current);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FACTORY_CALIBRATION, (const char *)factory_calibration, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
#endif
}

#if MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_factory_calibration_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll_offset, float pitch_offset, float pitch_scale, float yaw_scale, float range_scale, uint16_t max_range, uint8_t pitch_enforce_minimum_steps, int16_t pitch_home_offset_steps, uint16_t pitch_current, uint8_t yaw_enforce_minimum_steps, int16_t yaw_home_offset_steps, uint16_t yaw_current)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll_offset);
    _mav_put_float(buf, 4, pitch_offset);
    _mav_put_float(buf, 8, pitch_scale);
    _mav_put_float(buf, 12, yaw_scale);
    _mav_put_float(buf, 16, range_scale);
    _mav_put_uint16_t(buf, 20, max_range);
    _mav_put_int16_t(buf, 22, pitch_home_offset_steps);
    _mav_put_uint16_t(buf, 24, pitch_current);
    _mav_put_int16_t(buf, 26, yaw_home_offset_steps);
    _mav_put_uint16_t(buf, 28, yaw_current);
    _mav_put_uint8_t(buf, 30, pitch_enforce_minimum_steps);
    _mav_put_uint8_t(buf, 31, yaw_enforce_minimum_steps);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FACTORY_CALIBRATION, buf, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
#else
    mavlink_factory_calibration_t *packet = (mavlink_factory_calibration_t *)msgbuf;
    packet->roll_offset = roll_offset;
    packet->pitch_offset = pitch_offset;
    packet->pitch_scale = pitch_scale;
    packet->yaw_scale = yaw_scale;
    packet->range_scale = range_scale;
    packet->max_range = max_range;
    packet->pitch_home_offset_steps = pitch_home_offset_steps;
    packet->pitch_current = pitch_current;
    packet->yaw_home_offset_steps = yaw_home_offset_steps;
    packet->yaw_current = yaw_current;
    packet->pitch_enforce_minimum_steps = pitch_enforce_minimum_steps;
    packet->yaw_enforce_minimum_steps = yaw_enforce_minimum_steps;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_FACTORY_CALIBRATION, (const char *)packet, MAVLINK_MSG_ID_FACTORY_CALIBRATION_MIN_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN, MAVLINK_MSG_ID_FACTORY_CALIBRATION_CRC);
#endif
}
#endif

#endif

// MESSAGE FACTORY_CALIBRATION UNPACKING


/**
 * @brief Get field roll_offset from factory_calibration message
 *
 * @return [degrees] Offset for the mechanical roll error in the scanner 
 */
static inline float mavlink_msg_factory_calibration_get_roll_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch_offset from factory_calibration message
 *
 * @return [degrees] Offset for the pitch alignement error in the scanner
 */
static inline float mavlink_msg_factory_calibration_get_pitch_offset(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field pitch_scale from factory_calibration message
 *
 * @return [%] Scale to apply to pitch values
 */
static inline float mavlink_msg_factory_calibration_get_pitch_scale(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field yaw_scale from factory_calibration message
 *
 * @return [%] Scale to apply to the yaw values
 */
static inline float mavlink_msg_factory_calibration_get_yaw_scale(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field range_scale from factory_calibration message
 *
 * @return [%] Scale to apply to the range values
 */
static inline float mavlink_msg_factory_calibration_get_range_scale(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  16);
}

/**
 * @brief Get field max_range from factory_calibration message
 *
 * @return [cm] Maximum range to use. Points with distances beyond this range will not be converted to viewable points. If set to UINT16_MAX field is ignored and all values are passed
 */
static inline uint16_t mavlink_msg_factory_calibration_get_max_range(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  20);
}

/**
 * @brief Get field pitch_enforce_minimum_steps from factory_calibration message
 *
 * @return  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 */
static inline uint8_t mavlink_msg_factory_calibration_get_pitch_enforce_minimum_steps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  30);
}

/**
 * @brief Get field pitch_home_offset_steps from factory_calibration message
 *
 * @return  Pitch Motor: Number of steps to move from home position after homing.
 */
static inline int16_t mavlink_msg_factory_calibration_get_pitch_home_offset_steps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  22);
}

/**
 * @brief Get field pitch_current from factory_calibration message
 *
 * @return   Motor current 0-2500 
 */
static inline uint16_t mavlink_msg_factory_calibration_get_pitch_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field yaw_enforce_minimum_steps from factory_calibration message
 *
 * @return  Pitch Motor: Enforce a minimum number of steps to next index. 0 = disabled, 1 = enabled
 */
static inline uint8_t mavlink_msg_factory_calibration_get_yaw_enforce_minimum_steps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  31);
}

/**
 * @brief Get field yaw_home_offset_steps from factory_calibration message
 *
 * @return  Pitch Motor: Number of steps to move from home position after homing.
 */
static inline int16_t mavlink_msg_factory_calibration_get_yaw_home_offset_steps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  26);
}

/**
 * @brief Get field yaw_current from factory_calibration message
 *
 * @return   Motor current 0-2500 
 */
static inline uint16_t mavlink_msg_factory_calibration_get_yaw_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  28);
}

/**
 * @brief Decode a factory_calibration message into a struct
 *
 * @param msg The message to decode
 * @param factory_calibration C-struct to decode the message contents into
 */
static inline void mavlink_msg_factory_calibration_decode(const mavlink_message_t* msg, mavlink_factory_calibration_t* factory_calibration)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    factory_calibration->roll_offset = mavlink_msg_factory_calibration_get_roll_offset(msg);
    factory_calibration->pitch_offset = mavlink_msg_factory_calibration_get_pitch_offset(msg);
    factory_calibration->pitch_scale = mavlink_msg_factory_calibration_get_pitch_scale(msg);
    factory_calibration->yaw_scale = mavlink_msg_factory_calibration_get_yaw_scale(msg);
    factory_calibration->range_scale = mavlink_msg_factory_calibration_get_range_scale(msg);
    factory_calibration->max_range = mavlink_msg_factory_calibration_get_max_range(msg);
    factory_calibration->pitch_home_offset_steps = mavlink_msg_factory_calibration_get_pitch_home_offset_steps(msg);
    factory_calibration->pitch_current = mavlink_msg_factory_calibration_get_pitch_current(msg);
    factory_calibration->yaw_home_offset_steps = mavlink_msg_factory_calibration_get_yaw_home_offset_steps(msg);
    factory_calibration->yaw_current = mavlink_msg_factory_calibration_get_yaw_current(msg);
    factory_calibration->pitch_enforce_minimum_steps = mavlink_msg_factory_calibration_get_pitch_enforce_minimum_steps(msg);
    factory_calibration->yaw_enforce_minimum_steps = mavlink_msg_factory_calibration_get_yaw_enforce_minimum_steps(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN? msg->len : MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN;
        memset(factory_calibration, 0, MAVLINK_MSG_ID_FACTORY_CALIBRATION_LEN);
    memcpy(factory_calibration, _MAV_PAYLOAD(msg), len);
#endif
}
