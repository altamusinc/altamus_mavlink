#pragma once
// MESSAGE POWER_INFORMATION PACKING

#define MAVLINK_MSG_ID_POWER_INFORMATION 12


typedef struct __mavlink_power_information_t {
 uint32_t energy_consumed; /*< [J]  Accumulated power since last reset in Joules*/
 uint16_t current; /*< [mA]  current in Milliamps*/
 uint16_t voltage; /*< [mV]  voltage in Millivolts*/
 uint16_t power; /*< [mW]  power in Milliwatts*/
 uint8_t type; /*<   Type of reading: instant, average, max, min*/
} mavlink_power_information_t;

#define MAVLINK_MSG_ID_POWER_INFORMATION_LEN 11
#define MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN 11
#define MAVLINK_MSG_ID_12_LEN 11
#define MAVLINK_MSG_ID_12_MIN_LEN 11

#define MAVLINK_MSG_ID_POWER_INFORMATION_CRC 42
#define MAVLINK_MSG_ID_12_CRC 42



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_POWER_INFORMATION { \
    12, \
    "POWER_INFORMATION", \
    5, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_power_information_t, type) }, \
         { "current", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_power_information_t, current) }, \
         { "voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_power_information_t, voltage) }, \
         { "power", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_power_information_t, power) }, \
         { "energy_consumed", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_power_information_t, energy_consumed) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_POWER_INFORMATION { \
    "POWER_INFORMATION", \
    5, \
    {  { "type", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_power_information_t, type) }, \
         { "current", NULL, MAVLINK_TYPE_UINT16_T, 0, 4, offsetof(mavlink_power_information_t, current) }, \
         { "voltage", NULL, MAVLINK_TYPE_UINT16_T, 0, 6, offsetof(mavlink_power_information_t, voltage) }, \
         { "power", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_power_information_t, power) }, \
         { "energy_consumed", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_power_information_t, energy_consumed) }, \
         } \
}
#endif

/**
 * @brief Pack a power_information message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param type   Type of reading: instant, average, max, min
 * @param current [mA]  current in Milliamps
 * @param voltage [mV]  voltage in Millivolts
 * @param power [mW]  power in Milliwatts
 * @param energy_consumed [J]  Accumulated power since last reset in Joules
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_power_information_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t type, uint16_t current, uint16_t voltage, uint16_t power, uint32_t energy_consumed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POWER_INFORMATION_LEN];
    _mav_put_uint32_t(buf, 0, energy_consumed);
    _mav_put_uint16_t(buf, 4, current);
    _mav_put_uint16_t(buf, 6, voltage);
    _mav_put_uint16_t(buf, 8, power);
    _mav_put_uint8_t(buf, 10, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
#else
    mavlink_power_information_t packet;
    packet.energy_consumed = energy_consumed;
    packet.current = current;
    packet.voltage = voltage;
    packet.power = power;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POWER_INFORMATION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
}

/**
 * @brief Pack a power_information message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param type   Type of reading: instant, average, max, min
 * @param current [mA]  current in Milliamps
 * @param voltage [mV]  voltage in Millivolts
 * @param power [mW]  power in Milliwatts
 * @param energy_consumed [J]  Accumulated power since last reset in Joules
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_power_information_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t type, uint16_t current, uint16_t voltage, uint16_t power, uint32_t energy_consumed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POWER_INFORMATION_LEN];
    _mav_put_uint32_t(buf, 0, energy_consumed);
    _mav_put_uint16_t(buf, 4, current);
    _mav_put_uint16_t(buf, 6, voltage);
    _mav_put_uint16_t(buf, 8, power);
    _mav_put_uint8_t(buf, 10, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
#else
    mavlink_power_information_t packet;
    packet.energy_consumed = energy_consumed;
    packet.current = current;
    packet.voltage = voltage;
    packet.power = power;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POWER_INFORMATION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
#endif
}

/**
 * @brief Pack a power_information message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param type   Type of reading: instant, average, max, min
 * @param current [mA]  current in Milliamps
 * @param voltage [mV]  voltage in Millivolts
 * @param power [mW]  power in Milliwatts
 * @param energy_consumed [J]  Accumulated power since last reset in Joules
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_power_information_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t type,uint16_t current,uint16_t voltage,uint16_t power,uint32_t energy_consumed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POWER_INFORMATION_LEN];
    _mav_put_uint32_t(buf, 0, energy_consumed);
    _mav_put_uint16_t(buf, 4, current);
    _mav_put_uint16_t(buf, 6, voltage);
    _mav_put_uint16_t(buf, 8, power);
    _mav_put_uint8_t(buf, 10, type);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
#else
    mavlink_power_information_t packet;
    packet.energy_consumed = energy_consumed;
    packet.current = current;
    packet.voltage = voltage;
    packet.power = power;
    packet.type = type;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_POWER_INFORMATION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
}

/**
 * @brief Encode a power_information struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param power_information C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_power_information_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_power_information_t* power_information)
{
    return mavlink_msg_power_information_pack(system_id, component_id, msg, power_information->type, power_information->current, power_information->voltage, power_information->power, power_information->energy_consumed);
}

/**
 * @brief Encode a power_information struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param power_information C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_power_information_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_power_information_t* power_information)
{
    return mavlink_msg_power_information_pack_chan(system_id, component_id, chan, msg, power_information->type, power_information->current, power_information->voltage, power_information->power, power_information->energy_consumed);
}

/**
 * @brief Encode a power_information struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param power_information C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_power_information_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_power_information_t* power_information)
{
    return mavlink_msg_power_information_pack_status(system_id, component_id, _status, msg,  power_information->type, power_information->current, power_information->voltage, power_information->power, power_information->energy_consumed);
}

/**
 * @brief Send a power_information message
 * @param chan MAVLink channel to send the message
 *
 * @param type   Type of reading: instant, average, max, min
 * @param current [mA]  current in Milliamps
 * @param voltage [mV]  voltage in Millivolts
 * @param power [mW]  power in Milliwatts
 * @param energy_consumed [J]  Accumulated power since last reset in Joules
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_power_information_send(mavlink_channel_t chan, uint8_t type, uint16_t current, uint16_t voltage, uint16_t power, uint32_t energy_consumed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_POWER_INFORMATION_LEN];
    _mav_put_uint32_t(buf, 0, energy_consumed);
    _mav_put_uint16_t(buf, 4, current);
    _mav_put_uint16_t(buf, 6, voltage);
    _mav_put_uint16_t(buf, 8, power);
    _mav_put_uint8_t(buf, 10, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_INFORMATION, buf, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
#else
    mavlink_power_information_t packet;
    packet.energy_consumed = energy_consumed;
    packet.current = current;
    packet.voltage = voltage;
    packet.power = power;
    packet.type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_INFORMATION, (const char *)&packet, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
#endif
}

/**
 * @brief Send a power_information message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_power_information_send_struct(mavlink_channel_t chan, const mavlink_power_information_t* power_information)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_power_information_send(chan, power_information->type, power_information->current, power_information->voltage, power_information->power, power_information->energy_consumed);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_INFORMATION, (const char *)power_information, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
#endif
}

#if MAVLINK_MSG_ID_POWER_INFORMATION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_power_information_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t type, uint16_t current, uint16_t voltage, uint16_t power, uint32_t energy_consumed)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, energy_consumed);
    _mav_put_uint16_t(buf, 4, current);
    _mav_put_uint16_t(buf, 6, voltage);
    _mav_put_uint16_t(buf, 8, power);
    _mav_put_uint8_t(buf, 10, type);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_INFORMATION, buf, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
#else
    mavlink_power_information_t *packet = (mavlink_power_information_t *)msgbuf;
    packet->energy_consumed = energy_consumed;
    packet->current = current;
    packet->voltage = voltage;
    packet->power = power;
    packet->type = type;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_POWER_INFORMATION, (const char *)packet, MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_LEN, MAVLINK_MSG_ID_POWER_INFORMATION_CRC);
#endif
}
#endif

#endif

// MESSAGE POWER_INFORMATION UNPACKING


/**
 * @brief Get field type from power_information message
 *
 * @return   Type of reading: instant, average, max, min
 */
static inline uint8_t mavlink_msg_power_information_get_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field current from power_information message
 *
 * @return [mA]  current in Milliamps
 */
static inline uint16_t mavlink_msg_power_information_get_current(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  4);
}

