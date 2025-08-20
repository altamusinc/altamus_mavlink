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

static void mavlink_test_titan(uint8_t system_id, uint8_t component_id, mavlink_message_t *last_msg)
{
    mavlink_test_state_input_event(system_id, component_id, last_msg);
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // TITAN_TESTSUITE_H
