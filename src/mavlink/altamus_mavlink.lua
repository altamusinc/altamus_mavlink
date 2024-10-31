-- Wireshark dissector for the MAVLink protocol (please see https://mavlink.io/en for details)

unknownFrameBeginOffset = 0
mavlink_proto = Proto("mavlink_proto", "MAVLink protocol")
f = mavlink_proto.fields

-- from http://lua-users.org/wiki/TimeZone
local function get_timezone()
    local now = os.time()
    return os.difftime(now, os.time(os.date("!*t", now)))
end
local signature_time_ref = get_timezone() + os.time{year=2015, month=1, day=1, hour=0}

-- threshold to decide if time is absolute or relative (some time in 2005)
time_usec_threshold = UInt64.new(0,0x40000)
-- function to append human-readable time onto unix_time_us fields
local function time_usec_decode(value)
    if value > time_usec_threshold then
        d = os.date("%Y-%m-%d %H:%M:%S",value:tonumber() / 1000000.0)
        us = value % 1000000
        us = string.format("%06d",us:tonumber())
        ok, tz = pcall(os.date," %Z",value:tonumber() / 1000000.0)
        if not ok then
            tz = os.date(" %z",value:tonumber() / 1000000.0)
        end
        return " (" .. d .. "." .. us .. tz .. ")"
    elseif value < 1000000 then
        return ""
    elseif type(value) == "number" then
        return string.format(" (%.6f s)",value / 1000000.0)
    else
        return string.format(" (%.6f s)",value:tonumber() / 1000000.0)
    end
end

payload_fns = {}

protocolVersions = {
    [0xfd] = "MAVLink 2.0",
    [0xfe] = "MAVLink 1.0",
    [0x55] = "MAVLink 0.9"
}

messageName = {
    [1] = 'LIDAR_READING',
    [2] = 'COMPONENT_POWER_CONTROL',
    [3] = 'SYSTEM_STATUS',
    [7] = 'IDENTIFIER',
    [8] = 'COMPONENT_HEALTH_TEST',
    [9] = 'SCAN_SETTINGS',
    [10] = 'SCAN_STATUS',
    [11] = 'REMOTE_SERVER_SETTINGS',
    [12] = 'POWER_INFORMATION',
    [13] = 'WIFI_INFORMATION',
    [14] = 'UPLOAD_STATUS',
    [15] = 'MOTOR_CONTROL',
    [16] = 'MOTOR_SETTINGS',
    [17] = 'MOTOR_STATUS',
    [0] = 'HEARTBEAT',
    [5] = 'CHANGE_OPERATOR_CONTROL',
    [6] = 'CHANGE_OPERATOR_CONTROL_ACK',
    [300] = 'PROTOCOL_VERSION',
    [24] = 'GPS_RAW_INT',
    [30] = 'ATTITUDE',
    [39] = 'MISSION_ITEM',
    [75] = 'COMMAND_INT',
    [76] = 'COMMAND_LONG',
    [77] = 'COMMAND_ACK',
    [80] = 'COMMAND_CANCEL',
    [244] = 'MESSAGE_INTERVAL',
    [253] = 'STATUSTEXT',
}

local enumEntryName = {
    ["MAV_RESULT"] = {
        [0] = "MAV_RESULT_ACCEPTED",
        [1] = "MAV_RESULT_TEMPORARILY_REJECTED",
        [2] = "MAV_RESULT_DENIED",
        [3] = "MAV_RESULT_UNSUPPORTED",
        [4] = "MAV_RESULT_FAILED",
        [5] = "MAV_RESULT_IN_PROGRESS",
        [6] = "MAV_RESULT_CANCELLED",
        [7] = "MAV_RESULT_TIMED_OUT",
    },
    ["MAV_CMD"] = {
        [1] = "MAV_CMD_START_EOS_SCAN",
        [2] = "MAV_CMD_STOP_EOS_SCAN",
        [3] = "MAV_CMD_IDENTIFY",
        [4] = "MAV_CMD_SEND_SETTINGS_TO_SERVER",
        [5] = "MAV_CMD_CLEAR_EEPROM",
        [511] = "MAV_CMD_SET_MESSAGE_INTERVAL",
        [512] = "MAV_CMD_REQUEST_MESSAGE",
    },
    ["EOS_COMPONENT"] = {
        [1] = "EOS_COMPONENT_LIDAR",
        [2] = "EOS_COMPONENT_YAW_MOTOR",
        [4] = "EOS_COMPONENT_PITCH_MOTOR",
        [8] = "EOS_COMPONENT_GPS",
        [16] = "EOS_COMPONENT_COMPASS",
        [32] = "EOS_COMPONENT_MCU",
        [64] = "EOS_COMPONENT_LED",
        [128] = "EOS_COMPONENT_ACCEL",
        [256] = "EOS_COMPONENT_POWER_SENSOR",
        [512] = "EOS_COMPONENT_SERIAL_BRIDGE",
        [1024] = "EOS_COMPONENT_PORT_EXPANDER",
        [2048] = "EOS_COMPONENT_FLASH",
        [4096] = "EOS_COMPONENT_ALL",
    },
    ["EOS_STATE"] = {
        [1] = "EOS_STATE_IDLE",
        [2] = "EOS_STATE_UPLOADING",
        [4] = "EOS_STATE_SCANNING",
        [8] = "EOS_STATE_INIT",
        [16] = "EOS_STATE_ERROR",
    },
    ["MOTOR_BEHAVIOR"] = {
        [1] = "MOTOR_BEHAVIOR_MOTOR_ENABLE",
        [2] = "MOTOR_BEHAVIOR_MOTOR_DISABLE",
        [4] = "MOTOR_BEHAVIOR_MOTOR_RPM",
        [8] = "MOTOR_BEHAVIOR_DEVICE_RPM",
        [16] = "MOTOR_BEHAVIOR_VACTUAL",
        [32] = "MOTOR_BEHAVIOR_GOTO_ANGLE",
        [64] = "MOTOR_BEHAVIOR_STEP",
        [128] = "MOTOR_BEHAVIOR_HOME",
    },
    ["EOS_COMPONENT_POWER_BEHAVIOR"] = {
        [1] = "EOS_COMPONENT_POWER_BEHAVIOR_ENABLE",
        [2] = "EOS_COMPONENT_POWER_BEHAVIOR_DISABLE",
        [4] = "EOS_COMPONENT_POWER_BEHAVIOR_REBOOT",
    },
    ["MAV_AUTOPILOT"] = {
        [0] = "MAV_AUTOPILOT_GENERIC",
        [8] = "MAV_AUTOPILOT_INVALID",
    },
    ["MAV_TYPE"] = {
        [0] = "MAV_TYPE_GENERIC",
        [1] = "MAV_TYPE_FIXED_WING",
        [6] = "MAV_TYPE_GCS",
        [12] = "MAV_AUTOPILOT_PX4",
        [18] = "MAV_TYPE_ONBOARD_CONTROLLER",
        [26] = "MAV_TYPE_GIMBAL",
        [27] = "MAV_TYPE_ADSB",
        [30] = "MAV_TYPE_CAMERA",
    },
    ["MAV_SEVERITY"] = {
        [0] = "MAV_SEVERITY_EMERGENCY",
        [1] = "MAV_SEVERITY_ALERT",
        [2] = "MAV_SEVERITY_CRITICAL",
        [3] = "MAV_SEVERITY_ERROR",
        [4] = "MAV_SEVERITY_WARNING",
        [5] = "MAV_SEVERITY_NOTICE",
        [6] = "MAV_SEVERITY_INFO",
        [7] = "MAV_SEVERITY_DEBUG",
    },
    ["MAV_MODE_FLAG"] = {
        [1] = "MAV_MODE_FLAG_CUSTOM_MODE_ENABLED",
        [2] = "MAV_MODE_FLAG_TEST_ENABLED",
        [4] = "MAV_MODE_FLAG_AUTO_ENABLED",
        [8] = "MAV_MODE_FLAG_GUIDED_ENABLED",
        [16] = "MAV_MODE_FLAG_STABILIZE_ENABLED",
        [32] = "MAV_MODE_FLAG_HIL_ENABLED",
        [64] = "MAV_MODE_FLAG_MANUAL_INPUT_ENABLED",
        [128] = "MAV_MODE_FLAG_SAFETY_ARMED",
    },
    ["MAV_MODE_FLAG_DECODE_POSITION"] = {
        [1] = "MAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE",
        [2] = "MAV_MODE_FLAG_DECODE_POSITION_TEST",
        [4] = "MAV_MODE_FLAG_DECODE_POSITION_AUTO",
        [8] = "MAV_MODE_FLAG_DECODE_POSITION_GUIDED",
        [16] = "MAV_MODE_FLAG_DECODE_POSITION_STABILIZE",
        [32] = "MAV_MODE_FLAG_DECODE_POSITION_HIL",
        [64] = "MAV_MODE_FLAG_DECODE_POSITION_MANUAL",
        [128] = "MAV_MODE_FLAG_DECODE_POSITION_SAFETY",
    },
    ["MAV_STATE"] = {
        [0] = "MAV_STATE_UNINIT",
        [1] = "MAV_STATE_BOOT",
        [2] = "MAV_STATE_CALIBRATING",
        [3] = "MAV_STATE_STANDBY",
        [4] = "MAV_STATE_ACTIVE",
        [5] = "MAV_STATE_CRITICAL",
        [6] = "MAV_STATE_EMERGENCY",
        [7] = "MAV_STATE_POWEROFF",
        [8] = "MAV_STATE_FLIGHT_TERMINATION",
    },
    ["MAV_COMPONENT"] = {
        [0] = "MAV_COMP_ID_ALL",
        [1] = "MAV_COMP_ID_AUTOPILOT1",
        [154] = "MAV_COMP_ID_GIMBAL",
    },
    ["MAV_MISSION_TYPE"] = {
        [0] = "MAV_MISSION_TYPE_MISSION",
        [1] = "MAV_MISSION_TYPE_FENCE",
        [2] = "MAV_MISSION_TYPE_RALLY",
        [255] = "MAV_MISSION_TYPE_ALL",
    },
    ["MAV_FRAME"] = {
        [0] = "MAV_FRAME_GLOBAL",
        [1] = "MAV_FRAME_LOCAL_NED",
    },
    ["GPS_FIX_TYPE"] = {
        [0] = "GPS_FIX_TYPE_NO_GPS",
        [1] = "GPS_FIX_TYPE_NO_FIX",
        [2] = "GPS_FIX_TYPE_2D_FIX",
        [3] = "GPS_FIX_TYPE_3D_FIX",
        [4] = "GPS_FIX_TYPE_DGPS",
        [5] = "GPS_FIX_TYPE_RTK_FLOAT",
        [6] = "GPS_FIX_TYPE_RTK_FIXED",
        [7] = "GPS_FIX_TYPE_STATIC",
        [8] = "GPS_FIX_TYPE_PPP",
    },
}
f.magic = ProtoField.uint8("mavlink_proto.magic", "Magic value / version", base.HEX, protocolVersions)
f.length = ProtoField.uint8("mavlink_proto.length", "Payload length")
f.incompatibility_flag = ProtoField.uint8("mavlink_proto.incompatibility_flag", "Incompatibility flag", base.HEX_DEC)
f.compatibility_flag = ProtoField.uint8("mavlink_proto.compatibility_flag", "Compatibility flag", base.HEX_DEC)
f.sequence = ProtoField.uint8("mavlink_proto.sequence", "Packet sequence")
f.sysid = ProtoField.uint8("mavlink_proto.sysid", "System id", base.DEC)
f.compid = ProtoField.uint8("mavlink_proto.compid", "Component id", base.DEC, enumEntryName.MAV_COMPONENT)
f.msgid = ProtoField.uint24("mavlink_proto.msgid", "Message id", base.DEC, messageName)
f.payload = ProtoField.uint8("mavlink_proto.payload", "Payload", base.DEC, messageName)
f.crc = ProtoField.uint16("mavlink_proto.crc", "Message CRC", base.HEX)
f.signature_link = ProtoField.uint8("mavlink_proto.signature_link", "Link id", base.DEC)
f.signature_time = ProtoField.absolute_time("mavlink_proto.signature_time", "Time")
f.signature_signature = ProtoField.bytes("mavlink_proto.signature_signature", "Signature")
f.rawheader = ProtoField.bytes("mavlink_proto.rawheader", "Unparsable header fragment")
f.rawpayload = ProtoField.bytes("mavlink_proto.rawpayload", "Unparsable payload")





f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param1 = ProtoField.new("param1: Message ID (float)", "mavlink_proto.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param1", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param2 = ProtoField.new("param2: Interval (float) us", "mavlink_proto.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param2", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param7 = ProtoField.new("param7: Response Target (float)", "mavlink_proto.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param7", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_z = ProtoField.new("z: Response Target (float)", "mavlink_proto.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_z", ftypes.FLOAT, nil)

f.cmd_MAV_CMD_REQUEST_MESSAGE_param1 = ProtoField.new("param1: Message ID (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_param1", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_param2 = ProtoField.new("param2: Req Param 1 (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_param2", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_param3 = ProtoField.new("param3: Req Param 2 (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_param3", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_param4 = ProtoField.new("param4: Req Param 3 (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_param4", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_param5 = ProtoField.new("param5: Req Param 4 (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_param5", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_x = ProtoField.new("x: Req Param 4 (int32_t)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_x", ftypes.INT32, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_param6 = ProtoField.new("param6: Req Param 5 (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_param6", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_y = ProtoField.new("y: Req Param 5 (int32_t)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_y", ftypes.INT32, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_param7 = ProtoField.new("param7: Response Target (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_param7", ftypes.FLOAT, nil)
f.cmd_MAV_CMD_REQUEST_MESSAGE_z = ProtoField.new("z: Response Target (float)", "mavlink_proto.cmd_MAV_CMD_REQUEST_MESSAGE_z", ftypes.FLOAT, nil)


f.LIDAR_READING_readings_0 = ProtoField.new("readings[0] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_0", ftypes.UINT64, nil)
f.LIDAR_READING_readings_1 = ProtoField.new("readings[1] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_1", ftypes.UINT64, nil)
f.LIDAR_READING_readings_2 = ProtoField.new("readings[2] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_2", ftypes.UINT64, nil)
f.LIDAR_READING_readings_3 = ProtoField.new("readings[3] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_3", ftypes.UINT64, nil)
f.LIDAR_READING_readings_4 = ProtoField.new("readings[4] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_4", ftypes.UINT64, nil)
f.LIDAR_READING_readings_5 = ProtoField.new("readings[5] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_5", ftypes.UINT64, nil)
f.LIDAR_READING_readings_6 = ProtoField.new("readings[6] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_6", ftypes.UINT64, nil)
f.LIDAR_READING_readings_7 = ProtoField.new("readings[7] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_7", ftypes.UINT64, nil)
f.LIDAR_READING_readings_8 = ProtoField.new("readings[8] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_8", ftypes.UINT64, nil)
f.LIDAR_READING_readings_9 = ProtoField.new("readings[9] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_9", ftypes.UINT64, nil)
f.LIDAR_READING_readings_10 = ProtoField.new("readings[10] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_10", ftypes.UINT64, nil)
f.LIDAR_READING_readings_11 = ProtoField.new("readings[11] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_11", ftypes.UINT64, nil)
f.LIDAR_READING_readings_12 = ProtoField.new("readings[12] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_12", ftypes.UINT64, nil)
f.LIDAR_READING_readings_13 = ProtoField.new("readings[13] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_13", ftypes.UINT64, nil)
f.LIDAR_READING_readings_14 = ProtoField.new("readings[14] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_14", ftypes.UINT64, nil)
f.LIDAR_READING_readings_15 = ProtoField.new("readings[15] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_15", ftypes.UINT64, nil)
f.LIDAR_READING_readings_16 = ProtoField.new("readings[16] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_16", ftypes.UINT64, nil)
f.LIDAR_READING_readings_17 = ProtoField.new("readings[17] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_17", ftypes.UINT64, nil)
f.LIDAR_READING_readings_18 = ProtoField.new("readings[18] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_18", ftypes.UINT64, nil)
f.LIDAR_READING_readings_19 = ProtoField.new("readings[19] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_19", ftypes.UINT64, nil)
f.LIDAR_READING_readings_20 = ProtoField.new("readings[20] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_20", ftypes.UINT64, nil)
f.LIDAR_READING_readings_21 = ProtoField.new("readings[21] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_21", ftypes.UINT64, nil)
f.LIDAR_READING_readings_22 = ProtoField.new("readings[22] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_22", ftypes.UINT64, nil)
f.LIDAR_READING_readings_23 = ProtoField.new("readings[23] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_23", ftypes.UINT64, nil)
f.LIDAR_READING_readings_24 = ProtoField.new("readings[24] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_24", ftypes.UINT64, nil)
f.LIDAR_READING_readings_25 = ProtoField.new("readings[25] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_25", ftypes.UINT64, nil)
f.LIDAR_READING_readings_26 = ProtoField.new("readings[26] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_26", ftypes.UINT64, nil)
f.LIDAR_READING_readings_27 = ProtoField.new("readings[27] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_27", ftypes.UINT64, nil)
f.LIDAR_READING_readings_28 = ProtoField.new("readings[28] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_28", ftypes.UINT64, nil)
f.LIDAR_READING_readings_29 = ProtoField.new("readings[29] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_29", ftypes.UINT64, nil)
f.LIDAR_READING_readings_30 = ProtoField.new("readings[30] (uint64_t)", "mavlink_proto.LIDAR_READING_readings_30", ftypes.UINT64, nil)

f.COMPONENT_POWER_CONTROL_device = ProtoField.new("device (EOS_COMPONENT)", "mavlink_proto.COMPONENT_POWER_CONTROL_device", ftypes.UINT16, nil, base.HEX_DEC)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_LIDAR = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_LIDAR", "EOS_COMPONENT_LIDAR", 16, nil, 1)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_YAW_MOTOR = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_YAW_MOTOR", "EOS_COMPONENT_YAW_MOTOR", 16, nil, 2)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_PITCH_MOTOR = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_PITCH_MOTOR", "EOS_COMPONENT_PITCH_MOTOR", 16, nil, 4)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_GPS = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_GPS", "EOS_COMPONENT_GPS", 16, nil, 8)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_COMPASS = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_COMPASS", "EOS_COMPONENT_COMPASS", 16, nil, 16)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_MCU = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_MCU", "EOS_COMPONENT_MCU", 16, nil, 32)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_LED = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_LED", "EOS_COMPONENT_LED", 16, nil, 64)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_ACCEL = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_ACCEL", "EOS_COMPONENT_ACCEL", 16, nil, 128)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_POWER_SENSOR = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_POWER_SENSOR", "EOS_COMPONENT_POWER_SENSOR", 16, nil, 256)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_SERIAL_BRIDGE = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_SERIAL_BRIDGE", "EOS_COMPONENT_SERIAL_BRIDGE", 16, nil, 512)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_PORT_EXPANDER = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_PORT_EXPANDER", "EOS_COMPONENT_PORT_EXPANDER", 16, nil, 1024)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_FLASH = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_FLASH", "EOS_COMPONENT_FLASH", 16, nil, 2048)
f.COMPONENT_POWER_CONTROL_device_flagEOS_COMPONENT_ALL = ProtoField.bool("mavlink_proto.COMPONENT_POWER_CONTROL_device.EOS_COMPONENT_ALL", "EOS_COMPONENT_ALL", 16, nil, 4096)
f.COMPONENT_POWER_CONTROL_behavior = ProtoField.new("behavior (EOS_COMPONENT_POWER_BEHAVIOR)", "mavlink_proto.COMPONENT_POWER_CONTROL_behavior", ftypes.UINT8, enumEntryName.EOS_COMPONENT_POWER_BEHAVIOR)

f.SYSTEM_STATUS_state = ProtoField.new("state (EOS_STATE)", "mavlink_proto.SYSTEM_STATUS_state", ftypes.UINT8, enumEntryName.EOS_STATE)
f.SYSTEM_STATUS_power_status_bitmask = ProtoField.new("power_status_bitmask (EOS_COMPONENT)", "mavlink_proto.SYSTEM_STATUS_power_status_bitmask", ftypes.UINT16, nil, base.HEX_DEC)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_LIDAR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_LIDAR", "EOS_COMPONENT_LIDAR", 16, nil, 1)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_YAW_MOTOR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_YAW_MOTOR", "EOS_COMPONENT_YAW_MOTOR", 16, nil, 2)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_PITCH_MOTOR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_PITCH_MOTOR", "EOS_COMPONENT_PITCH_MOTOR", 16, nil, 4)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_GPS = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_GPS", "EOS_COMPONENT_GPS", 16, nil, 8)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_COMPASS = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_COMPASS", "EOS_COMPONENT_COMPASS", 16, nil, 16)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_MCU = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_MCU", "EOS_COMPONENT_MCU", 16, nil, 32)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_LED = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_LED", "EOS_COMPONENT_LED", 16, nil, 64)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_ACCEL = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_ACCEL", "EOS_COMPONENT_ACCEL", 16, nil, 128)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_POWER_SENSOR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_POWER_SENSOR", "EOS_COMPONENT_POWER_SENSOR", 16, nil, 256)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_SERIAL_BRIDGE = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_SERIAL_BRIDGE", "EOS_COMPONENT_SERIAL_BRIDGE", 16, nil, 512)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_PORT_EXPANDER = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_PORT_EXPANDER", "EOS_COMPONENT_PORT_EXPANDER", 16, nil, 1024)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_FLASH = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_FLASH", "EOS_COMPONENT_FLASH", 16, nil, 2048)
f.SYSTEM_STATUS_power_status_bitmask_flagEOS_COMPONENT_ALL = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_power_status_bitmask.EOS_COMPONENT_ALL", "EOS_COMPONENT_ALL", 16, nil, 4096)
f.SYSTEM_STATUS_health_status_bitmask = ProtoField.new("health_status_bitmask (EOS_COMPONENT)", "mavlink_proto.SYSTEM_STATUS_health_status_bitmask", ftypes.UINT16, nil, base.HEX_DEC)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_LIDAR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_LIDAR", "EOS_COMPONENT_LIDAR", 16, nil, 1)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_YAW_MOTOR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_YAW_MOTOR", "EOS_COMPONENT_YAW_MOTOR", 16, nil, 2)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_PITCH_MOTOR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_PITCH_MOTOR", "EOS_COMPONENT_PITCH_MOTOR", 16, nil, 4)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_GPS = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_GPS", "EOS_COMPONENT_GPS", 16, nil, 8)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_COMPASS = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_COMPASS", "EOS_COMPONENT_COMPASS", 16, nil, 16)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_MCU = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_MCU", "EOS_COMPONENT_MCU", 16, nil, 32)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_LED = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_LED", "EOS_COMPONENT_LED", 16, nil, 64)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_ACCEL = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_ACCEL", "EOS_COMPONENT_ACCEL", 16, nil, 128)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_POWER_SENSOR = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_POWER_SENSOR", "EOS_COMPONENT_POWER_SENSOR", 16, nil, 256)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_SERIAL_BRIDGE = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_SERIAL_BRIDGE", "EOS_COMPONENT_SERIAL_BRIDGE", 16, nil, 512)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_PORT_EXPANDER = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_PORT_EXPANDER", "EOS_COMPONENT_PORT_EXPANDER", 16, nil, 1024)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_FLASH = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_FLASH", "EOS_COMPONENT_FLASH", 16, nil, 2048)
f.SYSTEM_STATUS_health_status_bitmask_flagEOS_COMPONENT_ALL = ProtoField.bool("mavlink_proto.SYSTEM_STATUS_health_status_bitmask.EOS_COMPONENT_ALL", "EOS_COMPONENT_ALL", 16, nil, 4096)
f.SYSTEM_STATUS_uptime = ProtoField.new("uptime (uint16_t) [seconds]", "mavlink_proto.SYSTEM_STATUS_uptime", ftypes.UINT16, nil)

