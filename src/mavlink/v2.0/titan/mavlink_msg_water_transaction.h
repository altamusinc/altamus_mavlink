#pragma once
// MESSAGE WATER_TRANSACTION PACKING

#define MAVLINK_MSG_ID_WATER_TRANSACTION 3


typedef struct __mavlink_water_transaction_t {
 uint64_t badge_id_int; /*<   badge ID as int*/
 uint32_t dispensed_ml; /*< [mL]  Number of ML dispensed in currenttransaction*/
 uint32_t limit_ml; /*< [mL]  Limit for this transaction */
 uint32_t start_time_utc; /*< [s]  unix start time of the transaction in seconds*/
 uint32_t stop_time_utc; /*< [s]  unix stop time of the transaction in seconds*/
 uint16_t pulses; /*<   Number of pulses in current transaction*/
 char truck_name[20]; /*<   Truck name associated with badge ID*/
 uint8_t start_reason; /*<   Reason the transaction began */
 uint8_t stop_reason; /*<   Reason the transaction stopped. 0 if transaction still running */
} mavlink_water_transaction_t;

#define MAVLINK_MSG_ID_WATER_TRANSACTION_LEN 48
#define MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN 48
#define MAVLINK_MSG_ID_3_LEN 48
#define MAVLINK_MSG_ID_3_MIN_LEN 48

#define MAVLINK_MSG_ID_WATER_TRANSACTION_CRC 28
#define MAVLINK_MSG_ID_3_CRC 28

#define MAVLINK_MSG_WATER_TRANSACTION_FIELD_TRUCK_NAME_LEN 20

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_WATER_TRANSACTION { \
    3, \
    "WATER_TRANSACTION", \
    9, \
    {  { "badge_id_int", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_water_transaction_t, badge_id_int) }, \
         { "truck_name", NULL, MAVLINK_TYPE_CHAR, 20, 26, offsetof(mavlink_water_transaction_t, truck_name) }, \
         { "pulses", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_water_transaction_t, pulses) }, \
         { "dispensed_ml", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_water_transaction_t, dispensed_ml) }, \
         { "limit_ml", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_water_transaction_t, limit_ml) }, \
         { "start_reason", NULL, MAVLINK_TYPE_UINT8_T, 0, 46, offsetof(mavlink_water_transaction_t, start_reason) }, \
         { "stop_reason", NULL, MAVLINK_TYPE_UINT8_T, 0, 47, offsetof(mavlink_water_transaction_t, stop_reason) }, \
         { "start_time_utc", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_water_transaction_t, start_time_utc) }, \
         { "stop_time_utc", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_water_transaction_t, stop_time_utc) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_WATER_TRANSACTION { \
    "WATER_TRANSACTION", \
    9, \
    {  { "badge_id_int", NULL, MAVLINK_TYPE_UINT64_T, 0, 0, offsetof(mavlink_water_transaction_t, badge_id_int) }, \
         { "truck_name", NULL, MAVLINK_TYPE_CHAR, 20, 26, offsetof(mavlink_water_transaction_t, truck_name) }, \
         { "pulses", NULL, MAVLINK_TYPE_UINT16_T, 0, 24, offsetof(mavlink_water_transaction_t, pulses) }, \
         { "dispensed_ml", NULL, MAVLINK_TYPE_UINT32_T, 0, 8, offsetof(mavlink_water_transaction_t, dispensed_ml) }, \
         { "limit_ml", NULL, MAVLINK_TYPE_UINT32_T, 0, 12, offsetof(mavlink_water_transaction_t, limit_ml) }, \
         { "start_reason", NULL, MAVLINK_TYPE_UINT8_T, 0, 46, offsetof(mavlink_water_transaction_t, start_reason) }, \
         { "stop_reason", NULL, MAVLINK_TYPE_UINT8_T, 0, 47, offsetof(mavlink_water_transaction_t, stop_reason) }, \
         { "start_time_utc", NULL, MAVLINK_TYPE_UINT32_T, 0, 16, offsetof(mavlink_water_transaction_t, start_time_utc) }, \
         { "stop_time_utc", NULL, MAVLINK_TYPE_UINT32_T, 0, 20, offsetof(mavlink_water_transaction_t, stop_time_utc) }, \
         } \
}
#endif

