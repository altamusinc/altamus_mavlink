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

#define MAVLINK_ALTAMUS_XML_HASH -4454082403777423202

#ifdef __cplusplus
extern "C" {
#endif

// MESSAGE LENGTHS AND CRCS

#ifndef MAVLINK_MESSAGE_LENGTHS
#define MAVLINK_MESSAGE_LENGTHS {}
#endif

#ifndef MAVLINK_MESSAGE_CRCS
#define MAVLINK_MESSAGE_CRCS {{0, 50, 9, 9, 0, 0, 0}, {1, 125, 248, 248, 0, 0, 0}, {2, 246, 3, 3, 0, 0, 0}, {3, 212, 7, 7, 0, 0, 0}, {5, 217, 28, 28, 1, 0, 0}, {6, 104, 3, 3, 0, 0, 0}, {7, 88, 114, 114, 0, 0, 0}, {8, 179, 4, 4, 0, 0, 0}, {9, 92, 30, 30, 0, 0, 0}, {10, 17, 7, 7, 0, 0, 0}, {11, 79, 230, 230, 0, 0, 0}, {12, 42, 11, 11, 0, 0, 0}, {13, 121, 42, 42, 0, 0, 0}, {14, 141, 17, 17, 0, 0, 0}, {15, 37, 18, 18, 0, 0, 0}, {16, 42, 24, 24, 0, 0, 0}, {17, 61, 23, 23, 0, 0, 0}, {18, 78, 34, 34, 0, 0, 0}, {19, 100, 102, 102, 0, 0, 0}, {20, 236, 14, 14, 0, 0, 0}, {21, 31, 33, 33, 0, 0, 0}, {22, 140, 16, 16, 0, 0, 0}, {24, 24, 30, 52, 0, 0, 0}, {39, 254, 37, 38, 3, 32, 33}, {75, 158, 35, 35, 3, 30, 31}, {76, 152, 33, 33, 3, 30, 31}, {77, 143, 3, 10, 3, 8, 9}, {80, 14, 4, 4, 3, 2, 3}, {110, 84, 254, 254, 3, 1, 2}, {111, 34, 16, 18, 3, 16, 17}, {244, 95, 6, 6, 0, 0, 0}, {251, 170, 18, 18, 0, 0, 0}, {252, 44, 18, 18, 0, 0, 0}, {253, 83, 51, 54, 0, 0, 0}, {300, 217, 22, 22, 0, 0, 0}}
#endif

#include "../protocol.h"

#define MAVLINK_ENABLED_ALTAMUS

// ENUM DEFINITIONS


/** @brief Result from a MAVLink command (MAV_CMD) */
#ifndef HAVE_ENUM_MAV_RESULT
#define HAVE_ENUM_MAV_RESULT
typedef enum MAV_RESULT
{
   MAV_RESULT_ACCEPTED=0, /* Command is valid (is supported and has valid parameters), and was
              executed. | */
   MAV_RESULT_TEMPORARILY_REJECTED=1, /* Command is valid, but cannot be executed at this time. This is used to
              indicate a problem that should be fixed just by waiting (e.g. a state machine is
              busy, can't arm because have not got GPS lock, etc.). Retrying later should
              work. | */
   MAV_RESULT_DENIED=2, /* Command is invalid (is supported but has invalid parameters). Retrying
              same command and parameters will not work. | */
   MAV_RESULT_UNSUPPORTED=3, /* Command is not supported (unknown). | */
   MAV_RESULT_FAILED=4, /* Command is valid, but execution has failed. This is used to indicate
              any non-temporary or unexpected problem, i.e. any problem that must be fixed
              before the command can succeed/be retried. For example, attempting to write a
              file when out of memory, attempting to arm when sensors are not calibrated, etc. | */
   MAV_RESULT_IN_PROGRESS=5, /* Command is valid and is being executed. This will be followed by
              further progress updates, i.e. the component may send further COMMAND_ACK
              messages with result MAV_RESULT_IN_PROGRESS (at a rate decided by the
              implementation), and must terminate by sending a COMMAND_ACK message with final
              result of the operation. The COMMAND_ACK.progress field can be used to indicate
              the progress of the operation. | */
   MAV_RESULT_CANCELLED=6, /* Command has been cancelled (as a result of receiving a COMMAND_CANCEL
              message). | */
   MAV_RESULT_TIMED_OUT=7, /* Indicates that a command has timed out. Intended for use on GCS side to indicate that target hasn't replied back with an expected ACK/NACK | */
   MAV_RESULT_ENUM_END=8, /*  | */
} MAV_RESULT;
#endif

/** @brief  */
#ifndef HAVE_ENUM_MAV_CMD
#define HAVE_ENUM_MAV_CMD
typedef enum MAV_CMD
{
   MAV_CMD_START_EOS_SCAN=1, /* Starts a scan on the targeted scanner. Takes no arguments |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_STOP_EOS_SCAN=2, /* Stops a scan on the targeted scanner. Takes no arguments |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_IDENTIFY=3, /* Requests that device identify itself by flashing it's LED. Takes no arguments |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SEND_SETTINGS_TO_SERVER=4, /* Requests that device sends it's settings to the settings server configured in REMOTE_SERVER_SETTINGS. Takes no arguments |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_CLEAR_EEPROM=5, /* Requests that device clears it's stored EEPROM. Takes no Arguments |Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)|  */
   MAV_CMD_SET_MESSAGE_INTERVAL=511, /* Set the interval between messages for a particular MAVLink message ID. This interface replaces REQUEST_DATA_STREAM. |The MAVLink message ID| The interval between two messages. -1: disable. 0: request default rate (which may be zero).| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Reserved (default:0)| Target address of message stream (if message has target address fields). 0: Flight-stack default (recommended), 1: address of requestor, 2: broadcast.|  */
   MAV_CMD_REQUEST_MESSAGE=512, /* Request the target system(s) emit a single instance of a specified message (i.e. a "one-shot" version of MAV_CMD_SET_MESSAGE_INTERVAL). |The MAVLink message ID of the requested message.| Use for index ID, if required. Otherwise, the use of this parameter (if any) must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| The use of this parameter (if any), must be defined in the requested message. By default assumed not used (0).| Target address for requested message (if message has target address fields). 0: Flight-stack default, 1: address of requestor, 2: broadcast.|  */
   MAV_CMD_ENUM_END=513, /*  | */
} MAV_CMD;
#endif

/** @brief MAV FTP opcodes: https://mavlink.io/en/services/ftp.html */
#ifndef HAVE_ENUM_MAV_FTP_OPCODE
#define HAVE_ENUM_MAV_FTP_OPCODE
typedef enum MAV_FTP_OPCODE
{
   MAV_FTP_OPCODE_NONE=0, /* None. Ignored, always ACKed | */
   MAV_FTP_OPCODE_TERMINATESESSION=1, /* TerminateSession: Terminates open Read session | */
   MAV_FTP_OPCODE_RESETSESSION=2, /* ResetSessions: Terminates all open read sessions | */
   MAV_FTP_OPCODE_LISTDIRECTORY=3, /* ListDirectory. List files and directories in path from offset | */
   MAV_FTP_OPCODE_OPENFILERO=4, /* OpenFileRO: Opens file at path for reading, returns session | */
   MAV_FTP_OPCODE_READFILE=5, /* ReadFile: Reads size bytes from offset in session | */
   MAV_FTP_OPCODE_CREATEFILE=6, /* CreateFile: Creates file at path for writing, returns session | */
   MAV_FTP_OPCODE_WRITEFILE=7, /* WriteFile: Writes size bytes to offset in session | */
   MAV_FTP_OPCODE_REMOVEFILE=8, /* RemoveFile: Remove file at path | */
   MAV_FTP_OPCODE_CREATEDIRECTORY=9, /* CreateDirectory: Creates directory at path | */
   MAV_FTP_OPCODE_REMOVEDIRECTORY=10, /* RemoveDirectory: Removes directory at path. The directory must be empty. | */
   MAV_FTP_OPCODE_OPENFILEWO=11, /* OpenFileWO: Opens file at path for writing, returns session | */
   MAV_FTP_OPCODE_TRUNCATEFILE=12, /* TruncateFile: Truncate file at path to offset length | */
   MAV_FTP_OPCODE_RENAME=13, /* Rename: Rename path1 to path2 | */
   MAV_FTP_OPCODE_CALCFILECRC=14, /* CalcFileCRC32: Calculate CRC32 for file at path | */
   MAV_FTP_OPCODE_BURSTREADFILE=15, /* BurstReadFile: Burst download session file | */
   MAV_FTP_OPCODE_UPLOAD_TO_REMOTE=16, /*  Upload file at given path to the remote server configured in REMOTE_SERVER_SETTINGS | */
   MAV_FTP_OPCODE_ACK=128, /* ACK: ACK response | */
   MAV_FTP_OPCODE_NAK=129, /* NAK: NAK response | */
   MAV_FTP_OPCODE_ENUM_END=130, /*  | */
} MAV_FTP_OPCODE;
#endif

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
   EOS_STATE_SCANNING=3, /*  | */
   EOS_STATE_INIT=4, /*  | */
   EOS_STATE_ERROR=5, /*  | */
   EOS_STATE_HOMING=6, /*  | */
   EOS_STATE_STARTING_SCAN=7, /*  | */
   EOS_STATE_STOPPING_SCAN=8, /*  | */
   EOS_STATE_ENUM_END=9, /*  | */
} EOS_STATE;
#endif

