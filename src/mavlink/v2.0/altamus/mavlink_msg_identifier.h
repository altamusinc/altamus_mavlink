#pragma once
// MESSAGE IDENTIFIER PACKING

#define MAVLINK_MSG_ID_IDENTIFIER 7


typedef struct __mavlink_identifier_t {
 char particle_id[24]; /*<   Particle ID of device. Unique and unchangable */
 uint8_t local_ip[4]; /*<   local IPV4 Address of the device*/
 uint8_t mac[6]; /*<   MAC address of the device*/
 char name[16]; /*<  Friendly name of device i.e. P2-123456*/
} mavlink_identifier_t;

#define MAVLINK_MSG_ID_IDENTIFIER_LEN 50
#define MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN 50
#define MAVLINK_MSG_ID_7_LEN 50
#define MAVLINK_MSG_ID_7_MIN_LEN 50

#define MAVLINK_MSG_ID_IDENTIFIER_CRC 110
#define MAVLINK_MSG_ID_7_CRC 110

#define MAVLINK_MSG_IDENTIFIER_FIELD_PARTICLE_ID_LEN 24
#define MAVLINK_MSG_IDENTIFIER_FIELD_LOCAL_IP_LEN 4
#define MAVLINK_MSG_IDENTIFIER_FIELD_MAC_LEN 6
#define MAVLINK_MSG_IDENTIFIER_FIELD_NAME_LEN 16

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_IDENTIFIER { \
    7, \
    "IDENTIFIER", \
    4, \
    {  { "particle_id", NULL, MAVLINK_TYPE_CHAR, 24, 0, offsetof(mavlink_identifier_t, particle_id) }, \
         { "local_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 24, offsetof(mavlink_identifier_t, local_ip) }, \
         { "mac", NULL, MAVLINK_TYPE_UINT8_T, 6, 28, offsetof(mavlink_identifier_t, mac) }, \
         { "name", NULL, MAVLINK_TYPE_CHAR, 16, 34, offsetof(mavlink_identifier_t, name) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_IDENTIFIER { \
    "IDENTIFIER", \
    4, \
    {  { "particle_id", NULL, MAVLINK_TYPE_CHAR, 24, 0, offsetof(mavlink_identifier_t, particle_id) }, \
         { "local_ip", NULL, MAVLINK_TYPE_UINT8_T, 4, 24, offsetof(mavlink_identifier_t, local_ip) }, \
         { "mac", NULL, MAVLINK_TYPE_UINT8_T, 6, 28, offsetof(mavlink_identifier_t, mac) }, \
         { "name", NULL, MAVLINK_TYPE_CHAR, 16, 34, offsetof(mavlink_identifier_t, name) }, \
         } \
}
#endif

/**
 * @brief Pack a identifier message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param particle_id   Particle ID of device. Unique and unchangable 
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 * @param name  Friendly name of device i.e. P2-123456
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_identifier_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const char *particle_id, const uint8_t *local_ip, const uint8_t *mac, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];

    _mav_put_char_array(buf, 0, particle_id, 24);
    _mav_put_uint8_t_array(buf, 24, local_ip, 4);
    _mav_put_uint8_t_array(buf, 28, mac, 6);
    _mav_put_char_array(buf, 34, name, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#else
    mavlink_identifier_t packet;

    mav_array_memcpy(packet.particle_id, particle_id, sizeof(char)*24);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.name, name, sizeof(char)*16);
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
 * @param particle_id   Particle ID of device. Unique and unchangable 
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 * @param name  Friendly name of device i.e. P2-123456
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_identifier_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const char *particle_id, const uint8_t *local_ip, const uint8_t *mac, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];

    _mav_put_char_array(buf, 0, particle_id, 24);
    _mav_put_uint8_t_array(buf, 24, local_ip, 4);
    _mav_put_uint8_t_array(buf, 28, mac, 6);
    _mav_put_char_array(buf, 34, name, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#else
    mavlink_identifier_t packet;

    mav_array_memcpy(packet.particle_id, particle_id, sizeof(char)*24);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.name, name, sizeof(char)*16);
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
 * @param particle_id   Particle ID of device. Unique and unchangable 
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 * @param name  Friendly name of device i.e. P2-123456
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_identifier_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const char *particle_id,const uint8_t *local_ip,const uint8_t *mac,const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];

    _mav_put_char_array(buf, 0, particle_id, 24);
    _mav_put_uint8_t_array(buf, 24, local_ip, 4);
    _mav_put_uint8_t_array(buf, 28, mac, 6);
    _mav_put_char_array(buf, 34, name, 16);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_IDENTIFIER_LEN);
#else
    mavlink_identifier_t packet;

    mav_array_memcpy(packet.particle_id, particle_id, sizeof(char)*24);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.name, name, sizeof(char)*16);
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
    return mavlink_msg_identifier_pack(system_id, component_id, msg, identifier->particle_id, identifier->local_ip, identifier->mac, identifier->name);
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
    return mavlink_msg_identifier_pack_chan(system_id, component_id, chan, msg, identifier->particle_id, identifier->local_ip, identifier->mac, identifier->name);
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
    return mavlink_msg_identifier_pack_status(system_id, component_id, _status, msg,  identifier->particle_id, identifier->local_ip, identifier->mac, identifier->name);
}

/**
 * @brief Send a identifier message
 * @param chan MAVLink channel to send the message
 *
 * @param particle_id   Particle ID of device. Unique and unchangable 
 * @param local_ip   local IPV4 Address of the device
 * @param mac   MAC address of the device
 * @param name  Friendly name of device i.e. P2-123456
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_identifier_send(mavlink_channel_t chan, const char *particle_id, const uint8_t *local_ip, const uint8_t *mac, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_IDENTIFIER_LEN];

    _mav_put_char_array(buf, 0, particle_id, 24);
    _mav_put_uint8_t_array(buf, 24, local_ip, 4);
    _mav_put_uint8_t_array(buf, 28, mac, 6);
    _mav_put_char_array(buf, 34, name, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, buf, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#else
    mavlink_identifier_t packet;

    mav_array_memcpy(packet.particle_id, particle_id, sizeof(char)*24);
    mav_array_memcpy(packet.local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet.mac, mac, sizeof(uint8_t)*6);
    mav_array_memcpy(packet.name, name, sizeof(char)*16);
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
    mavlink_msg_identifier_send(chan, identifier->particle_id, identifier->local_ip, identifier->mac, identifier->name);
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
static inline void mavlink_msg_identifier_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *particle_id, const uint8_t *local_ip, const uint8_t *mac, const char *name)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_char_array(buf, 0, particle_id, 24);
    _mav_put_uint8_t_array(buf, 24, local_ip, 4);
    _mav_put_uint8_t_array(buf, 28, mac, 6);
    _mav_put_char_array(buf, 34, name, 16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, buf, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#else
    mavlink_identifier_t *packet = (mavlink_identifier_t *)msgbuf;

    mav_array_memcpy(packet->particle_id, particle_id, sizeof(char)*24);
    mav_array_memcpy(packet->local_ip, local_ip, sizeof(uint8_t)*4);
    mav_array_memcpy(packet->mac, mac, sizeof(uint8_t)*6);
    mav_array_memcpy(packet->name, name, sizeof(char)*16);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_IDENTIFIER, (const char *)packet, MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN, MAVLINK_MSG_ID_IDENTIFIER_LEN, MAVLINK_MSG_ID_IDENTIFIER_CRC);
#endif
}
#endif

#endif

// MESSAGE IDENTIFIER UNPACKING


/**
 * @brief Get field particle_id from identifier message
 *
 * @return   Particle ID of device. Unique and unchangable 
 */
static inline uint16_t mavlink_msg_identifier_get_particle_id(const mavlink_message_t* msg, char *particle_id)
{
    return _MAV_RETURN_char_array(msg, particle_id, 24,  0);
}

/**
 * @brief Get field local_ip from identifier message
 *
 * @return   local IPV4 Address of the device
 */
static inline uint16_t mavlink_msg_identifier_get_local_ip(const mavlink_message_t* msg, uint8_t *local_ip)
{
    return _MAV_RETURN_uint8_t_array(msg, local_ip, 4,  24);
}

/**
 * @brief Get field mac from identifier message
 *
 * @return   MAC address of the device
 */
static inline uint16_t mavlink_msg_identifier_get_mac(const mavlink_message_t* msg, uint8_t *mac)
{
    return _MAV_RETURN_uint8_t_array(msg, mac, 6,  28);
}

/**
 * @brief Get field name from identifier message
 *
 * @return  Friendly name of device i.e. P2-123456
 */
static inline uint16_t mavlink_msg_identifier_get_name(const mavlink_message_t* msg, char *name)
{
    return _MAV_RETURN_char_array(msg, name, 16,  34);
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
    mavlink_msg_identifier_get_particle_id(msg, identifier->particle_id);
    mavlink_msg_identifier_get_local_ip(msg, identifier->local_ip);
    mavlink_msg_identifier_get_mac(msg, identifier->mac);
    mavlink_msg_identifier_get_name(msg, identifier->name);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_IDENTIFIER_LEN? msg->len : MAVLINK_MSG_ID_IDENTIFIER_LEN;
        memset(identifier, 0, MAVLINK_MSG_ID_IDENTIFIER_LEN);
    memcpy(identifier, _MAV_PAYLOAD(msg), len);
#endif
}