/**
 * @brief Pack a water_transaction message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param pulses   Number of pulses in current transaction
 * @param dispensed_ml [mL]  Number of ML dispensed in currenttransaction
 * @param limit_ml [mL]  Limit for this transaction 
 * @param start_reason   Reason the transaction began 
 * @param stop_reason   Reason the transaction stopped. 0 if transaction still running 
 * @param start_time_utc [s]  unix start time of the transaction in seconds
 * @param stop_time_utc [s]  unix stop time of the transaction in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_water_transaction_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint64_t badge_id_int, const char *truck_name, uint16_t pulses, uint32_t dispensed_ml, uint32_t limit_ml, uint8_t start_reason, uint8_t stop_reason, uint32_t start_time_utc, uint32_t stop_time_utc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WATER_TRANSACTION_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, dispensed_ml);
    _mav_put_uint32_t(buf, 12, limit_ml);
    _mav_put_uint32_t(buf, 16, start_time_utc);
    _mav_put_uint32_t(buf, 20, stop_time_utc);
    _mav_put_uint16_t(buf, 24, pulses);
    _mav_put_uint8_t(buf, 46, start_reason);
    _mav_put_uint8_t(buf, 47, stop_reason);
    _mav_put_char_array(buf, 26, truck_name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
#else
    mavlink_water_transaction_t packet;
    packet.badge_id_int = badge_id_int;
    packet.dispensed_ml = dispensed_ml;
    packet.limit_ml = limit_ml;
    packet.start_time_utc = start_time_utc;
    packet.stop_time_utc = stop_time_utc;
    packet.pulses = pulses;
    packet.start_reason = start_reason;
    packet.stop_reason = stop_reason;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WATER_TRANSACTION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
}

/**
 * @brief Pack a water_transaction message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param pulses   Number of pulses in current transaction
 * @param dispensed_ml [mL]  Number of ML dispensed in currenttransaction
 * @param limit_ml [mL]  Limit for this transaction 
 * @param start_reason   Reason the transaction began 
 * @param stop_reason   Reason the transaction stopped. 0 if transaction still running 
 * @param start_time_utc [s]  unix start time of the transaction in seconds
 * @param stop_time_utc [s]  unix stop time of the transaction in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_water_transaction_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               uint64_t badge_id_int, const char *truck_name, uint16_t pulses, uint32_t dispensed_ml, uint32_t limit_ml, uint8_t start_reason, uint8_t stop_reason, uint32_t start_time_utc, uint32_t stop_time_utc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WATER_TRANSACTION_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, dispensed_ml);
    _mav_put_uint32_t(buf, 12, limit_ml);
    _mav_put_uint32_t(buf, 16, start_time_utc);
    _mav_put_uint32_t(buf, 20, stop_time_utc);
    _mav_put_uint16_t(buf, 24, pulses);
    _mav_put_uint8_t(buf, 46, start_reason);
    _mav_put_uint8_t(buf, 47, stop_reason);
    _mav_put_char_array(buf, 26, truck_name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
#else
    mavlink_water_transaction_t packet;
    packet.badge_id_int = badge_id_int;
    packet.dispensed_ml = dispensed_ml;
    packet.limit_ml = limit_ml;
    packet.start_time_utc = start_time_utc;
    packet.stop_time_utc = stop_time_utc;
    packet.pulses = pulses;
    packet.start_reason = start_reason;
    packet.stop_reason = stop_reason;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WATER_TRANSACTION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
#endif
}

/**
 * @brief Pack a water_transaction message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param pulses   Number of pulses in current transaction
 * @param dispensed_ml [mL]  Number of ML dispensed in currenttransaction
 * @param limit_ml [mL]  Limit for this transaction 
 * @param start_reason   Reason the transaction began 
 * @param stop_reason   Reason the transaction stopped. 0 if transaction still running 
 * @param start_time_utc [s]  unix start time of the transaction in seconds
 * @param stop_time_utc [s]  unix stop time of the transaction in seconds
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_water_transaction_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint64_t badge_id_int,const char *truck_name,uint16_t pulses,uint32_t dispensed_ml,uint32_t limit_ml,uint8_t start_reason,uint8_t stop_reason,uint32_t start_time_utc,uint32_t stop_time_utc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WATER_TRANSACTION_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, dispensed_ml);
    _mav_put_uint32_t(buf, 12, limit_ml);
    _mav_put_uint32_t(buf, 16, start_time_utc);
    _mav_put_uint32_t(buf, 20, stop_time_utc);
    _mav_put_uint16_t(buf, 24, pulses);
    _mav_put_uint8_t(buf, 46, start_reason);
    _mav_put_uint8_t(buf, 47, stop_reason);
    _mav_put_char_array(buf, 26, truck_name, 20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
#else
    mavlink_water_transaction_t packet;
    packet.badge_id_int = badge_id_int;
    packet.dispensed_ml = dispensed_ml;
    packet.limit_ml = limit_ml;
    packet.start_time_utc = start_time_utc;
    packet.stop_time_utc = stop_time_utc;
    packet.pulses = pulses;
    packet.start_reason = start_reason;
    packet.stop_reason = stop_reason;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_WATER_TRANSACTION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
}

/**
 * @brief Encode a water_transaction struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param water_transaction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_water_transaction_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_water_transaction_t* water_transaction)
{
    return mavlink_msg_water_transaction_pack(system_id, component_id, msg, water_transaction->badge_id_int, water_transaction->truck_name, water_transaction->pulses, water_transaction->dispensed_ml, water_transaction->limit_ml, water_transaction->start_reason, water_transaction->stop_reason, water_transaction->start_time_utc, water_transaction->stop_time_utc);
}

/**
 * @brief Encode a water_transaction struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param water_transaction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_water_transaction_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_water_transaction_t* water_transaction)
{
    return mavlink_msg_water_transaction_pack_chan(system_id, component_id, chan, msg, water_transaction->badge_id_int, water_transaction->truck_name, water_transaction->pulses, water_transaction->dispensed_ml, water_transaction->limit_ml, water_transaction->start_reason, water_transaction->stop_reason, water_transaction->start_time_utc, water_transaction->stop_time_utc);
}

/**
 * @brief Encode a water_transaction struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param water_transaction C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_water_transaction_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_water_transaction_t* water_transaction)
{
    return mavlink_msg_water_transaction_pack_status(system_id, component_id, _status, msg,  water_transaction->badge_id_int, water_transaction->truck_name, water_transaction->pulses, water_transaction->dispensed_ml, water_transaction->limit_ml, water_transaction->start_reason, water_transaction->stop_reason, water_transaction->start_time_utc, water_transaction->stop_time_utc);
}

/**
 * @brief Send a water_transaction message
 * @param chan MAVLink channel to send the message
 *
 * @param badge_id_int   badge ID as int
 * @param truck_name   Truck name associated with badge ID
 * @param pulses   Number of pulses in current transaction
 * @param dispensed_ml [mL]  Number of ML dispensed in currenttransaction
 * @param limit_ml [mL]  Limit for this transaction 
 * @param start_reason   Reason the transaction began 
 * @param stop_reason   Reason the transaction stopped. 0 if transaction still running 
 * @param start_time_utc [s]  unix start time of the transaction in seconds
 * @param stop_time_utc [s]  unix stop time of the transaction in seconds
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_water_transaction_send(mavlink_channel_t chan, uint64_t badge_id_int, const char *truck_name, uint16_t pulses, uint32_t dispensed_ml, uint32_t limit_ml, uint8_t start_reason, uint8_t stop_reason, uint32_t start_time_utc, uint32_t stop_time_utc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_WATER_TRANSACTION_LEN];
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, dispensed_ml);
    _mav_put_uint32_t(buf, 12, limit_ml);
    _mav_put_uint32_t(buf, 16, start_time_utc);
    _mav_put_uint32_t(buf, 20, stop_time_utc);
    _mav_put_uint16_t(buf, 24, pulses);
    _mav_put_uint8_t(buf, 46, start_reason);
    _mav_put_uint8_t(buf, 47, stop_reason);
    _mav_put_char_array(buf, 26, truck_name, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WATER_TRANSACTION, buf, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
#else
    mavlink_water_transaction_t packet;
    packet.badge_id_int = badge_id_int;
    packet.dispensed_ml = dispensed_ml;
    packet.limit_ml = limit_ml;
    packet.start_time_utc = start_time_utc;
    packet.stop_time_utc = stop_time_utc;
    packet.pulses = pulses;
    packet.start_reason = start_reason;
    packet.stop_reason = stop_reason;
    mav_array_memcpy(packet.truck_name, truck_name, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WATER_TRANSACTION, (const char *)&packet, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
#endif
}

/**
 * @brief Send a water_transaction message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_water_transaction_send_struct(mavlink_channel_t chan, const mavlink_water_transaction_t* water_transaction)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_water_transaction_send(chan, water_transaction->badge_id_int, water_transaction->truck_name, water_transaction->pulses, water_transaction->dispensed_ml, water_transaction->limit_ml, water_transaction->start_reason, water_transaction->stop_reason, water_transaction->start_time_utc, water_transaction->stop_time_utc);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WATER_TRANSACTION, (const char *)water_transaction, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
#endif
}

#if MAVLINK_MSG_ID_WATER_TRANSACTION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_water_transaction_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint64_t badge_id_int, const char *truck_name, uint16_t pulses, uint32_t dispensed_ml, uint32_t limit_ml, uint8_t start_reason, uint8_t stop_reason, uint32_t start_time_utc, uint32_t stop_time_utc)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint64_t(buf, 0, badge_id_int);
    _mav_put_uint32_t(buf, 8, dispensed_ml);
    _mav_put_uint32_t(buf, 12, limit_ml);
    _mav_put_uint32_t(buf, 16, start_time_utc);
    _mav_put_uint32_t(buf, 20, stop_time_utc);
    _mav_put_uint16_t(buf, 24, pulses);
    _mav_put_uint8_t(buf, 46, start_reason);
    _mav_put_uint8_t(buf, 47, stop_reason);
    _mav_put_char_array(buf, 26, truck_name, 20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WATER_TRANSACTION, buf, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
#else
    mavlink_water_transaction_t *packet = (mavlink_water_transaction_t *)msgbuf;
    packet->badge_id_int = badge_id_int;
    packet->dispensed_ml = dispensed_ml;
    packet->limit_ml = limit_ml;
    packet->start_time_utc = start_time_utc;
    packet->stop_time_utc = stop_time_utc;
    packet->pulses = pulses;
    packet->start_reason = start_reason;
    packet->stop_reason = stop_reason;
    mav_array_memcpy(packet->truck_name, truck_name, sizeof(char)*20);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_WATER_TRANSACTION, (const char *)packet, MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN, MAVLINK_MSG_ID_WATER_TRANSACTION_CRC);
#endif
}
#endif

#endif

// MESSAGE WATER_TRANSACTION UNPACKING


/**
 * @brief Get field badge_id_int from water_transaction message
 *
 * @return   badge ID as int
 */
