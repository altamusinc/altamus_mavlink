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
        s = math.floor(value:tonumber() / 1000000.0)
        us = value % 1000000
        d = os.date("%Y-%m-%d %H:%M:%S",s)
        us = string.format("%06d",us:tonumber())
        ok, tz = pcall(os.date," %Z",s)
        if not ok then
            tz = os.date(" %z",s)
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
    [1] = 'STATE_INPUT_EVENT',
    [2] = 'IDENTIFIER',
    [3] = 'WATER_TRANSACTION',
    [4] = 'STATION_STATE',
    [0] = 'HEARTBEAT',
    [5] = 'CHANGE_OPERATOR_CONTROL',
    [6] = 'CHANGE_OPERATOR_CONTROL_ACK',
    [300] = 'PROTOCOL_VERSION',
    [24] = 'GPS_RAW_INT',
    [39] = 'MISSION_ITEM',
    [75] = 'COMMAND_INT',
    [76] = 'COMMAND_LONG',
    [77] = 'COMMAND_ACK',
    [80] = 'COMMAND_CANCEL',
    [110] = 'FILE_TRANSFER_PROTOCOL',
    [111] = 'TIMESYNC',
    [244] = 'MESSAGE_INTERVAL',
    [251] = 'NAMED_VALUE_FLOAT',
    [252] = 'NAMED_VALUE_INT',
    [253] = 'STATUSTEXT',
}

