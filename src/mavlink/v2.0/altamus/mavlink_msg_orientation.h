#pragma once
// MESSAGE ORIENTATION PACKING

#define MAVLINK_MSG_ID_ORIENTATION 18


typedef struct __mavlink_orientation_t {
 float roll; /*< [rad] Roll angle (-pi..+pi). Comes from Accelerometer*/
 float pitch; /*< [rad] Pitch angle (-pi..+pi). Comes from Accelerometer*/
 float temp; /*< [degreesC] Temperature. Comes from Accelerometer*/
 float heading; /*< [rad] heading angle (-pi..+pi). Comes from Compass*/
 int32_t lat; /*< [degE7] Latitude (WGS84, EGM96 ellipsoid)*/
 int32_t lon; /*< [degE7] Longitude (WGS84, EGM96 ellipsoid)*/
 int32_t alt; /*< [mm] Altitude (MSL). Positive for up.*/
 int16_t xmag; /*< [mgauss] X magnetic field strength. Comes from compass */
 int16_t ymag; /*< [mgauss] Y magnetic field strength. Comes from compass */
 int16_t zmag; /*< [mgauss] Z magnetic field strength. Comes from compass */
} mavlink_orientation_t;

#define MAVLINK_MSG_ID_ORIENTATION_LEN 34
#define MAVLINK_MSG_ID_ORIENTATION_MIN_LEN 34
#define MAVLINK_MSG_ID_18_LEN 34
#define MAVLINK_MSG_ID_18_MIN_LEN 34

#define MAVLINK_MSG_ID_ORIENTATION_CRC 78
#define MAVLINK_MSG_ID_18_CRC 78



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_ORIENTATION { \
    18, \
    "ORIENTATION", \
    10, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_orientation_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_orientation_t, pitch) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_orientation_t, temp) }, \
         { "xmag", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_orientation_t, xmag) }, \
         { "ymag", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_orientation_t, ymag) }, \
         { "zmag", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_orientation_t, zmag) }, \
         { "heading", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_orientation_t, heading) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_orientation_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_orientation_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_orientation_t, alt) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_ORIENTATION { \
    "ORIENTATION", \
    10, \
    {  { "roll", NULL, MAVLINK_TYPE_FLOAT, 0, 0, offsetof(mavlink_orientation_t, roll) }, \
         { "pitch", NULL, MAVLINK_TYPE_FLOAT, 0, 4, offsetof(mavlink_orientation_t, pitch) }, \
         { "temp", NULL, MAVLINK_TYPE_FLOAT, 0, 8, offsetof(mavlink_orientation_t, temp) }, \
         { "xmag", NULL, MAVLINK_TYPE_INT16_T, 0, 28, offsetof(mavlink_orientation_t, xmag) }, \
         { "ymag", NULL, MAVLINK_TYPE_INT16_T, 0, 30, offsetof(mavlink_orientation_t, ymag) }, \
         { "zmag", NULL, MAVLINK_TYPE_INT16_T, 0, 32, offsetof(mavlink_orientation_t, zmag) }, \
         { "heading", NULL, MAVLINK_TYPE_FLOAT, 0, 12, offsetof(mavlink_orientation_t, heading) }, \
         { "lat", NULL, MAVLINK_TYPE_INT32_T, 0, 16, offsetof(mavlink_orientation_t, lat) }, \
         { "lon", NULL, MAVLINK_TYPE_INT32_T, 0, 20, offsetof(mavlink_orientation_t, lon) }, \
         { "alt", NULL, MAVLINK_TYPE_INT32_T, 0, 24, offsetof(mavlink_orientation_t, alt) }, \
         } \
}
#endif

