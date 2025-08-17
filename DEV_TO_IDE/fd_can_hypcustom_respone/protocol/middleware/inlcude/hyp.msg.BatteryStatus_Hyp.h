
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>




#define HYP_MSG_BATTERYSTATUS_HYP_MAX_SIZE 66
#define HYP_MSG_BATTERYSTATUS_HYP_SIGNATURE (0xCF2A3806FA81025FULL)

#define HYP_MSG_BATTERYSTATUS_HYP_ID 1000





#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class hyp_msg_BatteryStatus_Hyp_cxx_iface;
#endif


struct hyp_msg_BatteryStatus_Hyp {

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = hyp_msg_BatteryStatus_Hyp_cxx_iface;
#endif




    float temperature;



    uint16_t voltage;



    int16_t current;



    uint16_t time_to_full;



    uint16_t time_to_empty;



    uint8_t button;



    uint8_t is_charging;



    uint8_t adapter_power;



    struct { uint8_t len; uint8_t data[50]; }name;



    uint8_t state_of_charge_percent;



    uint8_t full_charge_flag;



};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t hyp_msg_BatteryStatus_Hyp_encode(struct hyp_msg_BatteryStatus_Hyp* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool hyp_msg_BatteryStatus_Hyp_decode(const CanardRxTransfer* transfer, struct hyp_msg_BatteryStatus_Hyp* msg);

#if defined(CANARD_DSDLC_INTERNAL)

static inline void _hyp_msg_BatteryStatus_Hyp_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_BatteryStatus_Hyp* msg, bool tao);
static inline bool _hyp_msg_BatteryStatus_Hyp_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_BatteryStatus_Hyp* msg, bool tao);
void _hyp_msg_BatteryStatus_Hyp_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_BatteryStatus_Hyp* msg, bool tao) {

    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;






    {
        uint16_t float16_val = canardConvertNativeFloatToFloat16(msg->temperature);
        canardEncodeScalar(buffer, *bit_ofs, 16, &float16_val);
    }

    *bit_ofs += 16;






    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->voltage);

    *bit_ofs += 16;






    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->current);

    *bit_ofs += 16;






    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->time_to_full);

    *bit_ofs += 16;






    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->time_to_empty);

    *bit_ofs += 16;






    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->button);

    *bit_ofs += 8;






    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->is_charging);

    *bit_ofs += 8;






    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->adapter_power);

    *bit_ofs += 8;






#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t name_len = msg->name.len > 50 ? 50 : msg->name.len;
#pragma GCC diagnostic pop

    canardEncodeScalar(buffer, *bit_ofs, 6, &name_len);
    *bit_ofs += 6;

    for (size_t i=0; i < name_len; i++) {




        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->name.data[i]);

        *bit_ofs += 8;


    }






    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->state_of_charge_percent);

    *bit_ofs += 8;






    canardEncodeScalar(buffer, *bit_ofs, 8, &msg->full_charge_flag);

    *bit_ofs += 8;





}

/*
 decode hyp_msg_BatteryStatus_Hyp, return true on failure, false on success
*/
bool _hyp_msg_BatteryStatus_Hyp_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_BatteryStatus_Hyp* msg, bool tao) {

    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;





    {
        uint16_t float16_val;
        canardDecodeScalar(transfer, *bit_ofs, 16, true, &float16_val);
        msg->temperature = canardConvertFloat16ToNativeFloat(float16_val);
    }

    *bit_ofs += 16;







    canardDecodeScalar(transfer, *bit_ofs, 16, false, &msg->voltage);

    *bit_ofs += 16;







    canardDecodeScalar(transfer, *bit_ofs, 16, true, &msg->current);

    *bit_ofs += 16;







    canardDecodeScalar(transfer, *bit_ofs, 16, false, &msg->time_to_full);

    *bit_ofs += 16;







    canardDecodeScalar(transfer, *bit_ofs, 16, false, &msg->time_to_empty);

    *bit_ofs += 16;







    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->button);

    *bit_ofs += 8;







    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->is_charging);

    *bit_ofs += 8;







    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->adapter_power);

    *bit_ofs += 8;








    canardDecodeScalar(transfer, *bit_ofs, 6, false, &msg->name.len);
    *bit_ofs += 6;


#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->name.len > 50) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->name.len; i++) {




        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->name.data[i]);

        *bit_ofs += 8;


    }








    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->state_of_charge_percent);

    *bit_ofs += 8;







    canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->full_charge_flag);

    *bit_ofs += 8;





    return false; /* success */

}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct hyp_msg_BatteryStatus_Hyp sample_hyp_msg_BatteryStatus_Hyp_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>


BROADCAST_MESSAGE_CXX_IFACE(hyp_msg_BatteryStatus_Hyp, HYP_MSG_BATTERYSTATUS_HYP_ID, HYP_MSG_BATTERYSTATUS_HYP_SIGNATURE, HYP_MSG_BATTERYSTATUS_HYP_MAX_SIZE);


#endif
#endif