static inline uint64_t mavlink_msg_water_transaction_get_badge_id_int(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint64_t(msg,  0);
}

/**
 * @brief Get field truck_name from water_transaction message
 *
 * @return   Truck name associated with badge ID
 */
static inline uint16_t mavlink_msg_water_transaction_get_truck_name(const mavlink_message_t* msg, char *truck_name)
{
    return _MAV_RETURN_char_array(msg, truck_name, 20,  26);
}

/**
 * @brief Get field pulses from water_transaction message
 *
 * @return   Number of pulses in current transaction
 */
static inline uint16_t mavlink_msg_water_transaction_get_pulses(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint16_t(msg,  24);
}

/**
 * @brief Get field dispensed_ml from water_transaction message
 *
 * @return [mL]  Number of ML dispensed in currenttransaction
 */
static inline uint32_t mavlink_msg_water_transaction_get_dispensed_ml(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  8);
}

/**
 * @brief Get field limit_ml from water_transaction message
 *
 * @return [mL]  Limit for this transaction 
 */
static inline uint32_t mavlink_msg_water_transaction_get_limit_ml(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  12);
}

/**
 * @brief Get field start_reason from water_transaction message
 *
 * @return   Reason the transaction began 
 */
static inline uint8_t mavlink_msg_water_transaction_get_start_reason(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  46);
}