f.IDENTIFIER_particle_id = ProtoField.new("particle_id (char)", "mavlink_proto.IDENTIFIER_particle_id", ftypes.STRING, nil)
f.IDENTIFIER_local_ip_0 = ProtoField.new("local_ip[0] (uint8_t)", "mavlink_proto.IDENTIFIER_local_ip_0", ftypes.UINT8, nil)
f.IDENTIFIER_local_ip_1 = ProtoField.new("local_ip[1] (uint8_t)", "mavlink_proto.IDENTIFIER_local_ip_1", ftypes.UINT8, nil)
f.IDENTIFIER_local_ip_2 = ProtoField.new("local_ip[2] (uint8_t)", "mavlink_proto.IDENTIFIER_local_ip_2", ftypes.UINT8, nil)
f.IDENTIFIER_local_ip_3 = ProtoField.new("local_ip[3] (uint8_t)", "mavlink_proto.IDENTIFIER_local_ip_3", ftypes.UINT8, nil)
f.IDENTIFIER_mac_0 = ProtoField.new("mac[0] (uint8_t)", "mavlink_proto.IDENTIFIER_mac_0", ftypes.UINT8, nil)
f.IDENTIFIER_mac_1 = ProtoField.new("mac[1] (uint8_t)", "mavlink_proto.IDENTIFIER_mac_1", ftypes.UINT8, nil)
f.IDENTIFIER_mac_2 = ProtoField.new("mac[2] (uint8_t)", "mavlink_proto.IDENTIFIER_mac_2", ftypes.UINT8, nil)
f.IDENTIFIER_mac_3 = ProtoField.new("mac[3] (uint8_t)", "mavlink_proto.IDENTIFIER_mac_3", ftypes.UINT8, nil)
f.IDENTIFIER_mac_4 = ProtoField.new("mac[4] (uint8_t)", "mavlink_proto.IDENTIFIER_mac_4", ftypes.UINT8, nil)
f.IDENTIFIER_mac_5 = ProtoField.new("mac[5] (uint8_t)", "mavlink_proto.IDENTIFIER_mac_5", ftypes.UINT8, nil)
f.IDENTIFIER_name = ProtoField.new("name (char)", "mavlink_proto.IDENTIFIER_name", ftypes.STRING, nil)

