#pragma once
// MESSAGE TRUCK_INFO PACKING

#define MAVLINK_MSG_ID_TRUCK_INFO 8


typedef struct __mavlink_truck_info_t {
 uint64_t badge_id_int; /*<   badge ID as int*/
 uint32_t arrival_time; /*< [s]  unix start time of when the truck arrived*/
 char truck_name[20]; /*<   Truck name associated with badge ID*/
} mavlink_truck_info_t;

#define MAVLINK_MSG_ID_TRUCK_INFO_LEN 32
#define MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN 32
#define MAVLINK_MSG_ID_8_LEN 32
#define MAVLINK_MSG_ID_8_MIN_LEN 32

#define MAVLINK_MSG_ID_TRUCK_INFO_CRC 201
#define MAVLINK_MSG_ID_8_CRC 201

#define MAVLINK_MSG_TRUCK_INFO_FIELD_TRUCK_NAME_LEN 20

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_TRUCK_INFO { \
    8, \
    "TRUCK_INFO", \
    3, \
    {  { "badge_id_int", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_truck_info_t, badge_id_int) }, \
         { "truck_name", NULL, MAVLINK_TYPE_CHAR, 20, 12, offsetof(mavlink_truck_info_t, truck_name) }, \
         { "arrival_time", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_truck_info_t, arrival_time) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_TRUCK_INFO { \
    "TRUCK_INFO", \
    3, \
    {  { "badge_id_int", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_truck_info_t, badge_id_int) }, \
         { "truck_name", NULL, MAVLINK_TYPE_CHAR, 20, 12, offsetof(mavlink_truck_info_t, truck_name) }, \
         { "arrival_time", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_truck_info_t, arrival_time) }, \
         } \
}
#endif

/**
 * @brief Pack a truck_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param arrival_time [s]  unix start time of when the truck arrived
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_truck_info_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t badge_id_int, const char *truck_name, uint32_t arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRUCK_INFO_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, arrival_time);
    _mav_put_char_array(buf, 12, truck_name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
#else
    mavlink_truck_info_t packet;
    packet.badge_id_int = badge_id_int;
    packet.arrival_time = arrival_time;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TRUCK_INFO;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
}

/**
 * @brief Pack a truck_info message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param arrival_time [s]  unix start time of when the truck arrived
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_truck_info_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t badge_id_int, const char *truck_name, uint32_t arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRUCK_INFO_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, arrival_time);
    _mav_put_char_array(buf, 12, truck_name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
#else
    mavlink_truck_info_t packet;
    packet.badge_id_int = badge_id_int;
    packet.arrival_time = arrival_time;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TRUCK_INFO;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
#endif
}

/**
 * @brief Pack a truck_info message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param arrival_time [s]  unix start time of when the truck arrived
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_truck_info_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t badge_id_int,const char *truck_name,uint32_t arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRUCK_INFO_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, arrival_time);
    _mav_put_char_array(buf, 12, truck_name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
#else
    mavlink_truck_info_t packet;
    packet.badge_id_int = badge_id_int;
    packet.arrival_time = arrival_time;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_TRUCK_INFO;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
}

/**
 * @brief Encode a truck_info struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param truck_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_truck_info_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_truck_info_t* truck_info)
{
    return mavlink_msg_truck_info_pack(system_id, component_id, msg, truck_info->badge_id_int, truck_info->truck_name, truck_info->arrival_time);
}

/**
 * @brief Encode a truck_info struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param truck_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_truck_info_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_truck_info_t* truck_info)
{
    return mavlink_msg_truck_info_pack_chan(system_id, component_id, chan, msg, truck_info->badge_id_int, truck_info->truck_name, truck_info->arrival_time);
}

/**
 * @brief Encode a truck_info struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param truck_info C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_truck_info_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_truck_info_t* truck_info)
{
    return mavlink_msg_truck_info_pack_status(system_id, component_id, _status, msg,  truck_info->badge_id_int, truck_info->truck_name, truck_info->arrival_time);
}

/**
 * @brief Send a truck_info message
 * @param chan MAVLink channel to send the message
 *
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param arrival_time [s]  unix start time of when the truck arrived
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_truck_info_send(mavlink_channel_t chan, uint64_t badge_id_int, const char *truck_name, uint32_t arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_TRUCK_INFO_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, arrival_time);
    _mav_put_char_array(buf, 12, truck_name, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRUCK_INFO, buf, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
#else
    mavlink_truck_info_t packet;
    packet.badge_id_int = badge_id_int;
    packet.arrival_time = arrival_time;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRUCK_INFO, (const char *)&packet, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
#endif
}

/**
 * @brief Send a truck_info message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_truck_info_send_struct(mavlink_channel_t chan, const mavlink_truck_info_t* truck_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_truck_info_send(chan, truck_info->badge_id_int, truck_info->truck_name, truck_info->arrival_time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRUCK_INFO, (const char *)truck_info, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
#endif
}

#if MAVLINK_MSG_ID_TRUCK_INFO_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_truck_info_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t badge_id_int, const char *truck_name, uint32_t arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, arrival_time);
    _mav_put_char_array(buf, 12, truck_name, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRUCK_INFO, buf, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
#else
    mavlink_truck_info_t *packet = (mavlink_truck_info_t *)msgbuf;
    packet->badge_id_int = badge_id_int;
    packet->arrival_time = arrival_time;
    mav_array_memcpy(packet->truck_name, truck_name, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_TRUCK_INFO, (const char *)packet, MAVLINK_MSG_ID_TRUCK_INFO_MIN_LEN, MAVLINK_MSG_ID_TRUCK_INFO_LEN, MAVLINK_MSG_ID_TRUCK_INFO_CRC);
#endif
}
#endif

#endif

// MESSAGE TRUCK_INFO UNPACKING


/**
 * @brief Get field badge_id_int from truck_info message
 *
 * @return   badge ID as int
 */
static inline uint64_t mavlink_msg_truck_info_get_badge_id_int(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field truck_name from truck_info message
 *
 * @return   Truck name associated with badge ID
 */
static inline uint16_t mavlink_msg_truck_info_get_truck_name(const mavlink_message_t* msg, char *truck_name)
{
    return _MAV_RETURN_char_array(msg, truck_name, 20,  12);
}

/**
 * @brief Get field arrival_time from truck_info message
 *
 * @return [s]  unix start time of when the truck arrived
 */
static inline uint32_t mavlink_msg_truck_info_get_arrival_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Decode a truck_info message into a struct
 *
 * @param msg The message to decode
 * @param truck_info C-struct to decode the message contents into
 */
static inline void mavlink_msg_truck_info_decode(const mavlink_message_t* msg, mavlink_truck_info_t* truck_info)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    truck_info->badge_id_int = mavlink_msg_truck_info_get_badge_id_int(msg);
    truck_info->arrival_time = mavlink_msg_truck_info_get_arrival_time(msg);
    mavlink_msg_truck_info_get_truck_name(msg, truck_info->truck_name);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_TRUCK_INFO_LEN? msg->len : MAVLINK_MSG_ID_TRUCK_INFO_LEN;
        memset(truck_info, 0, MAVLINK_MSG_ID_TRUCK_INFO_LEN);
    memcpy(truck_info, _MAV_PAYLOAD(msg), len);
#endif
}
