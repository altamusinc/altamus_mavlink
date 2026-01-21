#pragma once
// MESSAGE STATION_STATE PACKING

#define MAVLINK_MSG_ID_STATION_STATE 4


typedef struct __mavlink_station_state_t {
 uint32_t untracked_pulses; /*<   number of untracked pulses received */
 uint32_t system_time; /*< [s]  System time in Unix time*/
 uint16_t stored_transactions_count; /*<   number of transactions stored in memory, will be uploaded when internet returns*/
 uint8_t system_state; /*<   Current state of the station */
 uint8_t solenoid_state; /*<   State of the solenoid: 0 closed 1 open*/
 uint8_t detected_badges_count; /*<   number of badges current registered by the RFID reader*/
 uint8_t internet_connectivity; /*<   if the station is connected to the internet, 0 false, 1 true*/
 uint8_t indicator_state; /*<  State of the light tower indicator*/
} mavlink_station_state_t;

#define MAVLINK_MSG_ID_STATION_STATE_LEN 15
#define MAVLINK_MSG_ID_STATION_STATE_MIN_LEN 15
#define MAVLINK_MSG_ID_4_LEN 15
#define MAVLINK_MSG_ID_4_MIN_LEN 15

#define MAVLINK_MSG_ID_STATION_STATE_CRC 176
#define MAVLINK_MSG_ID_4_CRC 176



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_STATION_STATE { \
    4, \
    "STATION_STATE", \
    8, \
    {  { "system_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_station_state_t, system_state) }, \
         { "solenoid_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_station_state_t, solenoid_state) }, \
         { "untracked_pulses", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_station_state_t, untracked_pulses) }, \
         { "system_time", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_station_state_t, system_time) }, \
         { "detected_badges_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_station_state_t, detected_badges_count) }, \
         { "internet_connectivity", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_station_state_t, internet_connectivity) }, \
         { "stored_transactions_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_station_state_t, stored_transactions_count) }, \
         { "indicator_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_station_state_t, indicator_state) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_STATION_STATE { \
    "STATION_STATE", \
    8, \
    {  { "system_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 10, offsetof(mavlink_station_state_t, system_state) }, \
         { "solenoid_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 11, offsetof(mavlink_station_state_t, solenoid_state) }, \
         { "untracked_pulses", NULL, MAVLINK_TYPE_UINT32_T, 0, 0, offsetof(mavlink_station_state_t, untracked_pulses) }, \
         { "system_time", NULL, MAVLINK_TYPE_UINT32_T, 0, 4, offsetof(mavlink_station_state_t, system_time) }, \
         { "detected_badges_count", NULL, MAVLINK_TYPE_UINT8_T, 0, 12, offsetof(mavlink_station_state_t, detected_badges_count) }, \
         { "internet_connectivity", NULL, MAVLINK_TYPE_UINT8_T, 0, 13, offsetof(mavlink_station_state_t, internet_connectivity) }, \
         { "stored_transactions_count", NULL, MAVLINK_TYPE_UINT16_T, 0, 8, offsetof(mavlink_station_state_t, stored_transactions_count) }, \
         { "indicator_state", NULL, MAVLINK_TYPE_UINT8_T, 0, 14, offsetof(mavlink_station_state_t, indicator_state) }, \
         } \
}
#endif

/**
 * @brief Pack a station_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param system_state   Current state of the station 
 * @param solenoid_state   State of the solenoid: 0 closed 1 open
 * @param untracked_pulses   number of untracked pulses received 
 * @param system_time [s]  System time in Unix time
 * @param detected_badges_count   number of badges current registered by the RFID reader
 * @param internet_connectivity   if the station is connected to the internet, 0 false, 1 true
 * @param stored_transactions_count   number of transactions stored in memory, will be uploaded when internet returns
 * @param indicator_state  State of the light tower indicator
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_station_state_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t system_state, uint8_t solenoid_state, uint32_t untracked_pulses, uint32_t system_time, uint8_t detected_badges_count, uint8_t internet_connectivity, uint16_t stored_transactions_count, uint8_t indicator_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_STATE_LEN];
    _mav_put_uint32_t(buf, 0, untracked_pulses);
    _mav_put_uint32_t(buf, 4, system_time);
    _mav_put_uint16_t(buf, 8, stored_transactions_count);
    _mav_put_uint8_t(buf, 10, system_state);
    _mav_put_uint8_t(buf, 11, solenoid_state);
    _mav_put_uint8_t(buf, 12, detected_badges_count);
    _mav_put_uint8_t(buf, 13, internet_connectivity);
    _mav_put_uint8_t(buf, 14, indicator_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATION_STATE_LEN);
#else
    mavlink_station_state_t packet;
    packet.untracked_pulses = untracked_pulses;
    packet.system_time = system_time;
    packet.stored_transactions_count = stored_transactions_count;
    packet.system_state = system_state;
    packet.solenoid_state = solenoid_state;
    packet.detected_badges_count = detected_badges_count;
    packet.internet_connectivity = internet_connectivity;
    packet.indicator_state = indicator_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATION_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATION_STATE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
}

/**
 * @brief Pack a station_state message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param system_state   Current state of the station 
 * @param solenoid_state   State of the solenoid: 0 closed 1 open
 * @param untracked_pulses   number of untracked pulses received 
 * @param system_time [s]  System time in Unix time
 * @param detected_badges_count   number of badges current registered by the RFID reader
 * @param internet_connectivity   if the station is connected to the internet, 0 false, 1 true
 * @param stored_transactions_count   number of transactions stored in memory, will be uploaded when internet returns
 * @param indicator_state  State of the light tower indicator
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_station_state_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint8_t system_state, uint8_t solenoid_state, uint32_t untracked_pulses, uint32_t system_time, uint8_t detected_badges_count, uint8_t internet_connectivity, uint16_t stored_transactions_count, uint8_t indicator_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_STATE_LEN];
    _mav_put_uint32_t(buf, 0, untracked_pulses);
    _mav_put_uint32_t(buf, 4, system_time);
    _mav_put_uint16_t(buf, 8, stored_transactions_count);
    _mav_put_uint8_t(buf, 10, system_state);
    _mav_put_uint8_t(buf, 11, solenoid_state);
    _mav_put_uint8_t(buf, 12, detected_badges_count);
    _mav_put_uint8_t(buf, 13, internet_connectivity);
    _mav_put_uint8_t(buf, 14, indicator_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATION_STATE_LEN);
#else
    mavlink_station_state_t packet;
    packet.untracked_pulses = untracked_pulses;
    packet.system_time = system_time;
    packet.stored_transactions_count = stored_transactions_count;
    packet.system_state = system_state;
    packet.solenoid_state = solenoid_state;
    packet.detected_badges_count = detected_badges_count;
    packet.internet_connectivity = internet_connectivity;
    packet.indicator_state = indicator_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATION_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATION_STATE;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN);
#endif
}

/**
 * @brief Pack a station_state message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param system_state   Current state of the station 
 * @param solenoid_state   State of the solenoid: 0 closed 1 open
 * @param untracked_pulses   number of untracked pulses received 
 * @param system_time [s]  System time in Unix time
 * @param detected_badges_count   number of badges current registered by the RFID reader
 * @param internet_connectivity   if the station is connected to the internet, 0 false, 1 true
 * @param stored_transactions_count   number of transactions stored in memory, will be uploaded when internet returns
 * @param indicator_state  State of the light tower indicator
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_station_state_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t system_state,uint8_t solenoid_state,uint32_t untracked_pulses,uint32_t system_time,uint8_t detected_badges_count,uint8_t internet_connectivity,uint16_t stored_transactions_count,uint8_t indicator_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_STATE_LEN];
    _mav_put_uint32_t(buf, 0, untracked_pulses);
    _mav_put_uint32_t(buf, 4, system_time);
    _mav_put_uint16_t(buf, 8, stored_transactions_count);
    _mav_put_uint8_t(buf, 10, system_state);
    _mav_put_uint8_t(buf, 11, solenoid_state);
    _mav_put_uint8_t(buf, 12, detected_badges_count);
    _mav_put_uint8_t(buf, 13, internet_connectivity);
    _mav_put_uint8_t(buf, 14, indicator_state);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_STATION_STATE_LEN);
#else
    mavlink_station_state_t packet;
    packet.untracked_pulses = untracked_pulses;
    packet.system_time = system_time;
    packet.stored_transactions_count = stored_transactions_count;
    packet.system_state = system_state;
    packet.solenoid_state = solenoid_state;
    packet.detected_badges_count = detected_badges_count;
    packet.internet_connectivity = internet_connectivity;
    packet.indicator_state = indicator_state;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_STATION_STATE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_STATION_STATE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
}

/**
 * @brief Encode a station_state struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param station_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_station_state_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_station_state_t* station_state)
{
    return mavlink_msg_station_state_pack(system_id, component_id, msg, station_state->system_state, station_state->solenoid_state, station_state->untracked_pulses, station_state->system_time, station_state->detected_badges_count, station_state->internet_connectivity, station_state->stored_transactions_count, station_state->indicator_state);
}

/**
 * @brief Encode a station_state struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param station_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_station_state_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_station_state_t* station_state)
{
    return mavlink_msg_station_state_pack_chan(system_id, component_id, chan, msg, station_state->system_state, station_state->solenoid_state, station_state->untracked_pulses, station_state->system_time, station_state->detected_badges_count, station_state->internet_connectivity, station_state->stored_transactions_count, station_state->indicator_state);
}

/**
 * @brief Encode a station_state struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param station_state C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_station_state_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_station_state_t* station_state)
{
    return mavlink_msg_station_state_pack_status(system_id, component_id, _status, msg,  station_state->system_state, station_state->solenoid_state, station_state->untracked_pulses, station_state->system_time, station_state->detected_badges_count, station_state->internet_connectivity, station_state->stored_transactions_count, station_state->indicator_state);
}

/**
 * @brief Send a station_state message
 * @param chan MAVLink channel to send the message
 *
 * @param system_state   Current state of the station 
 * @param solenoid_state   State of the solenoid: 0 closed 1 open
 * @param untracked_pulses   number of untracked pulses received 
 * @param system_time [s]  System time in Unix time
 * @param detected_badges_count   number of badges current registered by the RFID reader
 * @param internet_connectivity   if the station is connected to the internet, 0 false, 1 true
 * @param stored_transactions_count   number of transactions stored in memory, will be uploaded when internet returns
 * @param indicator_state  State of the light tower indicator
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_station_state_send(mavlink_channel_t chan, uint8_t system_state, uint8_t solenoid_state, uint32_t untracked_pulses, uint32_t system_time, uint8_t detected_badges_count, uint8_t internet_connectivity, uint16_t stored_transactions_count, uint8_t indicator_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_STATION_STATE_LEN];
    _mav_put_uint32_t(buf, 0, untracked_pulses);
    _mav_put_uint32_t(buf, 4, system_time);
    _mav_put_uint16_t(buf, 8, stored_transactions_count);
    _mav_put_uint8_t(buf, 10, system_state);
    _mav_put_uint8_t(buf, 11, solenoid_state);
    _mav_put_uint8_t(buf, 12, detected_badges_count);
    _mav_put_uint8_t(buf, 13, internet_connectivity);
    _mav_put_uint8_t(buf, 14, indicator_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_STATE, buf, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
#else
    mavlink_station_state_t packet;
    packet.untracked_pulses = untracked_pulses;
    packet.system_time = system_time;
    packet.stored_transactions_count = stored_transactions_count;
    packet.system_state = system_state;
    packet.solenoid_state = solenoid_state;
    packet.detected_badges_count = detected_badges_count;
    packet.internet_connectivity = internet_connectivity;
    packet.indicator_state = indicator_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_STATE, (const char *)&packet, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
#endif
}

/**
 * @brief Send a station_state message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_station_state_send_struct(mavlink_channel_t chan, const mavlink_station_state_t* station_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_station_state_send(chan, station_state->system_state, station_state->solenoid_state, station_state->untracked_pulses, station_state->system_time, station_state->detected_badges_count, station_state->internet_connectivity, station_state->stored_transactions_count, station_state->indicator_state);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_STATE, (const char *)station_state, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
#endif
}

#if MAVLINK_MSG_ID_STATION_STATE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by reusing
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_station_state_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t system_state, uint8_t solenoid_state, uint32_t untracked_pulses, uint32_t system_time, uint8_t detected_badges_count, uint8_t internet_connectivity, uint16_t stored_transactions_count, uint8_t indicator_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint32_t(buf, 0, untracked_pulses);
    _mav_put_uint32_t(buf, 4, system_time);
    _mav_put_uint16_t(buf, 8, stored_transactions_count);
    _mav_put_uint8_t(buf, 10, system_state);
    _mav_put_uint8_t(buf, 11, solenoid_state);
    _mav_put_uint8_t(buf, 12, detected_badges_count);
    _mav_put_uint8_t(buf, 13, internet_connectivity);
    _mav_put_uint8_t(buf, 14, indicator_state);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_STATE, buf, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
#else
    mavlink_station_state_t *packet = (mavlink_station_state_t *)msgbuf;
    packet->untracked_pulses = untracked_pulses;
    packet->system_time = system_time;
    packet->stored_transactions_count = stored_transactions_count;
    packet->system_state = system_state;
    packet->solenoid_state = solenoid_state;
    packet->detected_badges_count = detected_badges_count;
    packet->internet_connectivity = internet_connectivity;
    packet->indicator_state = indicator_state;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_STATION_STATE, (const char *)packet, MAVLINK_MSG_ID_STATION_STATE_MIN_LEN, MAVLINK_MSG_ID_STATION_STATE_LEN, MAVLINK_MSG_ID_STATION_STATE_CRC);
#endif
}
#endif

#endif

// MESSAGE STATION_STATE UNPACKING


/**
 * @brief Get field system_state from station_state message
 *
 * @return   Current state of the station 
 */
static inline uint8_t mavlink_msg_station_state_get_system_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  10);
}

