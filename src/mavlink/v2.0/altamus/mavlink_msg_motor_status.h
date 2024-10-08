#pragma once
// MESSAGE MOTOR_STATUS PACKING

#define MAVLINK_MSG_ID_MOTOR_STATUS 6


typedef struct __mavlink_motor_status_t {
 float motor_rpm; /*<  Current RPM of the motor.*/
 float device_rpm; /*<  Current RPM of the device, accounting for gearing.*/
 float measured_rpm; /*<   Measured RPM, if external sensor is available*/
 float current_angle; /*<  Current angle: 0-360. INF if not homed.*/
 uint16_t vactual; /*<  Current VACTUAL value.*/
 int16_t steps_count; /*<  Number of steps from home. UINT16_MAX if motor is in RPM mode.*/
 uint8_t motor; /*<  Which motor we're referring to.*/
 uint8_t enabled; /*<  Boolean if the motor is enabled or not. 0 = disabled, 1 = enabled.*/
 uint8_t homed; /*<  Boolean if the motor is homed or not. 0 = not homed, 1 = homed.*/
} mavlink_motor_status_t;

#define MAVLINK_MSG_ID_MOTOR_STATUS_LEN 23
#define MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN 23
#define MAVLINK_MSG_ID_6_LEN 23
#define MAVLINK_MSG_ID_6_MIN_LEN 23

#define MAVLINK_MSG_ID_MOTOR_STATUS_CRC 61
#define MAVLINK_MSG_ID_6_CRC 61



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_STATUS { \
    6, \
    "MOTOR_STATUS", \
    9, \
    {  { "motor", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_motor_status_t, motor) }, \
         { "enabled", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_motor_status_t, enabled) }, \
         { "homed", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_motor_status_t, homed) }, \
         { "motor_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_status_t, motor_rpm) }, \
         { "device_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_status_t, device_rpm) }, \
         { "measured_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_status_t, measured_rpm) }, \
         { "vactual", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_motor_status_t, vactual) }, \
         { "steps_count", NULL, MAVLINK_TYPE_INT16_T, 0, 18, offsetof(mavlink_motor_status_t, steps_count) }, \
         { "current_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_motor_status_t, current_angle) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_STATUS { \
    "MOTOR_STATUS", \
    9, \
    {  { "motor", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_motor_status_t, motor) }, \
         { "enabled", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_motor_status_t, enabled) }, \
         { "homed", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_motor_status_t, homed) }, \
         { "motor_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_status_t, motor_rpm) }, \
         { "device_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_status_t, device_rpm) }, \
         { "measured_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_status_t, measured_rpm) }, \
         { "vactual", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_motor_status_t, vactual) }, \
         { "steps_count", NULL, MAVLINK_TYPE_INT16_T, 0, 18, offsetof(mavlink_motor_status_t, steps_count) }, \
         { "current_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_motor_status_t, current_angle) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param motor  Which motor we're referring to.
 * @param enabled  Boolean if the motor is enabled or not. 0 = disabled, 1 = enabled.
 * @param homed  Boolean if the motor is homed or not. 0 = not homed, 1 = homed.
 * @param motor_rpm  Current RPM of the motor.
 * @param device_rpm  Current RPM of the device, accounting for gearing.
 * @param measured_rpm   Measured RPM, if external sensor is available
 * @param vactual  Current VACTUAL value.
 * @param steps_count  Number of steps from home. UINT16_MAX if motor is in RPM mode.
 * @param current_angle  Current angle: 0-360. INF if not homed.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t motor, uint8_t enabled, uint8_t homed, float motor_rpm, float device_rpm, float measured_rpm, uint16_t vactual, int16_t steps_count, float current_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_STATUS_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, device_rpm);
    _mav_put_float(buf, 8, measured_rpm);
    _mav_put_float(buf, 12, current_angle);
    _mav_put_uint16_t(buf, 16, vactual);
    _mav_put_int16_t(buf, 18, steps_count);
    _mav_put_uint8_t(buf, 20, motor);
    _mav_put_uint8_t(buf, 21, enabled);
    _mav_put_uint8_t(buf, 22, homed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
#else
    mavlink_motor_status_t packet;
    packet.motor_rpm = motor_rpm;
    packet.device_rpm = device_rpm;
    packet.measured_rpm = measured_rpm;
    packet.current_angle = current_angle;
    packet.vactual = vactual;
    packet.steps_count = steps_count;
    packet.motor = motor;
    packet.enabled = enabled;
    packet.homed = homed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
}

