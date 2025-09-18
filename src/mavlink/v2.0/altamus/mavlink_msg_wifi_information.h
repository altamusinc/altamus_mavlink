#pragma once
// MESSAGE WIFI_INFORMATION PACKING

#define MAVLINK_MSG_ID_WIFI_INFORMATION 13


typedef struct __mavlink_wifi_information_t {
 char ssid[32]; /*<   Name of the SSID */
 uint8_t bssid[6]; /*<  BSSID of the access point that the scanner is connected to*/
 uint8_t rssi; /*<   RSSI of the signal. expressed in negative dBm*/
 uint8_t rssi_percent; /*<   RSSI of the signal, expressed as a percentage*/
 uint8_t snr; /*<   SNR of the wifi. expressed as positive dB*/
 uint8_t snr_percent; /*<  SNR of the wifi, expreseed as a percentage*/
 uint8_t internet_connected; /*<   Connected to internet. 0 = false, 1 = true*/
 uint8_t local_ip[4]; /*<   local IPV4 Address of the device*/
 uint8_t gateway_ip[4]; /*<   gateway IPV4 Address */
} mavlink_wifi_information_t;

#define MAVLINK_MSG_ID_WIFI_INFORMATION_LEN 51
#define MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN 51
#define MAVLINK_MSG_ID_13_LEN 51
#define MAVLINK_MSG_ID_13_MIN_LEN 51

#define MAVLINK_MSG_ID_WIFI_INFORMATION_CRC 163
#define MAVLINK_MSG_ID_13_CRC 163