/**
 * @brief Get field solenoid_state from station_state message
 *
 * @return   State of the solenoid: 0 closed 1 open
 */
static inline uint8_t mavlink_msg_station_state_get_solenoid_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  11);
}

/**
 * @brief Get field untracked_pulses from station_state message
 *
 * @return   number of untracked pulses received 
 */
static inline uint32_t mavlink_msg_station_state_get_untracked_pulses(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  0);
}

/**
 * @brief Get field system_time from station_state message
 *
 * @return [s]  System time in Unix time
 */
static inline uint32_t mavlink_msg_station_state_get_system_time(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  4);
}

/**
 * @brief Get field detected_badges_count from station_state message
 *
 * @return   number of badges current registered by the RFID reader
 */
static inline uint8_t mavlink_msg_station_state_get_detected_badges_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  12);
}

/**
 * @brief Get field internet_connectivity from station_state message
 *
 * @return   if the station is connected to the internet, 0 false, 1 true
 */
static inline uint8_t mavlink_msg_station_state_get_internet_connectivity(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  13);
}

/**
 * @brief Get field stored_transactions_count from station_state message
 *
 * @return   number of transactions stored in memory, will be uploaded when internet returns
 */
static inline uint16_t mavlink_msg_station_state_get_stored_transactions_count(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  8);
}