/**
 * @brief Pack a orientation message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll [rad] Roll angle (-pi..+pi). Comes from Accelerometer
 * @param pitch [rad] Pitch angle (-pi..+pi). Comes from Accelerometer
 * @param temp [degreesC] Temperature. Comes from Accelerometer
 * @param xmag [mgauss] X magnetic field strength. Comes from compass 
 * @param ymag [mgauss] Y magnetic field strength. Comes from compass 
 * @param zmag [mgauss] Z magnetic field strength. Comes from compass 
 * @param heading [rad] heading angle (-pi..+pi). Comes from Compass
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param alt [mm] Altitude (MSL). Positive for up.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orientation_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               float roll, float pitch, float temp, int16_t xmag, int16_t ymag, int16_t zmag, float heading, int32_t lat, int32_t lon, int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ORIENTATION_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, temp);
    _mav_put_float(buf, 12, heading);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_int16_t(buf, 28, xmag);
    _mav_put_int16_t(buf, 30, ymag);
    _mav_put_int16_t(buf, 32, zmag);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ORIENTATION_LEN);
#else
    mavlink_orientation_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.temp = temp;
    packet.heading = heading;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ORIENTATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ORIENTATION;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
}

/**
 * @brief Pack a orientation message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 *
 * @param roll [rad] Roll angle (-pi..+pi). Comes from Accelerometer
 * @param pitch [rad] Pitch angle (-pi..+pi). Comes from Accelerometer
 * @param temp [degreesC] Temperature. Comes from Accelerometer
 * @param xmag [mgauss] X magnetic field strength. Comes from compass 
 * @param ymag [mgauss] Y magnetic field strength. Comes from compass 
 * @param zmag [mgauss] Z magnetic field strength. Comes from compass 
 * @param heading [rad] heading angle (-pi..+pi). Comes from Compass
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param alt [mm] Altitude (MSL). Positive for up.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orientation_pack_status(uint8_t system_id, uint8_t component_id, mavlink_status_t *_status, mavlink_message_t* msg,
                               float roll, float pitch, float temp, int16_t xmag, int16_t ymag, int16_t zmag, float heading, int32_t lat, int32_t lon, int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ORIENTATION_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, temp);
    _mav_put_float(buf, 12, heading);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_int16_t(buf, 28, xmag);
    _mav_put_int16_t(buf, 30, ymag);
    _mav_put_int16_t(buf, 32, zmag);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ORIENTATION_LEN);
#else
    mavlink_orientation_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.temp = temp;
    packet.heading = heading;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ORIENTATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ORIENTATION;
#if MAVLINK_CRC_EXTRA
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
#else
    return mavlink_finalize_message_buffer(msg, system_id, component_id, _status, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN);
#endif
}

/**
 * @brief Pack a orientation message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param roll [rad] Roll angle (-pi..+pi). Comes from Accelerometer
 * @param pitch [rad] Pitch angle (-pi..+pi). Comes from Accelerometer
 * @param temp [degreesC] Temperature. Comes from Accelerometer
 * @param xmag [mgauss] X magnetic field strength. Comes from compass 
 * @param ymag [mgauss] Y magnetic field strength. Comes from compass 
 * @param zmag [mgauss] Z magnetic field strength. Comes from compass 
 * @param heading [rad] heading angle (-pi..+pi). Comes from Compass
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param alt [mm] Altitude (MSL). Positive for up.
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_orientation_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   float roll,float pitch,float temp,int16_t xmag,int16_t ymag,int16_t zmag,float heading,int32_t lat,int32_t lon,int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ORIENTATION_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, temp);
    _mav_put_float(buf, 12, heading);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_int16_t(buf, 28, xmag);
    _mav_put_int16_t(buf, 30, ymag);
    _mav_put_int16_t(buf, 32, zmag);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_ORIENTATION_LEN);
#else
    mavlink_orientation_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.temp = temp;
    packet.heading = heading;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_ORIENTATION_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_ORIENTATION;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
}

/**
 * @brief Encode a orientation struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param orientation C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orientation_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_orientation_t* orientation)
{
    return mavlink_msg_orientation_pack(system_id, component_id, msg, orientation->roll, orientation->pitch, orientation->temp, orientation->xmag, orientation->ymag, orientation->zmag, orientation->heading, orientation->lat, orientation->lon, orientation->alt);
}

/**
 * @brief Encode a orientation struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param orientation C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orientation_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_orientation_t* orientation)
{
    return mavlink_msg_orientation_pack_chan(system_id, component_id, chan, msg, orientation->roll, orientation->pitch, orientation->temp, orientation->xmag, orientation->ymag, orientation->zmag, orientation->heading, orientation->lat, orientation->lon, orientation->alt);
}

/**
 * @brief Encode a orientation struct with provided status structure
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param status MAVLink status structure
 * @param msg The MAVLink message to compress the data into
 * @param orientation C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_orientation_encode_status(uint8_t system_id, uint8_t component_id, mavlink_status_t* _status, mavlink_message_t* msg, const mavlink_orientation_t* orientation)
{
    return mavlink_msg_orientation_pack_status(system_id, component_id, _status, msg,  orientation->roll, orientation->pitch, orientation->temp, orientation->xmag, orientation->ymag, orientation->zmag, orientation->heading, orientation->lat, orientation->lon, orientation->alt);
}

/**
 * @brief Send a orientation message
 * @param chan MAVLink channel to send the message
 *
 * @param roll [rad] Roll angle (-pi..+pi). Comes from Accelerometer
 * @param pitch [rad] Pitch angle (-pi..+pi). Comes from Accelerometer
 * @param temp [degreesC] Temperature. Comes from Accelerometer
 * @param xmag [mgauss] X magnetic field strength. Comes from compass 
 * @param ymag [mgauss] Y magnetic field strength. Comes from compass 
 * @param zmag [mgauss] Z magnetic field strength. Comes from compass 
 * @param heading [rad] heading angle (-pi..+pi). Comes from Compass
 * @param lat [degE7] Latitude (WGS84, EGM96 ellipsoid)
 * @param lon [degE7] Longitude (WGS84, EGM96 ellipsoid)
 * @param alt [mm] Altitude (MSL). Positive for up.
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_orientation_send(mavlink_channel_t chan, float roll, float pitch, float temp, int16_t xmag, int16_t ymag, int16_t zmag, float heading, int32_t lat, int32_t lon, int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_ORIENTATION_LEN];
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, temp);
    _mav_put_float(buf, 12, heading);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_int16_t(buf, 28, xmag);
    _mav_put_int16_t(buf, 30, ymag);
    _mav_put_int16_t(buf, 32, zmag);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORIENTATION, buf, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
#else
    mavlink_orientation_t packet;
    packet.roll = roll;
    packet.pitch = pitch;
    packet.temp = temp;
    packet.heading = heading;
    packet.lat = lat;
    packet.lon = lon;
    packet.alt = alt;
    packet.xmag = xmag;
    packet.ymag = ymag;
    packet.zmag = zmag;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORIENTATION, (const char *)&packet, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
#endif
}

/**
 * @brief Send a orientation message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_orientation_send_struct(mavlink_channel_t chan, const mavlink_orientation_t* orientation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_orientation_send(chan, orientation->roll, orientation->pitch, orientation->temp, orientation->xmag, orientation->ymag, orientation->zmag, orientation->heading, orientation->lat, orientation->lon, orientation->alt);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORIENTATION, (const char *)orientation, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
#endif
}

#if MAVLINK_MSG_ID_ORIENTATION_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_orientation_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  float roll, float pitch, float temp, int16_t xmag, int16_t ymag, int16_t zmag, float heading, int32_t lat, int32_t lon, int32_t alt)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_float(buf, 0, roll);
    _mav_put_float(buf, 4, pitch);
    _mav_put_float(buf, 8, temp);
    _mav_put_float(buf, 12, heading);
    _mav_put_int32_t(buf, 16, lat);
    _mav_put_int32_t(buf, 20, lon);
    _mav_put_int32_t(buf, 24, alt);
    _mav_put_int16_t(buf, 28, xmag);
    _mav_put_int16_t(buf, 30, ymag);
    _mav_put_int16_t(buf, 32, zmag);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORIENTATION, buf, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
#else
    mavlink_orientation_t *packet = (mavlink_orientation_t *)msgbuf;
    packet->roll = roll;
    packet->pitch = pitch;
    packet->temp = temp;
    packet->heading = heading;
    packet->lat = lat;
    packet->lon = lon;
    packet->alt = alt;
    packet->xmag = xmag;
    packet->ymag = ymag;
    packet->zmag = zmag;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_ORIENTATION, (const char *)packet, MAVLINK_MSG_ID_ORIENTATION_MIN_LEN, MAVLINK_MSG_ID_ORIENTATION_LEN, MAVLINK_MSG_ID_ORIENTATION_CRC);
#endif
}
#endif

#endif

// MESSAGE ORIENTATION UNPACKING


/**
 * @brief Get field roll from orientation message
 *
 * @return [rad] Roll angle (-pi..+pi). Comes from Accelerometer
 */
