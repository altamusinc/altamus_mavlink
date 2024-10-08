#pragma once
// MESSAGE MOTOR_CONTROL PACKING

#define MAVLINK_MSG_ID_MOTOR_CONTROL 4


typedef struct __mavlink_motor_control_t {
 float motor_rpm; /*<   RPM to set motor shaft too. Ignores gearing. Only used if MOTOR_BEHAVIOR_MOTOR_RPM is selected. */
 float target_angle; /*<  Angle to goto. Accounts for gearing. 0-360. Values above 360 will be wrapped around.*/
 float device_rpm; /*<   RPM to set device too. Takes into account gearing. Only used if MOTOR_BEHAVIOR_DEVICE_RPM is selected */
 int16_t steps_count; /*<   Number of steps to execute. Negative values will step backwards. Only used if MOTOR_BEHAVIOR_STEP is selected*/
 int16_t vactual; /*<   VACTUAL value to send to stepper driver. Negative values will go backwards. Only used if MOTOR_BEHAVIOR_VACTUAL is selected*/
 uint8_t target; /*<   Which motor to target. Only responds to EOS_COMPONENT_YAW_MOTOR and EOS_COMPONENT_PITCH_MOTOR*/
 uint8_t behavior; /*<   Behavior to Execute */
} mavlink_motor_control_t;

#define MAVLINK_MSG_ID_MOTOR_CONTROL_LEN 18
#define MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN 18
#define MAVLINK_MSG_ID_4_LEN 18
#define MAVLINK_MSG_ID_4_MIN_LEN 18

#define MAVLINK_MSG_ID_MOTOR_CONTROL_CRC 37
#define MAVLINK_MSG_ID_4_CRC 37



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_CONTROL { \
    4, \
    "MOTOR_CONTROL", \
    7, \
    {  { "target", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_motor_control_t, target) }, \
         { "behavior", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_motor_control_t, behavior) }, \
         { "motor_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_control_t, motor_rpm) }, \
         { "target_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_control_t, target_angle) }, \
         { "device_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_control_t, device_rpm) }, \
         { "steps_count", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_motor_control_t, steps_count) }, \
         { "vactual", NULL, MAVLINK_TYPE_INT16_T, 0, 14, offsetof(mavlink_motor_control_t, vactual) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_CONTROL { \
    "MOTOR_CONTROL", \
    7, \
    {  { "target", NULL, MAVLINK_TYPE_UINT8_T, 0, 16, offsetof(mavlink_motor_control_t, target) }, \
         { "behavior", NULL, MAVLINK_TYPE_UINT8_T, 0, 17, offsetof(mavlink_motor_control_t, behavior) }, \
         { "motor_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_control_t, motor_rpm) }, \
         { "target_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_control_t, target_angle) }, \
         { "device_rpm", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_control_t, device_rpm) }, \
         { "steps_count", NULL, MAVLINK_TYPE_INT16_T, 0, 12, offsetof(mavlink_motor_control_t, steps_count) }, \
         { "vactual", NULL, MAVLINK_TYPE_INT16_T, 0, 14, offsetof(mavlink_motor_control_t, vactual) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target   Which motor to target. Only responds to EOS_COMPONENT_YAW_MOTOR and EOS_COMPONENT_PITCH_MOTOR
 * @param behavior   Behavior to Execute 
 * @param motor_rpm   RPM to set motor shaft too. Ignores gearing. Only used if MOTOR_BEHAVIOR_MOTOR_RPM is selected. 
 * @param target_angle  Angle to goto. Accounts for gearing. 0-360. Values above 360 will be wrapped around.
 * @param device_rpm   RPM to set device too. Takes into account gearing. Only used if MOTOR_BEHAVIOR_DEVICE_RPM is selected 
 * @param steps_count   Number of steps to execute. Negative values will step backwards. Only used if MOTOR_BEHAVIOR_STEP is selected
 * @param vactual   VACTUAL value to send to stepper driver. Negative values will go backwards. Only used if MOTOR_BEHAVIOR_VACTUAL is selected
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target, uint8_t behavior, float motor_rpm, float target_angle, float device_rpm, int16_t steps_count, int16_t vactual)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_CONTROL_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, target_angle);
    _mav_put_float(buf, 8, device_rpm);
    _mav_put_int16_t(buf, 12, steps_count);
    _mav_put_int16_t(buf, 14, vactual);
    _mav_put_uint8_t(buf, 16, target);
    _mav_put_uint8_t(buf, 17, behavior);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
#else
    mavlink_motor_control_t packet;
    packet.motor_rpm = motor_rpm;
    packet.target_angle = target_angle;
    packet.device_rpm = device_rpm;
    packet.steps_count = steps_count;
    packet.vactual = vactual;
    packet.target = target;
    packet.behavior = behavior;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
}

