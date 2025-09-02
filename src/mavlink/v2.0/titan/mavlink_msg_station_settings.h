#pragma once
// MESSAGE STATION_SETTINGS PACKING

#define MAVLINK_MSG_ID_STATION_SETTINGS 7


typedef struct __mavlink_station_settings_t {
 uint32_t badge_present_timeout; /*< [ms]  Timeout before a present badge is no longer considered present*/
 uint32_t badge_present_threshold; /*< [ms]  How long a new badge needs to be seen for before it's considered present*/
 uint32_t upload_attempt_timeout; /*< [ms]  How often the system should re-attempt uploading files after the last failure */
 uint32_t server_reply_timeout; /*< [ms]  How long the system should wait for the server to confirm that it received the transaction before deleting from memory */
 uint32_t fill_limit_ml; /*< [mL]  Default fill limit for each transaction*/
 uint32_t ml_per_pulse; /*< [mL]  How many mL are registered per pulse of the measuring device*/
 int8_t station_timezone; /*<   Timezone of the station */
} mavlink_station_settings_t;

#define MAVLINK_MSG_ID_STATION_SETTINGS_LEN 25
#define MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN 25
#define MAVLINK_MSG_ID_7_LEN 25
#define MAVLINK_MSG_ID_7_MIN_LEN 25

#define MAVLINK_MSG_ID_STATION_SETTINGS_CRC 167
#define MAVLINK_MSG_ID_7_CRC 167



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_STATION_SETTINGS { \
    7, \
    "STATION_SETTINGS", \
    7, \
    {  { "badge_present_timeout", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_station_settings_t, badge_present_timeout) }, \
         { "badge_present_threshold", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_station_settings_t, badge_present_threshold) }, \
         { "upload_attempt_timeout", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_station_settings_t, upload_attempt_timeout) }, \
         { "server_reply_timeout", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_station_settings_t, server_reply_timeout) }, \
         { "fill_limit_ml", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_station_settings_t, fill_limit_ml) }, \
         { "ml_per_pulse", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_station_settings_t, ml_per_pulse) }, \
         { "station_timezone", NULL, MAVLINK_TYPE_INT8_T, 0, 24, offsetof(mavlink_station_settings_t, station_timezone) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_STATION_SETTINGS { \
    "STATION_SETTINGS", \
    7, \
    {  { "badge_present_timeout", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_station_settings_t, badge_present_timeout) }, \
         { "badge_present_threshold", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_station_settings_t, badge_present_threshold) }, \
         { "upload_attempt_timeout", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_station_settings_t, upload_attempt_timeout) }, \
         { "server_reply_timeout", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_station_settings_t, server_reply_timeout) }, \
         { "fill_limit_ml", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_station_settings_t, fill_limit_ml) }, \
         { "ml_per_pulse", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_station_settings_t, ml_per_pulse) }, \
         { "station_timezone", NULL, MAVLINK_TYPE_INT8_T, 0, 24, offsetof(mavlink_station_settings_t, station_timezone) }, \
         } \
}
#endif

