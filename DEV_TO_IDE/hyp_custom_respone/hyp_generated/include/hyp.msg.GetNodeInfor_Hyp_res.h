
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>


#include <hyp.msg.HeartBeat_Hyp.h>



#define HYP_MSG_GETNODEINFOR_HYP_RESPONSE_MAX_SIZE 88
#define HYP_MSG_GETNODEINFOR_HYP_RESPONSE_SIGNATURE (0x510F865F0FC110CFULL)

#define HYP_MSG_GETNODEINFOR_HYP_RESPONSE_ID 10





#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class hyp_msg_GetNodeInfor_Hyp_cxx_iface;
#endif


struct hyp_msg_GetNodeInfor_HypResponse {

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = hyp_msg_GetNodeInfor_Hyp_cxx_iface;
#endif




    struct hyp_msg_HeartBeat_Hyp status;



    struct { uint8_t len; uint8_t data[80]; }name;



};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t hyp_msg_GetNodeInfor_HypResponse_encode(struct hyp_msg_GetNodeInfor_HypResponse* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool hyp_msg_GetNodeInfor_HypResponse_decode(const CanardRxTransfer* transfer, struct hyp_msg_GetNodeInfor_HypResponse* msg);

#if defined(CANARD_DSDLC_INTERNAL)

static inline void _hyp_msg_GetNodeInfor_HypResponse_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypResponse* msg, bool tao);
static inline bool _hyp_msg_GetNodeInfor_HypResponse_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypResponse* msg, bool tao);
void _hyp_msg_GetNodeInfor_HypResponse_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypResponse* msg, bool tao) {

    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;





    _hyp_msg_HeartBeat_Hyp_encode(buffer, bit_ofs, &msg->status, false);






#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    const uint8_t name_len = msg->name.len > 80 ? 80 : msg->name.len;
#pragma GCC diagnostic pop

    if (!tao) {


        canardEncodeScalar(buffer, *bit_ofs, 7, &name_len);
        *bit_ofs += 7;


    }

    for (size_t i=0; i < name_len; i++) {




        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->name.data[i]);

        *bit_ofs += 8;


    }





}

/*
 decode hyp_msg_GetNodeInfor_HypResponse, return true on failure, false on success
*/
bool _hyp_msg_GetNodeInfor_HypResponse_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_msg_GetNodeInfor_HypResponse* msg, bool tao) {

    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;




    if (_hyp_msg_HeartBeat_Hyp_decode(transfer, bit_ofs, &msg->status, false)) {return true;}








    if (!tao) {


        canardDecodeScalar(transfer, *bit_ofs, 7, false, &msg->name.len);
        *bit_ofs += 7;



    } else {

        msg->name.len = ((transfer->payload_len*8)-*bit_ofs)/8;


    }



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wtype-limits"
    if (msg->name.len > 80) {
        return true; /* invalid value */
    }
#pragma GCC diagnostic pop
    for (size_t i=0; i < msg->name.len; i++) {




        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->name.data[i]);

        *bit_ofs += 8;


    }






    return false; /* success */

}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct hyp_msg_GetNodeInfor_HypResponse sample_hyp_msg_GetNodeInfor_HypResponse_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>



#endif
#endif