/** @brief  Behaviors a motor can execute  */
#ifndef HAVE_ENUM_MOTOR_BEHAVIOR
#define HAVE_ENUM_MOTOR_BEHAVIOR
typedef enum MOTOR_BEHAVIOR
{
   MOTOR_BEHAVIOR_MOTOR_ENABLE=1, /*  | */
   MOTOR_BEHAVIOR_MOTOR_DISABLE=2, /*  | */
   MOTOR_BEHAVIOR_MOTOR_RPM=3, /*  | */
   MOTOR_BEHAVIOR_DEVICE_RPM=4, /*  | */
   MOTOR_BEHAVIOR_VACTUAL=5, /*  | */
   MOTOR_BEHAVIOR_GOTO_ANGLE=6, /*  | */
   MOTOR_BEHAVIOR_STEP=7, /*  | */
   MOTOR_BEHAVIOR_HOME=8, /*  | */
   MOTOR_BEHAVIOR_ENUM_END=9, /*  | */
} MOTOR_BEHAVIOR;
#endif

/** @brief  Power behavior to execute  */
#ifndef HAVE_ENUM_EOS_COMPONENT_POWER_BEHAVIOR
#define HAVE_ENUM_EOS_COMPONENT_POWER_BEHAVIOR
typedef enum EOS_COMPONENT_POWER_BEHAVIOR
{
   EOS_COMPONENT_POWER_BEHAVIOR_ENABLE=1, /*  | */
   EOS_COMPONENT_POWER_BEHAVIOR_DISABLE=2, /*  | */
   EOS_COMPONENT_POWER_BEHAVIOR_REBOOT=3, /*  | */
   EOS_COMPONENT_POWER_BEHAVIOR_ENUM_END=4, /*  | */
} EOS_COMPONENT_POWER_BEHAVIOR;
#endif

