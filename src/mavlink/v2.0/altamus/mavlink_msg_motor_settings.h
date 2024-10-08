#pragma once
// MESSAGE MOTOR_SETTINGS PACKING

#define MAVLINK_MSG_ID_MOTOR_SETTINGS 5


typedef struct __mavlink_motor_settings_t {
 float gearing_ratio; /*<   Gearing ratio to apply, specified as Motor Teeth:Device Teeth; Send as float i.e. 20.0/72.0 becomes 0.2777777*/
 float usteps_rate; /*< [Hz] Rate at which microsteps are being triggered by the driver internal oscillator. Read Only.*/
 float ustep_angle; /*< [deg] Device angle travelled per microstep. Read Only.*/
 uint16_t current; /*<   Motor current 0-2500 */
 uint16_t home_offset_steps; /*<  Number of steps to move from home position after homing.*/
 uint16_t steps_to_next_index; /*<  Number of steps from home switch triggering to repeatable index pulse. Read Only.*/
 uint8_t motor; /*<  Which motor we're referring to.*/
 uint8_t microsteps; /*<   Microsteps used for stepping 1-256 in powers of 2*/
 uint8_t spread_cycle; /*<  Boolean if spread cycle is enabled. 0 = disabled, 1 = enabled*/
 uint8_t pwm_autoscale; /*<  Boolean if pwm_autoscale is enabled. 0 = disabled, 1 = enabled*/
 uint8_t pwm_autograd; /*<  Boolean if pwm_autograd is enabled. 0 = disabled, 1 = enabled*/
 uint8_t min_steps_to_next_index; /*<  Mininimum steps between index pulse and home switch. Set to 0 to not enforce a minimum*/
} mavlink_motor_settings_t;

#define MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN 24
#define MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN 24
#define MAVLINK_MSG_ID_5_LEN 24
#define MAVLINK_MSG_ID_5_MIN_LEN 24

#define MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC 39
#define MAVLINK_MSG_ID_5_CRC 39



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_MOTOR_SETTINGS { \
    5, \
    "MOTOR_SETTINGS", \
    12, \
    {  { "motor", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_motor_settings_t, motor) }, \
         { "current", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_motor_settings_t, current) }, \
         { "microsteps", NULL, MAVLINK_TYPE_UINT8_T, 0, 19, offsetof(mavlink_motor_settings_t, microsteps) }, \
         { "gearing_ratio", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_settings_t, gearing_ratio) }, \
         { "spread_cycle", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_motor_settings_t, spread_cycle) }, \
         { "pwm_autoscale", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_motor_settings_t, pwm_autoscale) }, \
         { "pwm_autograd", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_motor_settings_t, pwm_autograd) }, \
         { "min_steps_to_next_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 23, offsetof(mavlink_motor_settings_t, min_steps_to_next_index) }, \
         { "home_offset_steps", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_motor_settings_t, home_offset_steps) }, \
         { "steps_to_next_index", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_motor_settings_t, steps_to_next_index) }, \
         { "usteps_rate", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_settings_t, usteps_rate) }, \
         { "ustep_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_settings_t, ustep_angle) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_MOTOR_SETTINGS { \
    "MOTOR_SETTINGS", \
    12, \
    {  { "motor", NULL, MAVLINK_TYPE_UINT8_T, 0, 18, offsetof(mavlink_motor_settings_t, motor) }, \
         { "current", NULL, MAVLINK_TYPE_UINT16_T, 0, 12, offsetof(mavlink_motor_settings_t, current) }, \
         { "microsteps", NULL, MAVLINK_TYPE_UINT8_T, 0, 19, offsetof(mavlink_motor_settings_t, microsteps) }, \
         { "gearing_ratio", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_motor_settings_t, gearing_ratio) }, \
         { "spread_cycle", NULL, MAVLINK_TYPE_UINT8_T, 0, 20, offsetof(mavlink_motor_settings_t, spread_cycle) }, \
         { "pwm_autoscale", NULL, MAVLINK_TYPE_UINT8_T, 0, 21, offsetof(mavlink_motor_settings_t, pwm_autoscale) }, \
         { "pwm_autograd", NULL, MAVLINK_TYPE_UINT8_T, 0, 22, offsetof(mavlink_motor_settings_t, pwm_autograd) }, \
         { "min_steps_to_next_index", NULL, MAVLINK_TYPE_UINT8_T, 0, 23, offsetof(mavlink_motor_settings_t, min_steps_to_next_index) }, \
         { "home_offset_steps", NULL, MAVLINK_TYPE_UINT16_T, 0, 14, offsetof(mavlink_motor_settings_t, home_offset_steps) }, \
         { "steps_to_next_index", NULL, MAVLINK_TYPE_UINT16_T, 0, 16, offsetof(mavlink_motor_settings_t, steps_to_next_index) }, \
         { "usteps_rate", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_motor_settings_t, usteps_rate) }, \
         { "ustep_angle", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_motor_settings_t, ustep_angle) }, \
         } \
}
#endif