static inline float mavlink_msg_orientation_get_roll(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  0);
}

/**
 * @brief Get field pitch from orientation message
 *
 * @return [rad] Pitch angle (-pi..+pi). Comes from Accelerometer
 */
static inline float mavlink_msg_orientation_get_pitch(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  4);
}

/**
 * @brief Get field temp from orientation message
 *
 * @return [degreesC] Temperature. Comes from Accelerometer
 */
static inline float mavlink_msg_orientation_get_temp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  8);
}

/**
 * @brief Get field xmag from orientation message
 *
 * @return [mgauss] X magnetic field strength. Comes from compass 
 */
static inline int16_t mavlink_msg_orientation_get_xmag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  28);
}

/**
 * @brief Get field ymag from orientation message
 *
 * @return [mgauss] Y magnetic field strength. Comes from compass 
 */
static inline int16_t mavlink_msg_orientation_get_ymag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  30);
}

/**
 * @brief Get field zmag from orientation message
 *
 * @return [mgauss] Z magnetic field strength. Comes from compass 
 */
static inline int16_t mavlink_msg_orientation_get_zmag(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int16_t(msg,  32);
}

/**
 * @brief Get field heading from orientation message
 *
 * @return [rad] heading angle (-pi..+pi). Comes from Compass
 */
