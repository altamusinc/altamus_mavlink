/** @file
 *    @brief MAVLink comm protocol testsuite generated from titan.xml
 *    @see https://mavlink.io/en/
 */
#pragma once
#ifndef TITAN_TESTSUITE_H
#define TITAN_TESTSUITE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef MAVLINK_TEST_ALL
#define MAVLINK_TEST_ALL
static void mavlink_test_common_minimal(uint8_t, uint8_t, mavlink_message_t *last_msg);
static void mavlink_test_titan(uint8_t, uint8_t, mavlink_message_t *last_msg);

static void mavlink_test_all(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_common_minimal(system_id, component_id, last_msg);
    mavlink_test_titan(system_id, component_id, last_msg);
}
#endif

#include "../common_minimal/testsuite.h"


static void mavlink_test_state_input_event(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_STATE_INPUT_EVENT >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_state_input_event_t packet_in = {
        5
    };
    mavlink_state_input_event_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.event = packet_in.event;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_STATE_INPUT_EVENT_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_state_input_event_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_state_input_event_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_state_input_event_pack(system_id, component_id, &msg , packet1.event );
    mavlink_msg_state_input_event_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_state_input_event_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.event );
    mavlink_msg_state_input_event_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_state_input_event_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_state_input_event_send(MAVLINK_COMM_1 , packet1.event );
    mavlink_msg_state_input_event_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("STATE_INPUT_EVENT") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_STATE_INPUT_EVENT) != NULL);
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

static void mavlink_test_water_transaction(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_WATER_TRANSACTION >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_water_transaction_t packet_in = {
        93372036854775807ULL,963497880,963498088,963498296,963498504,18483,"ABCDEFGHIJKLMNOPQRS",15,82
    };
    mavlink_water_transaction_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.badge_id_int = packet_in.badge_id_int;
        packet1.dispensed_ml = packet_in.dispensed_ml;
        packet1.limit_ml = packet_in.limit_ml;
        packet1.start_time_utc = packet_in.start_time_utc;
        packet1.stop_time_utc = packet_in.stop_time_utc;
        packet1.pulses = packet_in.pulses;
        packet1.start_reason = packet_in.start_reason;
        packet1.stop_reason = packet_in.stop_reason;
        
        mav_array_memcpy(packet1.truck_name, packet_in.truck_name, sizeof(char)*20);
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_WATER_TRANSACTION_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_water_transaction_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_water_transaction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_water_transaction_pack(system_id, component_id, &msg , packet1.badge_id_int , packet1.truck_name , packet1.pulses , packet1.dispensed_ml , packet1.limit_ml , packet1.start_reason , packet1.stop_reason , packet1.start_time_utc , packet1.stop_time_utc );
    mavlink_msg_water_transaction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_water_transaction_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.badge_id_int , packet1.truck_name , packet1.pulses , packet1.dispensed_ml , packet1.limit_ml , packet1.start_reason , packet1.stop_reason , packet1.start_time_utc , packet1.stop_time_utc );
    mavlink_msg_water_transaction_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_water_transaction_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_water_transaction_send(MAVLINK_COMM_1 , packet1.badge_id_int , packet1.truck_name , packet1.pulses , packet1.dispensed_ml , packet1.limit_ml , packet1.start_reason , packet1.stop_reason , packet1.start_time_utc , packet1.stop_time_utc );
    mavlink_msg_water_transaction_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("WATER_TRANSACTION") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_WATER_TRANSACTION) != NULL);
#endif
}

static void mavlink_test_station_state(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_STATION_STATE >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_station_state_t packet_in = {
        963497464,963497672,17651,163,230,41,108
    };
    mavlink_station_state_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.untracked_pulses = packet_in.untracked_pulses;
        packet1.system_time = packet_in.system_time;
        packet1.stored_transactions_count = packet_in.stored_transactions_count;
        packet1.system_state = packet_in.system_state;
        packet1.solenoid_state = packet_in.solenoid_state;
        packet1.detected_badges_count = packet_in.detected_badges_count;
        packet1.internet_connectivity = packet_in.internet_connectivity;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_STATION_STATE_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_STATION_STATE_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_state_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_station_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_state_pack(system_id, component_id, &msg , packet1.system_state , packet1.solenoid_state , packet1.untracked_pulses , packet1.system_time , packet1.detected_badges_count , packet1.internet_connectivity , packet1.stored_transactions_count );
    mavlink_msg_station_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_state_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.system_state , packet1.solenoid_state , packet1.untracked_pulses , packet1.system_time , packet1.detected_badges_count , packet1.internet_connectivity , packet1.stored_transactions_count );
    mavlink_msg_station_state_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_station_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_state_send(MAVLINK_COMM_1 , packet1.system_state , packet1.solenoid_state , packet1.untracked_pulses , packet1.system_time , packet1.detected_badges_count , packet1.internet_connectivity , packet1.stored_transactions_count );
    mavlink_msg_station_state_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("STATION_STATE") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_STATION_STATE) != NULL);
