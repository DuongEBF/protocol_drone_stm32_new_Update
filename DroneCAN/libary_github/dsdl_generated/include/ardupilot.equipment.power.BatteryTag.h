#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#define ARDUPILOT_EQUIPMENT_POWER_BATTERYTAG_MAX_SIZE 24
#define ARDUPILOT_EQUIPMENT_POWER_BATTERYTAG_SIGNATURE (0x4A5A9B42099F73E1ULL)
#define ARDUPILOT_EQUIPMENT_POWER_BATTERYTAG_ID 20500

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class ardupilot_equipment_power_BatteryTag_cxx_iface;
#endif

struct ardupilot_equipment_power_BatteryTag {
#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = ardupilot_equipment_power_BatteryTag_cxx_iface;
#endif
    uint32_t serial_number;
    uint32_t num_cycles;
    float armed_hours;
    uint32_t battery_capacity_mAh;
    uint32_t first_use_mins;
    uint32_t last_arm_time_mins;
};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t ardupilot_equipment_power_BatteryTag_encode(struct ardupilot_equipment_power_BatteryTag* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool ardupilot_equipment_power_BatteryTag_decode(const CanardRxTransfer* transfer, struct ardupilot_equipment_power_BatteryTag* msg);

#if defined(CANARD_DSDLC_INTERNAL)
static inline void _ardupilot_equipment_power_BatteryTag_encode(uint8_t* buffer, uint32_t* bit_ofs, struct ardupilot_equipment_power_BatteryTag* msg, bool tao);
static inline bool _ardupilot_equipment_power_BatteryTag_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct ardupilot_equipment_power_BatteryTag* msg, bool tao);
void _ardupilot_equipment_power_BatteryTag_encode(uint8_t* buffer, uint32_t* bit_ofs, struct ardupilot_equipment_power_BatteryTag* msg, bool tao) {
    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;

    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->serial_number);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->num_cycles);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->armed_hours);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->battery_capacity_mAh);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->first_use_mins);
    *bit_ofs += 32;
    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->last_arm_time_mins);
    *bit_ofs += 32;
}

/*
 decode ardupilot_equipment_power_BatteryTag, return true on failure, false on success
*/
bool _ardupilot_equipment_power_BatteryTag_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct ardupilot_equipment_power_BatteryTag* msg, bool tao) {
    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;
    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->serial_number);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->num_cycles);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 32, true, &msg->armed_hours);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->battery_capacity_mAh);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->first_use_mins);
    *bit_ofs += 32;

    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->last_arm_time_mins);
    *bit_ofs += 32;

    return false; /* success */
}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct ardupilot_equipment_power_BatteryTag sample_ardupilot_equipment_power_BatteryTag_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>
BROADCAST_MESSAGE_CXX_IFACE(ardupilot_equipment_power_BatteryTag, ARDUPILOT_EQUIPMENT_POWER_BATTERYTAG_ID, ARDUPILOT_EQUIPMENT_POWER_BATTERYTAG_SIGNATURE, ARDUPILOT_EQUIPMENT_POWER_BATTERYTAG_MAX_SIZE);
#endif
#endif