/**
 * @brief Pack a motor_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param target   Which motor to target. Only responds to EOS_COMPONENT_YAW_MOTOR and EOS_COMPONENT_PITCH_MOTOR
 * @param behavior   Behavior to Execute 
 * @param motor_rpm   RPM to set motor shaft too. Ignores gearing. Only used if MOTOR_BEHAVIOR_MOTOR_RPM is selected. 
 * @param target_angle  Angle to goto. Accounts for gearing. 0-360. Values above 360 will be wrapped around.
 * @param device_rpm   RPM to set device too. Takes into account gearing. Only used if MOTOR_BEHAVIOR_DEVICE_RPM is selected 
 * @param steps_count   Number of steps to execute. Negative values will step backwards. Only used if MOTOR_BEHAVIOR_STEP is selected
 * @param vactual   VACTUAL value to send to stepper driver. Negative values will go backwards. Only used if MOTOR_BEHAVIOR_VACTUAL is selected
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_control_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t target, uint8_t behavior, float motor_rpm, float target_angle, float device_rpm, int16_t steps_count, int16_t vactual)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_CONTROL_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, target_angle);
    _mav_put_float(buf, 8, device_rpm);
    _mav_put_int16_t(buf, 12, steps_count);
    _mav_put_int16_t(buf, 14, vactual);
    _mav_put_uint8_t(buf, 16, target);
    _mav_put_uint8_t(buf, 17, behavior);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
#else
    mavlink_motor_control_t packet;
    packet.motor_rpm = motor_rpm;
    packet.target_angle = target_angle;
    packet.device_rpm = device_rpm;
    packet.steps_count = steps_count;
    packet.vactual = vactual;
    packet.target = target;
    packet.behavior = behavior;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
#endif
}

/**
 * @brief Pack a motor_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target   Which motor to target. Only responds to EOS_COMPONENT_YAW_MOTOR and EOS_COMPONENT_PITCH_MOTOR
 * @param behavior   Behavior to Execute 
 * @param motor_rpm   RPM to set motor shaft too. Ignores gearing. Only used if MOTOR_BEHAVIOR_MOTOR_RPM is selected. 
 * @param target_angle  Angle to goto. Accounts for gearing. 0-360. Values above 360 will be wrapped around.
 * @param device_rpm   RPM to set device too. Takes into account gearing. Only used if MOTOR_BEHAVIOR_DEVICE_RPM is selected 
 * @param steps_count   Number of steps to execute. Negative values will step backwards. Only used if MOTOR_BEHAVIOR_STEP is selected
 * @param vactual   VACTUAL value to send to stepper driver. Negative values will go backwards. Only used if MOTOR_BEHAVIOR_VACTUAL is selected
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target,uint8_t behavior,float motor_rpm,float target_angle,float device_rpm,int16_t steps_count,int16_t vactual)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_CONTROL_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, target_angle);
    _mav_put_float(buf, 8, device_rpm);
    _mav_put_int16_t(buf, 12, steps_count);
    _mav_put_int16_t(buf, 14, vactual);
    _mav_put_uint8_t(buf, 16, target);
    _mav_put_uint8_t(buf, 17, behavior);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
#else
    mavlink_motor_control_t packet;
    packet.motor_rpm = motor_rpm;
    packet.target_angle = target_angle;
    packet.device_rpm = device_rpm;
    packet.steps_count = steps_count;
    packet.vactual = vactual;
    packet.target = target;
    packet.behavior = behavior;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
}

/**
 * @brief Encode a motor_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_control_t* motor_control)
{
    return mavlink_msg_motor_control_pack(system_id, component_id, msg, motor_control->target, motor_control->behavior, motor_control->motor_rpm, motor_control->target_angle, motor_control->device_rpm, motor_control->steps_count, motor_control->vactual);
}

/**
 * @brief Encode a motor_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_control_t* motor_control)
{
    return mavlink_msg_motor_control_pack_chan(system_id, component_id, chan, msg, motor_control->target, motor_control->behavior, motor_control->motor_rpm, motor_control->target_angle, motor_control->device_rpm, motor_control->steps_count, motor_control->vactual);
}

/**
 * @brief Encode a motor_control struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motor_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_control_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motor_control_t* motor_control)
{
    return mavlink_msg_motor_control_pack_status(system_id, component_id, _status, msg,  motor_control->target, motor_control->behavior, motor_control->motor_rpm, motor_control->target_angle, motor_control->device_rpm, motor_control->steps_count, motor_control->vactual);
}

/**
 * @brief Send a motor_control message
 * @param chan MAVLink channel to send the message
 *
 * @param target   Which motor to target. Only responds to EOS_COMPONENT_YAW_MOTOR and EOS_COMPONENT_PITCH_MOTOR
 * @param behavior   Behavior to Execute 
 * @param motor_rpm   RPM to set motor shaft too. Ignores gearing. Only used if MOTOR_BEHAVIOR_MOTOR_RPM is selected. 
 * @param target_angle  Angle to goto. Accounts for gearing. 0-360. Values above 360 will be wrapped around.
 * @param device_rpm   RPM to set device too. Takes into account gearing. Only used if MOTOR_BEHAVIOR_DEVICE_RPM is selected 
 * @param steps_count   Number of steps to execute. Negative values will step backwards. Only used if MOTOR_BEHAVIOR_STEP is selected
 * @param vactual   VACTUAL value to send to stepper driver. Negative values will go backwards. Only used if MOTOR_BEHAVIOR_VACTUAL is selected
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_control_send(mavlink_channel_t chan, uint8_t target, uint8_t behavior, float motor_rpm, float target_angle, float device_rpm, int16_t steps_count, int16_t vactual)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_CONTROL_LEN];
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, target_angle);
    _mav_put_float(buf, 8, device_rpm);
    _mav_put_int16_t(buf, 12, steps_count);
    _mav_put_int16_t(buf, 14, vactual);
    _mav_put_uint8_t(buf, 16, target);
    _mav_put_uint8_t(buf, 17, behavior);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_CONTROL, buf, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
#else
    mavlink_motor_control_t packet;
    packet.motor_rpm = motor_rpm;
    packet.target_angle = target_angle;
    packet.device_rpm = device_rpm;
    packet.steps_count = steps_count;
    packet.vactual = vactual;
    packet.target = target;
    packet.behavior = behavior;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
#endif
}

/**
 * @brief Send a motor_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motor_control_send_struct(mavlink_channel_t chan, const mavlink_motor_control_t* motor_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motor_control_send(chan, motor_control->target, motor_control->behavior, motor_control->motor_rpm, motor_control->target_angle, motor_control->device_rpm, motor_control->steps_count, motor_control->vactual);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_CONTROL, (const char *)motor_control, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOTOR_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target, uint8_t behavior, float motor_rpm, float target_angle, float device_rpm, int16_t steps_count, int16_t vactual)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, motor_rpm);
    _mav_put_float(buf, 4, target_angle);
    _mav_put_float(buf, 8, device_rpm);
    _mav_put_int16_t(buf, 12, steps_count);
    _mav_put_int16_t(buf, 14, vactual);
    _mav_put_uint8_t(buf, 16, target);
    _mav_put_uint8_t(buf, 17, behavior);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_CONTROL, buf, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
#else
    mavlink_motor_control_t *packet = (mavlink_motor_control_t *)msgbuf;
    packet->motor_rpm = motor_rpm;
    packet->target_angle = target_angle;
    packet->device_rpm = device_rpm;
    packet->steps_count = steps_count;
    packet->vactual = vactual;
    packet->target = target;
    packet->behavior = behavior;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_CONTROL, (const char *)packet, MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN, MAVLINK_MSG_ID_MOTOR_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_CONTROL UNPACKING


/**
 * @brief Get field target from motor_control message
 *
 * @return   Which motor to target. Only responds to EOS_COMPONENT_YAW_MOTOR and EOS_COMPONENT_PITCH_MOTOR
 */