/**
 * @brief Pack a motor_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param motor  Which motor we're referring to.
 * @param enabled  Boolean if the motor is enabled or not. 0 = disabled, 1 = enabled.
 * @param homed  Boolean if the motor is homed or not. 0 = not homed, 1 = homed.
 * @param motor_rpm  Current RPM of the motor.
 * @param device_rpm  Current RPM of the device, accounting for gearing.
 * @param measured_rpm   Measured RPM, if external sensor is available
 * @param vactual  Current VACTUAL value.
 * @param steps_count  Number of steps from home. UINT16_MAX if motor is in RPM mode.
 * @param current_angle  Current angle: 0-360. INF if not homed.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t motor, uint8_t enabled, uint8_t homed, float motor_rpm, float device_rpm, float measured_rpm, uint16_t vactual, int16_t steps_count, float current_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_STATUS_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, device_rpm);
    _mav_put_float(buf, 8, measured_rpm);
    _mav_put_float(buf, 12, current_angle);
    _mav_put_uint16_t(buf, 16, vactual);
    _mav_put_int16_t(buf, 18, steps_count);
    _mav_put_uint8_t(buf, 20, motor);
    _mav_put_uint8_t(buf, 21, enabled);
    _mav_put_uint8_t(buf, 22, homed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
#else
    mavlink_motor_status_t packet;
    packet.motor_rpm = motor_rpm;
    packet.device_rpm = device_rpm;
    packet.measured_rpm = measured_rpm;
    packet.current_angle = current_angle;
    packet.vactual = vactual;
    packet.steps_count = steps_count;
    packet.motor = motor;
    packet.enabled = enabled;
    packet.homed = homed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
#endif
}

/**
 * @brief Pack a motor_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor  Which motor we're referring to.
 * @param enabled  Boolean if the motor is enabled or not. 0 = disabled, 1 = enabled.
 * @param homed  Boolean if the motor is homed or not. 0 = not homed, 1 = homed.
 * @param motor_rpm  Current RPM of the motor.
 * @param device_rpm  Current RPM of the device, accounting for gearing.
 * @param measured_rpm   Measured RPM, if external sensor is available
 * @param vactual  Current VACTUAL value.
 * @param steps_count  Number of steps from home. UINT16_MAX if motor is in RPM mode.
 * @param current_angle  Current angle: 0-360. INF if not homed.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t motor,uint8_t enabled,uint8_t homed,float motor_rpm,float device_rpm,float measured_rpm,uint16_t vactual,int16_t steps_count,float current_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_STATUS_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, device_rpm);
    _mav_put_float(buf, 8, measured_rpm);
    _mav_put_float(buf, 12, current_angle);
    _mav_put_uint16_t(buf, 16, vactual);
    _mav_put_int16_t(buf, 18, steps_count);
    _mav_put_uint8_t(buf, 20, motor);
    _mav_put_uint8_t(buf, 21, enabled);
    _mav_put_uint8_t(buf, 22, homed);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
#else
    mavlink_motor_status_t packet;
    packet.motor_rpm = motor_rpm;
    packet.device_rpm = device_rpm;
    packet.measured_rpm = measured_rpm;
    packet.current_angle = current_angle;
    packet.vactual = vactual;
    packet.steps_count = steps_count;
    packet.motor = motor;
    packet.enabled = enabled;
    packet.homed = homed;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
}

/**
 * @brief Encode a motor_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_status_t* motor_status)
{
    return mavlink_msg_motor_status_pack(system_id, component_id, msg, motor_status->motor, motor_status->enabled, motor_status->homed, motor_status->motor_rpm, motor_status->device_rpm, motor_status->measured_rpm, motor_status->vactual, motor_status->steps_count, motor_status->current_angle);
}

/**
 * @brief Encode a motor_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_status_t* motor_status)
{
    return mavlink_msg_motor_status_pack_chan(system_id, component_id, chan, msg, motor_status->motor, motor_status->enabled, motor_status->homed, motor_status->motor_rpm, motor_status->device_rpm, motor_status->measured_rpm, motor_status->vactual, motor_status->steps_count, motor_status->current_angle);
}

/**
 * @brief Encode a motor_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motor_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motor_status_t* motor_status)
{
    return mavlink_msg_motor_status_pack_status(system_id, component_id, _status, msg,  motor_status->motor, motor_status->enabled, motor_status->homed, motor_status->motor_rpm, motor_status->device_rpm, motor_status->measured_rpm, motor_status->vactual, motor_status->steps_count, motor_status->current_angle);
}

/**
 * @brief Send a motor_status message
 * @param chan MAVLink channel to send the message
 *
 * @param motor  Which motor we're referring to.
 * @param enabled  Boolean if the motor is enabled or not. 0 = disabled, 1 = enabled.
 * @param homed  Boolean if the motor is homed or not. 0 = not homed, 1 = homed.
 * @param motor_rpm  Current RPM of the motor.
 * @param device_rpm  Current RPM of the device, accounting for gearing.
 * @param measured_rpm   Measured RPM, if external sensor is available
 * @param vactual  Current VACTUAL value.
 * @param steps_count  Number of steps from home. UINT16_MAX if motor is in RPM mode.
 * @param current_angle  Current angle: 0-360. INF if not homed.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_status_send(mavlink_channel_t chan, uint8_t motor, uint8_t enabled, uint8_t homed, float motor_rpm, float device_rpm, float measured_rpm, uint16_t vactual, int16_t steps_count, float current_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_STATUS_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, device_rpm);
    _mav_put_float(buf, 8, measured_rpm);
    _mav_put_float(buf, 12, current_angle);
    _mav_put_uint16_t(buf, 16, vactual);
    _mav_put_int16_t(buf, 18, steps_count);
    _mav_put_uint8_t(buf, 20, motor);
    _mav_put_uint8_t(buf, 21, enabled);
    _mav_put_uint8_t(buf, 22, homed);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATUS, buf, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
#else
    mavlink_motor_status_t packet;
    packet.motor_rpm = motor_rpm;
    packet.device_rpm = device_rpm;
    packet.measured_rpm = measured_rpm;
    packet.current_angle = current_angle;
    packet.vactual = vactual;
    packet.steps_count = steps_count;
    packet.motor = motor;
    packet.enabled = enabled;
    packet.homed = homed;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATUS, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
#endif
}

/**
 * @brief Send a motor_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motor_status_send_struct(mavlink_channel_t chan, const mavlink_motor_status_t* motor_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motor_status_send(chan, motor_status->motor, motor_status->enabled, motor_status->homed, motor_status->motor_rpm, motor_status->device_rpm, motor_status->measured_rpm, motor_status->vactual, motor_status->steps_count, motor_status->current_angle);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATUS, (const char *)motor_status, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOTOR_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t motor, uint8_t enabled, uint8_t homed, float motor_rpm, float device_rpm, float measured_rpm, uint16_t vactual, int16_t steps_count, float current_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, device_rpm);
    _mav_put_float(buf, 8, measured_rpm);
    _mav_put_float(buf, 12, current_angle);
    _mav_put_uint16_t(buf, 16, vactual);
    _mav_put_int16_t(buf, 18, steps_count);
    _mav_put_uint8_t(buf, 20, motor);
    _mav_put_uint8_t(buf, 21, enabled);
    _mav_put_uint8_t(buf, 22, homed);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATUS, buf, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
#else
    mavlink_motor_status_t *packet = (mavlink_motor_status_t *)msgbuf;
    packet->motor_rpm = motor_rpm;
    packet->device_rpm = device_rpm;
    packet->measured_rpm = measured_rpm;
    packet->current_angle = current_angle;
    packet->vactual = vactual;
    packet->steps_count = steps_count;
    packet->motor = motor;
    packet->enabled = enabled;
    packet->homed = homed;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_STATUS, (const char *)packet, MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_LEN, MAVLINK_MSG_ID_MOTOR_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_STATUS UNPACKING


/**
 * @brief Get field motor from motor_status message
 *
 * @return  Which motor we're referring to.
 */