#define MAVLINK_MSG_WIFI_INFORMATION_FIELD_SSID_LEN 32
#define MAVLINK_MSG_WIFI_INFORMATION_FIELD_BSSID_LEN 6
#define MAVLINK_MSG_WIFI_INFORMATION_FIELD_LOCAL_IP_LEN 4
#define MAVLINK_MSG_WIFI_INFORMATION_FIELD_GATEWAY_IP_LEN 4

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WIFI_INFORMATION { \
    13, \
    "WIFI_INFORMATION", \
    9, \
    {  { "ssid", NULL, MAVLINK_TYPE_CHAR, 32, 0, offsetof(mavlink_wifi_information_t, ssid) }, \
         { "bssid", NULL, MAVLINK_TYPE_UINT8_T, 6, 32, offsetof(mavlink_wifi_information_t, bssid) }, \
         { "rssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 38, offsetof(mavlink_wifi_information_t, rssi) }, \
         { "rssi_percent", NULL, MAVLINK_TYPE_UINT8_T, 0, 39, offsetof(mavlink_wifi_information_t, rssi_percent) }, \
         { "snr", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_wifi_information_t, snr) }, \
         { "snr_percent", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_wifi_information_t, snr_percent) }, \
         { "internet_connected", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_wifi_information_t, internet_connected) }, \
         { "local_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 43, offsetof(mavlink_wifi_information_t, local_ip) }, \
         { "gateway_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 47, offsetof(mavlink_wifi_information_t, gateway_ip) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WIFI_INFORMATION { \
    "WIFI_INFORMATION", \
    9, \
    {  { "ssid", NULL, MAVLINK_TYPE_CHAR, 32, 0, offsetof(mavlink_wifi_information_t, ssid) }, \
         { "bssid", NULL, MAVLINK_TYPE_UINT8_T, 6, 32, offsetof(mavlink_wifi_information_t, bssid) }, \
         { "rssi", NULL, MAVLINK_TYPE_UINT8_T, 0, 38, offsetof(mavlink_wifi_information_t, rssi) }, \
         { "rssi_percent", NULL, MAVLINK_TYPE_UINT8_T, 0, 39, offsetof(mavlink_wifi_information_t, rssi_percent) }, \
         { "snr", NULL, MAVLINK_TYPE_UINT8_T, 0, 40, offsetof(mavlink_wifi_information_t, snr) }, \
         { "snr_percent", NULL, MAVLINK_TYPE_UINT8_T, 0, 41, offsetof(mavlink_wifi_information_t, snr_percent) }, \
         { "internet_connected", NULL, MAVLINK_TYPE_UINT8_T, 0, 42, offsetof(mavlink_wifi_information_t, internet_connected) }, \
         { "local_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 43, offsetof(mavlink_wifi_information_t, local_ip) }, \
         { "gateway_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 47, offsetof(mavlink_wifi_information_t, gateway_ip) }, \
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
 * @param rssi_percent   RSSI of the signal, expressed as a percentage
 * @param snr   SNR of the wifi. expressed as positive dB
 * @param snr_percent  SNR of the wifi, expreseed as a percentage
 * @param internet_connected   Connected to internet. 0 = false, 1 = true
 * @param local_ip   local IPV4 Address of the device
 * @param gateway_ip   gateway IPV4 Address 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_information_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t rssi_percent, uint8_t snr, uint8_t snr_percent, uint8_t internet_connected, const uint8_t *local_ip, const uint8_t *gateway_ip)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, rssi_percent);
    _mav_put_uint8_t(buf, 40, snr);
    _mav_put_uint8_t(buf, 41, snr_percent);
    _mav_put_uint8_t(buf, 42, internet_connected);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
    _mav_put_uint8_t_array(buf, 43, local_ip, 4);
    _mav_put_uint8_t_array(buf, 47, gateway_ip, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.rssi_percent = rssi_percent;
    packet.snr = snr;
    packet.snr_percent = snr_percent;
    packet.internet_connected = internet_connected;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.gateway_ip, gateway_ip, sizeof(uint8_t)*4);
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
 * @param rssi_percent   RSSI of the signal, expressed as a percentage
 * @param snr   SNR of the wifi. expressed as positive dB
 * @param snr_percent  SNR of the wifi, expreseed as a percentage
 * @param internet_connected   Connected to internet. 0 = false, 1 = true
 * @param local_ip   local IPV4 Address of the device
 * @param gateway_ip   gateway IPV4 Address 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_information_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t rssi_percent, uint8_t snr, uint8_t snr_percent, uint8_t internet_connected, const uint8_t *local_ip, const uint8_t *gateway_ip)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, rssi_percent);
    _mav_put_uint8_t(buf, 40, snr);
    _mav_put_uint8_t(buf, 41, snr_percent);
    _mav_put_uint8_t(buf, 42, internet_connected);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
    _mav_put_uint8_t_array(buf, 43, local_ip, 4);
    _mav_put_uint8_t_array(buf, 47, gateway_ip, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.rssi_percent = rssi_percent;
    packet.snr = snr;
    packet.snr_percent = snr_percent;
    packet.internet_connected = internet_connected;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.gateway_ip, gateway_ip, sizeof(uint8_t)*4);
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
 * @param rssi_percent   RSSI of the signal, expressed as a percentage
 * @param snr   SNR of the wifi. expressed as positive dB
 * @param snr_percent  SNR of the wifi, expreseed as a percentage
 * @param internet_connected   Connected to internet. 0 = false, 1 = true
 * @param local_ip   local IPV4 Address of the device
 * @param gateway_ip   gateway IPV4 Address 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_wifi_information_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const char *ssid,const uint8_t *bssid,uint8_t rssi,uint8_t rssi_percent,uint8_t snr,uint8_t snr_percent,uint8_t internet_connected,const uint8_t *local_ip,const uint8_t *gateway_ip)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, rssi_percent);
    _mav_put_uint8_t(buf, 40, snr);
    _mav_put_uint8_t(buf, 41, snr_percent);
    _mav_put_uint8_t(buf, 42, internet_connected);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
    _mav_put_uint8_t_array(buf, 43, local_ip, 4);
    _mav_put_uint8_t_array(buf, 47, gateway_ip, 4);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.rssi_percent = rssi_percent;
    packet.snr = snr;
    packet.snr_percent = snr_percent;
    packet.internet_connected = internet_connected;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.gateway_ip, gateway_ip, sizeof(uint8_t)*4);
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
    return mavlink_msg_wifi_information_pack(system_id, component_id, msg, wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->rssi_percent, wifi_information->snr, wifi_information->snr_percent, wifi_information->internet_connected, wifi_information->local_ip, wifi_information->gateway_ip);
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
    return mavlink_msg_wifi_information_pack_chan(system_id, component_id, chan, msg, wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->rssi_percent, wifi_information->snr, wifi_information->snr_percent, wifi_information->internet_connected, wifi_information->local_ip, wifi_information->gateway_ip);
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
    return mavlink_msg_wifi_information_pack_status(system_id, component_id, _status, msg,  wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->rssi_percent, wifi_information->snr, wifi_information->snr_percent, wifi_information->internet_connected, wifi_information->local_ip, wifi_information->gateway_ip);
}

