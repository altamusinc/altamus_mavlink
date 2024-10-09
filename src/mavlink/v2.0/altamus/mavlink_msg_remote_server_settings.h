#pragma once
// MESSAGE REMOTE_SERVER_SETTINGS PACKING

#define MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS 11


typedef struct __mavlink_remote_server_settings_t {
 uint16_t post_port; /*<  Port to send checkin info to. Defaults to 80*/
 uint16_t ftp_port; /*<  Port to send FTP info to. Defaults to 21*/
 uint8_t server_enable; /*<  Bool value controlling if settings and checkin information should be sent to a remote server. 0 = disabled, 1 = enabled. If enabled must provide server information.*/
 char post_server[64]; /*<  Server to send checkin info to, as well as get settings from*/
 char post_uri[32]; /*<  URI to send checkin info to. appended to post server. E.g. /php/api.php*/
 uint8_t ftp_enable; /*<  Bool value controlling if files should be sent to FTP server. 0 = disabled, 1 = enabled. If enabled, must provide valid settings.*/
 char ftp_server[64]; /*<  Address of server to send FTP files too.*/
 char ftp_username[32]; /*<  Username to use when logging into FTP server*/
 char ftp_password[32]; /*<  Password to use for FTP upload*/
} mavlink_remote_server_settings_t;

#define MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN 230
#define MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN 230
#define MAVLINK_MSG_ID_11_LEN 230
#define MAVLINK_MSG_ID_11_MIN_LEN 230

#define MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC 79
#define MAVLINK_MSG_ID_11_CRC 79