/** @brief  Behavior to execute related to wifi network */
#ifndef HAVE_ENUM_WIFI_CREDIENTIALS_BEHAVIOR
#define HAVE_ENUM_WIFI_CREDIENTIALS_BEHAVIOR
typedef enum WIFI_CREDIENTIALS_BEHAVIOR
{
   WIFI_CREDIENTIALS_BEHAVIOR_ADD=1, /*  | */
   WIFI_CREDIENTIALS_BEHAVIOR_CLEAR=2, /*  | */
   WIFI_CREDIENTIALS_BEHAVIOR_LIST=3, /*  | */
   WIFI_CREDIENTIALS_BEHAVIOR_LIST_RESPONSE=4, /*  | */
   WIFI_CREDIENTIALS_BEHAVIOR_ENUM_END=5, /*  | */
} WIFI_CREDIENTIALS_BEHAVIOR;
#endif

/** @brief Auth type of the wifi */
#ifndef HAVE_ENUM_WIFI_AUTH_TYPE
#define HAVE_ENUM_WIFI_AUTH_TYPE
typedef enum WIFI_AUTH_TYPE
{
   WIFI_AUTH_TYPE_UNSECURED=1, /*  | */
   WIFI_AUTH_TYPE_WEP=2, /*  | */
   WIFI_AUTH_TYPE_WPA=3, /*  | */
   WIFI_AUTH_TYPE_WPA2=4, /*  | */
   WIFI_AUTH_TYPE_ENUM_END=5, /*  | */
} WIFI_AUTH_TYPE;
#endif

