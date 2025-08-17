
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>




#define HYP_MSG_HEARTBEAT_HYP_MAX_SIZE 7
#define HYP_MSG_HEARTBEAT_HYP_SIGNATURE (0x645E9951715FA349ULL)

#define HYP_MSG_HEARTBEAT_HYP_ID 1001



#define HYP_MSG_HEARTBEAT_HYP_MAX_BROADCASTING_PERIOD_MS 1000

#define HYP_MSG_HEARTBEAT_HYP_MIN_BROADCASTING_PERIOD_MS 2

#define HYP_MSG_HEARTBEAT_HYP_OFFLINE_TIMEOUT_MS 3000

#define HYP_MSG_HEARTBEAT_HYP_HEALTH_OK 0

#define HYP_MSG_HEARTBEAT_HYP_HEALTH_WARNING 1

#define HYP_MSG_HEARTBEAT_HYP_HEALTH_ERROR 2

#define HYP_MSG_HEARTBEAT_HYP_HEALTH_CRITICAL 3

#define HYP_MSG_HEARTBEAT_HYP_MODE_OPERATIONAL 0

#define HYP_MSG_HEARTBEAT_HYP_MODE_INITIALIZATION 1

#define HYP_MSG_HEARTBEAT_HYP_MODE_MAINTENANCE 2

#define HYP_MSG_HEARTBEAT_HYP_MODE_SOFTWARE_UPDATE 3

#define HYP_MSG_HEARTBEAT_HYP_MODE_OFFLINE 7





#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class hyp_msg_HeartBeat_Hyp_cxx_iface;
#endif


struct hyp_msg_HeartBeat_Hyp {

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = hyp_msg_HeartBeat_Hyp_cxx_iface;
#endif




    uint32_t uptime_sec;



    uint8_t health;



    uint8_t mode;



    uint8_t sub_mode;



    uint16_t vendor_specific_status_code;



};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t hyp_msg_HeartBeat_Hyp_encode(struct hyp_msg_HeartBeat_Hyp* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool hyp_msg_HeartBeat_Hyp_decode(const CanardRxTransfer* transfer, struct hyp_msg_HeartBeat_Hyp* msg);

#if defined(CANARD_DSDLC_INTERNAL)

static inline void _hyp_msg_HeartBeat_Hyp_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_HeartBeat_Hyp* msg, bool tao);
static inline bool _hyp_msg_HeartBeat_Hyp_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_HeartBeat_Hyp* msg, bool tao);
void _hyp_msg_HeartBeat_Hyp_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_HeartBeat_Hyp* msg, bool tao) {

    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;






    canardEncodeScalar(buffer, *bit_ofs, 32, &msg->uptime_sec);

    *bit_ofs += 32;






    canardEncodeScalar(buffer, *bit_ofs, 2, &msg->health);

    *bit_ofs += 2;






    canardEncodeScalar(buffer, *bit_ofs, 3, &msg->mode);

    *bit_ofs += 3;






    canardEncodeScalar(buffer, *bit_ofs, 3, &msg->sub_mode);

    *bit_ofs += 3;






    canardEncodeScalar(buffer, *bit_ofs, 16, &msg->vendor_specific_status_code);

    *bit_ofs += 16;





}

/*
 decode hyp_msg_HeartBeat_Hyp, return true on failure, false on success
*/
bool _hyp_msg_HeartBeat_Hyp_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_HeartBeat_Hyp* msg, bool tao) {

    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;





    canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->uptime_sec);

    *bit_ofs += 32;







    canardDecodeScalar(transfer, *bit_ofs, 2, false, &msg->health);

    *bit_ofs += 2;







    canardDecodeScalar(transfer, *bit_ofs, 3, false, &msg->mode);

    *bit_ofs += 3;







    canardDecodeScalar(transfer, *bit_ofs, 3, false, &msg->sub_mode);

    *bit_ofs += 3;







    canardDecodeScalar(transfer, *bit_ofs, 16, false, &msg->vendor_specific_status_code);

    *bit_ofs += 16;





    return false; /* success */

}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct hyp_msg_HeartBeat_Hyp sample_hyp_msg_HeartBeat_Hyp_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>


BROADCAST_MESSAGE_CXX_IFACE(hyp_msg_HeartBeat_Hyp, HYP_MSG_HEARTBEAT_HYP_ID, HYP_MSG_HEARTBEAT_HYP_SIGNATURE, HYP_MSG_HEARTBEAT_HYP_MAX_SIZE);


#endif
#endif