/**
 * @brief Get field stop_reason from water_transaction message
 *
 * @return   Reason the transaction stopped. 0 if transaction still running 
 */
static inline uint8_t mavlink_msg_water_transaction_get_stop_reason(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  47);
}

/**
 * @brief Get field start_time_utc from water_transaction message
 *
 * @return [s]  unix start time of the transaction in seconds
 */
static inline uint32_t mavlink_msg_water_transaction_get_start_time_utc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  16);
}

/**
 * @brief Get field stop_time_utc from water_transaction message
 *
 * @return [s]  unix stop time of the transaction in seconds
 */
static inline uint32_t mavlink_msg_water_transaction_get_stop_time_utc(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint32_t(msg,  20);
}

/**
 * @brief Decode a water_transaction message into a struct
 *
 * @param msg The message to decode
 * @param water_transaction C-struct to decode the message contents into
 */
static inline void mavlink_msg_water_transaction_decode(const mavlink_message_t* msg, mavlink_water_transaction_t* water_transaction)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    water_transaction->badge_id_int = mavlink_msg_water_transaction_get_badge_id_int(msg);
    water_transaction->dispensed_ml = mavlink_msg_water_transaction_get_dispensed_ml(msg);
    water_transaction->limit_ml = mavlink_msg_water_transaction_get_limit_ml(msg);
    water_transaction->start_time_utc = mavlink_msg_water_transaction_get_start_time_utc(msg);
    water_transaction->stop_time_utc = mavlink_msg_water_transaction_get_stop_time_utc(msg);
    water_transaction->pulses = mavlink_msg_water_transaction_get_pulses(msg);
    mavlink_msg_water_transaction_get_truck_name(msg, water_transaction->truck_name);
    water_transaction->start_reason = mavlink_msg_water_transaction_get_start_reason(msg);
    water_transaction->stop_reason = mavlink_msg_water_transaction_get_stop_reason(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_WATER_TRANSACTION_LEN? msg->len : MAVLINK_MSG_ID_WATER_TRANSACTION_LEN;
        memset(water_transaction, 0, MAVLINK_MSG_ID_WATER_TRANSACTION_LEN);
    memcpy(water_transaction, _MAV_PAYLOAD(msg), len);
#endif
}
