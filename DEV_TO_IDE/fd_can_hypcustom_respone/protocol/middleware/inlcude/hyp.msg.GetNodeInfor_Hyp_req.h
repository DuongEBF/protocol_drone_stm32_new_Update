
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>




#define HYP_MSG_GETNODEINFOR_HYP_REQUEST_MAX_SIZE 0
#define HYP_MSG_GETNODEINFOR_HYP_REQUEST_SIGNATURE (0x510F865F0FC110CFULL)

#define HYP_MSG_GETNODEINFOR_HYP_REQUEST_ID 10





#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class hyp_msg_GetNodeInfor_Hyp_cxx_iface;
#endif


struct hyp_msg_GetNodeInfor_HypRequest {

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = hyp_msg_GetNodeInfor_Hyp_cxx_iface;
#endif




};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t hyp_msg_GetNodeInfor_HypRequest_encode(struct hyp_msg_GetNodeInfor_HypRequest* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool hyp_msg_GetNodeInfor_HypRequest_decode(const CanardRxTransfer* transfer, struct hyp_msg_GetNodeInfor_HypRequest* msg);

#if defined(CANARD_DSDLC_INTERNAL)

static inline void _hyp_msg_GetNodeInfor_HypRequest_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypRequest* msg, bool tao);
static inline bool _hyp_msg_GetNodeInfor_HypRequest_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypRequest* msg, bool tao);
void _hyp_msg_GetNodeInfor_HypRequest_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypRequest* msg, bool tao) {

    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;





}

/*
 decode hyp_msg_GetNodeInfor_HypRequest, return true on failure, false on success
*/
bool _hyp_msg_GetNodeInfor_HypRequest_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypRequest* msg, bool tao) {

    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;



    return false; /* success */

}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct hyp_msg_GetNodeInfor_HypRequest sample_hyp_msg_GetNodeInfor_HypRequest_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>



#endif
#endif