f.COMPONENT_HEALTH_TEST_component = ProtoField.new("component (EOS_COMPONENT)", "mavlink_proto.COMPONENT_HEALTH_TEST_component", ftypes.UINT32, nil, base.HEX_DEC)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_LIDAR = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_LIDAR", "EOS_COMPONENT_LIDAR", 16, nil, 1)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_YAW_MOTOR = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_YAW_MOTOR", "EOS_COMPONENT_YAW_MOTOR", 16, nil, 2)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_PITCH_MOTOR = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_PITCH_MOTOR", "EOS_COMPONENT_PITCH_MOTOR", 16, nil, 4)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_GPS = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_GPS", "EOS_COMPONENT_GPS", 16, nil, 8)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_COMPASS = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_COMPASS", "EOS_COMPONENT_COMPASS", 16, nil, 16)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_MCU = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_MCU", "EOS_COMPONENT_MCU", 16, nil, 32)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_LED = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_LED", "EOS_COMPONENT_LED", 16, nil, 64)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_ACCEL = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_ACCEL", "EOS_COMPONENT_ACCEL", 16, nil, 128)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_POWER_SENSOR = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_POWER_SENSOR", "EOS_COMPONENT_POWER_SENSOR", 16, nil, 256)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_SERIAL_BRIDGE = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_SERIAL_BRIDGE", "EOS_COMPONENT_SERIAL_BRIDGE", 16, nil, 512)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_PORT_EXPANDER = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_PORT_EXPANDER", "EOS_COMPONENT_PORT_EXPANDER", 16, nil, 1024)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_FLASH = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_FLASH", "EOS_COMPONENT_FLASH", 16, nil, 2048)
f.COMPONENT_HEALTH_TEST_component_flagEOS_COMPONENT_ALL = ProtoField.bool("mavlink_proto.COMPONENT_HEALTH_TEST_component.EOS_COMPONENT_ALL", "EOS_COMPONENT_ALL", 16, nil, 4096)

f.SCAN_SETTINGS_yaw_start = ProtoField.new("yaw_start (float) [deg]", "mavlink_proto.SCAN_SETTINGS_yaw_start", ftypes.FLOAT, nil)
f.SCAN_SETTINGS_yaw_stop = ProtoField.new("yaw_stop (float) [deg]", "mavlink_proto.SCAN_SETTINGS_yaw_stop", ftypes.FLOAT, nil)
f.SCAN_SETTINGS_pitch_start = ProtoField.new("pitch_start (float) [deg]", "mavlink_proto.SCAN_SETTINGS_pitch_start", ftypes.FLOAT, nil)
f.SCAN_SETTINGS_pitch_stop = ProtoField.new("pitch_stop (float) [deg]", "mavlink_proto.SCAN_SETTINGS_pitch_stop", ftypes.FLOAT, nil)
f.SCAN_SETTINGS_point_spacing = ProtoField.new("point_spacing (float) [deg]", "mavlink_proto.SCAN_SETTINGS_point_spacing", ftypes.FLOAT, nil)
f.SCAN_SETTINGS_scan_speed = ProtoField.new("scan_speed (float) [rpm]", "mavlink_proto.SCAN_SETTINGS_scan_speed", ftypes.FLOAT, nil)

f.SCAN_STATUS_start_time_unix = ProtoField.new("start_time_unix (uint32_t)", "mavlink_proto.SCAN_STATUS_start_time_unix", ftypes.UINT32, nil)
f.SCAN_STATUS_scan_completion = ProtoField.new("scan_completion (uint8_t) [%]", "mavlink_proto.SCAN_STATUS_scan_completion", ftypes.UINT8, nil)
f.SCAN_STATUS_time_remaining = ProtoField.new("time_remaining (uint16_t) [seconds]", "mavlink_proto.SCAN_STATUS_time_remaining", ftypes.UINT16, nil)

f.REMOTE_SERVER_SETTINGS_server_enable = ProtoField.new("server_enable (uint8_t)", "mavlink_proto.REMOTE_SERVER_SETTINGS_server_enable", ftypes.UINT8, nil)
f.REMOTE_SERVER_SETTINGS_post_server = ProtoField.new("post_server (char)", "mavlink_proto.REMOTE_SERVER_SETTINGS_post_server", ftypes.STRING, nil)
f.REMOTE_SERVER_SETTINGS_post_uri = ProtoField.new("post_uri (char)", "mavlink_proto.REMOTE_SERVER_SETTINGS_post_uri", ftypes.STRING, nil)
f.REMOTE_SERVER_SETTINGS_post_port = ProtoField.new("post_port (uint16_t)", "mavlink_proto.REMOTE_SERVER_SETTINGS_post_port", ftypes.UINT16, nil)
f.REMOTE_SERVER_SETTINGS_ftp_enable = ProtoField.new("ftp_enable (uint8_t)", "mavlink_proto.REMOTE_SERVER_SETTINGS_ftp_enable", ftypes.UINT8, nil)
f.REMOTE_SERVER_SETTINGS_ftp_server = ProtoField.new("ftp_server (char)", "mavlink_proto.REMOTE_SERVER_SETTINGS_ftp_server", ftypes.STRING, nil)
f.REMOTE_SERVER_SETTINGS_ftp_username = ProtoField.new("ftp_username (char)", "mavlink_proto.REMOTE_SERVER_SETTINGS_ftp_username", ftypes.STRING, nil)
f.REMOTE_SERVER_SETTINGS_ftp_password = ProtoField.new("ftp_password (char)", "mavlink_proto.REMOTE_SERVER_SETTINGS_ftp_password", ftypes.STRING, nil)
f.REMOTE_SERVER_SETTINGS_ftp_port = ProtoField.new("ftp_port (uint16_t)", "mavlink_proto.REMOTE_SERVER_SETTINGS_ftp_port", ftypes.UINT16, nil)

f.POWER_INFORMATION_instant_current = ProtoField.new("instant_current (uint16_t) [mA]", "mavlink_proto.POWER_INFORMATION_instant_current", ftypes.UINT16, nil)
f.POWER_INFORMATION_instant_voltage = ProtoField.new("instant_voltage (uint16_t) [mV]", "mavlink_proto.POWER_INFORMATION_instant_voltage", ftypes.UINT16, nil)
f.POWER_INFORMATION_instant_power = ProtoField.new("instant_power (uint16_t) [mW]", "mavlink_proto.POWER_INFORMATION_instant_power", ftypes.UINT16, nil)
f.POWER_INFORMATION_energy_consumed = ProtoField.new("energy_consumed (uint32_t) [J]", "mavlink_proto.POWER_INFORMATION_energy_consumed", ftypes.UINT32, nil)

f.WIFI_INFORMATION_ssid = ProtoField.new("ssid (char)", "mavlink_proto.WIFI_INFORMATION_ssid", ftypes.STRING, nil)
f.WIFI_INFORMATION_bssid_0 = ProtoField.new("bssid[0] (uint8_t)", "mavlink_proto.WIFI_INFORMATION_bssid_0", ftypes.UINT8, nil)
f.WIFI_INFORMATION_bssid_1 = ProtoField.new("bssid[1] (uint8_t)", "mavlink_proto.WIFI_INFORMATION_bssid_1", ftypes.UINT8, nil)
f.WIFI_INFORMATION_bssid_2 = ProtoField.new("bssid[2] (uint8_t)", "mavlink_proto.WIFI_INFORMATION_bssid_2", ftypes.UINT8, nil)
f.WIFI_INFORMATION_bssid_3 = ProtoField.new("bssid[3] (uint8_t)", "mavlink_proto.WIFI_INFORMATION_bssid_3", ftypes.UINT8, nil)
f.WIFI_INFORMATION_bssid_4 = ProtoField.new("bssid[4] (uint8_t)", "mavlink_proto.WIFI_INFORMATION_bssid_4", ftypes.UINT8, nil)
f.WIFI_INFORMATION_bssid_5 = ProtoField.new("bssid[5] (uint8_t)", "mavlink_proto.WIFI_INFORMATION_bssid_5", ftypes.UINT8, nil)
f.WIFI_INFORMATION_rssi = ProtoField.new("rssi (uint8_t)", "mavlink_proto.WIFI_INFORMATION_rssi", ftypes.UINT8, nil)
f.WIFI_INFORMATION_rssi_percent = ProtoField.new("rssi_percent (uint8_t)", "mavlink_proto.WIFI_INFORMATION_rssi_percent", ftypes.UINT8, nil)
f.WIFI_INFORMATION_snr = ProtoField.new("snr (uint8_t)", "mavlink_proto.WIFI_INFORMATION_snr", ftypes.UINT8, nil)
f.WIFI_INFORMATION_snr_percent = ProtoField.new("snr_percent (uint8_t)", "mavlink_proto.WIFI_INFORMATION_snr_percent", ftypes.UINT8, nil)

f.UPLOAD_STATUS_start_time_unix = ProtoField.new("start_time_unix (uint32_t)", "mavlink_proto.UPLOAD_STATUS_start_time_unix", ftypes.UINT32, nil)
f.UPLOAD_STATUS_upload_completion = ProtoField.new("upload_completion (uint8_t) [%]", "mavlink_proto.UPLOAD_STATUS_upload_completion", ftypes.UINT8, nil)
f.UPLOAD_STATUS_bytes_uploaded = ProtoField.new("bytes_uploaded (uint32_t)", "mavlink_proto.UPLOAD_STATUS_bytes_uploaded", ftypes.UINT32, nil)
f.UPLOAD_STATUS_upload_size = ProtoField.new("upload_size (uint32_t) [bytes]", "mavlink_proto.UPLOAD_STATUS_upload_size", ftypes.UINT32, nil)
f.UPLOAD_STATUS_upload_rate = ProtoField.new("upload_rate (uint16_t) [Bps]", "mavlink_proto.UPLOAD_STATUS_upload_rate", ftypes.UINT16, nil)
f.UPLOAD_STATUS_time_remaining = ProtoField.new("time_remaining (uint16_t) [seconds]", "mavlink_proto.UPLOAD_STATUS_time_remaining", ftypes.UINT16, nil)

f.MOTOR_CONTROL_target = ProtoField.new("target (EOS_COMPONENT)", "mavlink_proto.MOTOR_CONTROL_target", ftypes.UINT8, nil, base.HEX_DEC)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_LIDAR = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_LIDAR", "EOS_COMPONENT_LIDAR", 16, nil, 1)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_YAW_MOTOR = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_YAW_MOTOR", "EOS_COMPONENT_YAW_MOTOR", 16, nil, 2)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_PITCH_MOTOR = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_PITCH_MOTOR", "EOS_COMPONENT_PITCH_MOTOR", 16, nil, 4)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_GPS = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_GPS", "EOS_COMPONENT_GPS", 16, nil, 8)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_COMPASS = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_COMPASS", "EOS_COMPONENT_COMPASS", 16, nil, 16)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_MCU = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_MCU", "EOS_COMPONENT_MCU", 16, nil, 32)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_LED = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_LED", "EOS_COMPONENT_LED", 16, nil, 64)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_ACCEL = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_ACCEL", "EOS_COMPONENT_ACCEL", 16, nil, 128)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_POWER_SENSOR = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_POWER_SENSOR", "EOS_COMPONENT_POWER_SENSOR", 16, nil, 256)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_SERIAL_BRIDGE = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_SERIAL_BRIDGE", "EOS_COMPONENT_SERIAL_BRIDGE", 16, nil, 512)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_PORT_EXPANDER = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_PORT_EXPANDER", "EOS_COMPONENT_PORT_EXPANDER", 16, nil, 1024)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_FLASH = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_FLASH", "EOS_COMPONENT_FLASH", 16, nil, 2048)
f.MOTOR_CONTROL_target_flagEOS_COMPONENT_ALL = ProtoField.bool("mavlink_proto.MOTOR_CONTROL_target.EOS_COMPONENT_ALL", "EOS_COMPONENT_ALL", 16, nil, 4096)
f.MOTOR_CONTROL_behavior = ProtoField.new("behavior (MOTOR_BEHAVIOR)", "mavlink_proto.MOTOR_CONTROL_behavior", ftypes.UINT8, enumEntryName.MOTOR_BEHAVIOR)
f.MOTOR_CONTROL_motor_rpm = ProtoField.new("motor_rpm (float)", "mavlink_proto.MOTOR_CONTROL_motor_rpm", ftypes.FLOAT, nil)
f.MOTOR_CONTROL_target_angle = ProtoField.new("target_angle (float)", "mavlink_proto.MOTOR_CONTROL_target_angle", ftypes.FLOAT, nil)
f.MOTOR_CONTROL_device_rpm = ProtoField.new("device_rpm (float)", "mavlink_proto.MOTOR_CONTROL_device_rpm", ftypes.FLOAT, nil)
f.MOTOR_CONTROL_steps_count = ProtoField.new("steps_count (int16_t)", "mavlink_proto.MOTOR_CONTROL_steps_count", ftypes.INT16, nil)
f.MOTOR_CONTROL_vactual = ProtoField.new("vactual (int16_t)", "mavlink_proto.MOTOR_CONTROL_vactual", ftypes.INT16, nil)