/**
 * @brief Pack a motor_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param motor  Which motor we're referring to.
 * @param current   Motor current 0-2500 
 * @param microsteps   Microsteps used for stepping 1-256 in powers of 2
 * @param gearing_ratio   Gearing ratio to apply, specified as Motor Teeth:Device Teeth; Send as float i.e. 20.0/72.0 becomes 0.2777777
 * @param spread_cycle  Boolean if spread cycle is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autoscale  Boolean if pwm_autoscale is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autograd  Boolean if pwm_autograd is enabled. 0 = disabled, 1 = enabled
 * @param min_steps_to_next_index  Mininimum steps between index pulse and home switch. Set to 0 to not enforce a minimum
 * @param home_offset_steps  Number of steps to move from home position after homing.
 * @param steps_to_next_index  Number of steps from home switch triggering to repeatable index pulse. Read Only.
 * @param usteps_rate [Hz] Rate at which microsteps are being triggered by the driver internal oscillator. Read Only.
 * @param ustep_angle [deg] Device angle travelled per microstep. Read Only.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_settings_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t motor, uint16_t current, uint8_t microsteps, float gearing_ratio, uint8_t spread_cycle, uint8_t pwm_autoscale, uint8_t pwm_autograd, uint8_t min_steps_to_next_index, uint16_t home_offset_steps, uint16_t steps_to_next_index, float usteps_rate, float ustep_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN];
    _mav_put_float(buf, 0, gearing_ratio);
    _mav_put_float(buf, 4, usteps_rate);
    _mav_put_float(buf, 8, ustep_angle);
    _mav_put_uint16_t(buf, 12, current);
    _mav_put_uint16_t(buf, 14, home_offset_steps);
    _mav_put_uint16_t(buf, 16, steps_to_next_index);
    _mav_put_uint8_t(buf, 18, motor);
    _mav_put_uint8_t(buf, 19, microsteps);
    _mav_put_uint8_t(buf, 20, spread_cycle);
    _mav_put_uint8_t(buf, 21, pwm_autoscale);
    _mav_put_uint8_t(buf, 22, pwm_autograd);
    _mav_put_uint8_t(buf, 23, min_steps_to_next_index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
#else
    mavlink_motor_settings_t packet;
    packet.gearing_ratio = gearing_ratio;
    packet.usteps_rate = usteps_rate;
    packet.ustep_angle = ustep_angle;
    packet.current = current;
    packet.home_offset_steps = home_offset_steps;
    packet.steps_to_next_index = steps_to_next_index;
    packet.motor = motor;
    packet.microsteps = microsteps;
    packet.spread_cycle = spread_cycle;
    packet.pwm_autoscale = pwm_autoscale;
    packet.pwm_autograd = pwm_autograd;
    packet.min_steps_to_next_index = min_steps_to_next_index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_SETTINGS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
}

/**
 * @brief Pack a motor_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param motor  Which motor we're referring to.
 * @param current   Motor current 0-2500 
 * @param microsteps   Microsteps used for stepping 1-256 in powers of 2
 * @param gearing_ratio   Gearing ratio to apply, specified as Motor Teeth:Device Teeth; Send as float i.e. 20.0/72.0 becomes 0.2777777
 * @param spread_cycle  Boolean if spread cycle is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autoscale  Boolean if pwm_autoscale is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autograd  Boolean if pwm_autograd is enabled. 0 = disabled, 1 = enabled
 * @param min_steps_to_next_index  Mininimum steps between index pulse and home switch. Set to 0 to not enforce a minimum
 * @param home_offset_steps  Number of steps to move from home position after homing.
 * @param steps_to_next_index  Number of steps from home switch triggering to repeatable index pulse. Read Only.
 * @param usteps_rate [Hz] Rate at which microsteps are being triggered by the driver internal oscillator. Read Only.
 * @param ustep_angle [deg] Device angle travelled per microstep. Read Only.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_settings_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t motor, uint16_t current, uint8_t microsteps, float gearing_ratio, uint8_t spread_cycle, uint8_t pwm_autoscale, uint8_t pwm_autograd, uint8_t min_steps_to_next_index, uint16_t home_offset_steps, uint16_t steps_to_next_index, float usteps_rate, float ustep_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN];
    _mav_put_float(buf, 0, gearing_ratio);
    _mav_put_float(buf, 4, usteps_rate);
    _mav_put_float(buf, 8, ustep_angle);
    _mav_put_uint16_t(buf, 12, current);
    _mav_put_uint16_t(buf, 14, home_offset_steps);
    _mav_put_uint16_t(buf, 16, steps_to_next_index);
    _mav_put_uint8_t(buf, 18, motor);
    _mav_put_uint8_t(buf, 19, microsteps);
    _mav_put_uint8_t(buf, 20, spread_cycle);
    _mav_put_uint8_t(buf, 21, pwm_autoscale);
    _mav_put_uint8_t(buf, 22, pwm_autograd);
    _mav_put_uint8_t(buf, 23, min_steps_to_next_index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
#else
    mavlink_motor_settings_t packet;
    packet.gearing_ratio = gearing_ratio;
    packet.usteps_rate = usteps_rate;
    packet.ustep_angle = ustep_angle;
    packet.current = current;
    packet.home_offset_steps = home_offset_steps;
    packet.steps_to_next_index = steps_to_next_index;
    packet.motor = motor;
    packet.microsteps = microsteps;
    packet.spread_cycle = spread_cycle;
    packet.pwm_autoscale = pwm_autoscale;
    packet.pwm_autograd = pwm_autograd;
    packet.min_steps_to_next_index = min_steps_to_next_index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_SETTINGS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
#endif
}

/**
 * @brief Pack a motor_settings message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor  Which motor we're referring to.
 * @param current   Motor current 0-2500 
 * @param microsteps   Microsteps used for stepping 1-256 in powers of 2
 * @param gearing_ratio   Gearing ratio to apply, specified as Motor Teeth:Device Teeth; Send as float i.e. 20.0/72.0 becomes 0.2777777
 * @param spread_cycle  Boolean if spread cycle is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autoscale  Boolean if pwm_autoscale is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autograd  Boolean if pwm_autograd is enabled. 0 = disabled, 1 = enabled
 * @param min_steps_to_next_index  Mininimum steps between index pulse and home switch. Set to 0 to not enforce a minimum
 * @param home_offset_steps  Number of steps to move from home position after homing.
 * @param steps_to_next_index  Number of steps from home switch triggering to repeatable index pulse. Read Only.
 * @param usteps_rate [Hz] Rate at which microsteps are being triggered by the driver internal oscillator. Read Only.
 * @param ustep_angle [deg] Device angle travelled per microstep. Read Only.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_motor_settings_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t motor,uint16_t current,uint8_t microsteps,float gearing_ratio,uint8_t spread_cycle,uint8_t pwm_autoscale,uint8_t pwm_autograd,uint8_t min_steps_to_next_index,uint16_t home_offset_steps,uint16_t steps_to_next_index,float usteps_rate,float ustep_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN];
    _mav_put_float(buf, 0, gearing_ratio);
    _mav_put_float(buf, 4, usteps_rate);
    _mav_put_float(buf, 8, ustep_angle);
    _mav_put_uint16_t(buf, 12, current);
    _mav_put_uint16_t(buf, 14, home_offset_steps);
    _mav_put_uint16_t(buf, 16, steps_to_next_index);
    _mav_put_uint8_t(buf, 18, motor);
    _mav_put_uint8_t(buf, 19, microsteps);
    _mav_put_uint8_t(buf, 20, spread_cycle);
    _mav_put_uint8_t(buf, 21, pwm_autoscale);
    _mav_put_uint8_t(buf, 22, pwm_autograd);
    _mav_put_uint8_t(buf, 23, min_steps_to_next_index);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
#else
    mavlink_motor_settings_t packet;
    packet.gearing_ratio = gearing_ratio;
    packet.usteps_rate = usteps_rate;
    packet.ustep_angle = ustep_angle;
    packet.current = current;
    packet.home_offset_steps = home_offset_steps;
    packet.steps_to_next_index = steps_to_next_index;
    packet.motor = motor;
    packet.microsteps = microsteps;
    packet.spread_cycle = spread_cycle;
    packet.pwm_autoscale = pwm_autoscale;
    packet.pwm_autograd = pwm_autograd;
    packet.min_steps_to_next_index = min_steps_to_next_index;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_MOTOR_SETTINGS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
}

/**
 * @brief Encode a motor_settings struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param motor_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_settings_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_motor_settings_t* motor_settings)
{
    return mavlink_msg_motor_settings_pack(system_id, component_id, msg, motor_settings->motor, motor_settings->current, motor_settings->microsteps, motor_settings->gearing_ratio, motor_settings->spread_cycle, motor_settings->pwm_autoscale, motor_settings->pwm_autograd, motor_settings->min_steps_to_next_index, motor_settings->home_offset_steps, motor_settings->steps_to_next_index, motor_settings->usteps_rate, motor_settings->ustep_angle);
}

/**
 * @brief Encode a motor_settings struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param motor_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_settings_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_motor_settings_t* motor_settings)
{
    return mavlink_msg_motor_settings_pack_chan(system_id, component_id, chan, msg, motor_settings->motor, motor_settings->current, motor_settings->microsteps, motor_settings->gearing_ratio, motor_settings->spread_cycle, motor_settings->pwm_autoscale, motor_settings->pwm_autograd, motor_settings->min_steps_to_next_index, motor_settings->home_offset_steps, motor_settings->steps_to_next_index, motor_settings->usteps_rate, motor_settings->ustep_angle);
}

/**
 * @brief Encode a motor_settings struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param motor_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_motor_settings_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_motor_settings_t* motor_settings)
{
    return mavlink_msg_motor_settings_pack_status(system_id, component_id, _status, msg,  motor_settings->motor, motor_settings->current, motor_settings->microsteps, motor_settings->gearing_ratio, motor_settings->spread_cycle, motor_settings->pwm_autoscale, motor_settings->pwm_autograd, motor_settings->min_steps_to_next_index, motor_settings->home_offset_steps, motor_settings->steps_to_next_index, motor_settings->usteps_rate, motor_settings->ustep_angle);
}

/**
 * @brief Send a motor_settings message
 * @param chan MAVLink channel to send the message
 *
 * @param motor  Which motor we're referring to.
 * @param current   Motor current 0-2500 
 * @param microsteps   Microsteps used for stepping 1-256 in powers of 2
 * @param gearing_ratio   Gearing ratio to apply, specified as Motor Teeth:Device Teeth; Send as float i.e. 20.0/72.0 becomes 0.2777777
 * @param spread_cycle  Boolean if spread cycle is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autoscale  Boolean if pwm_autoscale is enabled. 0 = disabled, 1 = enabled
 * @param pwm_autograd  Boolean if pwm_autograd is enabled. 0 = disabled, 1 = enabled
 * @param min_steps_to_next_index  Mininimum steps between index pulse and home switch. Set to 0 to not enforce a minimum
 * @param home_offset_steps  Number of steps to move from home position after homing.
 * @param steps_to_next_index  Number of steps from home switch triggering to repeatable index pulse. Read Only.
 * @param usteps_rate [Hz] Rate at which microsteps are being triggered by the driver internal oscillator. Read Only.
 * @param ustep_angle [deg] Device angle travelled per microstep. Read Only.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_motor_settings_send(mavlink_channel_t chan, uint8_t motor, uint16_t current, uint8_t microsteps, float gearing_ratio, uint8_t spread_cycle, uint8_t pwm_autoscale, uint8_t pwm_autograd, uint8_t min_steps_to_next_index, uint16_t home_offset_steps, uint16_t steps_to_next_index, float usteps_rate, float ustep_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN];
    _mav_put_float(buf, 0, gearing_ratio);
    _mav_put_float(buf, 4, usteps_rate);
    _mav_put_float(buf, 8, ustep_angle);
    _mav_put_uint16_t(buf, 12, current);
    _mav_put_uint16_t(buf, 14, home_offset_steps);
    _mav_put_uint16_t(buf, 16, steps_to_next_index);
    _mav_put_uint8_t(buf, 18, motor);
    _mav_put_uint8_t(buf, 19, microsteps);
    _mav_put_uint8_t(buf, 20, spread_cycle);
    _mav_put_uint8_t(buf, 21, pwm_autoscale);
    _mav_put_uint8_t(buf, 22, pwm_autograd);
    _mav_put_uint8_t(buf, 23, min_steps_to_next_index);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETTINGS, buf, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
#else
    mavlink_motor_settings_t packet;
    packet.gearing_ratio = gearing_ratio;
    packet.usteps_rate = usteps_rate;
    packet.ustep_angle = ustep_angle;
    packet.current = current;
    packet.home_offset_steps = home_offset_steps;
    packet.steps_to_next_index = steps_to_next_index;
    packet.motor = motor;
    packet.microsteps = microsteps;
    packet.spread_cycle = spread_cycle;
    packet.pwm_autoscale = pwm_autoscale;
    packet.pwm_autograd = pwm_autograd;
    packet.min_steps_to_next_index = min_steps_to_next_index;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETTINGS, (const char *)&packet, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
#endif
}

/**
 * @brief Send a motor_settings message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_motor_settings_send_struct(mavlink_channel_t chan, const mavlink_motor_settings_t* motor_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_motor_settings_send(chan, motor_settings->motor, motor_settings->current, motor_settings->microsteps, motor_settings->gearing_ratio, motor_settings->spread_cycle, motor_settings->pwm_autoscale, motor_settings->pwm_autograd, motor_settings->min_steps_to_next_index, motor_settings->home_offset_steps, motor_settings->steps_to_next_index, motor_settings->usteps_rate, motor_settings->ustep_angle);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETTINGS, (const char *)motor_settings, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
#endif
}

#if MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_motor_settings_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t motor, uint16_t current, uint8_t microsteps, float gearing_ratio, uint8_t spread_cycle, uint8_t pwm_autoscale, uint8_t pwm_autograd, uint8_t min_steps_to_next_index, uint16_t home_offset_steps, uint16_t steps_to_next_index, float usteps_rate, float ustep_angle)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, gearing_ratio);
    _mav_put_float(buf, 4, usteps_rate);
    _mav_put_float(buf, 8, ustep_angle);
    _mav_put_uint16_t(buf, 12, current);
    _mav_put_uint16_t(buf, 14, home_offset_steps);
    _mav_put_uint16_t(buf, 16, steps_to_next_index);
    _mav_put_uint8_t(buf, 18, motor);
    _mav_put_uint8_t(buf, 19, microsteps);
    _mav_put_uint8_t(buf, 20, spread_cycle);
    _mav_put_uint8_t(buf, 21, pwm_autoscale);
    _mav_put_uint8_t(buf, 22, pwm_autograd);
    _mav_put_uint8_t(buf, 23, min_steps_to_next_index);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETTINGS, buf, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
#else
    mavlink_motor_settings_t *packet = (mavlink_motor_settings_t *)msgbuf;
    packet->gearing_ratio = gearing_ratio;
    packet->usteps_rate = usteps_rate;
    packet->ustep_angle = ustep_angle;
    packet->current = current;
    packet->home_offset_steps = home_offset_steps;
    packet->steps_to_next_index = steps_to_next_index;
    packet->motor = motor;
    packet->microsteps = microsteps;
    packet->spread_cycle = spread_cycle;
    packet->pwm_autoscale = pwm_autoscale;
    packet->pwm_autograd = pwm_autograd;
    packet->min_steps_to_next_index = min_steps_to_next_index;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_MOTOR_SETTINGS, (const char *)packet, MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN, MAVLINK_MSG_ID_MOTOR_SETTINGS_CRC);
#endif
}
#endif

#endif

// MESSAGE MOTOR_SETTINGS UNPACKING


/**
 * @brief Get field motor from motor_settings message
 *
 * @return  Which motor we're referring to.
 */