local enumEntryName = {
    ["SYSTEM_STATE"] = {
        [1] = "SYSTEM_STATE_INITALIZING",
        [2] = "SYSTEM_STATE_READY",
        [3] = "SYSTEM_STATE_FILLING_IDENTIFIED",
        [4] = "SYSTEM_STATE_FILLING_UNIDENTIFIED",
        [5] = "SYSTEM_STATE_PAUSE",
        [6] = "SYSTEM_STATE_UPLOADING",
        [7] = "SYSTEM_STATE_OVERRIDE_ON",
        [8] = "SYSTEM_STATE_ERROR",
    },
    ["STATE_INPUT"] = {
        [1] = "STATE_INPUT_BADGE_PRESENT",
        [2] = "STATE_INPUT_BADGE_LEAVE",
        [3] = "STATE_INPUT_PULSER_PULSE",
        [4] = "STATE_INPUT_OVERRIDE_ON",
        [5] = "STATE_INPUT_OVERRIDE_OFF",
        [6] = "STATE_INPUT_ADMIN_START",
        [7] = "STATE_INPUT_ADMIN_STOP",
        [8] = "STATE_INPUT_UPLOAD_REQUEST",
        [9] = "STATE_INPUT_UPLOAD_COMPLETE",
        [10] = "STATE_INPUT_UPLOAD_RETRY",
        [11] = "STATE_INPUT_UPLOAD_ABORT",
        [12] = "STATE_INPUT_FILL_LIMIT",
    },
    ["MAV_AUTOPILOT"] = {
        [0] = "MAV_AUTOPILOT_GENERIC",
        [8] = "MAV_AUTOPILOT_INVALID",
    },
    ["MAV_FTP_ERR"] = {
        [0] = "MAV_FTP_ERR_NONE",
        [1] = "MAV_FTP_ERR_FAIL",
        [2] = "MAV_FTP_ERR_FAILERRNO",
        [3] = "MAV_FTP_ERR_INVALIDDATASIZE",
        [4] = "MAV_FTP_ERR_INVALIDSESSION",
        [5] = "MAV_FTP_ERR_NOSESSIONSAVAILABLE",
        [6] = "MAV_FTP_ERR_EOF",
        [7] = "MAV_FTP_ERR_UNKNOWNCOMMAND",
        [8] = "MAV_FTP_ERR_FILEEXISTS",
        [9] = "MAV_FTP_ERR_FILEPROTECTED",
        [10] = "MAV_FTP_ERR_FILENOTFOUND",
    },
    ["MAV_FTP_OPCODE"] = {
        [0] = "MAV_FTP_OPCODE_NONE",
        [1] = "MAV_FTP_OPCODE_TERMINATESESSION",
        [2] = "MAV_FTP_OPCODE_RESETSESSION",
        [3] = "MAV_FTP_OPCODE_LISTDIRECTORY",
        [4] = "MAV_FTP_OPCODE_OPENFILERO",
        [5] = "MAV_FTP_OPCODE_READFILE",
        [6] = "MAV_FTP_OPCODE_CREATEFILE",
        [7] = "MAV_FTP_OPCODE_WRITEFILE",
        [8] = "MAV_FTP_OPCODE_REMOVEFILE",
        [9] = "MAV_FTP_OPCODE_CREATEDIRECTORY",
        [10] = "MAV_FTP_OPCODE_REMOVEDIRECTORY",
        [11] = "MAV_FTP_OPCODE_OPENFILEWO",
        [12] = "MAV_FTP_OPCODE_TRUNCATEFILE",
        [13] = "MAV_FTP_OPCODE_RENAME",
        [14] = "MAV_FTP_OPCODE_CALCFILECRC",
        [15] = "MAV_FTP_OPCODE_BURSTREADFILE",
        [128] = "MAV_FTP_OPCODE_ACK",
        [129] = "MAV_FTP_OPCODE_NAK",
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
    ["MAV_CMD"] = {
        [511] = "MAV_CMD_SET_MESSAGE_INTERVAL",
        [512] = "MAV_CMD_REQUEST_MESSAGE",
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
    ["MAV_RESULT"] = {
        [0] = "MAV_RESULT_ACCEPTED",
        [1] = "MAV_RESULT_TEMPORARILY_REJECTED",
        [2] = "MAV_RESULT_DENIED",
        [3] = "MAV_RESULT_UNSUPPORTED",
        [4] = "MAV_RESULT_FAILED",
        [5] = "MAV_RESULT_IN_PROGRESS",
        [6] = "MAV_RESULT_CANCELLED",
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


f.STATE_INPUT_EVENT_event = ProtoField.new("event (STATE_INPUT)", "mavlink_proto.STATE_INPUT_EVENT_event", ftypes.UINT8, enumEntryName.STATE_INPUT)

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
f.IDENTIFIER_site_friendly_name = ProtoField.new("site_friendly_name (char)", "mavlink_proto.IDENTIFIER_site_friendly_name", ftypes.STRING, nil)
f.IDENTIFIER_site_name = ProtoField.new("site_name (char)", "mavlink_proto.IDENTIFIER_site_name", ftypes.STRING, nil)

f.WATER_TRANSACTION_badge_id_int = ProtoField.new("badge_id_int (uint64_t)", "mavlink_proto.WATER_TRANSACTION_badge_id_int", ftypes.UINT64, nil)
f.WATER_TRANSACTION_truck_name = ProtoField.new("truck_name (char)", "mavlink_proto.WATER_TRANSACTION_truck_name", ftypes.STRING, nil)
f.WATER_TRANSACTION_pulses = ProtoField.new("pulses (uint16_t)", "mavlink_proto.WATER_TRANSACTION_pulses", ftypes.UINT16, nil)
f.WATER_TRANSACTION_dispensed_ml = ProtoField.new("dispensed_ml (uint32_t) [mL]", "mavlink_proto.WATER_TRANSACTION_dispensed_ml", ftypes.UINT32, nil)
f.WATER_TRANSACTION_limit_ml = ProtoField.new("limit_ml (uint32_t) [mL]", "mavlink_proto.WATER_TRANSACTION_limit_ml", ftypes.UINT32, nil)
f.WATER_TRANSACTION_start_reason = ProtoField.new("start_reason (STATE_INPUT)", "mavlink_proto.WATER_TRANSACTION_start_reason", ftypes.UINT8, enumEntryName.STATE_INPUT)
f.WATER_TRANSACTION_stop_reason = ProtoField.new("stop_reason (STATE_INPUT)", "mavlink_proto.WATER_TRANSACTION_stop_reason", ftypes.UINT8, enumEntryName.STATE_INPUT)
f.WATER_TRANSACTION_start_time_utc = ProtoField.new("start_time_utc (uint32_t) [s]", "mavlink_proto.WATER_TRANSACTION_start_time_utc", ftypes.UINT32, nil)
f.WATER_TRANSACTION_stop_time_utc = ProtoField.new("stop_time_utc (uint32_t) [s]", "mavlink_proto.WATER_TRANSACTION_stop_time_utc", ftypes.UINT32, nil)

f.STATION_STATE_system_state = ProtoField.new("system_state (SYSTEM_STATE)", "mavlink_proto.STATION_STATE_system_state", ftypes.UINT8, enumEntryName.SYSTEM_STATE)
f.STATION_STATE_solenoid_state = ProtoField.new("solenoid_state (uint8_t)", "mavlink_proto.STATION_STATE_solenoid_state", ftypes.UINT8, nil)
f.STATION_STATE_untracked_pulses = ProtoField.new("untracked_pulses (uint32_t)", "mavlink_proto.STATION_STATE_untracked_pulses", ftypes.UINT32, nil)
f.STATION_STATE_system_time = ProtoField.new("system_time (uint32_t) [s]", "mavlink_proto.STATION_STATE_system_time", ftypes.UINT32, nil)
f.STATION_STATE_detected_badges_count = ProtoField.new("detected_badges_count (uint8_t)", "mavlink_proto.STATION_STATE_detected_badges_count", ftypes.UINT8, nil)
f.STATION_STATE_internet_connectivity = ProtoField.new("internet_connectivity (uint8_t)", "mavlink_proto.STATION_STATE_internet_connectivity", ftypes.UINT8, nil)
f.STATION_STATE_stored_transactions_count = ProtoField.new("stored_transactions_count (uint16_t)", "mavlink_proto.STATION_STATE_stored_transactions_count", ftypes.UINT16, nil)

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

f.FILE_TRANSFER_PROTOCOL_target_network = ProtoField.new("target_network (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_target_network", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_target_system", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_target_component = ProtoField.new("target_component (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_target_component", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_0 = ProtoField.new("payload[0] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_0", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_1 = ProtoField.new("payload[1] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_1", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_2 = ProtoField.new("payload[2] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_2", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_3 = ProtoField.new("payload[3] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_3", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_4 = ProtoField.new("payload[4] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_4", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_5 = ProtoField.new("payload[5] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_5", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_6 = ProtoField.new("payload[6] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_6", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_7 = ProtoField.new("payload[7] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_7", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_8 = ProtoField.new("payload[8] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_8", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_9 = ProtoField.new("payload[9] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_9", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_10 = ProtoField.new("payload[10] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_10", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_11 = ProtoField.new("payload[11] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_11", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_12 = ProtoField.new("payload[12] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_12", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_13 = ProtoField.new("payload[13] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_13", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_14 = ProtoField.new("payload[14] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_14", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_15 = ProtoField.new("payload[15] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_15", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_16 = ProtoField.new("payload[16] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_16", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_17 = ProtoField.new("payload[17] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_17", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_18 = ProtoField.new("payload[18] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_18", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_19 = ProtoField.new("payload[19] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_19", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_20 = ProtoField.new("payload[20] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_20", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_21 = ProtoField.new("payload[21] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_21", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_22 = ProtoField.new("payload[22] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_22", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_23 = ProtoField.new("payload[23] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_23", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_24 = ProtoField.new("payload[24] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_24", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_25 = ProtoField.new("payload[25] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_25", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_26 = ProtoField.new("payload[26] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_26", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_27 = ProtoField.new("payload[27] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_27", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_28 = ProtoField.new("payload[28] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_28", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_29 = ProtoField.new("payload[29] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_29", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_30 = ProtoField.new("payload[30] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_30", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_31 = ProtoField.new("payload[31] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_31", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_32 = ProtoField.new("payload[32] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_32", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_33 = ProtoField.new("payload[33] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_33", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_34 = ProtoField.new("payload[34] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_34", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_35 = ProtoField.new("payload[35] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_35", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_36 = ProtoField.new("payload[36] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_36", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_37 = ProtoField.new("payload[37] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_37", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_38 = ProtoField.new("payload[38] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_38", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_39 = ProtoField.new("payload[39] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_39", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_40 = ProtoField.new("payload[40] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_40", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_41 = ProtoField.new("payload[41] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_41", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_42 = ProtoField.new("payload[42] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_42", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_43 = ProtoField.new("payload[43] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_43", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_44 = ProtoField.new("payload[44] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_44", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_45 = ProtoField.new("payload[45] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_45", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_46 = ProtoField.new("payload[46] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_46", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_47 = ProtoField.new("payload[47] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_47", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_48 = ProtoField.new("payload[48] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_48", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_49 = ProtoField.new("payload[49] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_49", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_50 = ProtoField.new("payload[50] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_50", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_51 = ProtoField.new("payload[51] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_51", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_52 = ProtoField.new("payload[52] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_52", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_53 = ProtoField.new("payload[53] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_53", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_54 = ProtoField.new("payload[54] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_54", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_55 = ProtoField.new("payload[55] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_55", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_56 = ProtoField.new("payload[56] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_56", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_57 = ProtoField.new("payload[57] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_57", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_58 = ProtoField.new("payload[58] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_58", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_59 = ProtoField.new("payload[59] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_59", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_60 = ProtoField.new("payload[60] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_60", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_61 = ProtoField.new("payload[61] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_61", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_62 = ProtoField.new("payload[62] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_62", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_63 = ProtoField.new("payload[63] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_63", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_64 = ProtoField.new("payload[64] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_64", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_65 = ProtoField.new("payload[65] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_65", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_66 = ProtoField.new("payload[66] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_66", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_67 = ProtoField.new("payload[67] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_67", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_68 = ProtoField.new("payload[68] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_68", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_69 = ProtoField.new("payload[69] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_69", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_70 = ProtoField.new("payload[70] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_70", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_71 = ProtoField.new("payload[71] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_71", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_72 = ProtoField.new("payload[72] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_72", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_73 = ProtoField.new("payload[73] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_73", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_74 = ProtoField.new("payload[74] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_74", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_75 = ProtoField.new("payload[75] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_75", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_76 = ProtoField.new("payload[76] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_76", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_77 = ProtoField.new("payload[77] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_77", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_78 = ProtoField.new("payload[78] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_78", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_79 = ProtoField.new("payload[79] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_79", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_80 = ProtoField.new("payload[80] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_80", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_81 = ProtoField.new("payload[81] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_81", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_82 = ProtoField.new("payload[82] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_82", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_83 = ProtoField.new("payload[83] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_83", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_84 = ProtoField.new("payload[84] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_84", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_85 = ProtoField.new("payload[85] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_85", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_86 = ProtoField.new("payload[86] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_86", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_87 = ProtoField.new("payload[87] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_87", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_88 = ProtoField.new("payload[88] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_88", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_89 = ProtoField.new("payload[89] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_89", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_90 = ProtoField.new("payload[90] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_90", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_91 = ProtoField.new("payload[91] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_91", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_92 = ProtoField.new("payload[92] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_92", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_93 = ProtoField.new("payload[93] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_93", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_94 = ProtoField.new("payload[94] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_94", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_95 = ProtoField.new("payload[95] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_95", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_96 = ProtoField.new("payload[96] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_96", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_97 = ProtoField.new("payload[97] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_97", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_98 = ProtoField.new("payload[98] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_98", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_99 = ProtoField.new("payload[99] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_99", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_100 = ProtoField.new("payload[100] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_100", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_101 = ProtoField.new("payload[101] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_101", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_102 = ProtoField.new("payload[102] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_102", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_103 = ProtoField.new("payload[103] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_103", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_104 = ProtoField.new("payload[104] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_104", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_105 = ProtoField.new("payload[105] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_105", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_106 = ProtoField.new("payload[106] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_106", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_107 = ProtoField.new("payload[107] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_107", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_108 = ProtoField.new("payload[108] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_108", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_109 = ProtoField.new("payload[109] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_109", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_110 = ProtoField.new("payload[110] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_110", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_111 = ProtoField.new("payload[111] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_111", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_112 = ProtoField.new("payload[112] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_112", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_113 = ProtoField.new("payload[113] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_113", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_114 = ProtoField.new("payload[114] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_114", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_115 = ProtoField.new("payload[115] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_115", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_116 = ProtoField.new("payload[116] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_116", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_117 = ProtoField.new("payload[117] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_117", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_118 = ProtoField.new("payload[118] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_118", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_119 = ProtoField.new("payload[119] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_119", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_120 = ProtoField.new("payload[120] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_120", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_121 = ProtoField.new("payload[121] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_121", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_122 = ProtoField.new("payload[122] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_122", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_123 = ProtoField.new("payload[123] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_123", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_124 = ProtoField.new("payload[124] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_124", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_125 = ProtoField.new("payload[125] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_125", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_126 = ProtoField.new("payload[126] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_126", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_127 = ProtoField.new("payload[127] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_127", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_128 = ProtoField.new("payload[128] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_128", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_129 = ProtoField.new("payload[129] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_129", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_130 = ProtoField.new("payload[130] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_130", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_131 = ProtoField.new("payload[131] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_131", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_132 = ProtoField.new("payload[132] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_132", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_133 = ProtoField.new("payload[133] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_133", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_134 = ProtoField.new("payload[134] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_134", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_135 = ProtoField.new("payload[135] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_135", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_136 = ProtoField.new("payload[136] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_136", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_137 = ProtoField.new("payload[137] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_137", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_138 = ProtoField.new("payload[138] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_138", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_139 = ProtoField.new("payload[139] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_139", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_140 = ProtoField.new("payload[140] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_140", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_141 = ProtoField.new("payload[141] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_141", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_142 = ProtoField.new("payload[142] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_142", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_143 = ProtoField.new("payload[143] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_143", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_144 = ProtoField.new("payload[144] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_144", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_145 = ProtoField.new("payload[145] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_145", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_146 = ProtoField.new("payload[146] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_146", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_147 = ProtoField.new("payload[147] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_147", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_148 = ProtoField.new("payload[148] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_148", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_149 = ProtoField.new("payload[149] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_149", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_150 = ProtoField.new("payload[150] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_150", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_151 = ProtoField.new("payload[151] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_151", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_152 = ProtoField.new("payload[152] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_152", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_153 = ProtoField.new("payload[153] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_153", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_154 = ProtoField.new("payload[154] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_154", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_155 = ProtoField.new("payload[155] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_155", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_156 = ProtoField.new("payload[156] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_156", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_157 = ProtoField.new("payload[157] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_157", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_158 = ProtoField.new("payload[158] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_158", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_159 = ProtoField.new("payload[159] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_159", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_160 = ProtoField.new("payload[160] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_160", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_161 = ProtoField.new("payload[161] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_161", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_162 = ProtoField.new("payload[162] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_162", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_163 = ProtoField.new("payload[163] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_163", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_164 = ProtoField.new("payload[164] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_164", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_165 = ProtoField.new("payload[165] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_165", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_166 = ProtoField.new("payload[166] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_166", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_167 = ProtoField.new("payload[167] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_167", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_168 = ProtoField.new("payload[168] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_168", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_169 = ProtoField.new("payload[169] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_169", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_170 = ProtoField.new("payload[170] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_170", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_171 = ProtoField.new("payload[171] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_171", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_172 = ProtoField.new("payload[172] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_172", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_173 = ProtoField.new("payload[173] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_173", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_174 = ProtoField.new("payload[174] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_174", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_175 = ProtoField.new("payload[175] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_175", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_176 = ProtoField.new("payload[176] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_176", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_177 = ProtoField.new("payload[177] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_177", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_178 = ProtoField.new("payload[178] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_178", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_179 = ProtoField.new("payload[179] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_179", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_180 = ProtoField.new("payload[180] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_180", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_181 = ProtoField.new("payload[181] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_181", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_182 = ProtoField.new("payload[182] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_182", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_183 = ProtoField.new("payload[183] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_183", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_184 = ProtoField.new("payload[184] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_184", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_185 = ProtoField.new("payload[185] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_185", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_186 = ProtoField.new("payload[186] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_186", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_187 = ProtoField.new("payload[187] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_187", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_188 = ProtoField.new("payload[188] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_188", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_189 = ProtoField.new("payload[189] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_189", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_190 = ProtoField.new("payload[190] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_190", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_191 = ProtoField.new("payload[191] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_191", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_192 = ProtoField.new("payload[192] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_192", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_193 = ProtoField.new("payload[193] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_193", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_194 = ProtoField.new("payload[194] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_194", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_195 = ProtoField.new("payload[195] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_195", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_196 = ProtoField.new("payload[196] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_196", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_197 = ProtoField.new("payload[197] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_197", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_198 = ProtoField.new("payload[198] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_198", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_199 = ProtoField.new("payload[199] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_199", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_200 = ProtoField.new("payload[200] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_200", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_201 = ProtoField.new("payload[201] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_201", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_202 = ProtoField.new("payload[202] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_202", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_203 = ProtoField.new("payload[203] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_203", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_204 = ProtoField.new("payload[204] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_204", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_205 = ProtoField.new("payload[205] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_205", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_206 = ProtoField.new("payload[206] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_206", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_207 = ProtoField.new("payload[207] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_207", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_208 = ProtoField.new("payload[208] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_208", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_209 = ProtoField.new("payload[209] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_209", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_210 = ProtoField.new("payload[210] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_210", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_211 = ProtoField.new("payload[211] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_211", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_212 = ProtoField.new("payload[212] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_212", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_213 = ProtoField.new("payload[213] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_213", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_214 = ProtoField.new("payload[214] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_214", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_215 = ProtoField.new("payload[215] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_215", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_216 = ProtoField.new("payload[216] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_216", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_217 = ProtoField.new("payload[217] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_217", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_218 = ProtoField.new("payload[218] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_218", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_219 = ProtoField.new("payload[219] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_219", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_220 = ProtoField.new("payload[220] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_220", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_221 = ProtoField.new("payload[221] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_221", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_222 = ProtoField.new("payload[222] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_222", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_223 = ProtoField.new("payload[223] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_223", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_224 = ProtoField.new("payload[224] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_224", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_225 = ProtoField.new("payload[225] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_225", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_226 = ProtoField.new("payload[226] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_226", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_227 = ProtoField.new("payload[227] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_227", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_228 = ProtoField.new("payload[228] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_228", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_229 = ProtoField.new("payload[229] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_229", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_230 = ProtoField.new("payload[230] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_230", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_231 = ProtoField.new("payload[231] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_231", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_232 = ProtoField.new("payload[232] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_232", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_233 = ProtoField.new("payload[233] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_233", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_234 = ProtoField.new("payload[234] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_234", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_235 = ProtoField.new("payload[235] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_235", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_236 = ProtoField.new("payload[236] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_236", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_237 = ProtoField.new("payload[237] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_237", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_238 = ProtoField.new("payload[238] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_238", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_239 = ProtoField.new("payload[239] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_239", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_240 = ProtoField.new("payload[240] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_240", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_241 = ProtoField.new("payload[241] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_241", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_242 = ProtoField.new("payload[242] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_242", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_243 = ProtoField.new("payload[243] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_243", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_244 = ProtoField.new("payload[244] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_244", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_245 = ProtoField.new("payload[245] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_245", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_246 = ProtoField.new("payload[246] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_246", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_247 = ProtoField.new("payload[247] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_247", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_248 = ProtoField.new("payload[248] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_248", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_249 = ProtoField.new("payload[249] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_249", ftypes.UINT8, nil)
f.FILE_TRANSFER_PROTOCOL_payload_250 = ProtoField.new("payload[250] (uint8_t)", "mavlink_proto.FILE_TRANSFER_PROTOCOL_payload_250", ftypes.UINT8, nil)

f.TIMESYNC_tc1 = ProtoField.new("tc1 (int64_t) [ns]", "mavlink_proto.TIMESYNC_tc1", ftypes.INT64, nil)
f.TIMESYNC_ts1 = ProtoField.new("ts1 (int64_t) [ns]", "mavlink_proto.TIMESYNC_ts1", ftypes.INT64, nil)
f.TIMESYNC_target_system = ProtoField.new("target_system (uint8_t)", "mavlink_proto.TIMESYNC_target_system", ftypes.UINT8, nil)
f.TIMESYNC_target_component = ProtoField.new("target_component (uint8_t)", "mavlink_proto.TIMESYNC_target_component", ftypes.UINT8, nil)

f.MESSAGE_INTERVAL_message_id = ProtoField.new("message_id (uint16_t)", "mavlink_proto.MESSAGE_INTERVAL_message_id", ftypes.UINT16, nil)
f.MESSAGE_INTERVAL_interval_us = ProtoField.new("interval_us (int32_t) [us]", "mavlink_proto.MESSAGE_INTERVAL_interval_us", ftypes.INT32, nil)

f.NAMED_VALUE_FLOAT_time_boot_ms = ProtoField.new("time_boot_ms (uint32_t) [ms]", "mavlink_proto.NAMED_VALUE_FLOAT_time_boot_ms", ftypes.UINT32, nil)
f.NAMED_VALUE_FLOAT_name = ProtoField.new("name (char)", "mavlink_proto.NAMED_VALUE_FLOAT_name", ftypes.STRING, nil)
f.NAMED_VALUE_FLOAT_value = ProtoField.new("value (float)", "mavlink_proto.NAMED_VALUE_FLOAT_value", ftypes.FLOAT, nil)

f.NAMED_VALUE_INT_time_boot_ms = ProtoField.new("time_boot_ms (uint32_t) [ms]", "mavlink_proto.NAMED_VALUE_INT_time_boot_ms", ftypes.UINT32, nil)
f.NAMED_VALUE_INT_name = ProtoField.new("name (char)", "mavlink_proto.NAMED_VALUE_INT_name", ftypes.STRING, nil)
f.NAMED_VALUE_INT_value = ProtoField.new("value (int32_t)", "mavlink_proto.NAMED_VALUE_INT_value", ftypes.INT32, nil)

f.STATUSTEXT_severity = ProtoField.new("severity (MAV_SEVERITY)", "mavlink_proto.STATUSTEXT_severity", ftypes.UINT8, enumEntryName.MAV_SEVERITY)
f.STATUSTEXT_text = ProtoField.new("text (char)", "mavlink_proto.STATUSTEXT_text", ftypes.STRING, nil)
f.STATUSTEXT_id = ProtoField.new("id (uint16_t)", "mavlink_proto.STATUSTEXT_id", ftypes.UINT16, nil)
f.STATUSTEXT_chunk_seq = ProtoField.new("chunk_seq (uint8_t)", "mavlink_proto.STATUSTEXT_chunk_seq", ftypes.UINT8, nil)

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
-- dissect payload of message type STATE_INPUT_EVENT
function payload_fns.payload_1(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 1 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 1)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 1)
    subtree = tree:add_le(f.STATE_INPUT_EVENT_event, tvbrange)
end
-- dissect payload of message type IDENTIFIER
function payload_fns.payload_2(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 114 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 114)
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
    tvbrange = padded(offset + 34, 20)
    subtree = tree:add_le(f.IDENTIFIER_name, tvbrange)
    tvbrange = padded(offset + 54, 30)
    subtree = tree:add_le(f.IDENTIFIER_site_friendly_name, tvbrange)
    tvbrange = padded(offset + 84, 30)
    subtree = tree:add_le(f.IDENTIFIER_site_name, tvbrange)
end
-- dissect payload of message type WATER_TRANSACTION
function payload_fns.payload_3(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 48 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 48)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 8)
    subtree = tree:add_le(f.WATER_TRANSACTION_badge_id_int, tvbrange)
    tvbrange = padded(offset + 26, 20)
    subtree = tree:add_le(f.WATER_TRANSACTION_truck_name, tvbrange)
    tvbrange = padded(offset + 24, 2)
    subtree = tree:add_le(f.WATER_TRANSACTION_pulses, tvbrange)
    tvbrange = padded(offset + 8, 4)
    subtree = tree:add_le(f.WATER_TRANSACTION_dispensed_ml, tvbrange)
    tvbrange = padded(offset + 12, 4)
    subtree = tree:add_le(f.WATER_TRANSACTION_limit_ml, tvbrange)
    tvbrange = padded(offset + 46, 1)
    subtree = tree:add_le(f.WATER_TRANSACTION_start_reason, tvbrange)
    tvbrange = padded(offset + 47, 1)
    subtree = tree:add_le(f.WATER_TRANSACTION_stop_reason, tvbrange)
    tvbrange = padded(offset + 16, 4)
    subtree = tree:add_le(f.WATER_TRANSACTION_start_time_utc, tvbrange)
    tvbrange = padded(offset + 20, 4)
    subtree = tree:add_le(f.WATER_TRANSACTION_stop_time_utc, tvbrange)
end
-- dissect payload of message type STATION_STATE
function payload_fns.payload_4(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 14 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 14)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 10, 1)
    subtree = tree:add_le(f.STATION_STATE_system_state, tvbrange)
    tvbrange = padded(offset + 11, 1)
    subtree = tree:add_le(f.STATION_STATE_solenoid_state, tvbrange)
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.STATION_STATE_untracked_pulses, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.STATION_STATE_system_time, tvbrange)
    tvbrange = padded(offset + 12, 1)
    subtree = tree:add_le(f.STATION_STATE_detected_badges_count, tvbrange)
    tvbrange = padded(offset + 13, 1)
    subtree = tree:add_le(f.STATION_STATE_internet_connectivity, tvbrange)
    tvbrange = padded(offset + 8, 2)
    subtree = tree:add_le(f.STATION_STATE_stored_transactions_count, tvbrange)
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
-- dissect payload of message type FILE_TRANSFER_PROTOCOL
function payload_fns.payload_110(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 254 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 254)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_target_network, tvbrange)
    tvbrange = padded(offset + 1, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_target_system, tvbrange)
    tvbrange = padded(offset + 2, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_target_component, tvbrange)
    tvbrange = padded(offset + 3, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_0, tvbrange)
    tvbrange = padded(offset + 4, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_1, tvbrange)
    tvbrange = padded(offset + 5, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_2, tvbrange)
    tvbrange = padded(offset + 6, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_3, tvbrange)
    tvbrange = padded(offset + 7, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_4, tvbrange)
    tvbrange = padded(offset + 8, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_5, tvbrange)
    tvbrange = padded(offset + 9, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_6, tvbrange)
    tvbrange = padded(offset + 10, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_7, tvbrange)
    tvbrange = padded(offset + 11, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_8, tvbrange)
    tvbrange = padded(offset + 12, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_9, tvbrange)
    tvbrange = padded(offset + 13, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_10, tvbrange)
    tvbrange = padded(offset + 14, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_11, tvbrange)
    tvbrange = padded(offset + 15, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_12, tvbrange)
    tvbrange = padded(offset + 16, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_13, tvbrange)
    tvbrange = padded(offset + 17, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_14, tvbrange)
    tvbrange = padded(offset + 18, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_15, tvbrange)
    tvbrange = padded(offset + 19, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_16, tvbrange)
    tvbrange = padded(offset + 20, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_17, tvbrange)
    tvbrange = padded(offset + 21, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_18, tvbrange)
    tvbrange = padded(offset + 22, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_19, tvbrange)
    tvbrange = padded(offset + 23, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_20, tvbrange)
    tvbrange = padded(offset + 24, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_21, tvbrange)
    tvbrange = padded(offset + 25, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_22, tvbrange)
    tvbrange = padded(offset + 26, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_23, tvbrange)
    tvbrange = padded(offset + 27, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_24, tvbrange)
    tvbrange = padded(offset + 28, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_25, tvbrange)
    tvbrange = padded(offset + 29, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_26, tvbrange)
    tvbrange = padded(offset + 30, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_27, tvbrange)
    tvbrange = padded(offset + 31, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_28, tvbrange)
    tvbrange = padded(offset + 32, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_29, tvbrange)
    tvbrange = padded(offset + 33, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_30, tvbrange)
    tvbrange = padded(offset + 34, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_31, tvbrange)
    tvbrange = padded(offset + 35, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_32, tvbrange)
    tvbrange = padded(offset + 36, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_33, tvbrange)
    tvbrange = padded(offset + 37, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_34, tvbrange)
    tvbrange = padded(offset + 38, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_35, tvbrange)
    tvbrange = padded(offset + 39, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_36, tvbrange)
    tvbrange = padded(offset + 40, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_37, tvbrange)
    tvbrange = padded(offset + 41, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_38, tvbrange)
    tvbrange = padded(offset + 42, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_39, tvbrange)
    tvbrange = padded(offset + 43, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_40, tvbrange)
    tvbrange = padded(offset + 44, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_41, tvbrange)
    tvbrange = padded(offset + 45, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_42, tvbrange)
    tvbrange = padded(offset + 46, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_43, tvbrange)
    tvbrange = padded(offset + 47, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_44, tvbrange)
    tvbrange = padded(offset + 48, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_45, tvbrange)
    tvbrange = padded(offset + 49, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_46, tvbrange)
    tvbrange = padded(offset + 50, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_47, tvbrange)
    tvbrange = padded(offset + 51, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_48, tvbrange)
    tvbrange = padded(offset + 52, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_49, tvbrange)
    tvbrange = padded(offset + 53, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_50, tvbrange)
    tvbrange = padded(offset + 54, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_51, tvbrange)
    tvbrange = padded(offset + 55, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_52, tvbrange)
    tvbrange = padded(offset + 56, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_53, tvbrange)
    tvbrange = padded(offset + 57, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_54, tvbrange)
    tvbrange = padded(offset + 58, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_55, tvbrange)
    tvbrange = padded(offset + 59, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_56, tvbrange)
    tvbrange = padded(offset + 60, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_57, tvbrange)
    tvbrange = padded(offset + 61, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_58, tvbrange)
    tvbrange = padded(offset + 62, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_59, tvbrange)
    tvbrange = padded(offset + 63, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_60, tvbrange)
    tvbrange = padded(offset + 64, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_61, tvbrange)
    tvbrange = padded(offset + 65, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_62, tvbrange)
    tvbrange = padded(offset + 66, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_63, tvbrange)
    tvbrange = padded(offset + 67, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_64, tvbrange)
    tvbrange = padded(offset + 68, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_65, tvbrange)
    tvbrange = padded(offset + 69, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_66, tvbrange)
    tvbrange = padded(offset + 70, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_67, tvbrange)
    tvbrange = padded(offset + 71, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_68, tvbrange)
    tvbrange = padded(offset + 72, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_69, tvbrange)
    tvbrange = padded(offset + 73, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_70, tvbrange)
    tvbrange = padded(offset + 74, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_71, tvbrange)
    tvbrange = padded(offset + 75, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_72, tvbrange)
    tvbrange = padded(offset + 76, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_73, tvbrange)
    tvbrange = padded(offset + 77, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_74, tvbrange)
    tvbrange = padded(offset + 78, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_75, tvbrange)
    tvbrange = padded(offset + 79, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_76, tvbrange)
    tvbrange = padded(offset + 80, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_77, tvbrange)
    tvbrange = padded(offset + 81, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_78, tvbrange)
    tvbrange = padded(offset + 82, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_79, tvbrange)
    tvbrange = padded(offset + 83, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_80, tvbrange)
    tvbrange = padded(offset + 84, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_81, tvbrange)
    tvbrange = padded(offset + 85, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_82, tvbrange)
    tvbrange = padded(offset + 86, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_83, tvbrange)
    tvbrange = padded(offset + 87, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_84, tvbrange)
    tvbrange = padded(offset + 88, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_85, tvbrange)
    tvbrange = padded(offset + 89, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_86, tvbrange)
    tvbrange = padded(offset + 90, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_87, tvbrange)
    tvbrange = padded(offset + 91, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_88, tvbrange)
    tvbrange = padded(offset + 92, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_89, tvbrange)
    tvbrange = padded(offset + 93, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_90, tvbrange)
    tvbrange = padded(offset + 94, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_91, tvbrange)
    tvbrange = padded(offset + 95, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_92, tvbrange)
    tvbrange = padded(offset + 96, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_93, tvbrange)
    tvbrange = padded(offset + 97, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_94, tvbrange)
    tvbrange = padded(offset + 98, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_95, tvbrange)
    tvbrange = padded(offset + 99, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_96, tvbrange)
    tvbrange = padded(offset + 100, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_97, tvbrange)
    tvbrange = padded(offset + 101, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_98, tvbrange)
    tvbrange = padded(offset + 102, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_99, tvbrange)
    tvbrange = padded(offset + 103, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_100, tvbrange)
    tvbrange = padded(offset + 104, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_101, tvbrange)
    tvbrange = padded(offset + 105, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_102, tvbrange)
    tvbrange = padded(offset + 106, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_103, tvbrange)
    tvbrange = padded(offset + 107, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_104, tvbrange)
    tvbrange = padded(offset + 108, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_105, tvbrange)
    tvbrange = padded(offset + 109, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_106, tvbrange)
    tvbrange = padded(offset + 110, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_107, tvbrange)
    tvbrange = padded(offset + 111, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_108, tvbrange)
    tvbrange = padded(offset + 112, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_109, tvbrange)
    tvbrange = padded(offset + 113, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_110, tvbrange)
    tvbrange = padded(offset + 114, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_111, tvbrange)
    tvbrange = padded(offset + 115, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_112, tvbrange)
    tvbrange = padded(offset + 116, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_113, tvbrange)
    tvbrange = padded(offset + 117, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_114, tvbrange)
    tvbrange = padded(offset + 118, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_115, tvbrange)
    tvbrange = padded(offset + 119, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_116, tvbrange)
    tvbrange = padded(offset + 120, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_117, tvbrange)
    tvbrange = padded(offset + 121, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_118, tvbrange)
    tvbrange = padded(offset + 122, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_119, tvbrange)
    tvbrange = padded(offset + 123, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_120, tvbrange)
    tvbrange = padded(offset + 124, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_121, tvbrange)
    tvbrange = padded(offset + 125, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_122, tvbrange)
    tvbrange = padded(offset + 126, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_123, tvbrange)
    tvbrange = padded(offset + 127, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_124, tvbrange)
    tvbrange = padded(offset + 128, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_125, tvbrange)
    tvbrange = padded(offset + 129, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_126, tvbrange)
    tvbrange = padded(offset + 130, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_127, tvbrange)
    tvbrange = padded(offset + 131, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_128, tvbrange)
    tvbrange = padded(offset + 132, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_129, tvbrange)
    tvbrange = padded(offset + 133, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_130, tvbrange)
    tvbrange = padded(offset + 134, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_131, tvbrange)
    tvbrange = padded(offset + 135, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_132, tvbrange)
    tvbrange = padded(offset + 136, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_133, tvbrange)
    tvbrange = padded(offset + 137, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_134, tvbrange)
    tvbrange = padded(offset + 138, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_135, tvbrange)
    tvbrange = padded(offset + 139, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_136, tvbrange)
    tvbrange = padded(offset + 140, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_137, tvbrange)
    tvbrange = padded(offset + 141, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_138, tvbrange)
    tvbrange = padded(offset + 142, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_139, tvbrange)
    tvbrange = padded(offset + 143, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_140, tvbrange)
    tvbrange = padded(offset + 144, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_141, tvbrange)
    tvbrange = padded(offset + 145, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_142, tvbrange)
    tvbrange = padded(offset + 146, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_143, tvbrange)
    tvbrange = padded(offset + 147, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_144, tvbrange)
    tvbrange = padded(offset + 148, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_145, tvbrange)
    tvbrange = padded(offset + 149, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_146, tvbrange)
    tvbrange = padded(offset + 150, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_147, tvbrange)
    tvbrange = padded(offset + 151, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_148, tvbrange)
    tvbrange = padded(offset + 152, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_149, tvbrange)
    tvbrange = padded(offset + 153, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_150, tvbrange)
    tvbrange = padded(offset + 154, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_151, tvbrange)
    tvbrange = padded(offset + 155, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_152, tvbrange)
    tvbrange = padded(offset + 156, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_153, tvbrange)
    tvbrange = padded(offset + 157, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_154, tvbrange)
    tvbrange = padded(offset + 158, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_155, tvbrange)
    tvbrange = padded(offset + 159, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_156, tvbrange)
    tvbrange = padded(offset + 160, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_157, tvbrange)
    tvbrange = padded(offset + 161, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_158, tvbrange)
    tvbrange = padded(offset + 162, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_159, tvbrange)
    tvbrange = padded(offset + 163, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_160, tvbrange)
    tvbrange = padded(offset + 164, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_161, tvbrange)
    tvbrange = padded(offset + 165, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_162, tvbrange)
    tvbrange = padded(offset + 166, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_163, tvbrange)
    tvbrange = padded(offset + 167, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_164, tvbrange)
    tvbrange = padded(offset + 168, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_165, tvbrange)
    tvbrange = padded(offset + 169, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_166, tvbrange)
    tvbrange = padded(offset + 170, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_167, tvbrange)
    tvbrange = padded(offset + 171, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_168, tvbrange)
    tvbrange = padded(offset + 172, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_169, tvbrange)
    tvbrange = padded(offset + 173, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_170, tvbrange)
    tvbrange = padded(offset + 174, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_171, tvbrange)
    tvbrange = padded(offset + 175, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_172, tvbrange)
    tvbrange = padded(offset + 176, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_173, tvbrange)
    tvbrange = padded(offset + 177, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_174, tvbrange)
    tvbrange = padded(offset + 178, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_175, tvbrange)
    tvbrange = padded(offset + 179, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_176, tvbrange)
    tvbrange = padded(offset + 180, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_177, tvbrange)
    tvbrange = padded(offset + 181, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_178, tvbrange)
    tvbrange = padded(offset + 182, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_179, tvbrange)
    tvbrange = padded(offset + 183, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_180, tvbrange)
    tvbrange = padded(offset + 184, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_181, tvbrange)
    tvbrange = padded(offset + 185, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_182, tvbrange)
    tvbrange = padded(offset + 186, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_183, tvbrange)
    tvbrange = padded(offset + 187, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_184, tvbrange)
    tvbrange = padded(offset + 188, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_185, tvbrange)
    tvbrange = padded(offset + 189, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_186, tvbrange)
    tvbrange = padded(offset + 190, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_187, tvbrange)
    tvbrange = padded(offset + 191, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_188, tvbrange)
    tvbrange = padded(offset + 192, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_189, tvbrange)
    tvbrange = padded(offset + 193, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_190, tvbrange)
    tvbrange = padded(offset + 194, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_191, tvbrange)
    tvbrange = padded(offset + 195, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_192, tvbrange)
    tvbrange = padded(offset + 196, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_193, tvbrange)
    tvbrange = padded(offset + 197, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_194, tvbrange)
    tvbrange = padded(offset + 198, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_195, tvbrange)
    tvbrange = padded(offset + 199, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_196, tvbrange)
    tvbrange = padded(offset + 200, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_197, tvbrange)
    tvbrange = padded(offset + 201, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_198, tvbrange)
    tvbrange = padded(offset + 202, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_199, tvbrange)
    tvbrange = padded(offset + 203, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_200, tvbrange)
    tvbrange = padded(offset + 204, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_201, tvbrange)
    tvbrange = padded(offset + 205, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_202, tvbrange)
    tvbrange = padded(offset + 206, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_203, tvbrange)
    tvbrange = padded(offset + 207, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_204, tvbrange)
    tvbrange = padded(offset + 208, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_205, tvbrange)
    tvbrange = padded(offset + 209, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_206, tvbrange)
    tvbrange = padded(offset + 210, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_207, tvbrange)
    tvbrange = padded(offset + 211, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_208, tvbrange)
    tvbrange = padded(offset + 212, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_209, tvbrange)
    tvbrange = padded(offset + 213, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_210, tvbrange)
    tvbrange = padded(offset + 214, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_211, tvbrange)
    tvbrange = padded(offset + 215, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_212, tvbrange)
    tvbrange = padded(offset + 216, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_213, tvbrange)
    tvbrange = padded(offset + 217, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_214, tvbrange)
    tvbrange = padded(offset + 218, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_215, tvbrange)
    tvbrange = padded(offset + 219, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_216, tvbrange)
    tvbrange = padded(offset + 220, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_217, tvbrange)
    tvbrange = padded(offset + 221, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_218, tvbrange)
    tvbrange = padded(offset + 222, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_219, tvbrange)
    tvbrange = padded(offset + 223, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_220, tvbrange)
    tvbrange = padded(offset + 224, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_221, tvbrange)
    tvbrange = padded(offset + 225, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_222, tvbrange)
    tvbrange = padded(offset + 226, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_223, tvbrange)
    tvbrange = padded(offset + 227, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_224, tvbrange)
    tvbrange = padded(offset + 228, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_225, tvbrange)
    tvbrange = padded(offset + 229, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_226, tvbrange)
    tvbrange = padded(offset + 230, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_227, tvbrange)
    tvbrange = padded(offset + 231, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_228, tvbrange)
    tvbrange = padded(offset + 232, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_229, tvbrange)
    tvbrange = padded(offset + 233, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_230, tvbrange)
    tvbrange = padded(offset + 234, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_231, tvbrange)
    tvbrange = padded(offset + 235, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_232, tvbrange)
    tvbrange = padded(offset + 236, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_233, tvbrange)
    tvbrange = padded(offset + 237, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_234, tvbrange)
    tvbrange = padded(offset + 238, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_235, tvbrange)
    tvbrange = padded(offset + 239, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_236, tvbrange)
    tvbrange = padded(offset + 240, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_237, tvbrange)
    tvbrange = padded(offset + 241, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_238, tvbrange)
    tvbrange = padded(offset + 242, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_239, tvbrange)
    tvbrange = padded(offset + 243, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_240, tvbrange)
    tvbrange = padded(offset + 244, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_241, tvbrange)
    tvbrange = padded(offset + 245, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_242, tvbrange)
    tvbrange = padded(offset + 246, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_243, tvbrange)
    tvbrange = padded(offset + 247, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_244, tvbrange)
    tvbrange = padded(offset + 248, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_245, tvbrange)
    tvbrange = padded(offset + 249, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_246, tvbrange)
    tvbrange = padded(offset + 250, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_247, tvbrange)
    tvbrange = padded(offset + 251, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_248, tvbrange)
    tvbrange = padded(offset + 252, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_249, tvbrange)
    tvbrange = padded(offset + 253, 1)
    subtree = tree:add_le(f.FILE_TRANSFER_PROTOCOL_payload_250, tvbrange)
end
-- dissect payload of message type TIMESYNC
function payload_fns.payload_111(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 18 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 18)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 8)
    subtree = tree:add_le(f.TIMESYNC_tc1, tvbrange)
    tvbrange = padded(offset + 8, 8)
    subtree = tree:add_le(f.TIMESYNC_ts1, tvbrange)
    tvbrange = padded(offset + 16, 1)
    subtree = tree:add_le(f.TIMESYNC_target_system, tvbrange)
    tvbrange = padded(offset + 17, 1)
    subtree = tree:add_le(f.TIMESYNC_target_component, tvbrange)
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
-- dissect payload of message type NAMED_VALUE_FLOAT
function payload_fns.payload_251(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 18 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 18)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.NAMED_VALUE_FLOAT_time_boot_ms, tvbrange)
    tvbrange = padded(offset + 8, 10)
    subtree = tree:add_le(f.NAMED_VALUE_FLOAT_name, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.NAMED_VALUE_FLOAT_value, tvbrange)
end
-- dissect payload of message type NAMED_VALUE_INT
function payload_fns.payload_252(buffer, tree, msgid, offset, limit, pinfo)
    local padded, field_offset, value, subtree, tvbrange
    if (offset + 18 > limit) then
        padded = buffer(0, limit):bytes()
        padded:set_size(offset + 18)
        padded = padded:tvb("Untruncated payload")
    else
        padded = buffer
    end
    tvbrange = padded(offset + 0, 4)
    subtree = tree:add_le(f.NAMED_VALUE_INT_time_boot_ms, tvbrange)
    tvbrange = padded(offset + 8, 10)
    subtree = tree:add_le(f.NAMED_VALUE_INT_name, tvbrange)
    tvbrange = padded(offset + 4, 4)
    subtree = tree:add_le(f.NAMED_VALUE_INT_value, tvbrange)
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