f.MOTOR_SETTINGS_motor = ProtoField.new("motor (EOS_COMPONENT)", "mavlink_proto.MOTOR_SETTINGS_motor", ftypes.UINT8, nil, base.HEX_DEC)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_LIDAR = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_LIDAR", "EOS_COMPONENT_LIDAR", 16, nil, 1)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_YAW_MOTOR = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_YAW_MOTOR", "EOS_COMPONENT_YAW_MOTOR", 16, nil, 2)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_PITCH_MOTOR = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_PITCH_MOTOR", "EOS_COMPONENT_PITCH_MOTOR", 16, nil, 4)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_GPS = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_GPS", "EOS_COMPONENT_GPS", 16, nil, 8)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_COMPASS = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_COMPASS", "EOS_COMPONENT_COMPASS", 16, nil, 16)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_MCU = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_MCU", "EOS_COMPONENT_MCU", 16, nil, 32)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_LED = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_LED", "EOS_COMPONENT_LED", 16, nil, 64)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_ACCEL = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_ACCEL", "EOS_COMPONENT_ACCEL", 16, nil, 128)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_POWER_SENSOR = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_POWER_SENSOR", "EOS_COMPONENT_POWER_SENSOR", 16, nil, 256)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_SERIAL_BRIDGE = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_SERIAL_BRIDGE", "EOS_COMPONENT_SERIAL_BRIDGE", 16, nil, 512)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_PORT_EXPANDER = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_PORT_EXPANDER", "EOS_COMPONENT_PORT_EXPANDER", 16, nil, 1024)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_FLASH = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_FLASH", "EOS_COMPONENT_FLASH", 16, nil, 2048)
f.MOTOR_SETTINGS_motor_flagEOS_COMPONENT_ALL = ProtoField.bool("mavlink_proto.MOTOR_SETTINGS_motor.EOS_COMPONENT_ALL", "EOS_COMPONENT_ALL", 16, nil, 4096)
f.MOTOR_SETTINGS_current = ProtoField.new("current (uint16_t)", "mavlink_proto.MOTOR_SETTINGS_current", ftypes.UINT16, nil)
f.MOTOR_SETTINGS_microsteps = ProtoField.new("microsteps (uint8_t)", "mavlink_proto.MOTOR_SETTINGS_microsteps", ftypes.UINT8, nil)
f.MOTOR_SETTINGS_gearing_ratio = ProtoField.new("gearing_ratio (float)", "mavlink_proto.MOTOR_SETTINGS_gearing_ratio", ftypes.FLOAT, nil)
f.MOTOR_SETTINGS_spread_cycle = ProtoField.new("spread_cycle (uint8_t)", "mavlink_proto.MOTOR_SETTINGS_spread_cycle", ftypes.UINT8, nil)
f.MOTOR_SETTINGS_pwm_autoscale = ProtoField.new("pwm_autoscale (uint8_t)", "mavlink_proto.MOTOR_SETTINGS_pwm_autoscale", ftypes.UINT8, nil)
f.MOTOR_SETTINGS_pwm_autograd = ProtoField.new("pwm_autograd (uint8_t)", "mavlink_proto.MOTOR_SETTINGS_pwm_autograd", ftypes.UINT8, nil)
f.MOTOR_SETTINGS_min_steps_to_next_index = ProtoField.new("min_steps_to_next_index (uint8_t)", "mavlink_proto.MOTOR_SETTINGS_min_steps_to_next_index", ftypes.UINT8, nil)
f.MOTOR_SETTINGS_home_offset_steps = ProtoField.new("home_offset_steps (int16_t)", "mavlink_proto.MOTOR_SETTINGS_home_offset_steps", ftypes.INT16, nil)
f.MOTOR_SETTINGS_steps_to_next_index = ProtoField.new("steps_to_next_index (uint16_t)", "mavlink_proto.MOTOR_SETTINGS_steps_to_next_index", ftypes.UINT16, nil)
f.MOTOR_SETTINGS_usteps_rate = ProtoField.new("usteps_rate (float) [Hz]", "mavlink_proto.MOTOR_SETTINGS_usteps_rate", ftypes.FLOAT, nil)
f.MOTOR_SETTINGS_ustep_angle = ProtoField.new("ustep_angle (float) [deg]", "mavlink_proto.MOTOR_SETTINGS_ustep_angle", ftypes.FLOAT, nil)

f.MOTOR_STATUS_motor = ProtoField.new("motor (EOS_COMPONENT)", "mavlink_proto.MOTOR_STATUS_motor", ftypes.UINT8, nil, base.HEX_DEC)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_LIDAR = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_LIDAR", "EOS_COMPONENT_LIDAR", 16, nil, 1)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_YAW_MOTOR = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_YAW_MOTOR", "EOS_COMPONENT_YAW_MOTOR", 16, nil, 2)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_PITCH_MOTOR = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_PITCH_MOTOR", "EOS_COMPONENT_PITCH_MOTOR", 16, nil, 4)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_GPS = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_GPS", "EOS_COMPONENT_GPS", 16, nil, 8)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_COMPASS = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_COMPASS", "EOS_COMPONENT_COMPASS", 16, nil, 16)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_MCU = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_MCU", "EOS_COMPONENT_MCU", 16, nil, 32)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_LED = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_LED", "EOS_COMPONENT_LED", 16, nil, 64)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_ACCEL = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_ACCEL", "EOS_COMPONENT_ACCEL", 16, nil, 128)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_POWER_SENSOR = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_POWER_SENSOR", "EOS_COMPONENT_POWER_SENSOR", 16, nil, 256)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_SERIAL_BRIDGE = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_SERIAL_BRIDGE", "EOS_COMPONENT_SERIAL_BRIDGE", 16, nil, 512)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_PORT_EXPANDER = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_PORT_EXPANDER", "EOS_COMPONENT_PORT_EXPANDER", 16, nil, 1024)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_FLASH = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_FLASH", "EOS_COMPONENT_FLASH", 16, nil, 2048)
f.MOTOR_STATUS_motor_flagEOS_COMPONENT_ALL = ProtoField.bool("mavlink_proto.MOTOR_STATUS_motor.EOS_COMPONENT_ALL", "EOS_COMPONENT_ALL", 16, nil, 4096)
f.MOTOR_STATUS_enabled = ProtoField.new("enabled (uint8_t)", "mavlink_proto.MOTOR_STATUS_enabled", ftypes.UINT8, nil)
f.MOTOR_STATUS_homed = ProtoField.new("homed (uint8_t)", "mavlink_proto.MOTOR_STATUS_homed", ftypes.UINT8, nil)
f.MOTOR_STATUS_motor_rpm = ProtoField.new("motor_rpm (float)", "mavlink_proto.MOTOR_STATUS_motor_rpm", ftypes.FLOAT, nil)
f.MOTOR_STATUS_device_rpm = ProtoField.new("device_rpm (float)", "mavlink_proto.MOTOR_STATUS_device_rpm", ftypes.FLOAT, nil)
f.MOTOR_STATUS_measured_rpm = ProtoField.new("measured_rpm (float)", "mavlink_proto.MOTOR_STATUS_measured_rpm", ftypes.FLOAT, nil)
f.MOTOR_STATUS_vactual = ProtoField.new("vactual (uint16_t)", "mavlink_proto.MOTOR_STATUS_vactual", ftypes.UINT16, nil)
f.MOTOR_STATUS_steps_count = ProtoField.new("steps_count (int16_t)", "mavlink_proto.MOTOR_STATUS_steps_count", ftypes.INT16, nil)
f.MOTOR_STATUS_current_angle = ProtoField.new("current_angle (float)", "mavlink_proto.MOTOR_STATUS_current_angle", ftypes.FLOAT, nil)

f.HEARTBEAT_type = ProtoField.new("type (MAV_TYPE)", "mavlink_proto.HEARTBEAT_type", ftypes.UINT8, enumEntryName.MAV_TYPE)
f.HEARTBEAT_autopilot = ProtoField.new("autopilot (MAV_AUTOPILOT)", "mavlink_proto.HEARTBEAT_autopilot", ftypes.UINT8, enumEntryName.MAV_AUTOPILOT)
f.HEARTBEAT_base_mode = ProtoField.new("base_mode (MAV_MODE_FLAG)", "mavlink_proto.HEARTBEAT_base_mode", ftypes.UINT8, nil, base.HEX_DEC)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_CUSTOM_MODE_ENABLED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED", "MAV_MODE_FLAG_CUSTOM_MODE_ENABLED", 8, nil, 1)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_TEST_ENABLED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_TEST_ENABLED", "MAV_MODE_FLAG_TEST_ENABLED", 8, nil, 2)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_AUTO_ENABLED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_AUTO_ENABLED", "MAV_MODE_FLAG_AUTO_ENABLED", 8, nil, 4)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_GUIDED_ENABLED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_GUIDED_ENABLED", "MAV_MODE_FLAG_GUIDED_ENABLED", 8, nil, 8)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_STABILIZE_ENABLED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_STABILIZE_ENABLED", "MAV_MODE_FLAG_STABILIZE_ENABLED", 8, nil, 16)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_HIL_ENABLED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_HIL_ENABLED", "MAV_MODE_FLAG_HIL_ENABLED", 8, nil, 32)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_MANUAL_INPUT_ENABLED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_MANUAL_INPUT_ENABLED", "MAV_MODE_FLAG_MANUAL_INPUT_ENABLED", 8, nil, 64)
f.HEARTBEAT_base_mode_flagMAV_MODE_FLAG_SAFETY_ARMED = ProtoField.bool("mavlink_proto.HEARTBEAT_base_mode.MAV_MODE_FLAG_SAFETY_ARMED", "MAV_MODE_FLAG_SAFETY_ARMED", 8, nil, 128)
f.HEARTBEAT_custom_mode = ProtoField.new("custom_mode (uint32_t)", "mavlink_proto.HEARTBEAT_custom_mode", ftypes.UINT32, nil)
f.HEARTBEAT_system_status = ProtoField.new("system_status (MAV_STATE)", "mavlink_proto.HEARTBEAT_system_status", ftypes.UINT8, enumEntryName.MAV_STATE)
f.HEARTBEAT_mavlink_version = ProtoField.new("mavlink_version (uint8_t)", "mavlink_proto.HEARTBEAT_mavlink_version", ftypes.UINT8, nil)

f.CHANGE_OPERATOR_CONTROL_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.CHANGE_OPERATOR_CONTROL_target_system", ftypes.UINT8, nil)
f.CHANGE_OPERATOR_CONTROL_control_request = ProtoField.new("control_request (uint8_t)", "mavlink_proto.CHANGE_OPERATOR_CONTROL_control_request", ftypes.UINT8, nil)
f.CHANGE_OPERATOR_CONTROL_version = ProtoField.new("version (uint8_t) [rad]", "mavlink_proto.CHANGE_OPERATOR_CONTROL_version", ftypes.UINT8, nil)
f.CHANGE_OPERATOR_CONTROL_passkey = ProtoField.new("passkey (char)", "mavlink_proto.CHANGE_OPERATOR_CONTROL_passkey", ftypes.STRING, nil)

f.CHANGE_OPERATOR_CONTROL_ACK_gcs_system_id = ProtoField.new("gcs_system_id (uint8_t)", "mavlink_proto.CHANGE_OPERATOR_CONTROL_ACK_gcs_system_id", ftypes.UINT8, nil)
f.CHANGE_OPERATOR_CONTROL_ACK_control_request = ProtoField.new("control_request (uint8_t)", "mavlink_proto.CHANGE_OPERATOR_CONTROL_ACK_control_request", ftypes.UINT8, nil)
f.CHANGE_OPERATOR_CONTROL_ACK_ack = ProtoField.new("ack (uint8_t)", "mavlink_proto.CHANGE_OPERATOR_CONTROL_ACK_ack", ftypes.UINT8, nil)