static inline uint8_t mavlink_msg_motor_settings_get_motor(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  18);
}

/**
 * @brief Get field current from motor_settings message
 *
 * @return   Motor current 0-2500 
 */
static inline uint16_t mavlink_msg_motor_settings_get_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  12);
}

/**
 * @brief Get field microsteps from motor_settings message
 *
 * @return   Microsteps used for stepping 1-256 in powers of 2
 */
static inline uint8_t mavlink_msg_motor_settings_get_microsteps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  19);
}

/**
 * @brief Get field gearing_ratio from motor_settings message
 *
 * @return   Gearing ratio to apply, specified as Motor Teeth:Device Teeth; Send as float i.e. 20.0/72.0 becomes 0.2777777
 */
static inline float mavlink_msg_motor_settings_get_gearing_ratio(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field spread_cycle from motor_settings message
 *
 * @return  Boolean if spread cycle is enabled. 0 = disabled, 1 = enabled
 */
static inline uint8_t mavlink_msg_motor_settings_get_spread_cycle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  20);
}

/**
 * @brief Get field pwm_autoscale from motor_settings message
 *
 * @return  Boolean if pwm_autoscale is enabled. 0 = disabled, 1 = enabled
 */
static inline uint8_t mavlink_msg_motor_settings_get_pwm_autoscale(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  21);
}