/**
 * @brief Pack a station_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_present_timeout [ms]  Timeout before a present badge is no longer considered present
 * @param badge_present_threshold [ms]  How long a new badge needs to be seen for before it's considered present
 * @param upload_attempt_timeout [ms]  How often the system should re-attempt uploading files after the last failure 
 * @param server_reply_timeout [ms]  How long the system should wait for the server to confirm that it received the transaction before deleting from memory 
 * @param fill_limit_ml [mL]  Default fill limit for each transaction
 * @param ml_per_pulse [mL]  How many mL are registered per pulse of the measuring device
 * @param station_timezone   Timezone of the station 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_station_settings_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t badge_present_timeout, uint32_t badge_present_threshold, uint32_t upload_attempt_timeout, uint32_t server_reply_timeout, uint32_t fill_limit_ml, uint32_t ml_per_pulse, int8_t station_timezone)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_SETTINGS_LEN];
    _mav_put_uint32_t(buf, 0, badge_present_timeout);
    _mav_put_uint32_t(buf, 4, badge_present_threshold);
    _mav_put_uint32_t(buf, 8, upload_attempt_timeout);
    _mav_put_uint32_t(buf, 12, server_reply_timeout);
    _mav_put_uint32_t(buf, 16, fill_limit_ml);
    _mav_put_uint32_t(buf, 20, ml_per_pulse);
    _mav_put_int8_t(buf, 24, station_timezone);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
#else
    mavlink_station_settings_t packet;
    packet.badge_present_timeout = badge_present_timeout;
    packet.badge_present_threshold = badge_present_threshold;
    packet.upload_attempt_timeout = upload_attempt_timeout;
    packet.server_reply_timeout = server_reply_timeout;
    packet.fill_limit_ml = fill_limit_ml;
    packet.ml_per_pulse = ml_per_pulse;
    packet.station_timezone = station_timezone;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATION_SETTINGS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
}

/**
 * @brief Pack a station_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_present_timeout [ms]  Timeout before a present badge is no longer considered present
 * @param badge_present_threshold [ms]  How long a new badge needs to be seen for before it's considered present
 * @param upload_attempt_timeout [ms]  How often the system should re-attempt uploading files after the last failure 
 * @param server_reply_timeout [ms]  How long the system should wait for the server to confirm that it received the transaction before deleting from memory 
 * @param fill_limit_ml [mL]  Default fill limit for each transaction
 * @param ml_per_pulse [mL]  How many mL are registered per pulse of the measuring device
 * @param station_timezone   Timezone of the station 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_station_settings_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t badge_present_timeout, uint32_t badge_present_threshold, uint32_t upload_attempt_timeout, uint32_t server_reply_timeout, uint32_t fill_limit_ml, uint32_t ml_per_pulse, int8_t station_timezone)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_SETTINGS_LEN];
    _mav_put_uint32_t(buf, 0, badge_present_timeout);
    _mav_put_uint32_t(buf, 4, badge_present_threshold);
    _mav_put_uint32_t(buf, 8, upload_attempt_timeout);
    _mav_put_uint32_t(buf, 12, server_reply_timeout);
    _mav_put_uint32_t(buf, 16, fill_limit_ml);
    _mav_put_uint32_t(buf, 20, ml_per_pulse);
    _mav_put_int8_t(buf, 24, station_timezone);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
#else
    mavlink_station_settings_t packet;
    packet.badge_present_timeout = badge_present_timeout;
    packet.badge_present_threshold = badge_present_threshold;
    packet.upload_attempt_timeout = upload_attempt_timeout;
    packet.server_reply_timeout = server_reply_timeout;
    packet.fill_limit_ml = fill_limit_ml;
    packet.ml_per_pulse = ml_per_pulse;
    packet.station_timezone = station_timezone;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATION_SETTINGS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
#endif
}

/**
 * @brief Pack a station_settings message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param badge_present_timeout [ms]  Timeout before a present badge is no longer considered present
 * @param badge_present_threshold [ms]  How long a new badge needs to be seen for before it's considered present
 * @param upload_attempt_timeout [ms]  How often the system should re-attempt uploading files after the last failure 
 * @param server_reply_timeout [ms]  How long the system should wait for the server to confirm that it received the transaction before deleting from memory 
 * @param fill_limit_ml [mL]  Default fill limit for each transaction
 * @param ml_per_pulse [mL]  How many mL are registered per pulse of the measuring device
 * @param station_timezone   Timezone of the station 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_station_settings_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t badge_present_timeout,uint32_t badge_present_threshold,uint32_t upload_attempt_timeout,uint32_t server_reply_timeout,uint32_t fill_limit_ml,uint32_t ml_per_pulse,int8_t station_timezone)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_SETTINGS_LEN];
    _mav_put_uint32_t(buf, 0, badge_present_timeout);
    _mav_put_uint32_t(buf, 4, badge_present_threshold);
    _mav_put_uint32_t(buf, 8, upload_attempt_timeout);
    _mav_put_uint32_t(buf, 12, server_reply_timeout);
    _mav_put_uint32_t(buf, 16, fill_limit_ml);
    _mav_put_uint32_t(buf, 20, ml_per_pulse);
    _mav_put_int8_t(buf, 24, station_timezone);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
#else
    mavlink_station_settings_t packet;
    packet.badge_present_timeout = badge_present_timeout;
    packet.badge_present_threshold = badge_present_threshold;
    packet.upload_attempt_timeout = upload_attempt_timeout;
    packet.server_reply_timeout = server_reply_timeout;
    packet.fill_limit_ml = fill_limit_ml;
    packet.ml_per_pulse = ml_per_pulse;
    packet.station_timezone = station_timezone;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATION_SETTINGS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
}

/**
 * @brief Encode a station_settings struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param station_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_station_settings_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_station_settings_t* station_settings)
{
    return mavlink_msg_station_settings_pack(system_id, component_id, msg, station_settings->badge_present_timeout, station_settings->badge_present_threshold, station_settings->upload_attempt_timeout, station_settings->server_reply_timeout, station_settings->fill_limit_ml, station_settings->ml_per_pulse, station_settings->station_timezone);
}

/**
 * @brief Encode a station_settings struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param station_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_station_settings_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_station_settings_t* station_settings)
{
    return mavlink_msg_station_settings_pack_chan(system_id, component_id, chan, msg, station_settings->badge_present_timeout, station_settings->badge_present_threshold, station_settings->upload_attempt_timeout, station_settings->server_reply_timeout, station_settings->fill_limit_ml, station_settings->ml_per_pulse, station_settings->station_timezone);
}

/**
 * @brief Encode a station_settings struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param station_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_station_settings_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_station_settings_t* station_settings)
{
    return mavlink_msg_station_settings_pack_status(system_id, component_id, _status, msg,  station_settings->badge_present_timeout, station_settings->badge_present_threshold, station_settings->upload_attempt_timeout, station_settings->server_reply_timeout, station_settings->fill_limit_ml, station_settings->ml_per_pulse, station_settings->station_timezone);
}

/**
 * @brief Send a station_settings message
 * @param chan MAVLink channel to send the message
 *
 * @param badge_present_timeout [ms]  Timeout before a present badge is no longer considered present
 * @param badge_present_threshold [ms]  How long a new badge needs to be seen for before it's considered present
 * @param upload_attempt_timeout [ms]  How often the system should re-attempt uploading files after the last failure 
 * @param server_reply_timeout [ms]  How long the system should wait for the server to confirm that it received the transaction before deleting from memory 
 * @param fill_limit_ml [mL]  Default fill limit for each transaction
 * @param ml_per_pulse [mL]  How many mL are registered per pulse of the measuring device
 * @param station_timezone   Timezone of the station 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_station_settings_send(mavlink_channel_t chan, uint32_t badge_present_timeout, uint32_t badge_present_threshold, uint32_t upload_attempt_timeout, uint32_t server_reply_timeout, uint32_t fill_limit_ml, uint32_t ml_per_pulse, int8_t station_timezone)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_SETTINGS_LEN];
    _mav_put_uint32_t(buf, 0, badge_present_timeout);
    _mav_put_uint32_t(buf, 4, badge_present_threshold);
    _mav_put_uint32_t(buf, 8, upload_attempt_timeout);
    _mav_put_uint32_t(buf, 12, server_reply_timeout);
    _mav_put_uint32_t(buf, 16, fill_limit_ml);
    _mav_put_uint32_t(buf, 20, ml_per_pulse);
    _mav_put_int8_t(buf, 24, station_timezone);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_SETTINGS, buf, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
#else
    mavlink_station_settings_t packet;
    packet.badge_present_timeout = badge_present_timeout;
    packet.badge_present_threshold = badge_present_threshold;
    packet.upload_attempt_timeout = upload_attempt_timeout;
    packet.server_reply_timeout = server_reply_timeout;
    packet.fill_limit_ml = fill_limit_ml;
    packet.ml_per_pulse = ml_per_pulse;
    packet.station_timezone = station_timezone;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_SETTINGS, (const char *)&packet, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
#endif
}

/**
 * @brief Send a station_settings message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_station_settings_send_struct(mavlink_channel_t chan, const mavlink_station_settings_t* station_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_station_settings_send(chan, station_settings->badge_present_timeout, station_settings->badge_present_threshold, station_settings->upload_attempt_timeout, station_settings->server_reply_timeout, station_settings->fill_limit_ml, station_settings->ml_per_pulse, station_settings->station_timezone);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_SETTINGS, (const char *)station_settings, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
#endif
}

#if MAVLINK_MSG_ID_STATION_SETTINGS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_station_settings_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t badge_present_timeout, uint32_t badge_present_threshold, uint32_t upload_attempt_timeout, uint32_t server_reply_timeout, uint32_t fill_limit_ml, uint32_t ml_per_pulse, int8_t station_timezone)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, badge_present_timeout);
    _mav_put_uint32_t(buf, 4, badge_present_threshold);
    _mav_put_uint32_t(buf, 8, upload_attempt_timeout);
    _mav_put_uint32_t(buf, 12, server_reply_timeout);
    _mav_put_uint32_t(buf, 16, fill_limit_ml);
    _mav_put_uint32_t(buf, 20, ml_per_pulse);
    _mav_put_int8_t(buf, 24, station_timezone);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_SETTINGS, buf, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
#else
    mavlink_station_settings_t *packet = (mavlink_station_settings_t *)msgbuf;
    packet->badge_present_timeout = badge_present_timeout;
    packet->badge_present_threshold = badge_present_threshold;
    packet->upload_attempt_timeout = upload_attempt_timeout;
    packet->server_reply_timeout = server_reply_timeout;
    packet->fill_limit_ml = fill_limit_ml;
    packet->ml_per_pulse = ml_per_pulse;
    packet->station_timezone = station_timezone;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_SETTINGS, (const char *)packet, MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_LEN, MAVLINK_MSG_ID_STATION_SETTINGS_CRC);
#endif
}
#endif

#endif

// MESSAGE STATION_SETTINGS UNPACKING


/**
 * @brief Get field badge_present_timeout from station_settings message
 *
 * @return [ms]  Timeout before a present badge is no longer considered present
 */
