#pragma once
// MESSAGE WIFI_INFORMATION PACKING

#define MAVLINK_MSG_ID_WIFI_INFORMATION 13


typedef struct __mavlink_wifi_information_t {
 char ssid[32]; /*<   Name of the SSID */
 uint8_t bssid[6]; /*<  BSSID of the access point that the scanner is connected to*/
 uint8_t rssi; /*<   RSSI of the signal. expressed in negative dBm*/
 uint8_t snr; /*<   SNR of the wifi. expressed as positive dB*/
} mavlink_wifi_information_t;

#define MAVLINK_MSG_ID_WIFI_INFORMATION_LEN 40
#define MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN 40
#define MAVLINK_MSG_ID_13_LEN 40
#define MAVLINK_MSG_ID_13_MIN_LEN 40

#define MAVLINK_MSG_ID_WIFI_INFORMATION_CRC 206
#define MAVLINK_MSG_ID_13_CRC 206

#define MAVLINK_MSG_WIFI_INFORMATION_FIELD_SSID_LEN 32
#define MAVLINK_MSG_WIFI_INFORMATION_FIELD_BSSID_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WIFI_INFORMATION { \
    13, \
    "WIFI_INFORMATION", \
    4, \
    {  { "ssid", NULL, MAVLINK_TYPE_CHAR, 32, 0, offsetof(mavlink_wifi_information_t, ssid) }, \
         { "bssid", NULL, MAVLINK_TYPE_UINT8_T, 6, 32, offsetof(mavlink_wifi_information_t, bssid) }, \
         { "rssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 38, offsetof(mavlink_wifi_information_t, rssi) }, \
         { "snr", NULL, MAVLINK_TYPE_UINT8_T, 0, 39, offsetof(mavlink_wifi_information_t, snr) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WIFI_INFORMATION { \
    "WIFI_INFORMATION", \
    4, \
    {  { "ssid", NULL, MAVLINK_TYPE_CHAR, 32, 0, offsetof(mavlink_wifi_information_t, ssid) }, \
         { "bssid", NULL, MAVLINK_TYPE_UINT8_T, 6, 32, offsetof(mavlink_wifi_information_t, bssid) }, \
         { "rssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 38, offsetof(mavlink_wifi_information_t, rssi) }, \
         { "snr", NULL, MAVLINK_TYPE_UINT8_T, 0, 39, offsetof(mavlink_wifi_information_t, snr) }, \
         } \
}
#endif

/**
 * @brief Pack a wifi_information message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param ssid   Name of the SSID 
 * @param bssid  BSSID of the access point that the scanner is connected to
 * @param rssi   RSSI of the signal. expressed in negative dBm
 * @param snr   SNR of the wifi. expressed as positive dB
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_information_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t snr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, snr);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.snr = snr;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIFI_INFORMATION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
}

/**
 * @brief Pack a wifi_information message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param ssid   Name of the SSID 
 * @param bssid  BSSID of the access point that the scanner is connected to
 * @param rssi   RSSI of the signal. expressed in negative dBm
 * @param snr   SNR of the wifi. expressed as positive dB
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_information_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t snr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, snr);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.snr = snr;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIFI_INFORMATION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#endif
}

/**
 * @brief Pack a wifi_information message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param ssid   Name of the SSID 
 * @param bssid  BSSID of the access point that the scanner is connected to
 * @param rssi   RSSI of the signal. expressed in negative dBm
 * @param snr   SNR of the wifi. expressed as positive dB
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_information_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const char *ssid,const uint8_t *bssid,uint8_t rssi,uint8_t snr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, snr);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.snr = snr;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WIFI_INFORMATION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
}

/**
 * @brief Encode a wifi_information struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param wifi_information C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wifi_information_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_wifi_information_t* wifi_information)
{
    return mavlink_msg_wifi_information_pack(system_id, component_id, msg, wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->snr);
}

/**
 * @brief Encode a wifi_information struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param wifi_information C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wifi_information_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_wifi_information_t* wifi_information)
{
    return mavlink_msg_wifi_information_pack_chan(system_id, component_id, chan, msg, wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->snr);
}

/**
 * @brief Encode a wifi_information struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param wifi_information C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_wifi_information_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_wifi_information_t* wifi_information)
{
    return mavlink_msg_wifi_information_pack_status(system_id, component_id, _status, msg,  wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->snr);
}

/**
 * @brief Send a wifi_information message
 * @param chan MAVLink channel to send the message
 *
 * @param ssid   Name of the SSID 
 * @param bssid  BSSID of the access point that the scanner is connected to
 * @param rssi   RSSI of the signal. expressed in negative dBm
 * @param snr   SNR of the wifi. expressed as positive dB
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_wifi_information_send(mavlink_channel_t chan, const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t snr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, snr);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_INFORMATION, buf, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.snr = snr;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_INFORMATION, (const char *)&packet, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#endif
}

/**
 * @brief Send a wifi_information message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_wifi_information_send_struct(mavlink_channel_t chan, const mavlink_wifi_information_t* wifi_information)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_wifi_information_send(chan, wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->snr);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_INFORMATION, (const char *)wifi_information, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#endif
}

#if MAVLINK_MSG_ID_WIFI_INFORMATION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_wifi_information_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t snr)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, snr);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_INFORMATION, buf, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#else
    mavlink_wifi_information_t *packet = (mavlink_wifi_information_t *)msgbuf;
    packet->rssi = rssi;
    packet->snr = snr;
    mav_array_memcpy(packet->ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet->bssid, bssid, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_INFORMATION, (const char *)packet, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#endif
}
#endif

#endif

// MESSAGE WIFI_INFORMATION UNPACKING


/**
 * @brief Get field ssid from wifi_information message
 *
 * @return   Name of the SSID 
 */
static inline uint16_t mavlink_msg_wifi_information_get_ssid(const mavlink_message_t* msg, char *ssid)
{
    return _MAV_RETURN_char_array(msg, ssid, 32,  0);
}

/**
 * @brief Get field bssid from wifi_information message
 *
 * @return  BSSID of the access point that the scanner is connected to
 */
static inline uint16_t mavlink_msg_wifi_information_get_bssid(const mavlink_message_t* msg, uint8_t *bssid)
{
    return _MAV_RETURN_uint8_t_array(msg, bssid, 6,  32);
}

/**
 * @brief Get field rssi from wifi_information message
 *
 * @return   RSSI of the signal. expressed in negative dBm
 */
static inline uint8_t mavlink_msg_wifi_information_get_rssi(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  38);
}

/**
 * @brief Get field snr from wifi_information message
 *
 * @return   SNR of the wifi. expressed as positive dB
 */
static inline uint8_t mavlink_msg_wifi_information_get_snr(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  39);
}

/**
 * @brief Decode a wifi_information message into a struct
 *
 * @param msg The message to decode
 * @param wifi_information C-struct to decode the message contents into
 */
static inline void mavlink_msg_wifi_information_decode(const mavlink_message_t* msg, mavlink_wifi_information_t* wifi_information)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_wifi_information_get_ssid(msg, wifi_information->ssid);
    mavlink_msg_wifi_information_get_bssid(msg, wifi_information->bssid);
    wifi_information->rssi = mavlink_msg_wifi_information_get_rssi(msg);
    wifi_information->snr = mavlink_msg_wifi_information_get_snr(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_WIFI_INFORMATION_LEN? msg->len : MAVLINK_MSG_ID_WIFI_INFORMATION_LEN;
        memset(wifi_information, 0, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
    memcpy(wifi_information, _MAV_PAYLOAD(msg), len);
#endif
}