f.PROTOCOL_VERSION_version = ProtoField.new("version (uint16_t)", "mavlink_proto.PROTOCOL_VERSION_version", ftypes.UINT16, nil)
f.PROTOCOL_VERSION_min_version = ProtoField.new("min_version (uint16_t)", "mavlink_proto.PROTOCOL_VERSION_min_version", ftypes.UINT16, nil)
f.PROTOCOL_VERSION_max_version = ProtoField.new("max_version (uint16_t)", "mavlink_proto.PROTOCOL_VERSION_max_version", ftypes.UINT16, nil)
f.PROTOCOL_VERSION_spec_version_hash_0 = ProtoField.new("spec_version_hash[0] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_0", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_spec_version_hash_1 = ProtoField.new("spec_version_hash[1] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_1", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_spec_version_hash_2 = ProtoField.new("spec_version_hash[2] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_2", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_spec_version_hash_3 = ProtoField.new("spec_version_hash[3] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_3", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_spec_version_hash_4 = ProtoField.new("spec_version_hash[4] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_4", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_spec_version_hash_5 = ProtoField.new("spec_version_hash[5] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_5", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_spec_version_hash_6 = ProtoField.new("spec_version_hash[6] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_6", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_spec_version_hash_7 = ProtoField.new("spec_version_hash[7] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_spec_version_hash_7", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_0 = ProtoField.new("library_version_hash[0] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_0", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_1 = ProtoField.new("library_version_hash[1] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_1", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_2 = ProtoField.new("library_version_hash[2] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_2", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_3 = ProtoField.new("library_version_hash[3] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_3", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_4 = ProtoField.new("library_version_hash[4] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_4", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_5 = ProtoField.new("library_version_hash[5] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_5", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_6 = ProtoField.new("library_version_hash[6] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_6", ftypes.UINT8, nil)
f.PROTOCOL_VERSION_library_version_hash_7 = ProtoField.new("library_version_hash[7] (uint8_t)", "mavlink_proto.PROTOCOL_VERSION_library_version_hash_7", ftypes.UINT8, nil)

f.GPS_RAW_INT_time_usec = ProtoField.new("time_usec (uint64_t) [us]", "mavlink_proto.GPS_RAW_INT_time_usec", ftypes.UINT64, nil)
f.GPS_RAW_INT_fix_type = ProtoField.new("fix_type (GPS_FIX_TYPE)", "mavlink_proto.GPS_RAW_INT_fix_type", ftypes.UINT8, enumEntryName.GPS_FIX_TYPE)
f.GPS_RAW_INT_lat = ProtoField.new("lat (int32_t) [degE7]", "mavlink_proto.GPS_RAW_INT_lat", ftypes.INT32, nil)
f.GPS_RAW_INT_lon = ProtoField.new("lon (int32_t) [degE7]", "mavlink_proto.GPS_RAW_INT_lon", ftypes.INT32, nil)
f.GPS_RAW_INT_alt = ProtoField.new("alt (int32_t) [mm]", "mavlink_proto.GPS_RAW_INT_alt", ftypes.INT32, nil)
f.GPS_RAW_INT_eph = ProtoField.new("eph (uint16_t*1E-2)", "mavlink_proto.GPS_RAW_INT_eph", ftypes.DOUBLE, nil)
f.GPS_RAW_INT_epv = ProtoField.new("epv (uint16_t*1E-2)", "mavlink_proto.GPS_RAW_INT_epv", ftypes.DOUBLE, nil)
f.GPS_RAW_INT_vel = ProtoField.new("vel (uint16_t) [cm/s]", "mavlink_proto.GPS_RAW_INT_vel", ftypes.UINT16, nil)
f.GPS_RAW_INT_cog = ProtoField.new("cog (uint16_t) [cdeg]", "mavlink_proto.GPS_RAW_INT_cog", ftypes.UINT16, nil)
f.GPS_RAW_INT_satellites_visible = ProtoField.new("satellites_visible (uint8_t)", "mavlink_proto.GPS_RAW_INT_satellites_visible", ftypes.UINT8, nil)
f.GPS_RAW_INT_alt_ellipsoid = ProtoField.new("alt_ellipsoid (int32_t) [mm]", "mavlink_proto.GPS_RAW_INT_alt_ellipsoid", ftypes.INT32, nil)
f.GPS_RAW_INT_h_acc = ProtoField.new("h_acc (uint32_t) [mm]", "mavlink_proto.GPS_RAW_INT_h_acc", ftypes.UINT32, nil)
f.GPS_RAW_INT_v_acc = ProtoField.new("v_acc (uint32_t) [mm]", "mavlink_proto.GPS_RAW_INT_v_acc", ftypes.UINT32, nil)
f.GPS_RAW_INT_vel_acc = ProtoField.new("vel_acc (uint32_t) [mm]", "mavlink_proto.GPS_RAW_INT_vel_acc", ftypes.UINT32, nil)
f.GPS_RAW_INT_hdg_acc = ProtoField.new("hdg_acc (uint32_t) [degE5]", "mavlink_proto.GPS_RAW_INT_hdg_acc", ftypes.UINT32, nil)
f.GPS_RAW_INT_yaw = ProtoField.new("yaw (uint16_t) [cdeg]", "mavlink_proto.GPS_RAW_INT_yaw", ftypes.UINT16, nil)

f.ATTITUDE_time_boot_ms = ProtoField.new("time_boot_ms (uint32_t) [ms]", "mavlink_proto.ATTITUDE_time_boot_ms", ftypes.UINT32, nil)
f.ATTITUDE_roll = ProtoField.new("roll (float) [rad]", "mavlink_proto.ATTITUDE_roll", ftypes.FLOAT, nil)
f.ATTITUDE_pitch = ProtoField.new("pitch (float) [rad]", "mavlink_proto.ATTITUDE_pitch", ftypes.FLOAT, nil)
f.ATTITUDE_yaw = ProtoField.new("yaw (float) [rad]", "mavlink_proto.ATTITUDE_yaw", ftypes.FLOAT, nil)
f.ATTITUDE_rollspeed = ProtoField.new("rollspeed (float) [rad/s]", "mavlink_proto.ATTITUDE_rollspeed", ftypes.FLOAT, nil)
f.ATTITUDE_pitchspeed = ProtoField.new("pitchspeed (float) [rad/s]", "mavlink_proto.ATTITUDE_pitchspeed", ftypes.FLOAT, nil)
f.ATTITUDE_yawspeed = ProtoField.new("yawspeed (float) [rad/s]", "mavlink_proto.ATTITUDE_yawspeed", ftypes.FLOAT, nil)
f.ATTITUDE_temp = ProtoField.new("temp (float) [degreesC]", "mavlink_proto.ATTITUDE_temp", ftypes.FLOAT, nil)

f.MISSION_ITEM_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.MISSION_ITEM_target_system", ftypes.UINT8, nil)
f.MISSION_ITEM_target_component = ProtoField.new("target_component (uint8_t)", "mavlink_proto.MISSION_ITEM_target_component", ftypes.UINT8, nil)
f.MISSION_ITEM_seq = ProtoField.new("seq (uint16_t)", "mavlink_proto.MISSION_ITEM_seq", ftypes.UINT16, nil)
f.MISSION_ITEM_frame = ProtoField.new("frame (MAV_FRAME)", "mavlink_proto.MISSION_ITEM_frame", ftypes.UINT8, enumEntryName.MAV_FRAME)
f.MISSION_ITEM_command = ProtoField.new("command (MAV_CMD)", "mavlink_proto.MISSION_ITEM_command", ftypes.UINT16, enumEntryName.MAV_CMD)
f.MISSION_ITEM_current = ProtoField.new("current (uint8_t)", "mavlink_proto.MISSION_ITEM_current", ftypes.UINT8, nil)
f.MISSION_ITEM_autocontinue = ProtoField.new("autocontinue (uint8_t)", "mavlink_proto.MISSION_ITEM_autocontinue", ftypes.UINT8, nil)
f.MISSION_ITEM_param1 = ProtoField.new("param1 (float)", "mavlink_proto.MISSION_ITEM_param1", ftypes.FLOAT, nil)
f.MISSION_ITEM_param2 = ProtoField.new("param2 (float)", "mavlink_proto.MISSION_ITEM_param2", ftypes.FLOAT, nil)
f.MISSION_ITEM_param3 = ProtoField.new("param3 (float)", "mavlink_proto.MISSION_ITEM_param3", ftypes.FLOAT, nil)
f.MISSION_ITEM_param4 = ProtoField.new("param4 (float)", "mavlink_proto.MISSION_ITEM_param4", ftypes.FLOAT, nil)
f.MISSION_ITEM_x = ProtoField.new("x (float)", "mavlink_proto.MISSION_ITEM_x", ftypes.FLOAT, nil)
f.MISSION_ITEM_y = ProtoField.new("y (float)", "mavlink_proto.MISSION_ITEM_y", ftypes.FLOAT, nil)
f.MISSION_ITEM_z = ProtoField.new("z (float)", "mavlink_proto.MISSION_ITEM_z", ftypes.FLOAT, nil)
f.MISSION_ITEM_mission_type = ProtoField.new("mission_type (MAV_MISSION_TYPE)", "mavlink_proto.MISSION_ITEM_mission_type", ftypes.UINT8, enumEntryName.MAV_MISSION_TYPE)

f.COMMAND_INT_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.COMMAND_INT_target_system", ftypes.UINT8, nil)
f.COMMAND_INT_target_component = ProtoField.new("target_component (uint8_t)", "mavlink_proto.COMMAND_INT_target_component", ftypes.UINT8, nil)
f.COMMAND_INT_frame = ProtoField.new("frame (MAV_FRAME)", "mavlink_proto.COMMAND_INT_frame", ftypes.UINT8, enumEntryName.MAV_FRAME)
f.COMMAND_INT_command = ProtoField.new("command (MAV_CMD)", "mavlink_proto.COMMAND_INT_command", ftypes.UINT16, enumEntryName.MAV_CMD)
f.COMMAND_INT_current = ProtoField.new("current (uint8_t)", "mavlink_proto.COMMAND_INT_current", ftypes.UINT8, nil)
f.COMMAND_INT_autocontinue = ProtoField.new("autocontinue (uint8_t)", "mavlink_proto.COMMAND_INT_autocontinue", ftypes.UINT8, nil)
f.COMMAND_INT_param1 = ProtoField.new("param1 (float)", "mavlink_proto.COMMAND_INT_param1", ftypes.FLOAT, nil)
f.COMMAND_INT_param2 = ProtoField.new("param2 (float)", "mavlink_proto.COMMAND_INT_param2", ftypes.FLOAT, nil)
f.COMMAND_INT_param3 = ProtoField.new("param3 (float)", "mavlink_proto.COMMAND_INT_param3", ftypes.FLOAT, nil)
f.COMMAND_INT_param4 = ProtoField.new("param4 (float)", "mavlink_proto.COMMAND_INT_param4", ftypes.FLOAT, nil)
f.COMMAND_INT_x = ProtoField.new("x (int32_t)", "mavlink_proto.COMMAND_INT_x", ftypes.INT32, nil)
f.COMMAND_INT_y = ProtoField.new("y (int32_t)", "mavlink_proto.COMMAND_INT_y", ftypes.INT32, nil)
f.COMMAND_INT_z = ProtoField.new("z (float)", "mavlink_proto.COMMAND_INT_z", ftypes.FLOAT, nil)

f.COMMAND_LONG_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.COMMAND_LONG_target_system", ftypes.UINT8, nil)
f.COMMAND_LONG_target_component = ProtoField.new("target_component (uint8_t)", "mavlink_proto.COMMAND_LONG_target_component", ftypes.UINT8, nil)
f.COMMAND_LONG_command = ProtoField.new("command (MAV_CMD)", "mavlink_proto.COMMAND_LONG_command", ftypes.UINT16, enumEntryName.MAV_CMD)
f.COMMAND_LONG_confirmation = ProtoField.new("confirmation (uint8_t)", "mavlink_proto.COMMAND_LONG_confirmation", ftypes.UINT8, nil)
f.COMMAND_LONG_param1 = ProtoField.new("param1 (float)", "mavlink_proto.COMMAND_LONG_param1", ftypes.FLOAT, nil)
f.COMMAND_LONG_param2 = ProtoField.new("param2 (float)", "mavlink_proto.COMMAND_LONG_param2", ftypes.FLOAT, nil)
f.COMMAND_LONG_param3 = ProtoField.new("param3 (float)", "mavlink_proto.COMMAND_LONG_param3", ftypes.FLOAT, nil)
f.COMMAND_LONG_param4 = ProtoField.new("param4 (float)", "mavlink_proto.COMMAND_LONG_param4", ftypes.FLOAT, nil)
f.COMMAND_LONG_param5 = ProtoField.new("param5 (float)", "mavlink_proto.COMMAND_LONG_param5", ftypes.FLOAT, nil)
f.COMMAND_LONG_param6 = ProtoField.new("param6 (float)", "mavlink_proto.COMMAND_LONG_param6", ftypes.FLOAT, nil)
f.COMMAND_LONG_param7 = ProtoField.new("param7 (float)", "mavlink_proto.COMMAND_LONG_param7", ftypes.FLOAT, nil)

f.COMMAND_ACK_command = ProtoField.new("command (MAV_CMD)", "mavlink_proto.COMMAND_ACK_command", ftypes.UINT16, enumEntryName.MAV_CMD)
f.COMMAND_ACK_result = ProtoField.new("result (MAV_RESULT)", "mavlink_proto.COMMAND_ACK_result", ftypes.UINT8, enumEntryName.MAV_RESULT)
f.COMMAND_ACK_progress = ProtoField.new("progress (uint8_t) [%]", "mavlink_proto.COMMAND_ACK_progress", ftypes.UINT8, nil)
f.COMMAND_ACK_result_param2 = ProtoField.new("result_param2 (int32_t)", "mavlink_proto.COMMAND_ACK_result_param2", ftypes.INT32, nil)
f.COMMAND_ACK_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.COMMAND_ACK_target_system", ftypes.UINT8, nil)
f.COMMAND_ACK_target_component = ProtoField.new("target_component (uint8_t)", "mavlink_proto.COMMAND_ACK_target_component", ftypes.UINT8, nil)

f.COMMAND_CANCEL_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.COMMAND_CANCEL_target_system", ftypes.UINT8, nil)
f.COMMAND_CANCEL_target_component = ProtoField.new("target_component (uint8_t)", "mavlink_proto.COMMAND_CANCEL_target_component", ftypes.UINT8, nil)
f.COMMAND_CANCEL_command = ProtoField.new("command (MAV_CMD)", "mavlink_proto.COMMAND_CANCEL_command", ftypes.UINT16, enumEntryName.MAV_CMD)

f.MESSAGE_INTERVAL_message_id = ProtoField.new("message_id (uint16_t)", "mavlink_proto.MESSAGE_INTERVAL_message_id", ftypes.UINT16, nil)
f.MESSAGE_INTERVAL_interval_us = ProtoField.new("interval_us (int32_t) [us]", "mavlink_proto.MESSAGE_INTERVAL_interval_us", ftypes.INT32, nil)

f.STATUSTEXT_severity = ProtoField.new("severity (MAV_SEVERITY)", "mavlink_proto.STATUSTEXT_severity", ftypes.UINT8, enumEntryName.MAV_SEVERITY)
f.STATUSTEXT_text = ProtoField.new("text (char)", "mavlink_proto.STATUSTEXT_text", ftypes.STRING, nil)
f.STATUSTEXT_id = ProtoField.new("id (uint16_t)", "mavlink_proto.STATUSTEXT_id", ftypes.UINT16, nil)
f.STATUSTEXT_chunk_seq = ProtoField.new("chunk_seq (uint8_t)", "mavlink_proto.STATUSTEXT_chunk_seq", ftypes.UINT8, nil)

-- dissect flag field
function dissect_flags_EOS_COMPONENT(tree, name, tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_LIDAR"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_YAW_MOTOR"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_PITCH_MOTOR"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_GPS"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_COMPASS"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_MCU"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_LED"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_ACCEL"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_POWER_SENSOR"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_SERIAL_BRIDGE"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_PORT_EXPANDER"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_FLASH"], tvbrange, value)
    tree:add_le(f[name .. "_flagEOS_COMPONENT_ALL"], tvbrange, value)
end
-- dissect flag field
function dissect_flags_MAV_MODE_FLAG(tree, name, tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_CUSTOM_MODE_ENABLED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_TEST_ENABLED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_AUTO_ENABLED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_GUIDED_ENABLED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_STABILIZE_ENABLED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_HIL_ENABLED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_MANUAL_INPUT_ENABLED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_SAFETY_ARMED"], tvbrange, value)
end
-- dissect flag field
function dissect_flags_MAV_MODE_FLAG_DECODE_POSITION(tree, name, tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_CUSTOM_MODE"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_TEST"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_AUTO"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_GUIDED"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_STABILIZE"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_HIL"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_MANUAL"], tvbrange, value)
    tree:add_le(f[name .. "_flagMAV_MODE_FLAG_DECODE_POSITION_SAFETY"], tvbrange, value)
end
-- dissect payload of message type LIDAR_READING
function payload_fns.payload_1(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 248 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 248)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_0, tvbrange)
    tvbrange = padded(offset + 8, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_1, tvbrange)
    tvbrange = padded(offset + 16, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_2, tvbrange)
    tvbrange = padded(offset + 24, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_3, tvbrange)
    tvbrange = padded(offset + 32, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_4, tvbrange)
    tvbrange = padded(offset + 40, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_5, tvbrange)
    tvbrange = padded(offset + 48, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_6, tvbrange)
    tvbrange = padded(offset + 56, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_7, tvbrange)
    tvbrange = padded(offset + 64, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_8, tvbrange)
    tvbrange = padded(offset + 72, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_9, tvbrange)
    tvbrange = padded(offset + 80, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_10, tvbrange)
    tvbrange = padded(offset + 88, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_11, tvbrange)
    tvbrange = padded(offset + 96, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_12, tvbrange)
    tvbrange = padded(offset + 104, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_13, tvbrange)
    tvbrange = padded(offset + 112, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_14, tvbrange)
    tvbrange = padded(offset + 120, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_15, tvbrange)
    tvbrange = padded(offset + 128, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_16, tvbrange)
    tvbrange = padded(offset + 136, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_17, tvbrange)
    tvbrange = padded(offset + 144, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_18, tvbrange)
    tvbrange = padded(offset + 152, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_19, tvbrange)
    tvbrange = padded(offset + 160, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_20, tvbrange)
    tvbrange = padded(offset + 168, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_21, tvbrange)
    tvbrange = padded(offset + 176, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_22, tvbrange)
    tvbrange = padded(offset + 184, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_23, tvbrange)
    tvbrange = padded(offset + 192, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_24, tvbrange)
    tvbrange = padded(offset + 200, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_25, tvbrange)
    tvbrange = padded(offset + 208, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_26, tvbrange)
    tvbrange = padded(offset + 216, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_27, tvbrange)
    tvbrange = padded(offset + 224, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_28, tvbrange)
    tvbrange = padded(offset + 232, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_29, tvbrange)
    tvbrange = padded(offset + 240, 8)
    subtree = tree:add_le(f.LIDAR_READING_readings_30, tvbrange)
end
-- dissect payload of message type COMPONENT_POWER_CONTROL
function payload_fns.payload_2(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 3 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 3)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 2)
    subtree = tree:add_le(f.COMPONENT_POWER_CONTROL_device, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_EOS_COMPONENT(subtree, "COMPONENT_POWER_CONTROL_device", tvbrange, value)
    tvbrange = padded(offset + 2, 1)
    subtree = tree:add_le(f.COMPONENT_POWER_CONTROL_behavior, tvbrange)
end
-- dissect payload of message type SYSTEM_STATUS
function payload_fns.payload_3(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 7 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 7)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 6, 1)
    subtree = tree:add_le(f.SYSTEM_STATUS_state, tvbrange)
    tvbrange = padded(offset + 0, 2)
    subtree = tree:add_le(f.SYSTEM_STATUS_power_status_bitmask, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_EOS_COMPONENT(subtree, "SYSTEM_STATUS_power_status_bitmask", tvbrange, value)
    tvbrange = padded(offset + 2, 2)
    subtree = tree:add_le(f.SYSTEM_STATUS_health_status_bitmask, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_EOS_COMPONENT(subtree, "SYSTEM_STATUS_health_status_bitmask", tvbrange, value)
    tvbrange = padded(offset + 4, 2)
    subtree = tree:add_le(f.SYSTEM_STATUS_uptime, tvbrange)
end
-- dissect payload of message type IDENTIFIER
function payload_fns.payload_7(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 50 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 50)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 24)
    subtree = tree:add_le(f.IDENTIFIER_particle_id, tvbrange)
    tvbrange = padded(offset + 24, 1)
    subtree = tree:add_le(f.IDENTIFIER_local_ip_0, tvbrange)
    tvbrange = padded(offset + 25, 1)
    subtree = tree:add_le(f.IDENTIFIER_local_ip_1, tvbrange)
    tvbrange = padded(offset + 26, 1)
    subtree = tree:add_le(f.IDENTIFIER_local_ip_2, tvbrange)
    tvbrange = padded(offset + 27, 1)
    subtree = tree:add_le(f.IDENTIFIER_local_ip_3, tvbrange)
    tvbrange = padded(offset + 28, 1)
    subtree = tree:add_le(f.IDENTIFIER_mac_0, tvbrange)
    tvbrange = padded(offset + 29, 1)
    subtree = tree:add_le(f.IDENTIFIER_mac_1, tvbrange)
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.IDENTIFIER_mac_2, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.IDENTIFIER_mac_3, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.IDENTIFIER_mac_4, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.IDENTIFIER_mac_5, tvbrange)
    tvbrange = padded(offset + 34, 16)
    subtree = tree:add_le(f.IDENTIFIER_name, tvbrange)
end
-- dissect payload of message type COMPONENT_HEALTH_TEST
function payload_fns.payload_8(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 4 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 4)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMPONENT_HEALTH_TEST_component, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_EOS_COMPONENT(subtree, "COMPONENT_HEALTH_TEST_component", tvbrange, value)
end
-- dissect payload of message type SCAN_SETTINGS
function payload_fns.payload_9(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 24 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 24)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.SCAN_SETTINGS_yaw_start, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.SCAN_SETTINGS_yaw_stop, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.SCAN_SETTINGS_pitch_start, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.SCAN_SETTINGS_pitch_stop, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.SCAN_SETTINGS_point_spacing, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.SCAN_SETTINGS_scan_speed, tvbrange)
end
-- dissect payload of message type SCAN_STATUS
function payload_fns.payload_10(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 7 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 7)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.SCAN_STATUS_start_time_unix, tvbrange)
    tvbrange = padded(offset + 6, 1)
    subtree = tree:add_le(f.SCAN_STATUS_scan_completion, tvbrange)
    tvbrange = padded(offset + 4, 2)
    subtree = tree:add_le(f.SCAN_STATUS_time_remaining, tvbrange)
end
-- dissect payload of message type REMOTE_SERVER_SETTINGS
function payload_fns.payload_11(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 230 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 230)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 4, 1)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_server_enable, tvbrange)
    tvbrange = padded(offset + 5, 64)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_post_server, tvbrange)
    tvbrange = padded(offset + 69, 32)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_post_uri, tvbrange)
    tvbrange = padded(offset + 0, 2)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_post_port, tvbrange)
    tvbrange = padded(offset + 101, 1)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_ftp_enable, tvbrange)
    tvbrange = padded(offset + 102, 64)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_ftp_server, tvbrange)
    tvbrange = padded(offset + 166, 32)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_ftp_username, tvbrange)
    tvbrange = padded(offset + 198, 32)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_ftp_password, tvbrange)
    tvbrange = padded(offset + 2, 2)
    subtree = tree:add_le(f.REMOTE_SERVER_SETTINGS_ftp_port, tvbrange)
end
-- dissect payload of message type POWER_INFORMATION
function payload_fns.payload_12(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 10 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 10)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 4, 2)
    subtree = tree:add_le(f.POWER_INFORMATION_instant_current, tvbrange)
    tvbrange = padded(offset + 6, 2)
    subtree = tree:add_le(f.POWER_INFORMATION_instant_voltage, tvbrange)
    tvbrange = padded(offset + 8, 2)
    subtree = tree:add_le(f.POWER_INFORMATION_instant_power, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.POWER_INFORMATION_energy_consumed, tvbrange)
end
-- dissect payload of message type WIFI_INFORMATION
function payload_fns.payload_13(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 42 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 42)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 32)
    subtree = tree:add_le(f.WIFI_INFORMATION_ssid, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_bssid_0, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_bssid_1, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_bssid_2, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_bssid_3, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_bssid_4, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_bssid_5, tvbrange)
    tvbrange = padded(offset + 38, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_rssi, tvbrange)
    tvbrange = padded(offset + 39, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_rssi_percent, tvbrange)
    tvbrange = padded(offset + 40, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_snr, tvbrange)
    tvbrange = padded(offset + 41, 1)
    subtree = tree:add_le(f.WIFI_INFORMATION_snr_percent, tvbrange)