static inline uint32_t mavlink_msg_station_settings_get_badge_present_timeout(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field badge_present_threshold from station_settings message
 *
 * @return [ms]  How long a new badge needs to be seen for before it's considered present
 */
static inline uint32_t mavlink_msg_station_settings_get_badge_present_threshold(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field upload_attempt_timeout from station_settings message
 *
 * @return [ms]  How often the system should re-attempt uploading files after the last failure 
 */
static inline uint32_t mavlink_msg_station_settings_get_upload_attempt_timeout(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field server_reply_timeout from station_settings message
 *
 * @return [ms]  How long the system should wait for the server to confirm that it received the transaction before deleting from memory 
 */
static inline uint32_t mavlink_msg_station_settings_get_server_reply_timeout(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field fill_limit_ml from station_settings message
 *
 * @return [mL]  Default fill limit for each transaction
 */
static inline uint32_t mavlink_msg_station_settings_get_fill_limit_ml(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field ml_per_pulse from station_settings message
 *
 * @return [mL]  How many mL are registered per pulse of the measuring device
 */
static inline uint32_t mavlink_msg_station_settings_get_ml_per_pulse(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Get field station_timezone from station_settings message
 *
 * @return   Timezone of the station 
 */
static inline int8_t mavlink_msg_station_settings_get_station_timezone(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int8_t(msg,  24);
}

/**
 * @brief Decode a station_settings message into a struct
 *
 * @param msg The message to decode
 * @param station_settings C-struct to decode the message contents into
 */
static inline void mavlink_msg_station_settings_decode(const mavlink_message_t* msg, mavlink_station_settings_t* station_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    station_settings->badge_present_timeout = mavlink_msg_station_settings_get_badge_present_timeout(msg);
    station_settings->badge_present_threshold = mavlink_msg_station_settings_get_badge_present_threshold(msg);
    station_settings->upload_attempt_timeout = mavlink_msg_station_settings_get_upload_attempt_timeout(msg);
    station_settings->server_reply_timeout = mavlink_msg_station_settings_get_server_reply_timeout(msg);
    station_settings->fill_limit_ml = mavlink_msg_station_settings_get_fill_limit_ml(msg);
    station_settings->ml_per_pulse = mavlink_msg_station_settings_get_ml_per_pulse(msg);
    station_settings->station_timezone = mavlink_msg_station_settings_get_station_timezone(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_STATION_SETTINGS_LEN? msg->len : MAVLINK_MSG_ID_STATION_SETTINGS_LEN;
        memset(station_settings, 0, MAVLINK_MSG_ID_STATION_SETTINGS_LEN);
    memcpy(station_settings, _MAV_PAYLOAD(msg), len);
#endif
}
