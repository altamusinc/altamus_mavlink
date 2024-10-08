#pragma once
// MESSAGE SYSTEM_STATUS PACKING

#define MAVLINK_MSG_ID_SYSTEM_STATUS 3


typedef struct __mavlink_system_status_t {
 uint16_t power_status_bitmask; /*<   Bitmask of devices and their power status: 1 = on 0 = off */
 uint16_t health_status_bitmask; /*<   Bitmask of health of devices: 1 = healthy 0 = unhealthy */
 uint8_t state; /*<   Current State of the Device */
} mavlink_system_status_t;

#define MAVLINK_MSG_ID_SYSTEM_STATUS_LEN 5
#define MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN 5
#define MAVLINK_MSG_ID_3_LEN 5
#define MAVLINK_MSG_ID_3_MIN_LEN 5

#define MAVLINK_MSG_ID_SYSTEM_STATUS_CRC 252
#define MAVLINK_MSG_ID_3_CRC 252



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_SYSTEM_STATUS { \
    3, \
    "SYSTEM_STATUS", \
    3, \
    {  { "state", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_system_status_t, state) }, \
         { "power_status_bitmask", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_system_status_t, power_status_bitmask) }, \
         { "health_status_bitmask", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_system_status_t, health_status_bitmask) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_SYSTEM_STATUS { \
    "SYSTEM_STATUS", \
    3, \
    {  { "state", NULL, MAVLINK_TYPE_UINT8_T, 0, 4, offsetof(mavlink_system_status_t, state) }, \
         { "power_status_bitmask", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_system_status_t, power_status_bitmask) }, \
         { "health_status_bitmask", NULL, MAVLINK_TYPE_UINT16_T, 0, 2, offsetof(mavlink_system_status_t, health_status_bitmask) }, \
         } \
}
#endif

