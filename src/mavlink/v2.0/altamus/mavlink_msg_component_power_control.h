#pragma once
// MESSAGE COMPONENT_POWER_CONTROL PACKING

#define MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL 2


typedef struct __mavlink_component_power_control_t {
 uint16_t device; /*<   Device to target */
 uint8_t behavior; /*<   Behavior to execute */
} mavlink_component_power_control_t;

#define MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN 3
#define MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN 3
#define MAVLINK_MSG_ID_2_LEN 3
#define MAVLINK_MSG_ID_2_MIN_LEN 3

#define MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC 246
#define MAVLINK_MSG_ID_2_CRC 246



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COMPONENT_POWER_CONTROL { \
    2, \
    "COMPONENT_POWER_CONTROL", \
    2, \
    {  { "device", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_component_power_control_t, device) }, \
         { "behavior", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_component_power_control_t, behavior) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COMPONENT_POWER_CONTROL { \
    "COMPONENT_POWER_CONTROL", \
    2, \
    {  { "device", NULL, MAVLINK_TYPE_UINT16_T, 0, 0, offsetof(mavlink_component_power_control_t, device) }, \
         { "behavior", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_component_power_control_t, behavior) }, \
         } \
}
#endif

/**
 * @brief Pack a component_power_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param device   Device to target 
 * @param behavior   Behavior to execute 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_component_power_control_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint16_t device, uint8_t behavior)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN];
    _mav_put_uint16_t(buf, 0, device);
    _mav_put_uint8_t(buf, 2, behavior);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
#else
    mavlink_component_power_control_t packet;
    packet.device = device;
    packet.behavior = behavior;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
}

/**
 * @brief Pack a component_power_control message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param device   Device to target 
 * @param behavior   Behavior to execute 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_component_power_control_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint16_t device, uint8_t behavior)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN];
    _mav_put_uint16_t(buf, 0, device);
    _mav_put_uint8_t(buf, 2, behavior);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
#else
    mavlink_component_power_control_t packet;
    packet.device = device;
    packet.behavior = behavior;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
#endif
}

/**
 * @brief Pack a component_power_control message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param device   Device to target 
 * @param behavior   Behavior to execute 
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_component_power_control_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint16_t device,uint8_t behavior)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN];
    _mav_put_uint16_t(buf, 0, device);
    _mav_put_uint8_t(buf, 2, behavior);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
#else
    mavlink_component_power_control_t packet;
    packet.device = device;
    packet.behavior = behavior;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
}

/**
 * @brief Encode a component_power_control struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param component_power_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_component_power_control_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_component_power_control_t* component_power_control)
{
    return mavlink_msg_component_power_control_pack(system_id, component_id, msg, component_power_control->device, component_power_control->behavior);
}

/**
 * @brief Encode a component_power_control struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param component_power_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_component_power_control_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_component_power_control_t* component_power_control)
{
    return mavlink_msg_component_power_control_pack_chan(system_id, component_id, chan, msg, component_power_control->device, component_power_control->behavior);
}

/**
 * @brief Encode a component_power_control struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param component_power_control C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_component_power_control_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_component_power_control_t* component_power_control)
{
    return mavlink_msg_component_power_control_pack_status(system_id, component_id, _status, msg,  component_power_control->device, component_power_control->behavior);
}

/**
 * @brief Send a component_power_control message
 * @param chan MAVLink channel to send the message
 *
 * @param device   Device to target 
 * @param behavior   Behavior to execute 
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_component_power_control_send(mavlink_channel_t chan, uint16_t device, uint8_t behavior)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN];
    _mav_put_uint16_t(buf, 0, device);
    _mav_put_uint8_t(buf, 2, behavior);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL, buf, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
#else
    mavlink_component_power_control_t packet;
    packet.device = device;
    packet.behavior = behavior;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL, (const char *)&packet, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
#endif
}

/**
 * @brief Send a component_power_control message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_component_power_control_send_struct(mavlink_channel_t chan, const mavlink_component_power_control_t* component_power_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_component_power_control_send(chan, component_power_control->device, component_power_control->behavior);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL, (const char *)component_power_control, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
#endif
}

#if MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_component_power_control_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint16_t device, uint8_t behavior)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint16_t(buf, 0, device);
    _mav_put_uint8_t(buf, 2, behavior);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL, buf, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
#else
    mavlink_component_power_control_t *packet = (mavlink_component_power_control_t *)msgbuf;
    packet->device = device;
    packet->behavior = behavior;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL, (const char *)packet, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_CRC);
#endif
}
#endif

#endif

// MESSAGE COMPONENT_POWER_CONTROL UNPACKING


/**
 * @brief Get field device from component_power_control message
 *
 * @return   Device to target 
 */
static inline uint16_t mavlink_msg_component_power_control_get_device(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  0);
}

/**
 * @brief Get field behavior from component_power_control message
 *
 * @return   Behavior to execute 
 */
static inline uint8_t mavlink_msg_component_power_control_get_behavior(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Decode a component_power_control message into a struct
 *
 * @param msg The message to decode
 * @param component_power_control C-struct to decode the message contents into
 */
static inline void mavlink_msg_component_power_control_decode(const mavlink_message_t* msg, mavlink_component_power_control_t* component_power_control)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    component_power_control->device = mavlink_msg_component_power_control_get_device(msg);
    component_power_control->behavior = mavlink_msg_component_power_control_get_behavior(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN? msg->len : MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN;
        memset(component_power_control, 0, MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_LEN);
    memcpy(component_power_control, _MAV_PAYLOAD(msg), len);
#endif
}
