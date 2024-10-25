/** @file
 *  @brief MAVLink comm protocol generated from altamus.xml
 *  @see http://mavlink.org
 */
#pragma once
#ifndef MAVLINK_ALTAMUS_H
#define MAVLINK_ALTAMUS_H

#ifndef MAVLINK_H
    #error Wrong include order: MAVLINK_ALTAMUS.H MUST NOT BE DIRECTLY USED. Include mavlink.h from the same directory instead or set ALL AND EVERY defines from MAVLINK.H manually accordingly, including the #define MAVLINK_H call.
#endif

#define MAVLINK_ALTAMUS_XML_HASH -2324071029975242665

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 50, 9, 9, 0, 0, 0}, {1, 125, 248, 248, 0, 0, 0}, {2, 246, 3, 3, 0, 0, 0}, {3, 212, 7, 7, 0, 0, 0}, {4, 37, 18, 18, 0, 0, 0}, {5, 42, 24, 24, 0, 0, 0}, {6, 61, 23, 23, 0, 0, 0}, {7, 110, 50, 50, 0, 0, 0}, {8, 179, 4, 4, 0, 0, 0}, {9, 155, 24, 24, 0, 0, 0}, {10, 17, 7, 7, 0, 0, 0}, {11, 79, 230, 230, 0, 0, 0}, {12, 89, 10, 10, 0, 0, 0}, {13, 121, 42, 42, 0, 0, 0}, {24, 24, 30, 52, 0, 0, 0}, {30, 227, 32, 32, 0, 0, 0}, {39, 254, 37, 38, 3, 32, 33}, {75, 158, 35, 35, 3, 30, 31}, {76, 152, 33, 33, 3, 30, 31}, {77, 143, 3, 10, 3, 8, 9}, {80, 14, 4, 4, 3, 2, 3}, {244, 95, 6, 6, 0, 0, 0}, {253, 83, 51, 54, 0, 0, 0}, {300, 217, 22, 22, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_ALTAMUS

// ENUM DEFINITIONS


/** @brief  Components within the EOS scanner  */
#ifndef HAVE_ENUM_EOS_COMPONENT
#define HAVE_ENUM_EOS_COMPONENT
typedef enum EOS_COMPONENT
{
   EOS_COMPONENT_LIDAR=1, /*  | */
   EOS_COMPONENT_YAW_MOTOR=2, /*  | */
   EOS_COMPONENT_PITCH_MOTOR=4, /*  | */
   EOS_COMPONENT_GPS=8, /*  | */
   EOS_COMPONENT_COMPASS=16, /*  | */
   EOS_COMPONENT_MCU=32, /*  | */
   EOS_COMPONENT_LED=64, /*  | */
   EOS_COMPONENT_ACCEL=128, /*  | */
   EOS_COMPONENT_POWER_SENSOR=256, /*  | */
   EOS_COMPONENT_SERIAL_BRIDGE=512, /*  | */
   EOS_COMPONENT_PORT_EXPANDER=1024, /*  | */
   EOS_COMPONENT_FLASH=2048, /*  | */
   EOS_COMPONENT_ALL=4096, /*  | */
   EOS_COMPONENT_ENUM_END=4097, /*  | */
} EOS_COMPONENT;
#endif

/** @brief  State of the device  */
#ifndef HAVE_ENUM_EOS_STATE
#define HAVE_ENUM_EOS_STATE
typedef enum EOS_STATE
{
   EOS_STATE_IDLE=1, /*  | */
   EOS_STATE_UPLOADING=2, /*  | */
   EOS_STATE_SCANNING=4, /*  | */
   EOS_STATE_INIT=8, /*  | */
   EOS_STATE_ERROR=16, /*  | */
   EOS_STATE_ENUM_END=17, /*  | */
} EOS_STATE;
#endif

/** @brief  Behaviors a motor can execute  */
#ifndef HAVE_ENUM_MOTOR_BEHAVIOR
#define HAVE_ENUM_MOTOR_BEHAVIOR
typedef enum MOTOR_BEHAVIOR
{
   MOTOR_BEHAVIOR_MOTOR_ENABLE=1, /*  | */
   MOTOR_BEHAVIOR_MOTOR_DISABLE=2, /*  | */
   MOTOR_BEHAVIOR_MOTOR_RPM=4, /*  | */
   MOTOR_BEHAVIOR_DEVICE_RPM=8, /*  | */
   MOTOR_BEHAVIOR_VACTUAL=16, /*  | */
   MOTOR_BEHAVIOR_GOTO_ANGLE=32, /*  | */
   MOTOR_BEHAVIOR_STEP=64, /*  | */
   MOTOR_BEHAVIOR_HOME=128, /*  | */
   MOTOR_BEHAVIOR_ENUM_END=129, /*  | */
} MOTOR_BEHAVIOR;
#endif

/** @brief  Power behavior to execute  */
#ifndef HAVE_ENUM_EOS_COMPONENT_POWER_BEHAVIOR
#define HAVE_ENUM_EOS_COMPONENT_POWER_BEHAVIOR
typedef enum EOS_COMPONENT_POWER_BEHAVIOR
{
   EOS_COMPONENT_POWER_BEHAVIOR_ENABLE=1, /*  | */
   EOS_COMPONENT_POWER_BEHAVIOR_DISABLE=2, /*  | */
   EOS_COMPONENT_POWER_BEHAVIOR_REBOOT=4, /*  | */
   EOS_COMPONENT_POWER_BEHAVIOR_ENUM_END=5, /*  | */
} EOS_COMPONENT_POWER_BEHAVIOR;
#endif

// MAVLINK VERSION

#ifndef MAVLINK_VERSION
#define MAVLINK_VERSION 1
#endif

#if (MAVLINK_VERSION == 0)
#undef MAVLINK_VERSION
#define MAVLINK_VERSION 1
#endif

// MESSAGE DEFINITIONS
#include "./mavlink_msg_lidar_reading.h"
#include "./mavlink_msg_component_power_control.h"
#include "./mavlink_msg_system_status.h"
#include "./mavlink_msg_motor_control.h"
#include "./mavlink_msg_motor_settings.h"
#include "./mavlink_msg_motor_status.h"
#include "./mavlink_msg_identifier.h"
#include "./mavlink_msg_component_health_test.h"
#include "./mavlink_msg_scan_settings.h"
#include "./mavlink_msg_scan_status.h"
#include "./mavlink_msg_remote_server_settings.h"
#include "./mavlink_msg_power_information.h"
#include "./mavlink_msg_wifi_information.h"

// base include
#include "../common_minimal/common_minimal.h"


#if MAVLINK_ALTAMUS_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_LIDAR_READING, MAVLINK_MESSAGE_INFO_COMPONENT_POWER_CONTROL, MAVLINK_MESSAGE_INFO_SYSTEM_STATUS, MAVLINK_MESSAGE_INFO_MOTOR_CONTROL, MAVLINK_MESSAGE_INFO_MOTOR_SETTINGS, MAVLINK_MESSAGE_INFO_MOTOR_STATUS, MAVLINK_MESSAGE_INFO_IDENTIFIER, MAVLINK_MESSAGE_INFO_COMPONENT_HEALTH_TEST, MAVLINK_MESSAGE_INFO_SCAN_SETTINGS, MAVLINK_MESSAGE_INFO_SCAN_STATUS, MAVLINK_MESSAGE_INFO_REMOTE_SERVER_SETTINGS, MAVLINK_MESSAGE_INFO_POWER_INFORMATION, MAVLINK_MESSAGE_INFO_WIFI_INFORMATION, MAVLINK_MESSAGE_INFO_GPS_RAW_INT, MAVLINK_MESSAGE_INFO_ATTITUDE, MAVLINK_MESSAGE_INFO_MISSION_ITEM, MAVLINK_MESSAGE_INFO_COMMAND_INT, MAVLINK_MESSAGE_INFO_COMMAND_LONG, MAVLINK_MESSAGE_INFO_COMMAND_ACK, MAVLINK_MESSAGE_INFO_COMMAND_CANCEL, MAVLINK_MESSAGE_INFO_MESSAGE_INTERVAL, MAVLINK_MESSAGE_INFO_STATUSTEXT, MAVLINK_MESSAGE_INFO_PROTOCOL_VERSION}
# define MAVLINK_MESSAGE_NAMES {{ "ATTITUDE", 30 }, { "COMMAND_ACK", 77 }, { "COMMAND_CANCEL", 80 }, { "COMMAND_INT", 75 }, { "COMMAND_LONG", 76 }, { "COMPONENT_HEALTH_TEST", 8 }, { "COMPONENT_POWER_CONTROL", 2 }, { "GPS_RAW_INT", 24 }, { "HEARTBEAT", 0 }, { "IDENTIFIER", 7 }, { "LIDAR_READING", 1 }, { "MESSAGE_INTERVAL", 244 }, { "MISSION_ITEM", 39 }, { "MOTOR_CONTROL", 4 }, { "MOTOR_SETTINGS", 5 }, { "MOTOR_STATUS", 6 }, { "POWER_INFORMATION", 12 }, { "PROTOCOL_VERSION", 300 }, { "REMOTE_SERVER_SETTINGS", 11 }, { "SCAN_SETTINGS", 9 }, { "SCAN_STATUS", 10 }, { "STATUSTEXT", 253 }, { "SYSTEM_STATUS", 3 }, { "WIFI_INFORMATION", 13 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_ALTAMUS_H