static inline uint8_t mavlink_msg_motor_control_get_target(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  16);
}

/**
 * @brief Get field behavior from motor_control message
 *
 * @return   Behavior to Execute 
 */
static inline uint8_t mavlink_msg_motor_control_get_behavior(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  17);
}

/**
 * @brief Get field motor_rpm from motor_control message
 *
 * @return   RPM to set motor shaft too. Ignores gearing. Only used if MOTOR_BEHAVIOR_MOTOR_RPM is selected. 
 */
static inline float mavlink_msg_motor_control_get_motor_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field target_angle from motor_control message
 *
 * @return  Angle to goto. Accounts for gearing. 0-360. Values above 360 will be wrapped around.
 */
static inline float mavlink_msg_motor_control_get_target_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field device_rpm from motor_control message
 *
 * @return   RPM to set device too. Takes into account gearing. Only used if MOTOR_BEHAVIOR_DEVICE_RPM is selected 
 */
static inline float mavlink_msg_motor_control_get_device_rpm(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field steps_count from motor_control message
 *
 * @return   Number of steps to execute. Negative values will step backwards. Only used if MOTOR_BEHAVIOR_STEP is selected
 */
static inline int16_t mavlink_msg_motor_control_get_steps_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  12);
}

/**
 * @brief Get field vactual from motor_control message
 *
 * @return   VACTUAL value to send to stepper driver. Negative values will go backwards. Only used if MOTOR_BEHAVIOR_VACTUAL is selected
 */
static inline int16_t mavlink_msg_motor_control_get_vactual(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  14);
}

/**
 * @brief Decode a motor_control message into a struct
 *
 * @param msg The message to decode
 * @param motor_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_control_decode(const mavlink_message_t* msg, mavlink_motor_control_t* motor_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motor_control->motor_rpm = mavlink_msg_motor_control_get_motor_rpm(msg);
    motor_control->target_angle = mavlink_msg_motor_control_get_target_angle(msg);
    motor_control->device_rpm = mavlink_msg_motor_control_get_device_rpm(msg);
    motor_control->steps_count = mavlink_msg_motor_control_get_steps_count(msg);
    motor_control->vactual = mavlink_msg_motor_control_get_vactual(msg);
    motor_control->target = mavlink_msg_motor_control_get_target(msg);
    motor_control->behavior = mavlink_msg_motor_control_get_behavior(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_CONTROL_LEN;
        memset(motor_control, 0, MAVLINK_MSG_ID_MOTOR_CONTROL_LEN);
    memcpy(motor_control, _MAV_PAYLOAD(msg), len);
#endif
}