/**
 * @brief Get field pwm_autograd from motor_settings message
 *
 * @return  Boolean if pwm_autograd is enabled. 0 = disabled, 1 = enabled
 */
static inline uint8_t mavlink_msg_motor_settings_get_pwm_autograd(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  22);
}

/**
 * @brief Get field min_steps_to_next_index from motor_settings message
 *
 * @return  Mininimum steps between index pulse and home switch. Set to 0 to not enforce a minimum
 */
static inline uint8_t mavlink_msg_motor_settings_get_min_steps_to_next_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  23);
}

/**
 * @brief Get field home_offset_steps from motor_settings message
 *
 * @return  Number of steps to move from home position after homing.
 */
static inline uint16_t mavlink_msg_motor_settings_get_home_offset_steps(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  14);
}

/**
 * @brief Get field steps_to_next_index from motor_settings message
 *
 * @return  Number of steps from home switch triggering to repeatable index pulse. Read Only.
 */
static inline uint16_t mavlink_msg_motor_settings_get_steps_to_next_index(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  16);
}

/**
 * @brief Get field usteps_rate from motor_settings message
 *
 * @return [Hz] Rate at which microsteps are being triggered by the driver internal oscillator. Read Only.
 */
static inline float mavlink_msg_motor_settings_get_usteps_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field ustep_angle from motor_settings message
 *
 * @return [deg] Device angle travelled per microstep. Read Only.
 */