/**
 * @brief Send a wifi_information message
 * @param chan MAVLink channel to send the message
 *
 * @param ssid   Name of the SSID 
 * @param bssid  BSSID of the access point that the scanner is connected to
 * @param rssi   RSSI of the signal. expressed in negative dBm
 * @param rssi_percent   RSSI of the signal, expressed as a percentage
 * @param snr   SNR of the wifi. expressed as positive dB
 * @param snr_percent  SNR of the wifi, expreseed as a percentage
 * @param internet_connected   Connected to internet. 0 = false, 1 = true
 * @param local_ip   local IPV4 Address of the device
 * @param gateway_ip   gateway IPV4 Address 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_wifi_information_send(mavlink_channel_t chan, const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t rssi_percent, uint8_t snr, uint8_t snr_percent, uint8_t internet_connected, const uint8_t *local_ip, const uint8_t *gateway_ip)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WIFI_INFORMATION_LEN];
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, rssi_percent);
    _mav_put_uint8_t(buf, 40, snr);
    _mav_put_uint8_t(buf, 41, snr_percent);
    _mav_put_uint8_t(buf, 42, internet_connected);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
    _mav_put_uint8_t_array(buf, 43, local_ip, 4);
    _mav_put_uint8_t_array(buf, 47, gateway_ip, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_INFORMATION, buf, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#else
    mavlink_wifi_information_t packet;
    packet.rssi = rssi;
    packet.rssi_percent = rssi_percent;
    packet.snr = snr;
    packet.snr_percent = snr_percent;
    packet.internet_connected = internet_connected;
    mav_array_memcpy(packet.ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet.bssid, bssid, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.gateway_ip, gateway_ip, sizeof(uint8_t)*4);
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
    mavlink_msg_wifi_information_send(chan, wifi_information->ssid, wifi_information->bssid, wifi_information->rssi, wifi_information->rssi_percent, wifi_information->snr, wifi_information->snr_percent, wifi_information->internet_connected, wifi_information->local_ip, wifi_information->gateway_ip);
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
static inline void mavlink_msg_wifi_information_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *ssid, const uint8_t *bssid, uint8_t rssi, uint8_t rssi_percent, uint8_t snr, uint8_t snr_percent, uint8_t internet_connected, const uint8_t *local_ip, const uint8_t *gateway_ip)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 38, rssi);
    _mav_put_uint8_t(buf, 39, rssi_percent);
    _mav_put_uint8_t(buf, 40, snr);
    _mav_put_uint8_t(buf, 41, snr_percent);
    _mav_put_uint8_t(buf, 42, internet_connected);
    _mav_put_char_array(buf, 0, ssid, 32);
    _mav_put_uint8_t_array(buf, 32, bssid, 6);
    _mav_put_uint8_t_array(buf, 43, local_ip, 4);
    _mav_put_uint8_t_array(buf, 47, gateway_ip, 4);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WIFI_INFORMATION, buf, MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN, MAVLINK_MSG_ID_WIFI_INFORMATION_CRC);
#else
    mavlink_wifi_information_t *packet = (mavlink_wifi_information_t *)msgbuf;
    packet->rssi = rssi;
    packet->rssi_percent = rssi_percent;
    packet->snr = snr;
    packet->snr_percent = snr_percent;
    packet->internet_connected = internet_connected;
    mav_array_memcpy(packet->ssid, ssid, sizeof(char)*32);
    mav_array_memcpy(packet->bssid, bssid, sizeof(uint8_t)*6);
    mav_array_memcpy(packet->local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->gateway_ip, gateway_ip, sizeof(uint8_t)*4);
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
 * @brief Get field rssi_percent from wifi_information message
 *
 * @return   RSSI of the signal, expressed as a percentage
 */
static inline uint8_t mavlink_msg_wifi_information_get_rssi_percent(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  39);
}

/**
 * @brief Get field snr from wifi_information message
 *
 * @return   SNR of the wifi. expressed as positive dB
 */
static inline uint8_t mavlink_msg_wifi_information_get_snr(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  40);
}

/**
 * @brief Get field snr_percent from wifi_information message
 *
 * @return  SNR of the wifi, expreseed as a percentage
 */
static inline uint8_t mavlink_msg_wifi_information_get_snr_percent(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  41);
}

/**
 * @brief Get field internet_connected from wifi_information message
 *
 * @return   Connected to internet. 0 = false, 1 = true
 */
static inline uint8_t mavlink_msg_wifi_information_get_internet_connected(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  42);
}

/**
 * @brief Get field local_ip from wifi_information message
 *
 * @return   local IPV4 Address of the device
 */
static inline uint16_t mavlink_msg_wifi_information_get_local_ip(const mavlink_message_t* msg, uint8_t *local_ip)
{
    return _MAV_RETURN_uint8_t_array(msg, local_ip, 4,  43);
}

/**
 * @brief Get field gateway_ip from wifi_information message
 *
 * @return   gateway IPV4 Address 
 */
static inline uint16_t mavlink_msg_wifi_information_get_gateway_ip(const mavlink_message_t* msg, uint8_t *gateway_ip)
{
    return _MAV_RETURN_uint8_t_array(msg, gateway_ip, 4,  47);
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
    wifi_information->rssi_percent = mavlink_msg_wifi_information_get_rssi_percent(msg);
    wifi_information->snr = mavlink_msg_wifi_information_get_snr(msg);
    wifi_information->snr_percent = mavlink_msg_wifi_information_get_snr_percent(msg);
    wifi_information->internet_connected = mavlink_msg_wifi_information_get_internet_connected(msg);
    mavlink_msg_wifi_information_get_local_ip(msg, wifi_information->local_ip);
    mavlink_msg_wifi_information_get_gateway_ip(msg, wifi_information->gateway_ip);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_WIFI_INFORMATION_LEN? msg->len : MAVLINK_MSG_ID_WIFI_INFORMATION_LEN;
        memset(wifi_information, 0, MAVLINK_MSG_ID_WIFI_INFORMATION_LEN);
    memcpy(wifi_information, _MAV_PAYLOAD(msg), len);
#endif
}