end
-- dissect payload of message type UPLOAD_STATUS
function payload_fns.payload_14(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 17 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 17)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.UPLOAD_STATUS_start_time_unix, tvbrange)
    tvbrange = padded(offset + 16, 1)
    subtree = tree:add_le(f.UPLOAD_STATUS_upload_completion, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.UPLOAD_STATUS_bytes_uploaded, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.UPLOAD_STATUS_upload_size, tvbrange)
    tvbrange = padded(offset + 12, 2)
    subtree = tree:add_le(f.UPLOAD_STATUS_upload_rate, tvbrange)
    tvbrange = padded(offset + 14, 2)
    subtree = tree:add_le(f.UPLOAD_STATUS_time_remaining, tvbrange)
end
-- dissect payload of message type MOTOR_CONTROL
function payload_fns.payload_15(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 18 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 18)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 16, 1)
    subtree = tree:add_le(f.MOTOR_CONTROL_target, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_EOS_COMPONENT(subtree, "MOTOR_CONTROL_target", tvbrange, value)
    tvbrange = padded(offset + 17, 1)
    subtree = tree:add_le(f.MOTOR_CONTROL_behavior, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MOTOR_CONTROL_motor_rpm, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MOTOR_CONTROL_target_angle, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MOTOR_CONTROL_device_rpm, tvbrange)
    tvbrange = padded(offset + 12, 2)
    subtree = tree:add_le(f.MOTOR_CONTROL_steps_count, tvbrange)
    tvbrange = padded(offset + 14, 2)
    subtree = tree:add_le(f.MOTOR_CONTROL_vactual, tvbrange)
end
-- dissect payload of message type MOTOR_SETTINGS
function payload_fns.payload_16(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 24 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 24)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 18, 1)
    subtree = tree:add_le(f.MOTOR_SETTINGS_motor, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_EOS_COMPONENT(subtree, "MOTOR_SETTINGS_motor", tvbrange, value)
    tvbrange = padded(offset + 12, 2)
    subtree = tree:add_le(f.MOTOR_SETTINGS_current, tvbrange)
    tvbrange = padded(offset + 19, 1)
    subtree = tree:add_le(f.MOTOR_SETTINGS_microsteps, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MOTOR_SETTINGS_gearing_ratio, tvbrange)
    tvbrange = padded(offset + 20, 1)
    subtree = tree:add_le(f.MOTOR_SETTINGS_spread_cycle, tvbrange)
    tvbrange = padded(offset + 21, 1)
    subtree = tree:add_le(f.MOTOR_SETTINGS_pwm_autoscale, tvbrange)
    tvbrange = padded(offset + 22, 1)
    subtree = tree:add_le(f.MOTOR_SETTINGS_pwm_autograd, tvbrange)
    tvbrange = padded(offset + 23, 1)
    subtree = tree:add_le(f.MOTOR_SETTINGS_min_steps_to_next_index, tvbrange)
    tvbrange = padded(offset + 14, 2)
    subtree = tree:add_le(f.MOTOR_SETTINGS_home_offset_steps, tvbrange)
    tvbrange = padded(offset + 16, 2)
    subtree = tree:add_le(f.MOTOR_SETTINGS_steps_to_next_index, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MOTOR_SETTINGS_usteps_rate, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MOTOR_SETTINGS_ustep_angle, tvbrange)
end
-- dissect payload of message type MOTOR_STATUS
function payload_fns.payload_17(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 23 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 23)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 20, 1)
    subtree = tree:add_le(f.MOTOR_STATUS_motor, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_EOS_COMPONENT(subtree, "MOTOR_STATUS_motor", tvbrange, value)
    tvbrange = padded(offset + 21, 1)
    subtree = tree:add_le(f.MOTOR_STATUS_enabled, tvbrange)
    tvbrange = padded(offset + 22, 1)
    subtree = tree:add_le(f.MOTOR_STATUS_homed, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MOTOR_STATUS_motor_rpm, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MOTOR_STATUS_device_rpm, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MOTOR_STATUS_measured_rpm, tvbrange)
    tvbrange = padded(offset + 16, 2)
    subtree = tree:add_le(f.MOTOR_STATUS_vactual, tvbrange)
    tvbrange = padded(offset + 18, 2)
    subtree = tree:add_le(f.MOTOR_STATUS_steps_count, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MOTOR_STATUS_current_angle, tvbrange)
end
-- dissect payload of message type HEARTBEAT
function payload_fns.payload_0(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 9 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 9)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 4, 1)
    subtree = tree:add_le(f.HEARTBEAT_type, tvbrange)
    tvbrange = padded(offset + 5, 1)
    subtree = tree:add_le(f.HEARTBEAT_autopilot, tvbrange)
    tvbrange = padded(offset + 6, 1)
    subtree = tree:add_le(f.HEARTBEAT_base_mode, tvbrange)
    value = tvbrange:le_uint()
    dissect_flags_MAV_MODE_FLAG(subtree, "HEARTBEAT_base_mode", tvbrange, value)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.HEARTBEAT_custom_mode, tvbrange)
    tvbrange = padded(offset + 7, 1)
    subtree = tree:add_le(f.HEARTBEAT_system_status, tvbrange)
    tvbrange = padded(offset + 8, 1)
    subtree = tree:add_le(f.HEARTBEAT_mavlink_version, tvbrange)