/**
 * @brief Get field indicator_state from station_state message
 *
 * @return  State of the light tower indicator
 */
static inline uint8_t mavlink_msg_station_state_get_indicator_state(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  14);
}

/**
 * @brief Decode a station_state message into a struct
 *
 * @param msg The message to decode
 * @param station_state C-struct to decode the message contents into
 */
static inline void mavlink_msg_station_state_decode(const mavlink_message_t* msg, mavlink_station_state_t* station_state)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    station_state->untracked_pulses = mavlink_msg_station_state_get_untracked_pulses(msg);
    station_state->system_time = mavlink_msg_station_state_get_system_time(msg);
    station_state->stored_transactions_count = mavlink_msg_station_state_get_stored_transactions_count(msg);
    station_state->system_state = mavlink_msg_station_state_get_system_state(msg);
    station_state->solenoid_state = mavlink_msg_station_state_get_solenoid_state(msg);
    station_state->detected_badges_count = mavlink_msg_station_state_get_detected_badges_count(msg);
    station_state->internet_connectivity = mavlink_msg_station_state_get_internet_connectivity(msg);
    station_state->indicator_state = mavlink_msg_station_state_get_indicator_state(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_STATION_STATE_LEN? msg->len : MAVLINK_MSG_ID_STATION_STATE_LEN;
        memset(station_state, 0, MAVLINK_MSG_ID_STATION_STATE_LEN);
    memcpy(station_state, _MAV_PAYLOAD(msg), len);
#endif
}
