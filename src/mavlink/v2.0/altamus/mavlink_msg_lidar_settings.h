#pragma once
// MESSAGE LIDAR_SETTINGS PACKING

#define MAVLINK_MSG_ID_LIDAR_SETTINGS 20


typedef struct __mavlink_lidar_settings_t {
 uint16_t update_rate; /*< [hz] Lidar update rate, in hz*/
 uint8_t fog_mode_enable; /*<  Boolean for if fog mode should be enabled. 0 = off, 1 = on*/
 uint8_t output_disabled_at_boot; /*<   Boolean for if the lidar should be emitting readings when powered up, or if a separate "output enable" command must be sent after it's turned on. 0 = false , 1 = true*/
 char firmware_version[10]; /*<   String representation of firmware version of the lidar eg: "2.1.8". Read-only*/
} mavlink_lidar_settings_t;

#define MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN 14
#define MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN 14
#define MAVLINK_MSG_ID_20_LEN 14
#define MAVLINK_MSG_ID_20_MIN_LEN 14

#define MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC 236
#define MAVLINK_MSG_ID_20_CRC 236

#define MAVLINK_MSG_LIDAR_SETTINGS_FIELD_FIRMWARE_VERSION_LEN 10

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_LIDAR_SETTINGS { \
    20, \
    "LIDAR_SETTINGS", \
    4, \
    {  { "update_rate", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_lidar_settings_t, update_rate) }, \
         { "fog_mode_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_lidar_settings_t, fog_mode_enable) }, \
         { "output_disabled_at_boot", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_lidar_settings_t, output_disabled_at_boot) }, \
         { "firmware_version", NULL, MAVLINK_TYPE_CHAR, 10, 4, offsetof(mavlink_lidar_settings_t, firmware_version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_LIDAR_SETTINGS { \
    "LIDAR_SETTINGS", \
    4, \
    {  { "update_rate", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_lidar_settings_t, update_rate) }, \
         { "fog_mode_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_lidar_settings_t, fog_mode_enable) }, \
         { "output_disabled_at_boot", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_lidar_settings_t, output_disabled_at_boot) }, \
         { "firmware_version", NULL, MAVLINK_TYPE_CHAR, 10, 4, offsetof(mavlink_lidar_settings_t, firmware_version) }, \
         } \
}
#endif