/** @brief Reasons to stop a scan */
#ifndef HAVE_ENUM_SCAN_STOP_REASON
#define HAVE_ENUM_SCAN_STOP_REASON
typedef enum SCAN_STOP_REASON
{
   SCAN_STOP_REASON_INCOMPLETE=1, /*  | */
   SCAN_STOP_REASON_PITCH_HOME_ERROR=2, /*  | */
   SCAN_STOP_REASON_PITCH_INDEX_ERROR=4, /*  | */
   SCAN_STOP_REASON_PITCH_MAGNET_ERROR=8, /*  | */
   SCAN_STOP_REASON_YAW_HOME_ERROR=16, /*  | */
   SCAN_STOP_REASON_YAW_INDEX_ERROR=32, /*  | */
   SCAN_STOP_REASON_RANGEFINDER_ERROR_DISABLE_OUTPUT=64, /*  | */
   SCAN_STOP_REASON_RANGEFINDER_ERROR_ENABLE_OUTPUT=128, /*  | */
   SCAN_STOP_REASON_RANGEFINDER_ERROR_RATE=256, /*  | */
   SCAN_STOP_REASON_RANGEFINDER_ERROR_SAVE=512, /*  | */
   SCAN_STOP_REASON_RANGEFINDER_ERROR_FOG=1024, /*  | */
   SCAN_STOP_REASON_USER_CANCELED=2048, /*  | */
   SCAN_STOP_REASON_SCAN_TIMEOUT=4096, /*  | */
   SCAN_STOP_REASON_NORMAL_COMPLETE=8192, /*  | */
   SCAN_STOP_REASON_ENUM_END=8193, /*  | */
} SCAN_STOP_REASON;
#endif

/** @brief  */
#ifndef HAVE_ENUM_SCAN_START_REASON
#define HAVE_ENUM_SCAN_START_REASON
typedef enum SCAN_START_REASON
{
   SCAN_START_REASON_LOCAL_APP=1, /*  | */
   SCAN_START_REASON_WEB=2, /*  | */
   SCAN_START_REASON_SCHEDULE=4, /*  | */
   SCAN_START_REASON_ENUM_END=5, /*  | */
} SCAN_START_REASON;
#endif

/** @brief  */
#ifndef HAVE_ENUM_SCAN_RESULT_INFO_TYPE
#define HAVE_ENUM_SCAN_RESULT_INFO_TYPE
typedef enum SCAN_RESULT_INFO_TYPE
{
   SCAN_RESULT_INFO_ACTUAL=1, /*  | */
   SCAN_RESULT_INFO_ESTIMATED=2, /*  | */
   SCAN_RESULT_INFO_TYPE_ENUM_END=3, /*  | */
} SCAN_RESULT_INFO_TYPE;
#endif

/** @brief  */
#ifndef HAVE_ENUM_POWER_INFORMATION_TYPE
#define HAVE_ENUM_POWER_INFORMATION_TYPE
typedef enum POWER_INFORMATION_TYPE
{
   POWER_INFORMATION_TYPE_INSTANT=1, /*  | */
   POWER_INFORMATION_TYPE_AVERAGE=2, /*  | */
   POWER_INFORMATION_TYPE_MAXIMUM=3, /*  | */
   POWER_INFORMATION_TYPE_MINIMUM=4, /*  | */
   POWER_INFORMATION_TYPE_ENUM_END=5, /*  | */
} POWER_INFORMATION_TYPE;
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
#include "./mavlink_msg_identifier.h"
#include "./mavlink_msg_component_health_test.h"
#include "./mavlink_msg_scan_settings.h"
#include "./mavlink_msg_scan_status.h"
#include "./mavlink_msg_remote_server_settings.h"
#include "./mavlink_msg_power_information.h"
#include "./mavlink_msg_wifi_information.h"
#include "./mavlink_msg_upload_status.h"
#include "./mavlink_msg_motor_control.h"
#include "./mavlink_msg_motor_settings.h"
#include "./mavlink_msg_motor_status.h"
#include "./mavlink_msg_orientation.h"
#include "./mavlink_msg_wifi_credentials.h"
#include "./mavlink_msg_lidar_settings.h"
#include "./mavlink_msg_scan_result_info.h"
#include "./mavlink_msg_scan_transform.h"

// base include
#include "../common_minimal/common_minimal.h"


