#pragma once
// MESSAGE VISIBLE_BADGES PACKING

#define MAVLINK_MSG_ID_VISIBLE_BADGES 9


typedef struct __mavlink_visible_badges_t {
 uint64_t badge_id_int[15]; /*<  List of visible badge ids*/
 uint32_t arrival_time[15]; /*< [s]  unix start time of when the badge arrived*/
 uint8_t auth_state[15]; /*<  */
} mavlink_visible_badges_t;

#define MAVLINK_MSG_ID_VISIBLE_BADGES_LEN 195
#define MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN 195
#define MAVLINK_MSG_ID_9_LEN 195
#define MAVLINK_MSG_ID_9_MIN_LEN 195

#define MAVLINK_MSG_ID_VISIBLE_BADGES_CRC 75
#define MAVLINK_MSG_ID_9_CRC 75

#define MAVLINK_MSG_VISIBLE_BADGES_FIELD_BADGE_ID_INT_LEN 15
#define MAVLINK_MSG_VISIBLE_BADGES_FIELD_ARRIVAL_TIME_LEN 15
#define MAVLINK_MSG_VISIBLE_BADGES_FIELD_AUTH_STATE_LEN 15

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_VISIBLE_BADGES { \
    9, \
    "VISIBLE_BADGES", \
    3, \
    {  { "badge_id_int", NULL, MAVLINK_TYPE_UINT64_T, 15, 0, offsetof(mavlink_visible_badges_t, badge_id_int) }, \
         { "auth_state", NULL, MAVLINK_TYPE_UINT8_T, 15, 180, offsetof(mavlink_visible_badges_t, auth_state) }, \
         { "arrival_time", NULL, MAVLINK_TYPE_UINT32_T, 15, 120, offsetof(mavlink_visible_badges_t, arrival_time) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_VISIBLE_BADGES { \
    "VISIBLE_BADGES", \
    3, \
    {  { "badge_id_int", NULL, MAVLINK_TYPE_UINT64_T, 15, 0, offsetof(mavlink_visible_badges_t, badge_id_int) }, \
         { "auth_state", NULL, MAVLINK_TYPE_UINT8_T, 15, 180, offsetof(mavlink_visible_badges_t, auth_state) }, \
         { "arrival_time", NULL, MAVLINK_TYPE_UINT32_T, 15, 120, offsetof(mavlink_visible_badges_t, arrival_time) }, \
         } \
}
#endif

/**
 * @brief Pack a visible_badges message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_id_int  List of visible badge ids
 * @param auth_state  
 * @param arrival_time [s]  unix start time of when the badge arrived
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_visible_badges_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const uint64_t *badge_id_int, const uint8_t *auth_state, const uint32_t *arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VISIBLE_BADGES_LEN];

    _mav_put_uint64_t_array(buf, 0, badge_id_int, 15);
    _mav_put_uint32_t_array(buf, 120, arrival_time, 15);
    _mav_put_uint8_t_array(buf, 180, auth_state, 15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
#else
    mavlink_visible_badges_t packet;

    mav_array_memcpy(packet.badge_id_int, badge_id_int, sizeof(uint64_t)*15);
    mav_array_memcpy(packet.arrival_time, arrival_time, sizeof(uint32_t)*15);
    mav_array_memcpy(packet.auth_state, auth_state, sizeof(uint8_t)*15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VISIBLE_BADGES;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
}

/**
 * @brief Pack a visible_badges message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_id_int  List of visible badge ids
 * @param auth_state  
 * @param arrival_time [s]  unix start time of when the badge arrived
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_visible_badges_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               const uint64_t *badge_id_int, const uint8_t *auth_state, const uint32_t *arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VISIBLE_BADGES_LEN];

    _mav_put_uint64_t_array(buf, 0, badge_id_int, 15);
    _mav_put_uint32_t_array(buf, 120, arrival_time, 15);
    _mav_put_uint8_t_array(buf, 180, auth_state, 15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
#else
    mavlink_visible_badges_t packet;

    mav_array_memcpy(packet.badge_id_int, badge_id_int, sizeof(uint64_t)*15);
    mav_array_memcpy(packet.arrival_time, arrival_time, sizeof(uint32_t)*15);
    mav_array_memcpy(packet.auth_state, auth_state, sizeof(uint8_t)*15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VISIBLE_BADGES;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
#endif
}

/**
 * @brief Pack a visible_badges message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param badge_id_int  List of visible badge ids
 * @param auth_state  
 * @param arrival_time [s]  unix start time of when the badge arrived
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_visible_badges_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const uint64_t *badge_id_int,const uint8_t *auth_state,const uint32_t *arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VISIBLE_BADGES_LEN];

    _mav_put_uint64_t_array(buf, 0, badge_id_int, 15);
    _mav_put_uint32_t_array(buf, 120, arrival_time, 15);
    _mav_put_uint8_t_array(buf, 180, auth_state, 15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
#else
    mavlink_visible_badges_t packet;

    mav_array_memcpy(packet.badge_id_int, badge_id_int, sizeof(uint64_t)*15);
    mav_array_memcpy(packet.arrival_time, arrival_time, sizeof(uint32_t)*15);
    mav_array_memcpy(packet.auth_state, auth_state, sizeof(uint8_t)*15);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_VISIBLE_BADGES;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
}

/**
 * @brief Encode a visible_badges struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param visible_badges C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_visible_badges_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_visible_badges_t* visible_badges)
{
    return mavlink_msg_visible_badges_pack(system_id, component_id, msg, visible_badges->badge_id_int, visible_badges->auth_state, visible_badges->arrival_time);
}

/**
 * @brief Encode a visible_badges struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param visible_badges C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_visible_badges_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_visible_badges_t* visible_badges)
{
    return mavlink_msg_visible_badges_pack_chan(system_id, component_id, chan, msg, visible_badges->badge_id_int, visible_badges->auth_state, visible_badges->arrival_time);
}

/**
 * @brief Encode a visible_badges struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param visible_badges C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_visible_badges_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_visible_badges_t* visible_badges)
{
    return mavlink_msg_visible_badges_pack_status(system_id, component_id, _status, msg,  visible_badges->badge_id_int, visible_badges->auth_state, visible_badges->arrival_time);
}

/**
 * @brief Send a visible_badges message
 * @param chan MAVLink channel to send the message
 *
 * @param badge_id_int  List of visible badge ids
 * @param auth_state  
 * @param arrival_time [s]  unix start time of when the badge arrived
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_visible_badges_send(mavlink_channel_t chan, const uint64_t *badge_id_int, const uint8_t *auth_state, const uint32_t *arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_VISIBLE_BADGES_LEN];

    _mav_put_uint64_t_array(buf, 0, badge_id_int, 15);
    _mav_put_uint32_t_array(buf, 120, arrival_time, 15);
    _mav_put_uint8_t_array(buf, 180, auth_state, 15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VISIBLE_BADGES, buf, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
#else
    mavlink_visible_badges_t packet;

    mav_array_memcpy(packet.badge_id_int, badge_id_int, sizeof(uint64_t)*15);
    mav_array_memcpy(packet.arrival_time, arrival_time, sizeof(uint32_t)*15);
    mav_array_memcpy(packet.auth_state, auth_state, sizeof(uint8_t)*15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VISIBLE_BADGES, (const char *)&packet, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
#endif
}

/**
 * @brief Send a visible_badges message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_visible_badges_send_struct(mavlink_channel_t chan, const mavlink_visible_badges_t* visible_badges)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_visible_badges_send(chan, visible_badges->badge_id_int, visible_badges->auth_state, visible_badges->arrival_time);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VISIBLE_BADGES, (const char *)visible_badges, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
#endif
}

#if MAVLINK_MSG_ID_VISIBLE_BADGES_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_visible_badges_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const uint64_t *badge_id_int, const uint8_t *auth_state, const uint32_t *arrival_time)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_uint64_t_array(buf, 0, badge_id_int, 15);
    _mav_put_uint32_t_array(buf, 120, arrival_time, 15);
    _mav_put_uint8_t_array(buf, 180, auth_state, 15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VISIBLE_BADGES, buf, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
#else
    mavlink_visible_badges_t *packet = (mavlink_visible_badges_t *)msgbuf;

    mav_array_memcpy(packet->badge_id_int, badge_id_int, sizeof(uint64_t)*15);
    mav_array_memcpy(packet->arrival_time, arrival_time, sizeof(uint32_t)*15);
    mav_array_memcpy(packet->auth_state, auth_state, sizeof(uint8_t)*15);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_VISIBLE_BADGES, (const char *)packet, MAVLINK_MSG_ID_VISIBLE_BADGES_MIN_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN, MAVLINK_MSG_ID_VISIBLE_BADGES_CRC);
#endif
}
#endif

#endif

// MESSAGE VISIBLE_BADGES UNPACKING


/**
 * @brief Get field badge_id_int from visible_badges message
 *
 * @return  List of visible badge ids
 */
static inline uint16_t mavlink_msg_visible_badges_get_badge_id_int(const mavlink_message_t* msg, uint64_t *badge_id_int)
{
    return _MAV_RETURN_uint64_t_array(msg, badge_id_int, 15,  0);
}

/**
 * @brief Get field auth_state from visible_badges message
 *
 * @return  
 */
static inline uint16_t mavlink_msg_visible_badges_get_auth_state(const mavlink_message_t* msg, uint8_t *auth_state)
{
    return _MAV_RETURN_uint8_t_array(msg, auth_state, 15,  180);
}

/**
 * @brief Get field arrival_time from visible_badges message
 *
 * @return [s]  unix start time of when the badge arrived
 */
static inline uint16_t mavlink_msg_visible_badges_get_arrival_time(const mavlink_message_t* msg, uint32_t *arrival_time)
{
    return _MAV_RETURN_uint32_t_array(msg, arrival_time, 15,  120);
}

/**
 * @brief Decode a visible_badges message into a struct
 *
 * @param msg The message to decode
 * @param visible_badges C-struct to decode the message contents into
 */
static inline void mavlink_msg_visible_badges_decode(const mavlink_message_t* msg, mavlink_visible_badges_t* visible_badges)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_visible_badges_get_badge_id_int(msg, visible_badges->badge_id_int);
    mavlink_msg_visible_badges_get_arrival_time(msg, visible_badges->arrival_time);
    mavlink_msg_visible_badges_get_auth_state(msg, visible_badges->auth_state);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_VISIBLE_BADGES_LEN? msg->len : MAVLINK_MSG_ID_VISIBLE_BADGES_LEN;
        memset(visible_badges, 0, MAVLINK_MSG_ID_VISIBLE_BADGES_LEN);
    memcpy(visible_badges, _MAV_PAYLOAD(msg), len);
#endif
}