static inline float mavlink_msg_orientation_get_heading(const mavlink_message_t* msg)
{
    return _MAV_RETURN_float(msg,  12);
}

/**
 * @brief Get field lat from orientation message
 *
 * @return [degE7] Latitude (WGS84, EGM96 ellipsoid)
 */
static inline int32_t mavlink_msg_orientation_get_lat(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  16);
}

/**
 * @brief Get field lon from orientation message
 *
 * @return [degE7] Longitude (WGS84, EGM96 ellipsoid)
 */
static inline int32_t mavlink_msg_orientation_get_lon(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  20);
}

/**
 * @brief Get field alt from orientation message
 *
 * @return [mm] Altitude (MSL). Positive for up.
 */
static inline int32_t mavlink_msg_orientation_get_alt(const mavlink_message_t* msg)
{
    return _MAV_RETURN_int32_t(msg,  24);
}

/**
 * @brief Decode a orientation message into a struct
 *
 * @param msg The message to decode
 * @param orientation C-struct to decode the message contents into
 */
static inline void mavlink_msg_orientation_decode(const mavlink_message_t* msg, mavlink_orientation_t* orientation)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    orientation->roll = mavlink_msg_orientation_get_roll(msg);
    orientation->pitch = mavlink_msg_orientation_get_pitch(msg);
    orientation->temp = mavlink_msg_orientation_get_temp(msg);
    orientation->heading = mavlink_msg_orientation_get_heading(msg);
    orientation->lat = mavlink_msg_orientation_get_lat(msg);
    orientation->lon = mavlink_msg_orientation_get_lon(msg);
    orientation->alt = mavlink_msg_orientation_get_alt(msg);
    orientation->xmag = mavlink_msg_orientation_get_xmag(msg);
    orientation->ymag = mavlink_msg_orientation_get_ymag(msg);
    orientation->zmag = mavlink_msg_orientation_get_zmag(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_ORIENTATION_LEN? msg->len : MAVLINK_MSG_ID_ORIENTATION_LEN;
        memset(orientation, 0, MAVLINK_MSG_ID_ORIENTATION_LEN);
    memcpy(orientation, _MAV_PAYLOAD(msg), len);
#endif
}