#if MAVLINK_ALTAMUS_XML_HASH == MAVLINK_PRIMARY_XML_HASH
# define MAVLINK_MESSAGE_INFO {MAVLINK_MESSAGE_INFO_HEARTBEAT, MAVLINK_MESSAGE_INFO_LIDAR_READING, MAVLINK_MESSAGE_INFO_COMPONENT_POWER_CONTROL, MAVLINK_MESSAGE_INFO_SYSTEM_STATUS, MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL, MAVLINK_MESSAGE_INFO_CHANGE_OPERATOR_CONTROL_ACK, MAVLINK_MESSAGE_INFO_IDENTIFIER, MAVLINK_MESSAGE_INFO_COMPONENT_HEALTH_TEST, MAVLINK_MESSAGE_INFO_SCAN_SETTINGS, MAVLINK_MESSAGE_INFO_SCAN_STATUS, MAVLINK_MESSAGE_INFO_REMOTE_SERVER_SETTINGS, MAVLINK_MESSAGE_INFO_POWER_INFORMATION, MAVLINK_MESSAGE_INFO_WIFI_INFORMATION, MAVLINK_MESSAGE_INFO_UPLOAD_STATUS, MAVLINK_MESSAGE_INFO_MOTOR_CONTROL, MAVLINK_MESSAGE_INFO_MOTOR_SETTINGS, MAVLINK_MESSAGE_INFO_MOTOR_STATUS, MAVLINK_MESSAGE_INFO_ORIENTATION, MAVLINK_MESSAGE_INFO_WIFI_CREDENTIALS, MAVLINK_MESSAGE_INFO_LIDAR_SETTINGS, MAVLINK_MESSAGE_INFO_SCAN_RESULT_INFO, MAVLINK_MESSAGE_INFO_SCAN_TRANSFORM, MAVLINK_MESSAGE_INFO_GPS_RAW_INT, MAVLINK_MESSAGE_INFO_MISSION_ITEM, MAVLINK_MESSAGE_INFO_COMMAND_INT, MAVLINK_MESSAGE_INFO_COMMAND_LONG, MAVLINK_MESSAGE_INFO_COMMAND_ACK, MAVLINK_MESSAGE_INFO_COMMAND_CANCEL, MAVLINK_MESSAGE_INFO_FILE_TRANSFER_PROTOCOL, MAVLINK_MESSAGE_INFO_TIMESYNC, MAVLINK_MESSAGE_INFO_MESSAGE_INTERVAL, MAVLINK_MESSAGE_INFO_NAMED_VALUE_FLOAT, MAVLINK_MESSAGE_INFO_NAMED_VALUE_INT, MAVLINK_MESSAGE_INFO_STATUSTEXT, MAVLINK_MESSAGE_INFO_PROTOCOL_VERSION}
# define MAVLINK_MESSAGE_NAMES {{ "CHANGE_OPERATOR_CONTROL", 5 }, { "CHANGE_OPERATOR_CONTROL_ACK", 6 }, { "COMMAND_ACK", 77 }, { "COMMAND_CANCEL", 80 }, { "COMMAND_INT", 75 }, { "COMMAND_LONG", 76 }, { "COMPONENT_HEALTH_TEST", 8 }, { "COMPONENT_POWER_CONTROL", 2 }, { "FILE_TRANSFER_PROTOCOL", 110 }, { "GPS_RAW_INT", 24 }, { "HEARTBEAT", 0 }, { "IDENTIFIER", 7 }, { "LIDAR_READING", 1 }, { "LIDAR_SETTINGS", 20 }, { "MESSAGE_INTERVAL", 244 }, { "MISSION_ITEM", 39 }, { "MOTOR_CONTROL", 15 }, { "MOTOR_SETTINGS", 16 }, { "MOTOR_STATUS", 17 }, { "NAMED_VALUE_FLOAT", 251 }, { "NAMED_VALUE_INT", 252 }, { "ORIENTATION", 18 }, { "POWER_INFORMATION", 12 }, { "PROTOCOL_VERSION", 300 }, { "REMOTE_SERVER_SETTINGS", 11 }, { "SCAN_RESULT_INFO", 21 }, { "SCAN_SETTINGS", 9 }, { "SCAN_STATUS", 10 }, { "SCAN_TRANSFORM", 22 }, { "STATUSTEXT", 253 }, { "SYSTEM_STATUS", 3 }, { "TIMESYNC", 111 }, { "UPLOAD_STATUS", 14 }, { "WIFI_CREDENTIALS", 19 }, { "WIFI_INFORMATION", 13 }}
# if MAVLINK_COMMAND_24BIT
#  include "../mavlink_get_info.h"
# endif
#endif

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // MAVLINK_ALTAMUS_H