/**
 * @brief Pack a system_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param state   Current State of the Device 
 * @param power_status_bitmask   Bitmask of devices and their power status: 1 = on 0 = off 
 * @param health_status_bitmask   Bitmask of health of devices: 1 = healthy 0 = unhealthy 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_system_status_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t state, uint16_t power_status_bitmask, uint16_t health_status_bitmask)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SYSTEM_STATUS_LEN];
    _mav_put_uint16_t(buf, 0, power_status_bitmask);
    _mav_put_uint16_t(buf, 2, health_status_bitmask);
    _mav_put_uint8_t(buf, 4, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
#else
    mavlink_system_status_t packet;
    packet.power_status_bitmask = power_status_bitmask;
    packet.health_status_bitmask = health_status_bitmask;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SYSTEM_STATUS;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
}

/**
 * @brief Pack a system_status message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param state   Current State of the Device 
 * @param power_status_bitmask   Bitmask of devices and their power status: 1 = on 0 = off 
 * @param health_status_bitmask   Bitmask of health of devices: 1 = healthy 0 = unhealthy 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_system_status_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t state, uint16_t power_status_bitmask, uint16_t health_status_bitmask)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SYSTEM_STATUS_LEN];
    _mav_put_uint16_t(buf, 0, power_status_bitmask);
    _mav_put_uint16_t(buf, 2, health_status_bitmask);
    _mav_put_uint8_t(buf, 4, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
#else
    mavlink_system_status_t packet;
    packet.power_status_bitmask = power_status_bitmask;
    packet.health_status_bitmask = health_status_bitmask;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SYSTEM_STATUS;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
#endif
}

/**
 * @brief Pack a system_status message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param state   Current State of the Device 
 * @param power_status_bitmask   Bitmask of devices and their power status: 1 = on 0 = off 
 * @param health_status_bitmask   Bitmask of health of devices: 1 = healthy 0 = unhealthy 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_system_status_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t state,uint16_t power_status_bitmask,uint16_t health_status_bitmask)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SYSTEM_STATUS_LEN];
    _mav_put_uint16_t(buf, 0, power_status_bitmask);
    _mav_put_uint16_t(buf, 2, health_status_bitmask);
    _mav_put_uint8_t(buf, 4, state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
#else
    mavlink_system_status_t packet;
    packet.power_status_bitmask = power_status_bitmask;
    packet.health_status_bitmask = health_status_bitmask;
    packet.state = state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_SYSTEM_STATUS;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
}

/**
 * @brief Encode a system_status struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param system_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_system_status_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_system_status_t* system_status)
{
    return mavlink_msg_system_status_pack(system_id, component_id, msg, system_status->state, system_status->power_status_bitmask, system_status->health_status_bitmask);
}

/**
 * @brief Encode a system_status struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param system_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_system_status_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_system_status_t* system_status)
{
    return mavlink_msg_system_status_pack_chan(system_id, component_id, chan, msg, system_status->state, system_status->power_status_bitmask, system_status->health_status_bitmask);
}

/**
 * @brief Encode a system_status struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param system_status C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_system_status_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_system_status_t* system_status)
{
    return mavlink_msg_system_status_pack_status(system_id, component_id, _status, msg,  system_status->state, system_status->power_status_bitmask, system_status->health_status_bitmask);
}

/**
 * @brief Send a system_status message
 * @param chan MAVLink channel to send the message
 *
 * @param state   Current State of the Device 
 * @param power_status_bitmask   Bitmask of devices and their power status: 1 = on 0 = off 
 * @param health_status_bitmask   Bitmask of health of devices: 1 = healthy 0 = unhealthy 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_system_status_send(mavlink_channel_t chan, uint8_t state, uint16_t power_status_bitmask, uint16_t health_status_bitmask)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_SYSTEM_STATUS_LEN];
    _mav_put_uint16_t(buf, 0, power_status_bitmask);
    _mav_put_uint16_t(buf, 2, health_status_bitmask);
    _mav_put_uint8_t(buf, 4, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_STATUS, buf, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
#else
    mavlink_system_status_t packet;
    packet.power_status_bitmask = power_status_bitmask;
    packet.health_status_bitmask = health_status_bitmask;
    packet.state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_STATUS, (const char *)&packet, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
#endif
}

/**
 * @brief Send a system_status message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_system_status_send_struct(mavlink_channel_t chan, const mavlink_system_status_t* system_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_system_status_send(chan, system_status->state, system_status->power_status_bitmask, system_status->health_status_bitmask);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_STATUS, (const char *)system_status, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
#endif
}

#if MAVLINK_MSG_ID_SYSTEM_STATUS_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_system_status_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t state, uint16_t power_status_bitmask, uint16_t health_status_bitmask)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, power_status_bitmask);
    _mav_put_uint16_t(buf, 2, health_status_bitmask);
    _mav_put_uint8_t(buf, 4, state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_STATUS, buf, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
#else
    mavlink_system_status_t *packet = (mavlink_system_status_t *)msgbuf;
    packet->power_status_bitmask = power_status_bitmask;
    packet->health_status_bitmask = health_status_bitmask;
    packet->state = state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_SYSTEM_STATUS, (const char *)packet, MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN, MAVLINK_MSG_ID_SYSTEM_STATUS_CRC);
#endif
}
#endif

#endif

// MESSAGE SYSTEM_STATUS UNPACKING


/**
 * @brief Get field state from system_status message
 *
 * @return   Current State of the Device 
 */
static inline uint8_t mavlink_msg_system_status_get_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  4);
}

/**
 * @brief Get field power_status_bitmask from system_status message
 *
 * @return   Bitmask of devices and their power status: 1 = on 0 = off 
 */
static inline uint16_t mavlink_msg_system_status_get_power_status_bitmask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field health_status_bitmask from system_status message
 *
 * @return   Bitmask of health of devices: 1 = healthy 0 = unhealthy 
 */
static inline uint16_t mavlink_msg_system_status_get_health_status_bitmask(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  2);
}

/**
 * @brief Decode a system_status message into a struct
 *
 * @param msg The message to decode
 * @param system_status C-struct to decode the message contents into
 */
static inline void mavlink_msg_system_status_decode(const mavlink_message_t* msg, mavlink_system_status_t* system_status)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    system_status->power_status_bitmask = mavlink_msg_system_status_get_power_status_bitmask(msg);
    system_status->health_status_bitmask = mavlink_msg_system_status_get_health_status_bitmask(msg);
    system_status->state = mavlink_msg_system_status_get_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_SYSTEM_STATUS_LEN? msg->len : MAVLINK_MSG_ID_SYSTEM_STATUS_LEN;
        memset(system_status, 0, MAVLINK_MSG_ID_SYSTEM_STATUS_LEN);
    memcpy(system_status, _MAV_PAYLOAD(msg), len);
#endif
}