static inline float mavlink_msg_motor_settings_get_ustep_angle(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Decode a motor_settings message into a struct
 *
 * @param msg The message to decode
 * @param motor_settings C-struct to decode the message contents into
 */
static inline void mavlink_msg_motor_settings_decode(const mavlink_message_t* msg, mavlink_motor_settings_t* motor_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    motor_settings->gearing_ratio = mavlink_msg_motor_settings_get_gearing_ratio(msg);
    motor_settings->usteps_rate = mavlink_msg_motor_settings_get_usteps_rate(msg);
    motor_settings->ustep_angle = mavlink_msg_motor_settings_get_ustep_angle(msg);
    motor_settings->current = mavlink_msg_motor_settings_get_current(msg);
    motor_settings->home_offset_steps = mavlink_msg_motor_settings_get_home_offset_steps(msg);
    motor_settings->steps_to_next_index = mavlink_msg_motor_settings_get_steps_to_next_index(msg);
    motor_settings->motor = mavlink_msg_motor_settings_get_motor(msg);
    motor_settings->microsteps = mavlink_msg_motor_settings_get_microsteps(msg);
    motor_settings->spread_cycle = mavlink_msg_motor_settings_get_spread_cycle(msg);
    motor_settings->pwm_autoscale = mavlink_msg_motor_settings_get_pwm_autoscale(msg);
    motor_settings->pwm_autograd = mavlink_msg_motor_settings_get_pwm_autograd(msg);
    motor_settings->min_steps_to_next_index = mavlink_msg_motor_settings_get_min_steps_to_next_index(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN? msg->len : MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN;
        memset(motor_settings, 0, MAVLINK_MSG_ID_MOTOR_SETTINGS_LEN);
    memcpy(motor_settings, _MAV_PAYLOAD(msg), len);
#endif
}
