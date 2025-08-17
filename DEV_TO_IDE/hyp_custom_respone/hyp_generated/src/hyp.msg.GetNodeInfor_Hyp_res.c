

#define CANARD_DSDLC_INTERNAL
#include <hyp.msg.GetNodeInfor_Hyp_res.h>

#include <string.h>

#ifdef CANARD_DSDLC_TEST_BUILD
#include <test_helpers.h>
#endif

uint32_t hyp_msg_GetNodeInfor_HypResponse_encode(struct hyp_msg_GetNodeInfor_HypResponse* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
) {
    uint32_t bit_ofs = 0;
    memset(buffer, 0, HYP_MSG_GETNODEINFOR_HYP_RESPONSE_MAX_SIZE);
    _hyp_msg_GetNodeInfor_HypResponse_encode(buffer, &bit_ofs, msg, 
#if CANARD_ENABLE_TAO_OPTION
    tao
#else
    true
#endif
    );
    return ((bit_ofs+7)/8);
}

/*
  return true if the decode is invalid
 */
bool hyp_msg_GetNodeInfor_HypResponse_decode(const CanardRxTransfer* transfer, struct hyp_msg_GetNodeInfor_HypResponse* msg) {
#if CANARD_ENABLE_TAO_OPTION
    if (transfer->tao && (transfer->payload_len > HYP_MSG_GETNODEINFOR_HYP_RESPONSE_MAX_SIZE)) {
        return true; /* invalid payload length */
    }
#endif
    uint32_t bit_ofs = 0;
    if (_hyp_msg_GetNodeInfor_HypResponse_decode(transfer, &bit_ofs, msg,
#if CANARD_ENABLE_TAO_OPTION
    transfer->tao
#else
    true
#endif
    )) {
        return true; /* invalid payload */
    }

    const uint32_t byte_len = (bit_ofs+7U)/8U;
#if CANARD_ENABLE_TAO_OPTION
    // if this could be CANFD then the dlc could indicating more bytes than
    // we actually have
    if (!transfer->tao) {
        return byte_len > transfer->payload_len;
    }
#endif
    return byte_len != transfer->payload_len;
}

#ifdef CANARD_DSDLC_TEST_BUILD
struct hyp_msg_GetNodeInfor_HypResponse sample_hyp_msg_GetNodeInfor_HypResponse_msg(void) {

    struct hyp_msg_GetNodeInfor_HypResponse msg;





    msg.status = sample_hyp_msg_HeartBeat_Hyp_msg();






    msg.name.len = (uint8_t)random_range_unsigned_val(0, 80);
    for (size_t i=0; i < msg.name.len; i++) {




        msg.name.data[i] = (uint8_t)random_bitlen_unsigned_val(8);



    }




    return msg;

}
#endif
