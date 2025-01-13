/** @file
 *    @brief MAVLink comm protocol testsuite generated from altamus.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef ALTAMUS_TESTSUITE_H
#define ALTAMUS_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common_minimal(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_altamus(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common_minimal(system_id, component_id, last_msg);
    mavlink_test_altamus(system_id, component_id, last_msg);
}
#endif

#include "../common_minimal/testsuite.h"


static void mavlink_test_lidar_reading(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LIDAR_READING >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_lidar_reading_t packet_in = {
        { 93372036854775807, 93372036854775808, 93372036854775809, 93372036854775810, 93372036854775811, 93372036854775812, 93372036854775813, 93372036854775814, 93372036854775815, 93372036854775816, 93372036854775817, 93372036854775818, 93372036854775819, 93372036854775820, 93372036854775821, 93372036854775822, 93372036854775823, 93372036854775824, 93372036854775825, 93372036854775826, 93372036854775827, 93372036854775828, 93372036854775829, 93372036854775830, 93372036854775831, 93372036854775832, 93372036854775833, 93372036854775834, 93372036854775835, 93372036854775836, 93372036854775837 }
    };
    mavlink_lidar_reading_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.readings, packet_in.readings, sizeof(uint64_t)*31);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LIDAR_READING_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_reading_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_lidar_reading_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_reading_pack(system_id, component_id, &msg , packet1.readings );
    mavlink_msg_lidar_reading_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_reading_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.readings );
    mavlink_msg_lidar_reading_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_lidar_reading_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_reading_send(MAVLINK_COMM_1 , packet1.readings );
    mavlink_msg_lidar_reading_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LIDAR_READING") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LIDAR_READING) != NULL);
#endif
}

static void mavlink_test_component_power_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_component_power_control_t packet_in = {
        17235,139
    };
    mavlink_component_power_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.device = packet_in.device;
        packet1.behavior = packet_in.behavior;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_power_control_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_component_power_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_power_control_pack(system_id, component_id, &msg , packet1.device , packet1.behavior );
    mavlink_msg_component_power_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_power_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.device , packet1.behavior );
    mavlink_msg_component_power_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_component_power_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_power_control_send(MAVLINK_COMM_1 , packet1.device , packet1.behavior );
    mavlink_msg_component_power_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMPONENT_POWER_CONTROL") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMPONENT_POWER_CONTROL) != NULL);
#endif
}

static void mavlink_test_system_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SYSTEM_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_system_status_t packet_in = {
        17235,17339,17443,151
    };
    mavlink_system_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.power_status_bitmask = packet_in.power_status_bitmask;
        packet1.health_status_bitmask = packet_in.health_status_bitmask;
        packet1.uptime = packet_in.uptime;
        packet1.state = packet_in.state;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SYSTEM_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_system_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_status_pack(system_id, component_id, &msg , packet1.state , packet1.power_status_bitmask , packet1.health_status_bitmask , packet1.uptime );
    mavlink_msg_system_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.state , packet1.power_status_bitmask , packet1.health_status_bitmask , packet1.uptime );
    mavlink_msg_system_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_system_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_system_status_send(MAVLINK_COMM_1 , packet1.state , packet1.power_status_bitmask , packet1.health_status_bitmask , packet1.uptime );
    mavlink_msg_system_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SYSTEM_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SYSTEM_STATUS) != NULL);
#endif
}

static void mavlink_test_identifier(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_IDENTIFIER >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_identifier_t packet_in = {
        "ABCDEFGHIJKLMNOPQRSTUVW",{ 77, 78, 79, 80 },{ 89, 90, 91, 92, 93, 94 },"IJKLMNOPQRSTUVWXYZA","CDEFGHIJKLMNOPQRSTUVWXYZABCDE","GHIJKLMNOPQRSTUVWXYZABCDEFGHI"
    };
    mavlink_identifier_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        
        mav_array_memcpy(packet1.particle_id, packet_in.particle_id, sizeof(char)*24);
        mav_array_memcpy(packet1.local_ip, packet_in.local_ip, sizeof(uint8_t)*4);
        mav_array_memcpy(packet1.mac, packet_in.mac, sizeof(uint8_t)*6);
        mav_array_memcpy(packet1.name, packet_in.name, sizeof(char)*20);
        mav_array_memcpy(packet1.site_friendly_name, packet_in.site_friendly_name, sizeof(char)*30);
        mav_array_memcpy(packet1.site_name, packet_in.site_name, sizeof(char)*30);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_IDENTIFIER_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_identifier_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_identifier_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_identifier_pack(system_id, component_id, &msg , packet1.particle_id , packet1.local_ip , packet1.mac , packet1.name , packet1.site_friendly_name , packet1.site_name );
    mavlink_msg_identifier_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_identifier_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.particle_id , packet1.local_ip , packet1.mac , packet1.name , packet1.site_friendly_name , packet1.site_name );
    mavlink_msg_identifier_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_identifier_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_identifier_send(MAVLINK_COMM_1 , packet1.particle_id , packet1.local_ip , packet1.mac , packet1.name , packet1.site_friendly_name , packet1.site_name );
    mavlink_msg_identifier_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("IDENTIFIER") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_IDENTIFIER) != NULL);
#endif
}

static void mavlink_test_component_health_test(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_component_health_test_t packet_in = {
        963497464
    };
    mavlink_component_health_test_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.component = packet_in.component;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_health_test_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_component_health_test_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_health_test_pack(system_id, component_id, &msg , packet1.component );
    mavlink_msg_component_health_test_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_health_test_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.component );
    mavlink_msg_component_health_test_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_component_health_test_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_component_health_test_send(MAVLINK_COMM_1 , packet1.component );
    mavlink_msg_component_health_test_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("COMPONENT_HEALTH_TEST") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_COMPONENT_HEALTH_TEST) != NULL);
#endif
}

static void mavlink_test_scan_settings(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SCAN_SETTINGS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_scan_settings_t packet_in = {
        17.0,45.0,73.0,101.0,129.0,157.0,185.0,18691
    };
    mavlink_scan_settings_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.yaw_start = packet_in.yaw_start;
        packet1.yaw_stop = packet_in.yaw_stop;
        packet1.pitch_start = packet_in.pitch_start;
        packet1.pitch_stop = packet_in.pitch_stop;
        packet1.pitch_rest_angle = packet_in.pitch_rest_angle;
        packet1.point_spacing = packet_in.point_spacing;
        packet1.scan_speed = packet_in.scan_speed;
        packet1.scan_stop_reasons = packet_in.scan_stop_reasons;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SCAN_SETTINGS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_settings_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_scan_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_settings_pack(system_id, component_id, &msg , packet1.yaw_start , packet1.yaw_stop , packet1.pitch_start , packet1.pitch_stop , packet1.pitch_rest_angle , packet1.point_spacing , packet1.scan_speed , packet1.scan_stop_reasons );
    mavlink_msg_scan_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_settings_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.yaw_start , packet1.yaw_stop , packet1.pitch_start , packet1.pitch_stop , packet1.pitch_rest_angle , packet1.point_spacing , packet1.scan_speed , packet1.scan_stop_reasons );
    mavlink_msg_scan_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_scan_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_settings_send(MAVLINK_COMM_1 , packet1.yaw_start , packet1.yaw_stop , packet1.pitch_start , packet1.pitch_stop , packet1.pitch_rest_angle , packet1.point_spacing , packet1.scan_speed , packet1.scan_stop_reasons );
    mavlink_msg_scan_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SCAN_SETTINGS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SCAN_SETTINGS) != NULL);
#endif
}

static void mavlink_test_scan_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SCAN_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_scan_status_t packet_in = {
        963497464,17443,151
    };
    mavlink_scan_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.start_time_unix = packet_in.start_time_unix;
        packet1.time_remaining = packet_in.time_remaining;
        packet1.scan_completion = packet_in.scan_completion;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SCAN_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_scan_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_status_pack(system_id, component_id, &msg , packet1.start_time_unix , packet1.scan_completion , packet1.time_remaining );
    mavlink_msg_scan_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.start_time_unix , packet1.scan_completion , packet1.time_remaining );
    mavlink_msg_scan_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_scan_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_status_send(MAVLINK_COMM_1 , packet1.start_time_unix , packet1.scan_completion , packet1.time_remaining );
    mavlink_msg_scan_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SCAN_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SCAN_STATUS) != NULL);
#endif
}

static void mavlink_test_remote_server_settings(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_remote_server_settings_t packet_in = {
        17235,17339,17,"FGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOP","RSTUVWXYZABCDEFGHIJKLMNOPQRSTUV",116,"YZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHI","KLMNOPQRSTUVWXYZABCDEFGHIJKLMNO","QRSTUVWXYZABCDEFGHIJKLMNOPQRSTU"
    };
    mavlink_remote_server_settings_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.post_port = packet_in.post_port;
        packet1.ftp_port = packet_in.ftp_port;
        packet1.server_enable = packet_in.server_enable;
        packet1.ftp_enable = packet_in.ftp_enable;
        
        mav_array_memcpy(packet1.post_server, packet_in.post_server, sizeof(char)*64);
        mav_array_memcpy(packet1.post_uri, packet_in.post_uri, sizeof(char)*32);
        mav_array_memcpy(packet1.ftp_server, packet_in.ftp_server, sizeof(char)*64);
        mav_array_memcpy(packet1.ftp_username, packet_in.ftp_username, sizeof(char)*32);
        mav_array_memcpy(packet1.ftp_password, packet_in.ftp_password, sizeof(char)*32);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_remote_server_settings_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_remote_server_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_remote_server_settings_pack(system_id, component_id, &msg , packet1.server_enable , packet1.post_server , packet1.post_uri , packet1.post_port , packet1.ftp_enable , packet1.ftp_server , packet1.ftp_username , packet1.ftp_password , packet1.ftp_port );
    mavlink_msg_remote_server_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_remote_server_settings_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.server_enable , packet1.post_server , packet1.post_uri , packet1.post_port , packet1.ftp_enable , packet1.ftp_server , packet1.ftp_username , packet1.ftp_password , packet1.ftp_port );
    mavlink_msg_remote_server_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_remote_server_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_remote_server_settings_send(MAVLINK_COMM_1 , packet1.server_enable , packet1.post_server , packet1.post_uri , packet1.post_port , packet1.ftp_enable , packet1.ftp_server , packet1.ftp_username , packet1.ftp_password , packet1.ftp_port );
    mavlink_msg_remote_server_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("REMOTE_SERVER_SETTINGS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_REMOTE_SERVER_SETTINGS) != NULL);
#endif
}

static void mavlink_test_power_information(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_POWER_INFORMATION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_power_information_t packet_in = {
        963497464,17443,17547,17651,163
    };
    mavlink_power_information_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.energy_consumed = packet_in.energy_consumed;
        packet1.current = packet_in.current;
        packet1.voltage = packet_in.voltage;
        packet1.power = packet_in.power;
        packet1.type = packet_in.type;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_POWER_INFORMATION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_power_information_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_power_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_power_information_pack(system_id, component_id, &msg , packet1.type , packet1.current , packet1.voltage , packet1.power , packet1.energy_consumed );
    mavlink_msg_power_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_power_information_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.type , packet1.current , packet1.voltage , packet1.power , packet1.energy_consumed );
    mavlink_msg_power_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_power_information_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_power_information_send(MAVLINK_COMM_1 , packet1.type , packet1.current , packet1.voltage , packet1.power , packet1.energy_consumed );
    mavlink_msg_power_information_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("POWER_INFORMATION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_POWER_INFORMATION) != NULL);
#endif
}

static void mavlink_test_wifi_information(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_WIFI_INFORMATION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_wifi_information_t packet_in = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDE",{ 101, 102, 103, 104, 105, 106 },247,58,125,192
    };
    mavlink_wifi_information_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.rssi = packet_in.rssi;
        packet1.rssi_percent = packet_in.rssi_percent;
        packet1.snr = packet_in.snr;
        packet1.snr_percent = packet_in.snr_percent;
        
        mav_array_memcpy(packet1.ssid, packet_in.ssid, sizeof(char)*32);
        mav_array_memcpy(packet1.bssid, packet_in.bssid, sizeof(uint8_t)*6);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_WIFI_INFORMATION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_information_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_wifi_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_information_pack(system_id, component_id, &msg , packet1.ssid , packet1.bssid , packet1.rssi , packet1.rssi_percent , packet1.snr , packet1.snr_percent );
    mavlink_msg_wifi_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_information_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.ssid , packet1.bssid , packet1.rssi , packet1.rssi_percent , packet1.snr , packet1.snr_percent );
    mavlink_msg_wifi_information_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_wifi_information_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_information_send(MAVLINK_COMM_1 , packet1.ssid , packet1.bssid , packet1.rssi , packet1.rssi_percent , packet1.snr , packet1.snr_percent );
    mavlink_msg_wifi_information_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("WIFI_INFORMATION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_WIFI_INFORMATION) != NULL);
#endif
}

static void mavlink_test_upload_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_UPLOAD_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_upload_status_t packet_in = {
        963497464,963497672,963497880,17859,17963,53
    };
    mavlink_upload_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.start_time_unix = packet_in.start_time_unix;
        packet1.bytes_uploaded = packet_in.bytes_uploaded;
        packet1.upload_size = packet_in.upload_size;
        packet1.upload_rate = packet_in.upload_rate;
        packet1.time_remaining = packet_in.time_remaining;
        packet1.upload_completion = packet_in.upload_completion;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_UPLOAD_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_upload_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_upload_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_upload_status_pack(system_id, component_id, &msg , packet1.start_time_unix , packet1.upload_completion , packet1.bytes_uploaded , packet1.upload_size , packet1.upload_rate , packet1.time_remaining );
    mavlink_msg_upload_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_upload_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.start_time_unix , packet1.upload_completion , packet1.bytes_uploaded , packet1.upload_size , packet1.upload_rate , packet1.time_remaining );
    mavlink_msg_upload_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_upload_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_upload_status_send(MAVLINK_COMM_1 , packet1.start_time_unix , packet1.upload_completion , packet1.bytes_uploaded , packet1.upload_size , packet1.upload_rate , packet1.time_remaining );
    mavlink_msg_upload_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("UPLOAD_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_UPLOAD_STATUS) != NULL);
#endif
}

static void mavlink_test_motor_control(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MOTOR_CONTROL >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motor_control_t packet_in = {
        17.0,45.0,73.0,17859,17963,53,120
    };
    mavlink_motor_control_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.motor_rpm = packet_in.motor_rpm;
        packet1.target_angle = packet_in.target_angle;
        packet1.device_rpm = packet_in.device_rpm;
        packet1.steps_count = packet_in.steps_count;
        packet1.vactual = packet_in.vactual;
        packet1.target = packet_in.target;
        packet1.behavior = packet_in.behavior;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MOTOR_CONTROL_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_control_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motor_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_control_pack(system_id, component_id, &msg , packet1.target , packet1.behavior , packet1.motor_rpm , packet1.target_angle , packet1.device_rpm , packet1.steps_count , packet1.vactual );
    mavlink_msg_motor_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_control_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.target , packet1.behavior , packet1.motor_rpm , packet1.target_angle , packet1.device_rpm , packet1.steps_count , packet1.vactual );
    mavlink_msg_motor_control_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motor_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_control_send(MAVLINK_COMM_1 , packet1.target , packet1.behavior , packet1.motor_rpm , packet1.target_angle , packet1.device_rpm , packet1.steps_count , packet1.vactual );
    mavlink_msg_motor_control_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MOTOR_CONTROL") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MOTOR_CONTROL) != NULL);
#endif
}

static void mavlink_test_motor_settings(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MOTOR_SETTINGS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motor_settings_t packet_in = {
        17.0,45.0,73.0,17859,17963,18067,187,254,65,132,199,10
    };
    mavlink_motor_settings_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.gearing_ratio = packet_in.gearing_ratio;
        packet1.usteps_rate = packet_in.usteps_rate;
        packet1.ustep_angle = packet_in.ustep_angle;
        packet1.current = packet_in.current;
        packet1.home_offset_steps = packet_in.home_offset_steps;
        packet1.steps_to_next_index = packet_in.steps_to_next_index;
        packet1.motor = packet_in.motor;
        packet1.microsteps = packet_in.microsteps;
        packet1.spread_cycle = packet_in.spread_cycle;
        packet1.pwm_autoscale = packet_in.pwm_autoscale;
        packet1.pwm_autograd = packet_in.pwm_autograd;
        packet1.min_steps_to_next_index = packet_in.min_steps_to_next_index;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MOTOR_SETTINGS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_settings_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motor_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_settings_pack(system_id, component_id, &msg , packet1.motor , packet1.current , packet1.microsteps , packet1.gearing_ratio , packet1.spread_cycle , packet1.pwm_autoscale , packet1.pwm_autograd , packet1.min_steps_to_next_index , packet1.home_offset_steps , packet1.steps_to_next_index , packet1.usteps_rate , packet1.ustep_angle );
    mavlink_msg_motor_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_settings_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.motor , packet1.current , packet1.microsteps , packet1.gearing_ratio , packet1.spread_cycle , packet1.pwm_autoscale , packet1.pwm_autograd , packet1.min_steps_to_next_index , packet1.home_offset_steps , packet1.steps_to_next_index , packet1.usteps_rate , packet1.ustep_angle );
    mavlink_msg_motor_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motor_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_settings_send(MAVLINK_COMM_1 , packet1.motor , packet1.current , packet1.microsteps , packet1.gearing_ratio , packet1.spread_cycle , packet1.pwm_autoscale , packet1.pwm_autograd , packet1.min_steps_to_next_index , packet1.home_offset_steps , packet1.steps_to_next_index , packet1.usteps_rate , packet1.ustep_angle );
    mavlink_msg_motor_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MOTOR_SETTINGS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MOTOR_SETTINGS) != NULL);
#endif
}

static void mavlink_test_motor_status(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_MOTOR_STATUS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_motor_status_t packet_in = {
        17.0,45.0,73.0,101.0,18067,18171,65,132,199
    };
    mavlink_motor_status_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.motor_rpm = packet_in.motor_rpm;
        packet1.device_rpm = packet_in.device_rpm;
        packet1.measured_rpm = packet_in.measured_rpm;
        packet1.current_angle = packet_in.current_angle;
        packet1.vactual = packet_in.vactual;
        packet1.steps_count = packet_in.steps_count;
        packet1.motor = packet_in.motor;
        packet1.enabled = packet_in.enabled;
        packet1.homed = packet_in.homed;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_MOTOR_STATUS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_status_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_motor_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_status_pack(system_id, component_id, &msg , packet1.motor , packet1.enabled , packet1.homed , packet1.motor_rpm , packet1.device_rpm , packet1.measured_rpm , packet1.vactual , packet1.steps_count , packet1.current_angle );
    mavlink_msg_motor_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_status_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.motor , packet1.enabled , packet1.homed , packet1.motor_rpm , packet1.device_rpm , packet1.measured_rpm , packet1.vactual , packet1.steps_count , packet1.current_angle );
    mavlink_msg_motor_status_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_motor_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_motor_status_send(MAVLINK_COMM_1 , packet1.motor , packet1.enabled , packet1.homed , packet1.motor_rpm , packet1.device_rpm , packet1.measured_rpm , packet1.vactual , packet1.steps_count , packet1.current_angle );
    mavlink_msg_motor_status_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("MOTOR_STATUS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_MOTOR_STATUS) != NULL);
#endif
}

static void mavlink_test_orientation(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_ORIENTATION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_orientation_t packet_in = {
        17.0,45.0,73.0,101.0,963498296,963498504,963498712,18691,18795,18899
    };
    mavlink_orientation_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.roll = packet_in.roll;
        packet1.pitch = packet_in.pitch;
        packet1.temp = packet_in.temp;
        packet1.heading = packet_in.heading;
        packet1.lat = packet_in.lat;
        packet1.lon = packet_in.lon;
        packet1.alt = packet_in.alt;
        packet1.xmag = packet_in.xmag;
        packet1.ymag = packet_in.ymag;
        packet1.zmag = packet_in.zmag;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_ORIENTATION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_ORIENTATION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_orientation_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_orientation_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_orientation_pack(system_id, component_id, &msg , packet1.roll , packet1.pitch , packet1.temp , packet1.xmag , packet1.ymag , packet1.zmag , packet1.heading , packet1.lat , packet1.lon , packet1.alt );
    mavlink_msg_orientation_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_orientation_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.roll , packet1.pitch , packet1.temp , packet1.xmag , packet1.ymag , packet1.zmag , packet1.heading , packet1.lat , packet1.lon , packet1.alt );
    mavlink_msg_orientation_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_orientation_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_orientation_send(MAVLINK_COMM_1 , packet1.roll , packet1.pitch , packet1.temp , packet1.xmag , packet1.ymag , packet1.zmag , packet1.heading , packet1.lat , packet1.lon , packet1.alt );
    mavlink_msg_orientation_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("ORIENTATION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_ORIENTATION) != NULL);
#endif
}

static void mavlink_test_wifi_credentials(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_WIFI_CREDENTIALS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_wifi_credentials_t packet_in = {
        5,"BCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKL","NOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWXYZABCDEFGHIJKLMNOPQRSTUVWX",200
    };
    mavlink_wifi_credentials_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.behavior = packet_in.behavior;
        packet1.auth_type = packet_in.auth_type;
        
        mav_array_memcpy(packet1.ssid, packet_in.ssid, sizeof(char)*64);
        mav_array_memcpy(packet1.password, packet_in.password, sizeof(char)*64);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_WIFI_CREDENTIALS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_credentials_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_wifi_credentials_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_credentials_pack(system_id, component_id, &msg , packet1.behavior , packet1.ssid , packet1.password , packet1.auth_type );
    mavlink_msg_wifi_credentials_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_credentials_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.behavior , packet1.ssid , packet1.password , packet1.auth_type );
    mavlink_msg_wifi_credentials_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_wifi_credentials_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_wifi_credentials_send(MAVLINK_COMM_1 , packet1.behavior , packet1.ssid , packet1.password , packet1.auth_type );
    mavlink_msg_wifi_credentials_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("WIFI_CREDENTIALS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_WIFI_CREDENTIALS) != NULL);
#endif
}

static void mavlink_test_lidar_settings(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_LIDAR_SETTINGS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_lidar_settings_t packet_in = {
        17235,139,206,"EFGHIJKLM"
    };
    mavlink_lidar_settings_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.update_rate = packet_in.update_rate;
        packet1.fog_mode_enable = packet_in.fog_mode_enable;
        packet1.output_disabled_at_boot = packet_in.output_disabled_at_boot;
        
        mav_array_memcpy(packet1.firmware_version, packet_in.firmware_version, sizeof(char)*10);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_LIDAR_SETTINGS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_settings_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_lidar_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_settings_pack(system_id, component_id, &msg , packet1.update_rate , packet1.fog_mode_enable , packet1.output_disabled_at_boot , packet1.firmware_version );
    mavlink_msg_lidar_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_settings_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.update_rate , packet1.fog_mode_enable , packet1.output_disabled_at_boot , packet1.firmware_version );
    mavlink_msg_lidar_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_lidar_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_lidar_settings_send(MAVLINK_COMM_1 , packet1.update_rate , packet1.fog_mode_enable , packet1.output_disabled_at_boot , packet1.firmware_version );
    mavlink_msg_lidar_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("LIDAR_SETTINGS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_LIDAR_SETTINGS) != NULL);
#endif
}

static void mavlink_test_scan_result_info(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SCAN_RESULT_INFO >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_scan_result_info_t packet_in = {
        93372036854775807ULL,93372036854776311ULL,963498296,963498504,963498712,18691,18795,101
    };
    mavlink_scan_result_info_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.start_time_unix = packet_in.start_time_unix;
        packet1.end_time_unix = packet_in.end_time_unix;
        packet1.num_points = packet_in.num_points;
        packet1.file_size_bytes = packet_in.file_size_bytes;
        packet1.scan_duration = packet_in.scan_duration;
        packet1.scan_stop_reason = packet_in.scan_stop_reason;
        packet1.scan_start_reason = packet_in.scan_start_reason;
        packet1.type = packet_in.type;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SCAN_RESULT_INFO_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_result_info_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_scan_result_info_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_result_info_pack(system_id, component_id, &msg , packet1.type , packet1.num_points , packet1.file_size_bytes , packet1.start_time_unix , packet1.end_time_unix , packet1.scan_duration , packet1.scan_stop_reason , packet1.scan_start_reason );
    mavlink_msg_scan_result_info_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_result_info_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.type , packet1.num_points , packet1.file_size_bytes , packet1.start_time_unix , packet1.end_time_unix , packet1.scan_duration , packet1.scan_stop_reason , packet1.scan_start_reason );
    mavlink_msg_scan_result_info_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_scan_result_info_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_result_info_send(MAVLINK_COMM_1 , packet1.type , packet1.num_points , packet1.file_size_bytes , packet1.start_time_unix , packet1.end_time_unix , packet1.scan_duration , packet1.scan_stop_reason , packet1.scan_start_reason );
    mavlink_msg_scan_result_info_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SCAN_RESULT_INFO") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SCAN_RESULT_INFO) != NULL);
#endif
}

static void mavlink_test_scan_transform(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_SCAN_TRANSFORM >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_scan_transform_t packet_in = {
        17.0,45.0,17651,17755
    };
    mavlink_scan_transform_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.pitch_scale = packet_in.pitch_scale;
        packet1.yaw_scale = packet_in.yaw_scale;
        packet1.roll_offset = packet_in.roll_offset;
        packet1.pitch_offset = packet_in.pitch_offset;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_SCAN_TRANSFORM_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_transform_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_scan_transform_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_transform_pack(system_id, component_id, &msg , packet1.roll_offset , packet1.pitch_offset , packet1.pitch_scale , packet1.yaw_scale );
    mavlink_msg_scan_transform_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_transform_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.roll_offset , packet1.pitch_offset , packet1.pitch_scale , packet1.yaw_scale );
    mavlink_msg_scan_transform_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_scan_transform_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_scan_transform_send(MAVLINK_COMM_1 , packet1.roll_offset , packet1.pitch_offset , packet1.pitch_scale , packet1.yaw_scale );
    mavlink_msg_scan_transform_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("SCAN_TRANSFORM") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_SCAN_TRANSFORM) != NULL);
#endif
}

static void mavlink_test_altamus(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_lidar_reading(system_id, component_id, last_msg);
    mavlink_test_component_power_control(system_id, component_id, last_msg);
    mavlink_test_system_status(system_id, component_id, last_msg);
    mavlink_test_identifier(system_id, component_id, last_msg);
    mavlink_test_component_health_test(system_id, component_id, last_msg);
    mavlink_test_scan_settings(system_id, component_id, last_msg);
    mavlink_test_scan_status(system_id, component_id, last_msg);
    mavlink_test_remote_server_settings(system_id, component_id, last_msg);
    mavlink_test_power_information(system_id, component_id, last_msg);
    mavlink_test_wifi_information(system_id, component_id, last_msg);
    mavlink_test_upload_status(system_id, component_id, last_msg);
    mavlink_test_motor_control(system_id, component_id, last_msg);
    mavlink_test_motor_settings(system_id, component_id, last_msg);
    mavlink_test_motor_status(system_id, component_id, last_msg);
    mavlink_test_orientation(system_id, component_id, last_msg);
    mavlink_test_wifi_credentials(system_id, component_id, last_msg);
    mavlink_test_lidar_settings(system_id, component_id, last_msg);
    mavlink_test_scan_result_info(system_id, component_id, last_msg);
    mavlink_test_scan_transform(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // ALTAMUS_TESTSUITE_H