/**
 * @brief Pack a lidar_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param update_rate [hz] Lidar update rate, in hz
 * @param fog_mode_enable  Boolean for if fog mode should be enabled. 0 = off, 1 = on
 * @param output_disabled_at_boot   Boolean for if the lidar should be emitting readings when powered up, or if a separate "output enable" command must be sent after it's turned on. 0 = false , 1 = true
 * @param firmware_version   String representation of firmware version of the lidar eg: "2.1.8". Read-only
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_settings_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t update_rate, uint8_t fog_mode_enable, uint8_t output_disabled_at_boot, const char *firmware_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, update_rate);
    _mav_put_uint8_t(buf, 2, fog_mode_enable);
    _mav_put_uint8_t(buf, 3, output_disabled_at_boot);
    _mav_put_char_array(buf, 4, firmware_version, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
#else
    mavlink_lidar_settings_t packet;
    packet.update_rate = update_rate;
    packet.fog_mode_enable = fog_mode_enable;
    packet.output_disabled_at_boot = output_disabled_at_boot;
    mav_array_memcpy(packet.firmware_version, firmware_version, sizeof(char)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR_SETTINGS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
}

/**
 * @brief Pack a lidar_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param update_rate [hz] Lidar update rate, in hz
 * @param fog_mode_enable  Boolean for if fog mode should be enabled. 0 = off, 1 = on
 * @param output_disabled_at_boot   Boolean for if the lidar should be emitting readings when powered up, or if a separate "output enable" command must be sent after it's turned on. 0 = false , 1 = true
 * @param firmware_version   String representation of firmware version of the lidar eg: "2.1.8". Read-only
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_settings_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint16_t update_rate, uint8_t fog_mode_enable, uint8_t output_disabled_at_boot, const char *firmware_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, update_rate);
    _mav_put_uint8_t(buf, 2, fog_mode_enable);
    _mav_put_uint8_t(buf, 3, output_disabled_at_boot);
    _mav_put_char_array(buf, 4, firmware_version, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
#else
    mavlink_lidar_settings_t packet;
    packet.update_rate = update_rate;
    packet.fog_mode_enable = fog_mode_enable;
    packet.output_disabled_at_boot = output_disabled_at_boot;
    mav_array_memcpy(packet.firmware_version, firmware_version, sizeof(char)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR_SETTINGS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
#endif
}

/**
 * @brief Pack a lidar_settings message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param update_rate [hz] Lidar update rate, in hz
 * @param fog_mode_enable  Boolean for if fog mode should be enabled. 0 = off, 1 = on
 * @param output_disabled_at_boot   Boolean for if the lidar should be emitting readings when powered up, or if a separate "output enable" command must be sent after it's turned on. 0 = false , 1 = true
 * @param firmware_version   String representation of firmware version of the lidar eg: "2.1.8". Read-only
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_lidar_settings_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t update_rate,uint8_t fog_mode_enable,uint8_t output_disabled_at_boot,const char *firmware_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, update_rate);
    _mav_put_uint8_t(buf, 2, fog_mode_enable);
    _mav_put_uint8_t(buf, 3, output_disabled_at_boot);
    _mav_put_char_array(buf, 4, firmware_version, 10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
#else
    mavlink_lidar_settings_t packet;
    packet.update_rate = update_rate;
    packet.fog_mode_enable = fog_mode_enable;
    packet.output_disabled_at_boot = output_disabled_at_boot;
    mav_array_memcpy(packet.firmware_version, firmware_version, sizeof(char)*10);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_LIDAR_SETTINGS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
}

/**
 * @brief Encode a lidar_settings struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param lidar_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_settings_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_lidar_settings_t* lidar_settings)
{
    return mavlink_msg_lidar_settings_pack(system_id, component_id, msg, lidar_settings->update_rate, lidar_settings->fog_mode_enable, lidar_settings->output_disabled_at_boot, lidar_settings->firmware_version);
}

/**
 * @brief Encode a lidar_settings struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param lidar_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_settings_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_lidar_settings_t* lidar_settings)
{
    return mavlink_msg_lidar_settings_pack_chan(system_id, component_id, chan, msg, lidar_settings->update_rate, lidar_settings->fog_mode_enable, lidar_settings->output_disabled_at_boot, lidar_settings->firmware_version);
}

/**
 * @brief Encode a lidar_settings struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param lidar_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_lidar_settings_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_lidar_settings_t* lidar_settings)
{
    return mavlink_msg_lidar_settings_pack_status(system_id, component_id, _status, msg,  lidar_settings->update_rate, lidar_settings->fog_mode_enable, lidar_settings->output_disabled_at_boot, lidar_settings->firmware_version);
}

/**
 * @brief Send a lidar_settings message
 * @param chan MAVLink channel to send the message
 *
 * @param update_rate [hz] Lidar update rate, in hz
 * @param fog_mode_enable  Boolean for if fog mode should be enabled. 0 = off, 1 = on
 * @param output_disabled_at_boot   Boolean for if the lidar should be emitting readings when powered up, or if a separate "output enable" command must be sent after it's turned on. 0 = false , 1 = true
 * @param firmware_version   String representation of firmware version of the lidar eg: "2.1.8". Read-only
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_lidar_settings_send(mavlink_channel_t chan, uint16_t update_rate, uint8_t fog_mode_enable, uint8_t output_disabled_at_boot, const char *firmware_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, update_rate);
    _mav_put_uint8_t(buf, 2, fog_mode_enable);
    _mav_put_uint8_t(buf, 3, output_disabled_at_boot);
    _mav_put_char_array(buf, 4, firmware_version, 10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_SETTINGS, buf, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
#else
    mavlink_lidar_settings_t packet;
    packet.update_rate = update_rate;
    packet.fog_mode_enable = fog_mode_enable;
    packet.output_disabled_at_boot = output_disabled_at_boot;
    mav_array_memcpy(packet.firmware_version, firmware_version, sizeof(char)*10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_SETTINGS, (const char *)&packet, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
#endif
}

/**
 * @brief Send a lidar_settings message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_lidar_settings_send_struct(mavlink_channel_t chan, const mavlink_lidar_settings_t* lidar_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_lidar_settings_send(chan, lidar_settings->update_rate, lidar_settings->fog_mode_enable, lidar_settings->output_disabled_at_boot, lidar_settings->firmware_version);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_SETTINGS, (const char *)lidar_settings, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
#endif
}

#if MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_lidar_settings_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t update_rate, uint8_t fog_mode_enable, uint8_t output_disabled_at_boot, const char *firmware_version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, update_rate);
    _mav_put_uint8_t(buf, 2, fog_mode_enable);
    _mav_put_uint8_t(buf, 3, output_disabled_at_boot);
    _mav_put_char_array(buf, 4, firmware_version, 10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_SETTINGS, buf, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
#else
    mavlink_lidar_settings_t *packet = (mavlink_lidar_settings_t *)msgbuf;
    packet->update_rate = update_rate;
    packet->fog_mode_enable = fog_mode_enable;
    packet->output_disabled_at_boot = output_disabled_at_boot;
    mav_array_memcpy(packet->firmware_version, firmware_version, sizeof(char)*10);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_LIDAR_SETTINGS, (const char *)packet, MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN, MAVLINK_MSG_ID_LIDAR_SETTINGS_CRC);
#endif
}
#endif

#endif

// MESSAGE LIDAR_SETTINGS UNPACKING


/**
 * @brief Get field update_rate from lidar_settings message
 *
 * @return [hz] Lidar update rate, in hz
 */
