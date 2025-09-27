#pragma once
// MESSAGE IDENTIFIER PACKING

#define MAVLINK_MSG_ID_IDENTIFIER 7


typedef struct __mavlink_identifier_t {
 uint8_t fw_version; /*<  Particle FW version*/
 char particle_id_full[24]; /*<   Particle ID of device. Read Only. */
 char device_id[20]; /*<  Device id of scanner matching manufacturing sticker. i.e. P2-ABC123. Read only*/
 char device_name[30]; /*<   Friendly name of device. E.g. "57 Rock West". User settable*/
 uint8_t local_ip[4]; /*<   local IPV4 Address of the device*/
 uint8_t mac[6]; /*<   MAC address of the device*/
} mavlink_identifier_t;

#define MAVLINK_MSG_ID_IDENTIFIER_LEN 85
#define MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN 85
#define MAVLINK_MSG_ID_7_LEN 85
#define MAVLINK_MSG_ID_7_MIN_LEN 85

#define MAVLINK_MSG_ID_IDENTIFIER_CRC 86
#define MAVLINK_MSG_ID_7_CRC 86

#define MAVLINK_MSG_IDENTIFIER_FIELD_PARTICLE_ID_FULL_LEN 24
#define MAVLINK_MSG_IDENTIFIER_FIELD_DEVICE_ID_LEN 20
#define MAVLINK_MSG_IDENTIFIER_FIELD_DEVICE_NAME_LEN 30
#define MAVLINK_MSG_IDENTIFIER_FIELD_LOCAL_IP_LEN 4
#define MAVLINK_MSG_IDENTIFIER_FIELD_MAC_LEN 6

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_IDENTIFIER { \
    7, \
    "IDENTIFIER", \
    6, \
    {  { "fw_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_identifier_t, fw_version) }, \
         { "particle_id_full", NULL, MAVLINK_TYPE_CHAR, 24, 1, offsetof(mavlink_identifier_t, particle_id_full) }, \
         { "device_id", NULL, MAVLINK_TYPE_CHAR, 20, 25, offsetof(mavlink_identifier_t, device_id) }, \
         { "device_name", NULL, MAVLINK_TYPE_CHAR, 30, 45, offsetof(mavlink_identifier_t, device_name) }, \
         { "local_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 75, offsetof(mavlink_identifier_t, local_ip) }, \
         { "mac", NULL, MAVLINK_TYPE_UINT8_T, 6, 79, offsetof(mavlink_identifier_t, mac) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_IDENTIFIER { \
    "IDENTIFIER", \
    6, \
    {  { "fw_version", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_identifier_t, fw_version) }, \
         { "particle_id_full", NULL, MAVLINK_TYPE_CHAR, 24, 1, offsetof(mavlink_identifier_t, particle_id_full) }, \
         { "device_id", NULL, MAVLINK_TYPE_CHAR, 20, 25, offsetof(mavlink_identifier_t, device_id) }, \
         { "device_name", NULL, MAVLINK_TYPE_CHAR, 30, 45, offsetof(mavlink_identifier_t, device_name) }, \
         { "local_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 75, offsetof(mavlink_identifier_t, local_ip) }, \
         { "mac", NULL, MAVLINK_TYPE_UINT8_T, 6, 79, offsetof(mavlink_identifier_t, mac) }, \
         } \
}
#endif

/**
 * @brief Pack a identifier message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param fw_version  Particle FW version
 * @param particle_id_full   Particle ID of device. Read Only. 
 * @param device_id  Device id of scanner matching manufacturing sticker. i.e. P2-ABC123. Read only
 * @param device_name   Friendly name of device. E.g. "57 Rock West". User settable
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_identifier_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t fw_version, const char *particle_id_full, const char *device_id, const char *device_name, const uint8_t *local_ip, const uint8_t *mac)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];
    _mav_put_uint8_t(buf, 0, fw_version);
    _mav_put_char_array(buf, 1, particle_id_full, 24);
    _mav_put_char_array(buf, 25, device_id, 20);
    _mav_put_char_array(buf, 45, device_name, 30);
    _mav_put_uint8_t_array(buf, 75, local_ip, 4);
    _mav_put_uint8_t_array(buf, 79, mac, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#else
    mavlink_identifier_t packet;
    packet.fw_version = fw_version;
    mav_array_memcpy(packet.particle_id_full, particle_id_full, sizeof(char)*24);
    mav_array_memcpy(packet.device_id, device_id, sizeof(char)*20);
    mav_array_memcpy(packet.device_name, device_name, sizeof(char)*30);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IDENTIFIER;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
}

/**
 * @brief Pack a identifier message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param fw_version  Particle FW version
 * @param particle_id_full   Particle ID of device. Read Only. 
 * @param device_id  Device id of scanner matching manufacturing sticker. i.e. P2-ABC123. Read only
 * @param device_name   Friendly name of device. E.g. "57 Rock West". User settable
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_identifier_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t fw_version, const char *particle_id_full, const char *device_id, const char *device_name, const uint8_t *local_ip, const uint8_t *mac)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];
    _mav_put_uint8_t(buf, 0, fw_version);
    _mav_put_char_array(buf, 1, particle_id_full, 24);
    _mav_put_char_array(buf, 25, device_id, 20);
    _mav_put_char_array(buf, 45, device_name, 30);
    _mav_put_uint8_t_array(buf, 75, local_ip, 4);
    _mav_put_uint8_t_array(buf, 79, mac, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#else
    mavlink_identifier_t packet;
    packet.fw_version = fw_version;
    mav_array_memcpy(packet.particle_id_full, particle_id_full, sizeof(char)*24);
    mav_array_memcpy(packet.device_id, device_id, sizeof(char)*20);
    mav_array_memcpy(packet.device_name, device_name, sizeof(char)*30);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IDENTIFIER;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#endif
}

/**
 * @brief Pack a identifier message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param fw_version  Particle FW version
 * @param particle_id_full   Particle ID of device. Read Only. 
 * @param device_id  Device id of scanner matching manufacturing sticker. i.e. P2-ABC123. Read only
 * @param device_name   Friendly name of device. E.g. "57 Rock West". User settable
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_identifier_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t fw_version,const char *particle_id_full,const char *device_id,const char *device_name,const uint8_t *local_ip,const uint8_t *mac)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];
    _mav_put_uint8_t(buf, 0, fw_version);
    _mav_put_char_array(buf, 1, particle_id_full, 24);
    _mav_put_char_array(buf, 25, device_id, 20);
    _mav_put_char_array(buf, 45, device_name, 30);
    _mav_put_uint8_t_array(buf, 75, local_ip, 4);
    _mav_put_uint8_t_array(buf, 79, mac, 6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#else
    mavlink_identifier_t packet;
    packet.fw_version = fw_version;
    mav_array_memcpy(packet.particle_id_full, particle_id_full, sizeof(char)*24);
    mav_array_memcpy(packet.device_id, device_id, sizeof(char)*20);
    mav_array_memcpy(packet.device_name, device_name, sizeof(char)*30);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_IDENTIFIER;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
}

/**
 * @brief Encode a identifier struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param identifier C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_identifier_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_identifier_t* identifier)
{
    return mavlink_msg_identifier_pack(system_id, component_id, msg, identifier->fw_version, identifier->particle_id_full, identifier->device_id, identifier->device_name, identifier->local_ip, identifier->mac);
}

/**
 * @brief Encode a identifier struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param identifier C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_identifier_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_identifier_t* identifier)
{
    return mavlink_msg_identifier_pack_chan(system_id, component_id, chan, msg, identifier->fw_version, identifier->particle_id_full, identifier->device_id, identifier->device_name, identifier->local_ip, identifier->mac);
}

/**
 * @brief Encode a identifier struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param identifier C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_identifier_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_identifier_t* identifier)
{
    return mavlink_msg_identifier_pack_status(system_id, component_id, _status, msg,  identifier->fw_version, identifier->particle_id_full, identifier->device_id, identifier->device_name, identifier->local_ip, identifier->mac);
}

/**
 * @brief Send a identifier message
 * @param chan MAVLink channel to send the message
 *
 * @param fw_version  Particle FW version
 * @param particle_id_full   Particle ID of device. Read Only. 
 * @param device_id  Device id of scanner matching manufacturing sticker. i.e. P2-ABC123. Read only
 * @param device_name   Friendly name of device. E.g. "57 Rock West". User settable
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_identifier_send(mavlink_channel_t chan, uint8_t fw_version, const char *particle_id_full, const char *device_id, const char *device_name, const uint8_t *local_ip, const uint8_t *mac)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];
    _mav_put_uint8_t(buf, 0, fw_version);
    _mav_put_char_array(buf, 1, particle_id_full, 24);
    _mav_put_char_array(buf, 25, device_id, 20);
    _mav_put_char_array(buf, 45, device_name, 30);
    _mav_put_uint8_t_array(buf, 75, local_ip, 4);
    _mav_put_uint8_t_array(buf, 79, mac, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, buf, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#else
    mavlink_identifier_t packet;
    packet.fw_version = fw_version;
    mav_array_memcpy(packet.particle_id_full, particle_id_full, sizeof(char)*24);
    mav_array_memcpy(packet.device_id, device_id, sizeof(char)*20);
    mav_array_memcpy(packet.device_name, device_name, sizeof(char)*30);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, (const char *)&packet, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#endif
}

/**
 * @brief Send a identifier message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_identifier_send_struct(mavlink_channel_t chan, const mavlink_identifier_t* identifier)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_identifier_send(chan, identifier->fw_version, identifier->particle_id_full, identifier->device_id, identifier->device_name, identifier->local_ip, identifier->mac);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, (const char *)identifier, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#endif
}

#if MAVLINK_MSG_ID_IDENTIFIER_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_identifier_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t fw_version, const char *particle_id_full, const char *device_id, const char *device_name, const uint8_t *local_ip, const uint8_t *mac)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, fw_version);
    _mav_put_char_array(buf, 1, particle_id_full, 24);
    _mav_put_char_array(buf, 25, device_id, 20);
    _mav_put_char_array(buf, 45, device_name, 30);
    _mav_put_uint8_t_array(buf, 75, local_ip, 4);
    _mav_put_uint8_t_array(buf, 79, mac, 6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, buf, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#else
    mavlink_identifier_t *packet = (mavlink_identifier_t *)msgbuf;
    packet->fw_version = fw_version;
    mav_array_memcpy(packet->particle_id_full, particle_id_full, sizeof(char)*24);
    mav_array_memcpy(packet->device_id, device_id, sizeof(char)*20);
    mav_array_memcpy(packet->device_name, device_name, sizeof(char)*30);
    mav_array_memcpy(packet->local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->mac, mac, sizeof(uint8_t)*6);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, (const char *)packet, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#endif
}
#endif

#endif

// MESSAGE IDENTIFIER UNPACKING


/**
 * @brief Get field fw_version from identifier message
 *
 * @return  Particle FW version
 */
static inline uint8_t mavlink_msg_identifier_get_fw_version(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field particle_id_full from identifier message
 *
 * @return   Particle ID of device. Read Only. 
 */
static inline uint16_t mavlink_msg_identifier_get_particle_id_full(const mavlink_message_t* msg, char *particle_id_full)
{
    return _MAV_RETURN_char_array(msg, particle_id_full, 24,  1);
}

/**
 * @brief Get field device_id from identifier message
 *
 * @return  Device id of scanner matching manufacturing sticker. i.e. P2-ABC123. Read only
 */
static inline uint16_t mavlink_msg_identifier_get_device_id(const mavlink_message_t* msg, char *device_id)
{
    return _MAV_RETURN_char_array(msg, device_id, 20,  25);
}

/**
 * @brief Get field device_name from identifier message
 *
 * @return   Friendly name of device. E.g. "57 Rock West". User settable
 */
static inline uint16_t mavlink_msg_identifier_get_device_name(const mavlink_message_t* msg, char *device_name)
{
    return _MAV_RETURN_char_array(msg, device_name, 30,  45);
}

/**
 * @brief Get field local_ip from identifier message
 *
 * @return   local IPV4 Address of the device
 */
static inline uint16_t mavlink_msg_identifier_get_local_ip(const mavlink_message_t* msg, uint8_t *local_ip)
{
    return _MAV_RETURN_uint8_t_array(msg, local_ip, 4,  75);
}

/**
 * @brief Get field mac from identifier message
 *
 * @return   MAC address of the device
 */
static inline uint16_t mavlink_msg_identifier_get_mac(const mavlink_message_t* msg, uint8_t *mac)
{
    return _MAV_RETURN_uint8_t_array(msg, mac, 6,  79);
}

/**
 * @brief Decode a identifier message into a struct
 *
 * @param msg The message to decode
 * @param identifier C-struct to decode the message contents into
 */
static inline void mavlink_msg_identifier_decode(const mavlink_message_t* msg, mavlink_identifier_t* identifier)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    identifier->fw_version = mavlink_msg_identifier_get_fw_version(msg);
    mavlink_msg_identifier_get_particle_id_full(msg, identifier->particle_id_full);
    mavlink_msg_identifier_get_device_id(msg, identifier->device_id);
    mavlink_msg_identifier_get_device_name(msg, identifier->device_name);
    mavlink_msg_identifier_get_local_ip(msg, identifier->local_ip);
    mavlink_msg_identifier_get_mac(msg, identifier->mac);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_IDENTIFIER_LEN? msg->len : MAVLINK_MSG_ID_IDENTIFIER_LEN;
        memset(identifier, 0, MAVLINK_MSG_ID_IDENTIFIER_LEN);
    memcpy(identifier, _MAV_PAYLOAD(msg), len);
#endif
}
