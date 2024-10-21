#pragma once
// MESSAGE COMPONENT_HEALTH_TEST PACKING

#define MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST 8


typedef struct __mavlink_component_health_test_t {
 uint32_t component; /*<   Which component(s) to request retest for*/
} mavlink_component_health_test_t;

#define MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN 4
#define MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN 4
#define MAVLINK_MSG_ID_8_LEN 4
#define MAVLINK_MSG_ID_8_MIN_LEN 4

#define MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC 179
#define MAVLINK_MSG_ID_8_CRC 179



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_COMPONENT_HEALTH_TEST { \
    8, \
    "COMPONENT_HEALTH_TEST", \
    1, \
    {  { "component", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_component_health_test_t, component) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_COMPONENT_HEALTH_TEST { \
    "COMPONENT_HEALTH_TEST", \
    1, \
    {  { "component", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_component_health_test_t, component) }, \
         } \
}
#endif

/**
 * @brief Pack a component_health_test message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param component   Which component(s) to request retest for
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_component_health_test_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint32_t component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN];
    _mav_put_uint32_t(buf, 0, component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
#else
    mavlink_component_health_test_t packet;
    packet.component = component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
}

/**
 * @brief Pack a component_health_test message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param component   Which component(s) to request retest for
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_component_health_test_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint32_t component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN];
    _mav_put_uint32_t(buf, 0, component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
#else
    mavlink_component_health_test_t packet;
    packet.component = component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
#endif
}

/**
 * @brief Pack a component_health_test message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param component   Which component(s) to request retest for
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_component_health_test_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint32_t component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN];
    _mav_put_uint32_t(buf, 0, component);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
#else
    mavlink_component_health_test_t packet;
    packet.component = component;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
}

/**
 * @brief Encode a component_health_test struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param component_health_test C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_component_health_test_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_component_health_test_t* component_health_test)
{
    return mavlink_msg_component_health_test_pack(system_id, component_id, msg, component_health_test->component);
}

/**
 * @brief Encode a component_health_test struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param component_health_test C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_component_health_test_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_component_health_test_t* component_health_test)
{
    return mavlink_msg_component_health_test_pack_chan(system_id, component_id, chan, msg, component_health_test->component);
}

/**
 * @brief Encode a component_health_test struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param component_health_test C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_component_health_test_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_component_health_test_t* component_health_test)
{
    return mavlink_msg_component_health_test_pack_status(system_id, component_id, _status, msg,  component_health_test->component);
}

/**
 * @brief Send a component_health_test message
 * @param chan MAVLink channel to send the message
 *
 * @param component   Which component(s) to request retest for
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_component_health_test_send(mavlink_channel_t chan, uint32_t component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN];
    _mav_put_uint32_t(buf, 0, component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST, buf, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
#else
    mavlink_component_health_test_t packet;
    packet.component = component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST, (const char *)&packet, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
#endif
}

/**
 * @brief Send a component_health_test message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_component_health_test_send_struct(mavlink_channel_t chan, const mavlink_component_health_test_t* component_health_test)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_component_health_test_send(chan, component_health_test->component);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST, (const char *)component_health_test, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
#endif
}

#if MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_component_health_test_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint32_t component)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, component);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST, buf, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
#else
    mavlink_component_health_test_t *packet = (mavlink_component_health_test_t *)msgbuf;
    packet->component = component;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST, (const char *)packet, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_CRC);
#endif
}
#endif

#endif

// MESSAGE COMPONENT_HEALTH_TEST UNPACKING


/**
 * @brief Get field component from component_health_test message
 *
 * @return   Which component(s) to request retest for
 */
static inline uint32_t mavlink_msg_component_health_test_get_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Decode a component_health_test message into a struct
 *
 * @param msg The message to decode
 * @param component_health_test C-struct to decode the message contents into
 */
static inline void mavlink_msg_component_health_test_decode(const mavlink_message_t* msg, mavlink_component_health_test_t* component_health_test)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    component_health_test->component = mavlink_msg_component_health_test_get_component(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN? msg->len : MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN;
        memset(component_health_test, 0, MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_LEN);
    memcpy(component_health_test, _MAV_PAYLOAD(msg), len);
#endif
}
