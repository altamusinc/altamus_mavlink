#pragma once
// MESSAGE WIFI_CREDENTIALS PACKING

#define MAVLINK_MSG_ID_WIFI_CREDENTIALS 19


typedef struct __mavlink_wifi_credentials_t {
 uint8_t behavior; /*<  What behavior to execute, eg, clear, add, list*/
 char ssid[64]; /*<  Name of the SSID*/
 char password[64]; /*<  Password of the SSID. leave blank for open networks. Will be left blank if reporting*/
 uint8_t auth_type; /*<  Auth type of the network; eg; WPA2*/
} mavlink_wifi_credentials_t;

#define MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN 130
#define MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN 130
#define MAVLINK_MSG_ID_19_LEN 130
#define MAVLINK_MSG_ID_19_MIN_LEN 130

#define MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC 100
#define MAVLINK_MSG_ID_19_CRC 100

#define MAVLINK_MSG_WIFI_CREDENTIALS_FIELD_SSID_LEN 64
#define MAVLINK_MSG_WIFI_CREDENTIALS_FIELD_PASSWORD_LEN 64

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WIFI_CREDENTIALS { \
    19, \
    "WIFI_CREDENTIALS", \
    4, \
    {  { "behavior", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_wifi_credentials_t, behavior) }, \
         { "ssid", NULL, MAVLINK_TYPE_CHAR, 64, 1, offsetof(mavlink_wifi_credentials_t, ssid) }, \
         { "password", NULL, MAVLINK_TYPE_CHAR, 64, 65, offsetof(mavlink_wifi_credentials_t, password) }, \
         { "auth_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 129, offsetof(mavlink_wifi_credentials_t, auth_type) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WIFI_CREDENTIALS { \
    "WIFI_CREDENTIALS", \
    4, \
    {  { "behavior", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_wifi_credentials_t, behavior) }, \
         { "ssid", NULL, MAVLINK_TYPE_CHAR, 64, 1, offsetof(mavlink_wifi_credentials_t, ssid) }, \
         { "password", NULL, MAVLINK_TYPE_CHAR, 64, 65, offsetof(mavlink_wifi_credentials_t, password) }, \
         { "auth_type", NULL, MAVLINK_TYPE_UINT8_T, 0, 129, offsetof(mavlink_wifi_credentials_t, auth_type) }, \
         } \
}
#endif

/**
 * @brief Pack a wifi_credentials message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param behavior  What behavior to execute, eg, clear, add, list
 * @param ssid  Name of the SSID
 * @param password  Password of the SSID. leave blank for open networks. Will be left blank if reporting
 * @param auth_type  Auth type of the network; eg; WPA2
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_credentials_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t behavior, const char *ssid, const char *password, uint8_t auth_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN];
    _mav_put_uint8_t(buf, 0, behavior);
    _mav_put_uint8_t(buf, 129, auth_type);
    _mav_put_char_array(buf, 1, ssid, 64);
    _mav_put_char_array(buf, 65, password, 64);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
#else
    mavlink_wifi_credentials_t packet;
    packet.behavior = behavior;
    packet.auth_type = auth_type;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*64);
    mav_array_memcpy(packet.password, password, sizeof(char)*64);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIFI_CREDENTIALS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
}

/**
 * @brief Pack a wifi_credentials message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param behavior  What behavior to execute, eg, clear, add, list
 * @param ssid  Name of the SSID
 * @param password  Password of the SSID. leave blank for open networks. Will be left blank if reporting
 * @param auth_type  Auth type of the network; eg; WPA2
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_credentials_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t behavior, const char *ssid, const char *password, uint8_t auth_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN];
    _mav_put_uint8_t(buf, 0, behavior);
    _mav_put_uint8_t(buf, 129, auth_type);
    _mav_put_char_array(buf, 1, ssid, 64);
    _mav_put_char_array(buf, 65, password, 64);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
#else
    mavlink_wifi_credentials_t packet;
    packet.behavior = behavior;
    packet.auth_type = auth_type;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*64);
    mav_array_memcpy(packet.password, password, sizeof(char)*64);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIFI_CREDENTIALS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
#endif
}

/**
 * @brief Pack a wifi_credentials message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param behavior  What behavior to execute, eg, clear, add, list
 * @param ssid  Name of the SSID
 * @param password  Password of the SSID. leave blank for open networks. Will be left blank if reporting
 * @param auth_type  Auth type of the network; eg; WPA2
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_credentials_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t behavior,const char *ssid,const char *password,uint8_t auth_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN];
    _mav_put_uint8_t(buf, 0, behavior);
    _mav_put_uint8_t(buf, 129, auth_type);
    _mav_put_char_array(buf, 1, ssid, 64);
    _mav_put_char_array(buf, 65, password, 64);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
#else
    mavlink_wifi_credentials_t packet;
    packet.behavior = behavior;
    packet.auth_type = auth_type;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*64);
    mav_array_memcpy(packet.password, password, sizeof(char)*64);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIFI_CREDENTIALS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
}

/**
 * @brief Encode a wifi_credentials struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param wifi_credentials C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wifi_credentials_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_wifi_credentials_t* wifi_credentials)
{
    return mavlink_msg_wifi_credentials_pack(system_id, component_id, msg, wifi_credentials->behavior, wifi_credentials->ssid, wifi_credentials->password, wifi_credentials->auth_type);
}

/**
 * @brief Encode a wifi_credentials struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param wifi_credentials C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wifi_credentials_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_wifi_credentials_t* wifi_credentials)
{
    return mavlink_msg_wifi_credentials_pack_chan(system_id, component_id, chan, msg, wifi_credentials->behavior, wifi_credentials->ssid, wifi_credentials->password, wifi_credentials->auth_type);
}

/**
 * @brief Encode a wifi_credentials struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param wifi_credentials C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wifi_credentials_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_wifi_credentials_t* wifi_credentials)
{
    return mavlink_msg_wifi_credentials_pack_status(system_id, component_id, _status, msg,  wifi_credentials->behavior, wifi_credentials->ssid, wifi_credentials->password, wifi_credentials->auth_type);
}

/**
 * @brief Send a wifi_credentials message
 * @param chan MAVLink channel to send the message
 *
 * @param behavior  What behavior to execute, eg, clear, add, list
 * @param ssid  Name of the SSID
 * @param password  Password of the SSID. leave blank for open networks. Will be left blank if reporting
 * @param auth_type  Auth type of the network; eg; WPA2
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_wifi_credentials_send(mavlink_channel_t chan, uint8_t behavior, const char *ssid, const char *password, uint8_t auth_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN];
    _mav_put_uint8_t(buf, 0, behavior);
    _mav_put_uint8_t(buf, 129, auth_type);
    _mav_put_char_array(buf, 1, ssid, 64);
    _mav_put_char_array(buf, 65, password, 64);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_CREDENTIALS, buf, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
#else
    mavlink_wifi_credentials_t packet;
    packet.behavior = behavior;
    packet.auth_type = auth_type;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*64);
    mav_array_memcpy(packet.password, password, sizeof(char)*64);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_CREDENTIALS, (const char *)&packet, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
#endif
}

/**
 * @brief Send a wifi_credentials message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_wifi_credentials_send_struct(mavlink_channel_t chan, const mavlink_wifi_credentials_t* wifi_credentials)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_wifi_credentials_send(chan, wifi_credentials->behavior, wifi_credentials->ssid, wifi_credentials->password, wifi_credentials->auth_type);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_CREDENTIALS, (const char *)wifi_credentials, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
#endif
}

#if MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_wifi_credentials_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t behavior, const char *ssid, const char *password, uint8_t auth_type)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, behavior);
    _mav_put_uint8_t(buf, 129, auth_type);
    _mav_put_char_array(buf, 1, ssid, 64);
    _mav_put_char_array(buf, 65, password, 64);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_CREDENTIALS, buf, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
#else
    mavlink_wifi_credentials_t *packet = (mavlink_wifi_credentials_t *)msgbuf;
    packet->behavior = behavior;
    packet->auth_type = auth_type;
    mav_array_memcpy(packet->ssid, ssid, sizeof(char)*64);
    mav_array_memcpy(packet->password, password, sizeof(char)*64);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_CREDENTIALS, (const char *)packet, MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN, MAVLINK_MSG_ID_WIFI_CREDENTIALS_CRC);
#endif
}
#endif

#endif

// MESSAGE WIFI_CREDENTIALS UNPACKING


/**
 * @brief Get field behavior from wifi_credentials message
 *
 * @return  What behavior to execute, eg, clear, add, list
 */
static inline uint8_t mavlink_msg_wifi_credentials_get_behavior(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field ssid from wifi_credentials message
 *
 * @return  Name of the SSID
 */
static inline uint16_t mavlink_msg_wifi_credentials_get_ssid(const mavlink_message_t* msg, char *ssid)
{
    return _MAV_RETURN_char_array(msg, ssid, 64,  1);
}

/**
 * @brief Get field password from wifi_credentials message
 *
 * @return  Password of the SSID. leave blank for open networks. Will be left blank if reporting
 */
static inline uint16_t mavlink_msg_wifi_credentials_get_password(const mavlink_message_t* msg, char *password)
{
    return _MAV_RETURN_char_array(msg, password, 64,  65);
}

/**
 * @brief Get field auth_type from wifi_credentials message
 *
 * @return  Auth type of the network; eg; WPA2
 */
static inline uint8_t mavlink_msg_wifi_credentials_get_auth_type(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  129);
}

/**
 * @brief Decode a wifi_credentials message into a struct
 *
 * @param msg The message to decode
 * @param wifi_credentials C-struct to decode the message contents into
 */
static inline void mavlink_msg_wifi_credentials_decode(const mavlink_message_t* msg, mavlink_wifi_credentials_t* wifi_credentials)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    wifi_credentials->behavior = mavlink_msg_wifi_credentials_get_behavior(msg);
    mavlink_msg_wifi_credentials_get_ssid(msg, wifi_credentials->ssid);
    mavlink_msg_wifi_credentials_get_password(msg, wifi_credentials->password);
    wifi_credentials->auth_type = mavlink_msg_wifi_credentials_get_auth_type(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN? msg->len : MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN;
        memset(wifi_credentials, 0, MAVLINK_MSG_ID_WIFI_CREDENTIALS_LEN);
    memcpy(wifi_credentials, _MAV_PAYLOAD(msg), len);
#endif
}