#endif
}

static void mavlink_test_station_settings(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
    mavlink_status_t *status = mavlink_get_channel_status(MAVLINK_COMM_0);
        if ((status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) && MAVLINK_MSG_ID_STATION_SETTINGS >= 256) {
            return;
        }
#endif
    mavlink_message_t msg;
        uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
        uint16_t i;
    mavlink_station_settings_t packet_in = {
        963497464,963497672,963497880,963498088,963498296,963498504,77,144
    };
    mavlink_station_settings_t packet1, packet2;
        memset(&packet1, 0, sizeof(packet1));
        packet1.badge_present_timeout = packet_in.badge_present_timeout;
        packet1.badge_present_threshold = packet_in.badge_present_threshold;
        packet1.upload_attempt_timeout = packet_in.upload_attempt_timeout;
        packet1.server_reply_timeout = packet_in.server_reply_timeout;
        packet1.fill_limit_ml = packet_in.fill_limit_ml;
        packet1.ml_per_pulse = packet_in.ml_per_pulse;
        packet1.station_timezone = packet_in.station_timezone;
        packet1.rssi_threshold = packet_in.rssi_threshold;
        
        
#ifdef MAVLINK_STATUS_FLAG_OUT_MAVLINK1
        if (status->flags & MAVLINK_STATUS_FLAG_OUT_MAVLINK1) {
           // cope with extensions
           memset(MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN + (char *)&packet1, 0, sizeof(packet1)-MAVLINK_MSG_ID_STATION_SETTINGS_MIN_LEN);
        }
#endif
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_settings_encode(system_id, component_id, &msg, &packet1);
    mavlink_msg_station_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_settings_pack(system_id, component_id, &msg , packet1.badge_present_timeout , packet1.badge_present_threshold , packet1.upload_attempt_timeout , packet1.server_reply_timeout , packet1.fill_limit_ml , packet1.ml_per_pulse , packet1.station_timezone , packet1.rssi_threshold );
    mavlink_msg_station_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_settings_pack_chan(system_id, component_id, MAVLINK_COMM_0, &msg , packet1.badge_present_timeout , packet1.badge_present_threshold , packet1.upload_attempt_timeout , packet1.server_reply_timeout , packet1.fill_limit_ml , packet1.ml_per_pulse , packet1.station_timezone , packet1.rssi_threshold );
    mavlink_msg_station_settings_decode(&msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

        memset(&packet2, 0, sizeof(packet2));
        mavlink_msg_to_send_buffer(buffer, &msg);
        for (i=0; i<mavlink_msg_get_send_buffer_length(&msg); i++) {
            comm_send_ch(MAVLINK_COMM_0, buffer[i]);
        }
    mavlink_msg_station_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);
        
        memset(&packet2, 0, sizeof(packet2));
    mavlink_msg_station_settings_send(MAVLINK_COMM_1 , packet1.badge_present_timeout , packet1.badge_present_threshold , packet1.upload_attempt_timeout , packet1.server_reply_timeout , packet1.fill_limit_ml , packet1.ml_per_pulse , packet1.station_timezone , packet1.rssi_threshold );
    mavlink_msg_station_settings_decode(last_msg, &packet2);
        MAVLINK_ASSERT(memcmp(&packet1, &packet2, sizeof(packet1)) == 0);

#ifdef MAVLINK_HAVE_GET_MESSAGE_INFO
    MAVLINK_ASSERT(mavlink_get_message_info_by_name("STATION_SETTINGS") != NULL);
    MAVLINK_ASSERT(mavlink_get_message_info_by_id(MAVLINK_MSG_ID_STATION_SETTINGS) != NULL);
#endif
}

static void mavlink_test_titan(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_state_input_event(system_id, component_id, last_msg);
    mavlink_test_identifier(system_id, component_id, last_msg);
    mavlink_test_water_transaction(system_id, component_id, last_msg);
    mavlink_test_station_state(system_id, component_id, last_msg);
    mavlink_test_station_settings(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // TITAN_TESTSUITE_H