/**
 * @brief Get field voltage from power_information message
 *
 * @return [mV]  voltage in Millivolts
 */
static inline uint16_t mavlink_msg_power_information_get_voltage(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  6);
}

/**
 * @brief Get field power from power_information message
 *
 * @return [mW]  power in Milliwatts
 */
static inline uint16_t mavlink_msg_power_information_get_power(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field energy_consumed from power_information message
 *
 * @return [J]  Accumulated power since last reset in Joules
 */
static inline uint32_t mavlink_msg_power_information_get_energy_consumed(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a power_information message into a struct
 *
 * @param msg The message to decode
 * @param power_information C-struct to decode the message contents into
 */
static inline void mavlink_msg_power_information_decode(const mavlink_message_t* msg, mavlink_power_information_t* power_information)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    power_information->energy_consumed = mavlink_msg_power_information_get_energy_consumed(msg);
    power_information->current = mavlink_msg_power_information_get_current(msg);
    power_information->voltage = mavlink_msg_power_information_get_voltage(msg);
    power_information->power = mavlink_msg_power_information_get_power(msg);
    power_information->type = mavlink_msg_power_information_get_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_POWER_INFORMATION_LEN? msg->len : MAVLINK_MSG_ID_POWER_INFORMATION_LEN;
        memset(power_information, 0, MAVLINK_MSG_ID_POWER_INFORMATION_LEN);
    memcpy(power_information, _MAV_PAYLOAD(msg), len);
#endif
}