end
-- dissect payload of message type CHANGE_OPERATOR_CONTROL
function payload_fns.payload_5(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 28 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 28)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 1)
    subtree = tree:add_le(f.CHANGE_OPERATOR_CONTROL_target_system, tvbrange)
    tvbrange = padded(offset + 1, 1)
    subtree = tree:add_le(f.CHANGE_OPERATOR_CONTROL_control_request, tvbrange)
    tvbrange = padded(offset + 2, 1)
    subtree = tree:add_le(f.CHANGE_OPERATOR_CONTROL_version, tvbrange)
    value = tvbrange:le_uint()
    subtree:append_text(string.format(" (%g deg)",value*180/math.pi))
    tvbrange = padded(offset + 3, 25)
    subtree = tree:add_le(f.CHANGE_OPERATOR_CONTROL_passkey, tvbrange)
end
-- dissect payload of message type CHANGE_OPERATOR_CONTROL_ACK
function payload_fns.payload_6(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 3 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 3)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 1)
    subtree = tree:add_le(f.CHANGE_OPERATOR_CONTROL_ACK_gcs_system_id, tvbrange)
    tvbrange = padded(offset + 1, 1)
    subtree = tree:add_le(f.CHANGE_OPERATOR_CONTROL_ACK_control_request, tvbrange)
    tvbrange = padded(offset + 2, 1)
    subtree = tree:add_le(f.CHANGE_OPERATOR_CONTROL_ACK_ack, tvbrange)
end
-- dissect payload of message type PROTOCOL_VERSION
function payload_fns.payload_300(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 22 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 22)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 2)
    subtree = tree:add_le(f.PROTOCOL_VERSION_version, tvbrange)
    tvbrange = padded(offset + 2, 2)
    subtree = tree:add_le(f.PROTOCOL_VERSION_min_version, tvbrange)
    tvbrange = padded(offset + 4, 2)
    subtree = tree:add_le(f.PROTOCOL_VERSION_max_version, tvbrange)
    tvbrange = padded(offset + 6, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_0, tvbrange)
    tvbrange = padded(offset + 7, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_1, tvbrange)
    tvbrange = padded(offset + 8, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_2, tvbrange)
    tvbrange = padded(offset + 9, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_3, tvbrange)
    tvbrange = padded(offset + 10, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_4, tvbrange)
    tvbrange = padded(offset + 11, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_5, tvbrange)
    tvbrange = padded(offset + 12, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_6, tvbrange)
    tvbrange = padded(offset + 13, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_spec_version_hash_7, tvbrange)
    tvbrange = padded(offset + 14, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_0, tvbrange)
    tvbrange = padded(offset + 15, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_1, tvbrange)
    tvbrange = padded(offset + 16, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_2, tvbrange)
    tvbrange = padded(offset + 17, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_3, tvbrange)
    tvbrange = padded(offset + 18, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_4, tvbrange)
    tvbrange = padded(offset + 19, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_5, tvbrange)
    tvbrange = padded(offset + 20, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_6, tvbrange)
    tvbrange = padded(offset + 21, 1)
    subtree = tree:add_le(f.PROTOCOL_VERSION_library_version_hash_7, tvbrange)
end
-- dissect payload of message type GPS_RAW_INT
function payload_fns.payload_24(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 52 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 52)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 8)
    subtree = tree:add_le(f.GPS_RAW_INT_time_usec, tvbrange)
    value = tvbrange:le_uint64()
    subtree:append_text(time_usec_decode(value))
    tvbrange = padded(offset + 28, 1)
    subtree = tree:add_le(f.GPS_RAW_INT_fix_type, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_lat, tvbrange)
    value = tvbrange:le_int()
    subtree:append_text(string.format(" (%.7f deg)",value/1E7))
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_lon, tvbrange)
    value = tvbrange:le_int()
    subtree:append_text(string.format(" (%.7f deg)",value/1E7))
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_alt, tvbrange)
    tvbrange = padded(offset + 20, 2)
    value = tvbrange:le_uint() * 1E-2
    subtree = tree:add_le(f.GPS_RAW_INT_eph, tvbrange, value)
    tvbrange = padded(offset + 22, 2)
    value = tvbrange:le_uint() * 1E-2
    subtree = tree:add_le(f.GPS_RAW_INT_epv, tvbrange, value)
    tvbrange = padded(offset + 24, 2)
    subtree = tree:add_le(f.GPS_RAW_INT_vel, tvbrange)
    tvbrange = padded(offset + 26, 2)
    subtree = tree:add_le(f.GPS_RAW_INT_cog, tvbrange)
    tvbrange = padded(offset + 29, 1)
    subtree = tree:add_le(f.GPS_RAW_INT_satellites_visible, tvbrange)
    tvbrange = padded(offset + 30, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_alt_ellipsoid, tvbrange)
    tvbrange = padded(offset + 34, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_h_acc, tvbrange)
    tvbrange = padded(offset + 38, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_v_acc, tvbrange)
    tvbrange = padded(offset + 42, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_vel_acc, tvbrange)
    tvbrange = padded(offset + 46, 4)
    subtree = tree:add_le(f.GPS_RAW_INT_hdg_acc, tvbrange)
    tvbrange = padded(offset + 50, 2)
    subtree = tree:add_le(f.GPS_RAW_INT_yaw, tvbrange)