static inline uint8_t mavlink_msg_motor_status_get_motor(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field enabled from motor_status message
 *
 * @return  Boolean if the motor is enabled or not. 0 = disabled, 1 = enabled.
 */
static inline uint8_t mavlink_msg_motor_status_get_enabled(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  21);
}

/**
 * @brief Get field homed from motor_status message
 *
 * @return  Boolean if the motor is homed or not. 0 = not homed, 1 = homed.
 */
static inline uint8_t mavlink_msg_motor_status_get_homed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  22);
}

/**
 * @brief Get field motor_rpm from motor_status message
 *
 * @return  Current RPM of the motor.
 */
static inline float mavlink_msg_motor_status_get_motor_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field device_rpm from motor_status message
 *
 * @return  Current RPM of the device, accounting for gearing.
 */
static inline float mavlink_msg_motor_status_get_device_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field measured_rpm from motor_status message
 *
 * @return   Measured RPM, if external sensor is available
 */
static inline float mavlink_msg_motor_status_get_measured_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field vactual from motor_status message
 *
 * @return  Current VACTUAL value.
 */
static inline uint16_t mavlink_msg_motor_status_get_vactual(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field steps_count from motor_status message
 *
 * @return  Number of steps from home. UINT16_MAX if motor is in RPM mode.
 */
static inline int16_t mavlink_msg_motor_status_get_steps_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  18);
}

/**
 * @brief Get field current_angle from motor_status message
 *
 * @return  Current angle: 0-360. INF if not homed.
 */
static inline float mavlink_msg_motor_status_get_current_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Decode a motor_status message into a struct
 *
 * @param msg The message to decode
 * @param motor_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_status_decode(const mavlink_message_t* msg, mavlink_motor_status_t* motor_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motor_status->motor_rpm = mavlink_msg_motor_status_get_motor_rpm(msg);
    motor_status->device_rpm = mavlink_msg_motor_status_get_device_rpm(msg);
    motor_status->measured_rpm = mavlink_msg_motor_status_get_measured_rpm(msg);
    motor_status->current_angle = mavlink_msg_motor_status_get_current_angle(msg);
    motor_status->vactual = mavlink_msg_motor_status_get_vactual(msg);
    motor_status->steps_count = mavlink_msg_motor_status_get_steps_count(msg);
    motor_status->motor = mavlink_msg_motor_status_get_motor(msg);
    motor_status->enabled = mavlink_msg_motor_status_get_enabled(msg);
    motor_status->homed = mavlink_msg_motor_status_get_homed(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_STATUS_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_STATUS_LEN;
        memset(motor_status, 0, MAVLINK_MSG_ID_MOTOR_STATUS_LEN);
    memcpy(motor_status, _MAV_PAYLOAD(msg), len);
#endif
}
