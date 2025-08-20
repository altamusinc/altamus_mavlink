#pragma once
// MESSAGE STATE_INPUT_EVENT PACKING

#define MAVLINK_MSG_ID_STATE_INPUT_EVENT 1


typedef struct __mavlink_state_input_event_t {
 uint8_t event; /*<  the state input event*/
} mavlink_state_input_event_t;

#define MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN 1
#define MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN 1
#define MAVLINK_MSG_ID_1_LEN 1
#define MAVLINK_MSG_ID_1_MIN_LEN 1

#define MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC 95
#define MAVLINK_MSG_ID_1_CRC 95



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_STATE_INPUT_EVENT { \
    1, \
    "STATE_INPUT_EVENT", \
    1, \
    {  { "event", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_state_input_event_t, event) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_STATE_INPUT_EVENT { \
    "STATE_INPUT_EVENT", \
    1, \
    {  { "event", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_state_input_event_t, event) }, \
         } \
}
#endif

/**
 * @brief Pack a state_input_event message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param event  the state input event
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_state_input_event_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN];
    _mav_put_uint8_t(buf, 0, event);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
#else
    mavlink_state_input_event_t packet;
    packet.event = event;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATE_INPUT_EVENT;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
}

/**
 * @brief Pack a state_input_event message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param event  the state input event
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_state_input_event_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN];
    _mav_put_uint8_t(buf, 0, event);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
#else
    mavlink_state_input_event_t packet;
    packet.event = event;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATE_INPUT_EVENT;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
#endif
}

/**
 * @brief Pack a state_input_event message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param event  the state input event
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_state_input_event_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN];
    _mav_put_uint8_t(buf, 0, event);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
#else
    mavlink_state_input_event_t packet;
    packet.event = event;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATE_INPUT_EVENT;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
}

/**
 * @brief Encode a state_input_event struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param state_input_event C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_state_input_event_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_state_input_event_t* state_input_event)
{
    return mavlink_msg_state_input_event_pack(system_id, component_id, msg, state_input_event->event);
}

/**
 * @brief Encode a state_input_event struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param state_input_event C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_state_input_event_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_state_input_event_t* state_input_event)
{
    return mavlink_msg_state_input_event_pack_chan(system_id, component_id, chan, msg, state_input_event->event);
}

/**
 * @brief Encode a state_input_event struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param state_input_event C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_state_input_event_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_state_input_event_t* state_input_event)
{
    return mavlink_msg_state_input_event_pack_status(system_id, component_id, _status, msg,  state_input_event->event);
}

/**
 * @brief Send a state_input_event message
 * @param chan MAVLink channel to send the message
 *
 * @param event  the state input event
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_state_input_event_send(mavlink_channel_t chan, uint8_t event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN];
    _mav_put_uint8_t(buf, 0, event);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INPUT_EVENT, buf, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
#else
    mavlink_state_input_event_t packet;
    packet.event = event;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INPUT_EVENT, (const char *)&packet, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
#endif
}

/**
 * @brief Send a state_input_event message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_state_input_event_send_struct(mavlink_channel_t chan, const mavlink_state_input_event_t* state_input_event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_state_input_event_send(chan, state_input_event->event);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INPUT_EVENT, (const char *)state_input_event, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
#endif
}

#if MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_state_input_event_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, event);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INPUT_EVENT, buf, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
#else
    mavlink_state_input_event_t *packet = (mavlink_state_input_event_t *)msgbuf;
    packet->event = event;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATE_INPUT_EVENT, (const char *)packet, MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN, MAVLINK_MSG_ID_STATE_INPUT_EVENT_CRC);
#endif
}
#endif

#endif

// MESSAGE STATE_INPUT_EVENT UNPACKING


/**
 * @brief Get field event from state_input_event message
 *
 * @return  the state input event
 */
static inline uint8_t mavlink_msg_state_input_event_get_event(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Decode a state_input_event message into a struct
 *
 * @param msg The message to decode
 * @param state_input_event C-struct to decode the message contents into
 */
static inline void mavlink_msg_state_input_event_decode(const mavlink_message_t* msg, mavlink_state_input_event_t* state_input_event)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    state_input_event->event = mavlink_msg_state_input_event_get_event(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN? msg->len : MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN;
        memset(state_input_event, 0, MAVLINK_MSG_ID_STATE_INPUT_EVENT_LEN);
    memcpy(state_input_event, _MAV_PAYLOAD(msg), len);
#endif
}