end
-- dissect payload of message type ATTITUDE
function payload_fns.payload_30(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 32 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 32)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.ATTITUDE_time_boot_ms, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.ATTITUDE_roll, tvbrange)
    value = tvbrange:le_float()
    subtree:append_text(string.format(" (%g deg)",value*180/math.pi))
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.ATTITUDE_pitch, tvbrange)
    value = tvbrange:le_float()
    subtree:append_text(string.format(" (%g deg)",value*180/math.pi))
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.ATTITUDE_yaw, tvbrange)
    value = tvbrange:le_float()
    subtree:append_text(string.format(" (%g deg)",value*180/math.pi))
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.ATTITUDE_rollspeed, tvbrange)
    value = tvbrange:le_float()
    subtree:append_text(string.format(" (%g deg/s)",value*180/math.pi))
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.ATTITUDE_pitchspeed, tvbrange)
    value = tvbrange:le_float()
    subtree:append_text(string.format(" (%g deg/s)",value*180/math.pi))
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.ATTITUDE_yawspeed, tvbrange)
    value = tvbrange:le_float()
    subtree:append_text(string.format(" (%g deg/s)",value*180/math.pi))
    tvbrange = padded(offset + 28, 4)
    subtree = tree:add_le(f.ATTITUDE_temp, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_START_EOS_SCAN
function payload_fns.payload_39_cmd1(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.MISSION_ITEM_z, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_STOP_EOS_SCAN
function payload_fns.payload_39_cmd2(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.MISSION_ITEM_z, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_IDENTIFY
function payload_fns.payload_39_cmd3(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.MISSION_ITEM_z, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_SEND_SETTINGS_TO_SERVER
function payload_fns.payload_39_cmd4(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.MISSION_ITEM_z, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_CLEAR_EEPROM
function payload_fns.payload_39_cmd5(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.MISSION_ITEM_z, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_SET_MESSAGE_INTERVAL
function payload_fns.payload_39_cmd511(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param7, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_REQUEST_MESSAGE
function payload_fns.payload_39_cmd512(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param7, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM with command MAV_CMD_ENUM_END
function payload_fns.payload_39_cmd513(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.MISSION_ITEM_z, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type MISSION_ITEM
function payload_fns.payload_39(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 38 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 38)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    local cmd_id = padded(offset + 30, 2):le_uint()
    local cmd_name = enumEntryName.MAV_CMD[cmd_id]
    if cmd_name ~= nil then
        pinfo.cols.info:append(": " .. cmd_name)
    end
    local cmd_fn = payload_fns["payload_39_cmd" .. tostring(cmd_id)]
    if cmd_fn ~= nil then
        cmd_fn(buffer, tree, msgid, offset, limit, pinfo)
        return
    end
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_system, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.MISSION_ITEM_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.MISSION_ITEM_seq, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.MISSION_ITEM_frame, tvbrange)
    tvbrange = padded(offset + 30, 2)
    subtree = tree:add_le(f.MISSION_ITEM_command, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.MISSION_ITEM_current, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.MISSION_ITEM_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.MISSION_ITEM_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.MISSION_ITEM_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.MISSION_ITEM_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.MISSION_ITEM_z, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.MISSION_ITEM_mission_type, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_START_EOS_SCAN
function payload_fns.payload_75_cmd1(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_INT_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_INT_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_INT_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_STOP_EOS_SCAN
function payload_fns.payload_75_cmd2(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_INT_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_INT_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_INT_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_IDENTIFY
function payload_fns.payload_75_cmd3(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_INT_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_INT_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_INT_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_SEND_SETTINGS_TO_SERVER
function payload_fns.payload_75_cmd4(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_INT_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_INT_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_INT_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_CLEAR_EEPROM
function payload_fns.payload_75_cmd5(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_INT_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_INT_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_INT_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_SET_MESSAGE_INTERVAL
function payload_fns.payload_75_cmd511(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_REQUEST_MESSAGE
function payload_fns.payload_75_cmd512(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT with command MAV_CMD_ENUM_END
function payload_fns.payload_75_cmd513(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_INT_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_INT_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_INT_z, tvbrange)
end
-- dissect payload of message type COMMAND_INT
function payload_fns.payload_75(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 35 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 35)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    local cmd_id = padded(offset + 28, 2):le_uint()
    local cmd_name = enumEntryName.MAV_CMD[cmd_id]
    if cmd_name ~= nil then
        pinfo.cols.info:append(": " .. cmd_name)
    end
    local cmd_fn = payload_fns["payload_75_cmd" .. tostring(cmd_id)]
    if cmd_fn ~= nil then
        cmd_fn(buffer, tree, msgid, offset, limit, pinfo)
        return
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_INT_target_component, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_INT_frame, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_INT_command, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.COMMAND_INT_current, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.COMMAND_INT_autocontinue, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_INT_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_INT_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_INT_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_INT_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_INT_x, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_INT_y, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_INT_z, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_START_EOS_SCAN
function payload_fns.payload_76_cmd1(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_STOP_EOS_SCAN
function payload_fns.payload_76_cmd2(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_IDENTIFY
function payload_fns.payload_76_cmd3(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_SEND_SETTINGS_TO_SERVER
function payload_fns.payload_76_cmd4(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_CLEAR_EEPROM
function payload_fns.payload_76_cmd5(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_SET_MESSAGE_INTERVAL
function payload_fns.payload_76_cmd511(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_SET_MESSAGE_INTERVAL_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_REQUEST_MESSAGE
function payload_fns.payload_76_cmd512(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.cmd_MAV_CMD_REQUEST_MESSAGE_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG with command MAV_CMD_ENUM_END
function payload_fns.payload_76_cmd513(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param7, tvbrange)
end
-- dissect payload of message type COMMAND_LONG
function payload_fns.payload_76(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 33 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 33)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    local cmd_id = padded(offset + 28, 2):le_uint()
    local cmd_name = enumEntryName.MAV_CMD[cmd_id]
    if cmd_name ~= nil then
        pinfo.cols.info:append(": " .. cmd_name)
    end
    local cmd_fn = payload_fns["payload_76_cmd" .. tostring(cmd_id)]
    if cmd_fn ~= nil then
        cmd_fn(buffer, tree, msgid, offset, limit, pinfo)
        return
    end
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_system, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.COMMAND_LONG_target_component, tvbrange)
    tvbrange = padded(offset + 28, 2)
    subtree = tree:add_le(f.COMMAND_LONG_command, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.COMMAND_LONG_confirmation, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param1, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param2, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param3, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param4, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param5, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param6, tvbrange)
    tvbrange = padded(offset + 24, 4)
    subtree = tree:add_le(f.COMMAND_LONG_param7, tvbrange)
end
-- dissect payload of message type COMMAND_ACK
function payload_fns.payload_77(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 10 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 10)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    local cmd_id = padded(offset + 0, 2):le_uint()
    local cmd_name = enumEntryName.MAV_CMD[cmd_id]
    if cmd_name ~= nil then
        pinfo.cols.info:append(": " .. cmd_name)
    end
    tvbrange = padded(offset + 0, 2)
    subtree = tree:add_le(f.COMMAND_ACK_command, tvbrange)
    tvbrange = padded(offset + 2, 1)
    subtree = tree:add_le(f.COMMAND_ACK_result, tvbrange)
    tvbrange = padded(offset + 3, 1)
    subtree = tree:add_le(f.COMMAND_ACK_progress, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.COMMAND_ACK_result_param2, tvbrange)
    tvbrange = padded(offset + 8, 1)
    subtree = tree:add_le(f.COMMAND_ACK_target_system, tvbrange)
    tvbrange = padded(offset + 9, 1)
    subtree = tree:add_le(f.COMMAND_ACK_target_component, tvbrange)
end
-- dissect payload of message type COMMAND_CANCEL
function payload_fns.payload_80(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 4 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 4)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    local cmd_id = padded(offset + 0, 2):le_uint()
    local cmd_name = enumEntryName.MAV_CMD[cmd_id]
    if cmd_name ~= nil then
        pinfo.cols.info:append(": " .. cmd_name)
    end
    tvbrange = padded(offset + 2, 1)
    subtree = tree:add_le(f.COMMAND_CANCEL_target_system, tvbrange)
    tvbrange = padded(offset + 3, 1)
    subtree = tree:add_le(f.COMMAND_CANCEL_target_component, tvbrange)
    tvbrange = padded(offset + 0, 2)
    subtree = tree:add_le(f.COMMAND_CANCEL_command, tvbrange)
end
-- dissect payload of message type MESSAGE_INTERVAL
function payload_fns.payload_244(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 6 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 6)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 4, 2)
    subtree = tree:add_le(f.MESSAGE_INTERVAL_message_id, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.MESSAGE_INTERVAL_interval_us, tvbrange)
    value = tvbrange:le_int()
    subtree:append_text(time_usec_decode(value))
end
-- dissect payload of message type STATUSTEXT
function payload_fns.payload_253(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 54 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 54)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 1)
    subtree = tree:add_le(f.STATUSTEXT_severity, tvbrange)
    tvbrange = padded(offset + 1, 50)
    subtree = tree:add_le(f.STATUSTEXT_text, tvbrange)
    tvbrange = padded(offset + 51, 2)
    subtree = tree:add_le(f.STATUSTEXT_id, tvbrange)
    tvbrange = padded(offset + 53, 1)
    subtree = tree:add_le(f.STATUSTEXT_chunk_seq, tvbrange)
end
-- dissector function
function mavlink_proto.dissector(buffer,pinfo,tree)
    local offset = 0
    local msgCount = 0
    
    -- loop through the buffer to extract all the messages in the buffer
    while (offset < buffer:len()) 
    do
        msgCount = msgCount + 1
        local subtree = tree:add (mavlink_proto, buffer(), "MAVLink Protocol ("..buffer:len()..")")

        -- decode protocol version first
        local version = buffer(offset,1):uint()
        local protocolString = ""
    
    	while (true)
		do
            protocolString = protocolVersions[version]
            if (protocolString ~= nil) then
                break
            else
                protocolString = "unknown"
                -- some unknown data found, record the begin offset
                if (unknownFrameBeginOffset == 0) then
                    unknownFrameBeginOffset = offset
                end
               
                offset = offset + 1
                
                if (offset < buffer:len()) then
                    version = buffer(offset,1):uint()
                else
                    -- no magic value found in the whole buffer. print the raw data and exit
                    if (unknownFrameBeginOffset ~= 0) then
                        if (msgCount == 1) then
                            pinfo.cols.info:set("Unknown message")
                        else
                            pinfo.cols.info:append("  Unknown message")
                        end
                        size = offset - unknownFrameBeginOffset
                        subtree:add(f.rawpayload, buffer(unknownFrameBeginOffset,size))
                        unknownFrameBeginOffset = 0
                    end
                    return
                end
            end	
        end
        
        if (unknownFrameBeginOffset ~= 0) then
            pinfo.cols.info:append("Unknown message")
            size = offset - unknownFrameBeginOffset
            subtree:add(f.rawpayload, buffer(unknownFrameBeginOffset,size))
            unknownFrameBeginOffset = 0
            -- jump to next loop
            break
        end
        
        -- some Wireshark decoration
        pinfo.cols.protocol = protocolString

        -- HEADER ----------------------------------------
    
        local msgid
        local length
        local incompatibility_flag

        if (version == 0xfe) then
            if (buffer:len() - 2 - offset > 6) then
                -- normal header
                local header = subtree:add(buffer(offset, 6), "Header")
                header:add(f.magic, buffer(offset,1), version)
                offset = offset + 1
            
                length = buffer(offset,1)
                header:add(f.length, length)
                offset = offset + 1
            
                local sequence = buffer(offset,1)
                header:add(f.sequence, sequence)
                offset = offset + 1
            
                local sysid = buffer(offset,1)
                header:add(f.sysid, sysid)
                offset = offset + 1
        
                local compid = buffer(offset,1)
                header:add(f.compid, compid)
                offset = offset + 1
            
                pinfo.cols.src = "System: "..tostring(sysid:uint())..', Component: '..tostring(compid:uint())
        
                msgid = buffer(offset,1):uint()
                header:add(f.msgid, buffer(offset,1), msgid)
                offset = offset + 1
            else 
                -- handle truncated header
                local hsize = buffer:len() - 2 - offset
                subtree:add(f.rawheader, buffer(offset, hsize))
                offset = offset + hsize
            end
        elseif (version == 0xfd) then
            if (buffer:len() - 2 - offset > 10) then
                -- normal header
                local header = subtree:add(buffer(offset, 10), "Header")
                header:add(f.magic, buffer(offset,1), version)
                offset = offset + 1
                length = buffer(offset,1)
                header:add(f.length, length)
                offset = offset + 1
                incompatibility_flag = buffer(offset,1):uint()
                header:add(f.incompatibility_flag, buffer(offset,1), incompatibility_flag)
                offset = offset + 1
                local compatibility_flag = buffer(offset,1)
                header:add(f.compatibility_flag, compatibility_flag)
                offset = offset + 1
                local sequence = buffer(offset,1)
                header:add(f.sequence, sequence)
                offset = offset + 1
                local sysid = buffer(offset,1)
                header:add(f.sysid, sysid)
                offset = offset + 1
                local compid = buffer(offset,1)
                header:add(f.compid, compid)
                offset = offset + 1
                pinfo.cols.src = "System: "..tostring(sysid:uint())..', Component: '..tostring(compid:uint())
                msgid = buffer(offset,3):le_uint()
                header:add(f.msgid, buffer(offset,3), msgid)
                offset = offset + 3
            else 
                -- handle truncated header
                local hsize = buffer:len() - 2 - offset
                subtree:add(f.rawheader, buffer(offset, hsize))
                offset = offset + hsize
            end
        end


        -- BODY ----------------------------------------
    
        -- dynamically call the type-specific payload dissector    
        local msgnr = msgid
        local dissect_payload_fn = "payload_"..tostring(msgnr)
        local fn = payload_fns[dissect_payload_fn]
        local limit = buffer:len() - 2

        if (length) then
            length = length:uint()
        else
            length = 0
        end

        if (offset + length < limit) then
            limit = offset + length
        end
    
        if (fn == nil) then
            pinfo.cols.info:append ("Unknown message type   ")
            subtree:add_expert_info(PI_MALFORMED, PI_ERROR, "Unknown message type")
            size = buffer:len() - 2 - offset
            subtree:add(f.rawpayload, buffer(offset,size))
            offset = offset + size
        else
            local payload = subtree:add(f.payload, buffer(offset, limit - offset), msgid)
            pinfo.cols.dst:set(messageName[msgid])
            if (msgCount == 1) then
            -- first message should over write the TCP/UDP info
                pinfo.cols.info = messageName[msgid]
            else
                pinfo.cols.info:append("   "..messageName[msgid])
            end
            fn(buffer, payload, msgid, offset, limit, pinfo)
            offset = limit
        end

        -- CRC ----------------------------------------

        local crc = buffer(offset,2)
        subtree:add_le(f.crc, crc)
        offset = offset + 2

        -- SIGNATURE ----------------------------------

        if (version == 0xfd and incompatibility_flag == 0x01) then
            local signature = subtree:add("Signature")

            local link = buffer(offset,1)
            signature:add(f.signature_link, link)
            offset = offset + 1

            local signature_time = buffer(offset,6):le_uint64()
            local time_secs = signature_time / 100000
            local time_nsecs = (signature_time - (time_secs * 100000)) * 10000
            signature:add(f.signature_time, buffer(offset,6), NSTime.new(signature_time_ref + time_secs:tonumber(), time_nsecs:tonumber()))
            offset = offset + 6

            local signature_signature = buffer(offset,6)
            signature:add(f.signature_signature, signature_signature)
            offset = offset + 6
        end

    end
end


   
-- bind protocol dissector to USER0 linktype

wtap_encap = DissectorTable.get("wtap_encap")
wtap_encap:add(wtap.USER0, mavlink_proto)

-- bind protocol dissector to ports: 14550, 14580, 18570

local udp_dissector_table = DissectorTable.get("udp.port")
udp_dissector_table:add(14550, mavlink_proto)
udp_dissector_table:add(14580, mavlink_proto)
udp_dissector_table:add(18570, mavlink_proto)

-- register common Mavlink TCP ports

DissectorTable.get("tcp.port"):add("5760-5763", mavlink_proto)