static inline uint16_t mavlink_msg_lidar_settings_get_update_rate(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field fog_mode_enable from lidar_settings message
 *
 * @return  Boolean for if fog mode should be enabled. 0 = off, 1 = on
 */
static inline uint8_t mavlink_msg_lidar_settings_get_fog_mode_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field output_disabled_at_boot from lidar_settings message
 *
 * @return   Boolean for if the lidar should be emitting readings when powered up, or if a separate "output enable" command must be sent after it's turned on. 0 = false , 1 = true
 */
static inline uint8_t mavlink_msg_lidar_settings_get_output_disabled_at_boot(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Get field firmware_version from lidar_settings message
 *
 * @return   String representation of firmware version of the lidar eg: "2.1.8". Read-only
 */
static inline uint16_t mavlink_msg_lidar_settings_get_firmware_version(const mavlink_message_t* msg, char *firmware_version)
{
    return _MAV_RETURN_char_array(msg, firmware_version, 10,  4);
}

/**
 * @brief Decode a lidar_settings message into a struct
 *
 * @param msg The message to decode
 * @param lidar_settings C-struct to decode the message contents into
 */
static inline void mavlink_msg_lidar_settings_decode(const mavlink_message_t* msg, mavlink_lidar_settings_t* lidar_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    lidar_settings->update_rate = mavlink_msg_lidar_settings_get_update_rate(msg);
    lidar_settings->fog_mode_enable = mavlink_msg_lidar_settings_get_fog_mode_enable(msg);
    lidar_settings->output_disabled_at_boot = mavlink_msg_lidar_settings_get_output_disabled_at_boot(msg);
    mavlink_msg_lidar_settings_get_firmware_version(msg, lidar_settings->firmware_version);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN? msg->len : MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN;
        memset(lidar_settings, 0, MAVLINK_MSG_ID_LIDAR_SETTINGS_LEN);
    memcpy(lidar_settings, _MAV_PAYLOAD(msg), len);
#endif
}