#define MAVLINK_MSG_REMOTE_SERVER_SETTINGS_FIELD_POST_SERVER_LEN 64
#define MAVLINK_MSG_REMOTE_SERVER_SETTINGS_FIELD_POST_URI_LEN 32
#define MAVLINK_MSG_REMOTE_SERVER_SETTINGS_FIELD_FTP_SERVER_LEN 64
#define MAVLINK_MSG_REMOTE_SERVER_SETTINGS_FIELD_FTP_USERNAME_LEN 32
#define MAVLINK_MSG_REMOTE_SERVER_SETTINGS_FIELD_FTP_PASSWORD_LEN 32

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_REMOTE_SERVER_SETTINGS { \
    11, \
    "REMOTE_SERVER_SETTINGS", \
    9, \
    {  { "server_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_remote_server_settings_t, server_enable) }, \
         { "post_server", NULL, MAVLINK_TYPE_CHAR, 64, 5, offsetof(mavlink_remote_server_settings_t, post_server) }, \
         { "post_uri", NULL, MAVLINK_TYPE_CHAR, 32, 69, offsetof(mavlink_remote_server_settings_t, post_uri) }, \
         { "post_port", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_remote_server_settings_t, post_port) }, \
         { "ftp_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 101, offsetof(mavlink_remote_server_settings_t, ftp_enable) }, \
         { "ftp_server", NULL, MAVLINK_TYPE_CHAR, 64, 102, offsetof(mavlink_remote_server_settings_t, ftp_server) }, \
         { "ftp_username", NULL, MAVLINK_TYPE_CHAR, 32, 166, offsetof(mavlink_remote_server_settings_t, ftp_username) }, \
         { "ftp_password", NULL, MAVLINK_TYPE_CHAR, 32, 198, offsetof(mavlink_remote_server_settings_t, ftp_password) }, \
         { "ftp_port", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_remote_server_settings_t, ftp_port) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_REMOTE_SERVER_SETTINGS { \
    "REMOTE_SERVER_SETTINGS", \
    9, \
    {  { "server_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_remote_server_settings_t, server_enable) }, \
         { "post_server", NULL, MAVLINK_TYPE_CHAR, 64, 5, offsetof(mavlink_remote_server_settings_t, post_server) }, \
         { "post_uri", NULL, MAVLINK_TYPE_CHAR, 32, 69, offsetof(mavlink_remote_server_settings_t, post_uri) }, \
         { "post_port", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_remote_server_settings_t, post_port) }, \
         { "ftp_enable", NULL, MAVLINK_TYPE_UINT8_T, 0, 101, offsetof(mavlink_remote_server_settings_t, ftp_enable) }, \
         { "ftp_server", NULL, MAVLINK_TYPE_CHAR, 64, 102, offsetof(mavlink_remote_server_settings_t, ftp_server) }, \
         { "ftp_username", NULL, MAVLINK_TYPE_CHAR, 32, 166, offsetof(mavlink_remote_server_settings_t, ftp_username) }, \
         { "ftp_password", NULL, MAVLINK_TYPE_CHAR, 32, 198, offsetof(mavlink_remote_server_settings_t, ftp_password) }, \
         { "ftp_port", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_remote_server_settings_t, ftp_port) }, \
         } \
}
#endif

/**
 * @brief Pack a remote_server_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param server_enable  Bool value controlling if settings and checkin information should be sent to a remote server. 0 = disabled, 1 = enabled. If enabled must provide server information.
 * @param post_server  Server to send checkin info to, as well as get settings from
 * @param post_uri  URI to send checkin info to. appended to post server. E.g. /php/api.php
 * @param post_port  Port to send checkin info to. Defaults to 80
 * @param ftp_enable  Bool value controlling if files should be sent to FTP server. 0 = disabled, 1 = enabled. If enabled, must provide valid settings.
 * @param ftp_server  Address of server to send FTP files too.
 * @param ftp_username  Username to use when logging into FTP server
 * @param ftp_password  Password to use for FTP upload
 * @param ftp_port  Port to send FTP info to. Defaults to 21
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_remote_server_settings_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t server_enable, const char *post_server, const char *post_uri, uint16_t post_port, uint8_t ftp_enable, const char *ftp_server, const char *ftp_username, const char *ftp_password, uint16_t ftp_port)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, post_port);
    _mav_put_uint16_t(buf, 2, ftp_port);
    _mav_put_uint8_t(buf, 4, server_enable);
    _mav_put_uint8_t(buf, 101, ftp_enable);
    _mav_put_char_array(buf, 5, post_server, 64);
    _mav_put_char_array(buf, 69, post_uri, 32);
    _mav_put_char_array(buf, 102, ftp_server, 64);
    _mav_put_char_array(buf, 166, ftp_username, 32);
    _mav_put_char_array(buf, 198, ftp_password, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
#else
    mavlink_remote_server_settings_t packet;
    packet.post_port = post_port;
    packet.ftp_port = ftp_port;
    packet.server_enable = server_enable;
    packet.ftp_enable = ftp_enable;
    mav_array_memcpy(packet.post_server, post_server, sizeof(char)*64);
    mav_array_memcpy(packet.post_uri, post_uri, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_server, ftp_server, sizeof(char)*64);
    mav_array_memcpy(packet.ftp_username, ftp_username, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_password, ftp_password, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
}

/**
 * @brief Pack a remote_server_settings message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param server_enable  Bool value controlling if settings and checkin information should be sent to a remote server. 0 = disabled, 1 = enabled. If enabled must provide server information.
 * @param post_server  Server to send checkin info to, as well as get settings from
 * @param post_uri  URI to send checkin info to. appended to post server. E.g. /php/api.php
 * @param post_port  Port to send checkin info to. Defaults to 80
 * @param ftp_enable  Bool value controlling if files should be sent to FTP server. 0 = disabled, 1 = enabled. If enabled, must provide valid settings.
 * @param ftp_server  Address of server to send FTP files too.
 * @param ftp_username  Username to use when logging into FTP server
 * @param ftp_password  Password to use for FTP upload
 * @param ftp_port  Port to send FTP info to. Defaults to 21
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_remote_server_settings_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t server_enable, const char *post_server, const char *post_uri, uint16_t post_port, uint8_t ftp_enable, const char *ftp_server, const char *ftp_username, const char *ftp_password, uint16_t ftp_port)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, post_port);
    _mav_put_uint16_t(buf, 2, ftp_port);
    _mav_put_uint8_t(buf, 4, server_enable);
    _mav_put_uint8_t(buf, 101, ftp_enable);
    _mav_put_char_array(buf, 5, post_server, 64);
    _mav_put_char_array(buf, 69, post_uri, 32);
    _mav_put_char_array(buf, 102, ftp_server, 64);
    _mav_put_char_array(buf, 166, ftp_username, 32);
    _mav_put_char_array(buf, 198, ftp_password, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
#else
    mavlink_remote_server_settings_t packet;
    packet.post_port = post_port;
    packet.ftp_port = ftp_port;
    packet.server_enable = server_enable;
    packet.ftp_enable = ftp_enable;
    mav_array_memcpy(packet.post_server, post_server, sizeof(char)*64);
    mav_array_memcpy(packet.post_uri, post_uri, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_server, ftp_server, sizeof(char)*64);
    mav_array_memcpy(packet.ftp_username, ftp_username, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_password, ftp_password, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
#endif
}

/**
 * @brief Pack a remote_server_settings message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param server_enable  Bool value controlling if settings and checkin information should be sent to a remote server. 0 = disabled, 1 = enabled. If enabled must provide server information.
 * @param post_server  Server to send checkin info to, as well as get settings from
 * @param post_uri  URI to send checkin info to. appended to post server. E.g. /php/api.php
 * @param post_port  Port to send checkin info to. Defaults to 80
 * @param ftp_enable  Bool value controlling if files should be sent to FTP server. 0 = disabled, 1 = enabled. If enabled, must provide valid settings.
 * @param ftp_server  Address of server to send FTP files too.
 * @param ftp_username  Username to use when logging into FTP server
 * @param ftp_password  Password to use for FTP upload
 * @param ftp_port  Port to send FTP info to. Defaults to 21
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_remote_server_settings_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t server_enable,const char *post_server,const char *post_uri,uint16_t post_port,uint8_t ftp_enable,const char *ftp_server,const char *ftp_username,const char *ftp_password,uint16_t ftp_port)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, post_port);
    _mav_put_uint16_t(buf, 2, ftp_port);
    _mav_put_uint8_t(buf, 4, server_enable);
    _mav_put_uint8_t(buf, 101, ftp_enable);
    _mav_put_char_array(buf, 5, post_server, 64);
    _mav_put_char_array(buf, 69, post_uri, 32);
    _mav_put_char_array(buf, 102, ftp_server, 64);
    _mav_put_char_array(buf, 166, ftp_username, 32);
    _mav_put_char_array(buf, 198, ftp_password, 32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
#else
    mavlink_remote_server_settings_t packet;
    packet.post_port = post_port;
    packet.ftp_port = ftp_port;
    packet.server_enable = server_enable;
    packet.ftp_enable = ftp_enable;
    mav_array_memcpy(packet.post_server, post_server, sizeof(char)*64);
    mav_array_memcpy(packet.post_uri, post_uri, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_server, ftp_server, sizeof(char)*64);
    mav_array_memcpy(packet.ftp_username, ftp_username, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_password, ftp_password, sizeof(char)*32);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
}

/**
 * @brief Encode a remote_server_settings struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param remote_server_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_remote_server_settings_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_remote_server_settings_t* remote_server_settings)
{
    return mavlink_msg_remote_server_settings_pack(system_id, component_id, msg, remote_server_settings->server_enable, remote_server_settings->post_server, remote_server_settings->post_uri, remote_server_settings->post_port, remote_server_settings->ftp_enable, remote_server_settings->ftp_server, remote_server_settings->ftp_username, remote_server_settings->ftp_password, remote_server_settings->ftp_port);
}

/**
 * @brief Encode a remote_server_settings struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param remote_server_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_remote_server_settings_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_remote_server_settings_t* remote_server_settings)
{
    return mavlink_msg_remote_server_settings_pack_chan(system_id, component_id, chan, msg, remote_server_settings->server_enable, remote_server_settings->post_server, remote_server_settings->post_uri, remote_server_settings->post_port, remote_server_settings->ftp_enable, remote_server_settings->ftp_server, remote_server_settings->ftp_username, remote_server_settings->ftp_password, remote_server_settings->ftp_port);
}

/**
 * @brief Encode a remote_server_settings struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param remote_server_settings C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_remote_server_settings_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_remote_server_settings_t* remote_server_settings)
{
    return mavlink_msg_remote_server_settings_pack_status(system_id, component_id, _status, msg,  remote_server_settings->server_enable, remote_server_settings->post_server, remote_server_settings->post_uri, remote_server_settings->post_port, remote_server_settings->ftp_enable, remote_server_settings->ftp_server, remote_server_settings->ftp_username, remote_server_settings->ftp_password, remote_server_settings->ftp_port);
}

/**
 * @brief Send a remote_server_settings message
 * @param chan MAVLink channel to send the message
 *
 * @param server_enable  Bool value controlling if settings and checkin information should be sent to a remote server. 0 = disabled, 1 = enabled. If enabled must provide server information.
 * @param post_server  Server to send checkin info to, as well as get settings from
 * @param post_uri  URI to send checkin info to. appended to post server. E.g. /php/api.php
 * @param post_port  Port to send checkin info to. Defaults to 80
 * @param ftp_enable  Bool value controlling if files should be sent to FTP server. 0 = disabled, 1 = enabled. If enabled, must provide valid settings.
 * @param ftp_server  Address of server to send FTP files too.
 * @param ftp_username  Username to use when logging into FTP server
 * @param ftp_password  Password to use for FTP upload
 * @param ftp_port  Port to send FTP info to. Defaults to 21
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_remote_server_settings_send(mavlink_channel_t chan, uint8_t server_enable, const char *post_server, const char *post_uri, uint16_t post_port, uint8_t ftp_enable, const char *ftp_server, const char *ftp_username, const char *ftp_password, uint16_t ftp_port)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN];
    _mav_put_uint16_t(buf, 0, post_port);
    _mav_put_uint16_t(buf, 2, ftp_port);
    _mav_put_uint8_t(buf, 4, server_enable);
    _mav_put_uint8_t(buf, 101, ftp_enable);
    _mav_put_char_array(buf, 5, post_server, 64);
    _mav_put_char_array(buf, 69, post_uri, 32);
    _mav_put_char_array(buf, 102, ftp_server, 64);
    _mav_put_char_array(buf, 166, ftp_username, 32);
    _mav_put_char_array(buf, 198, ftp_password, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS, buf, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
#else
    mavlink_remote_server_settings_t packet;
    packet.post_port = post_port;
    packet.ftp_port = ftp_port;
    packet.server_enable = server_enable;
    packet.ftp_enable = ftp_enable;
    mav_array_memcpy(packet.post_server, post_server, sizeof(char)*64);
    mav_array_memcpy(packet.post_uri, post_uri, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_server, ftp_server, sizeof(char)*64);
    mav_array_memcpy(packet.ftp_username, ftp_username, sizeof(char)*32);
    mav_array_memcpy(packet.ftp_password, ftp_password, sizeof(char)*32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS, (const char *)&packet, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
#endif
}

/**
 * @brief Send a remote_server_settings message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_remote_server_settings_send_struct(mavlink_channel_t chan, const mavlink_remote_server_settings_t* remote_server_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_remote_server_settings_send(chan, remote_server_settings->server_enable, remote_server_settings->post_server, remote_server_settings->post_uri, remote_server_settings->post_port, remote_server_settings->ftp_enable, remote_server_settings->ftp_server, remote_server_settings->ftp_username, remote_server_settings->ftp_password, remote_server_settings->ftp_port);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS, (const char *)remote_server_settings, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
#endif
}

#if MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_remote_server_settings_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t server_enable, const char *post_server, const char *post_uri, uint16_t post_port, uint8_t ftp_enable, const char *ftp_server, const char *ftp_username, const char *ftp_password, uint16_t ftp_port)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, post_port);
    _mav_put_uint16_t(buf, 2, ftp_port);
    _mav_put_uint8_t(buf, 4, server_enable);
    _mav_put_uint8_t(buf, 101, ftp_enable);
    _mav_put_char_array(buf, 5, post_server, 64);
    _mav_put_char_array(buf, 69, post_uri, 32);
    _mav_put_char_array(buf, 102, ftp_server, 64);
    _mav_put_char_array(buf, 166, ftp_username, 32);
    _mav_put_char_array(buf, 198, ftp_password, 32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS, buf, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
#else
    mavlink_remote_server_settings_t *packet = (mavlink_remote_server_settings_t *)msgbuf;
    packet->post_port = post_port;
    packet->ftp_port = ftp_port;
    packet->server_enable = server_enable;
    packet->ftp_enable = ftp_enable;
    mav_array_memcpy(packet->post_server, post_server, sizeof(char)*64);
    mav_array_memcpy(packet->post_uri, post_uri, sizeof(char)*32);
    mav_array_memcpy(packet->ftp_server, ftp_server, sizeof(char)*64);
    mav_array_memcpy(packet->ftp_username, ftp_username, sizeof(char)*32);
    mav_array_memcpy(packet->ftp_password, ftp_password, sizeof(char)*32);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS, (const char *)packet, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_CRC);
#endif
}
#endif

#endif

// MESSAGE REMOTE_SERVER_SETTINGS UNPACKING


/**
 * @brief Get field server_enable from remote_server_settings message
 *
 * @return  Bool value controlling if settings and checkin information should be sent to a remote server. 0 = disabled, 1 = enabled. If enabled must provide server information.
 */
static inline uint8_t mavlink_msg_remote_server_settings_get_server_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field post_server from remote_server_settings message
 *
 * @return  Server to send checkin info to, as well as get settings from
 */
static inline uint16_t mavlink_msg_remote_server_settings_get_post_server(const mavlink_message_t* msg, char *post_server)
{
    return _MAV_RETURN_char_array(msg, post_server, 64,  5);
}

/**
 * @brief Get field post_uri from remote_server_settings message
 *
 * @return  URI to send checkin info to. appended to post server. E.g. /php/api.php
 */
static inline uint16_t mavlink_msg_remote_server_settings_get_post_uri(const mavlink_message_t* msg, char *post_uri)
{
    return _MAV_RETURN_char_array(msg, post_uri, 32,  69);
}

/**
 * @brief Get field post_port from remote_server_settings message
 *
 * @return  Port to send checkin info to. Defaults to 80
 */
static inline uint16_t mavlink_msg_remote_server_settings_get_post_port(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field ftp_enable from remote_server_settings message
 *
 * @return  Bool value controlling if files should be sent to FTP server. 0 = disabled, 1 = enabled. If enabled, must provide valid settings.
 */
static inline uint8_t mavlink_msg_remote_server_settings_get_ftp_enable(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  101);
}

/**
 * @brief Get field ftp_server from remote_server_settings message
 *
 * @return  Address of server to send FTP files too.
 */
static inline uint16_t mavlink_msg_remote_server_settings_get_ftp_server(const mavlink_message_t* msg, char *ftp_server)
{
    return _MAV_RETURN_char_array(msg, ftp_server, 64,  102);
}

/**
 * @brief Get field ftp_username from remote_server_settings message
 *
 * @return  Username to use when logging into FTP server
 */
static inline uint16_t mavlink_msg_remote_server_settings_get_ftp_username(const mavlink_message_t* msg, char *ftp_username)
{
    return _MAV_RETURN_char_array(msg, ftp_username, 32,  166);
}

/**
 * @brief Get field ftp_password from remote_server_settings message
 *
 * @return  Password to use for FTP upload
 */
static inline uint16_t mavlink_msg_remote_server_settings_get_ftp_password(const mavlink_message_t* msg, char *ftp_password)
{
    return _MAV_RETURN_char_array(msg, ftp_password, 32,  198);
}

/**
 * @brief Get field ftp_port from remote_server_settings message
 *
 * @return  Port to send FTP info to. Defaults to 21
 */
static inline uint16_t mavlink_msg_remote_server_settings_get_ftp_port(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Decode a remote_server_settings message into a struct
 *
 * @param msg The message to decode
 * @param remote_server_settings C-struct to decode the message contents into
 */
static inline void mavlink_msg_remote_server_settings_decode(const mavlink_message_t* msg, mavlink_remote_server_settings_t* remote_server_settings)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    remote_server_settings->post_port = mavlink_msg_remote_server_settings_get_post_port(msg);
    remote_server_settings->ftp_port = mavlink_msg_remote_server_settings_get_ftp_port(msg);
    remote_server_settings->server_enable = mavlink_msg_remote_server_settings_get_server_enable(msg);
    mavlink_msg_remote_server_settings_get_post_server(msg, remote_server_settings->post_server);
    mavlink_msg_remote_server_settings_get_post_uri(msg, remote_server_settings->post_uri);
    remote_server_settings->ftp_enable = mavlink_msg_remote_server_settings_get_ftp_enable(msg);
    mavlink_msg_remote_server_settings_get_ftp_server(msg, remote_server_settings->ftp_server);
    mavlink_msg_remote_server_settings_get_ftp_username(msg, remote_server_settings->ftp_username);
    mavlink_msg_remote_server_settings_get_ftp_password(msg, remote_server_settings->ftp_password);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN? msg->len : MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN;
        memset(remote_server_settings, 0, MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_LEN);
    memcpy(remote_server_settings, _MAV_PAYLOAD(msg), len);
#endif
}
