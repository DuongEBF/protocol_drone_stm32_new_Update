
#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <canard.h>




#define HYP_AES_ENCRYPTION_HYP_MAX_SIZE 256
#define HYP_AES_ENCRYPTION_HYP_SIGNATURE (0xB5EFEE67EE308D1ULL)

#define HYP_AES_ENCRYPTION_HYP_ID 44





#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
class hyp_aes_Encryption_Hyp_cxx_iface;
#endif


struct hyp_aes_Encryption_Hyp {

#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
    using cxx_iface = hyp_aes_Encryption_Hyp_cxx_iface;
#endif




    uint32_t payload_ciphertext[32];



    uint8_t payload_ciphertext_tiny[128];



};

#ifdef __cplusplus
extern "C"
{
#endif

uint32_t hyp_aes_Encryption_Hyp_encode(struct hyp_aes_Encryption_Hyp* msg, uint8_t* buffer
#if CANARD_ENABLE_TAO_OPTION
    , bool tao
#endif
);
bool hyp_aes_Encryption_Hyp_decode(const CanardRxTransfer* transfer, struct hyp_aes_Encryption_Hyp* msg);

#if defined(CANARD_DSDLC_INTERNAL)

static inline void _hyp_aes_Encryption_Hyp_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_aes_Encryption_Hyp* msg, bool tao);
static inline bool _hyp_aes_Encryption_Hyp_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_aes_Encryption_Hyp* msg, bool tao);
void _hyp_aes_Encryption_Hyp_encode(uint8_t* buffer, uint32_t* bit_ofs, struct hyp_aes_Encryption_Hyp* msg, bool tao) {

    (void)buffer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;






    for (size_t i=0; i < 32; i++) {




        canardEncodeScalar(buffer, *bit_ofs, 32, &msg->payload_ciphertext[i]);

        *bit_ofs += 32;


    }






    for (size_t i=0; i < 128; i++) {




        canardEncodeScalar(buffer, *bit_ofs, 8, &msg->payload_ciphertext_tiny[i]);

        *bit_ofs += 8;


    }





}

/*
 decode hyp_aes_Encryption_Hyp, return true on failure, false on success
*/
bool _hyp_aes_Encryption_Hyp_decode(const CanardRxTransfer* transfer, uint32_t* bit_ofs, struct hyp_aes_Encryption_Hyp* msg, bool tao) {

    (void)transfer;
    (void)bit_ofs;
    (void)msg;
    (void)tao;





    for (size_t i=0; i < 32; i++) {




        canardDecodeScalar(transfer, *bit_ofs, 32, false, &msg->payload_ciphertext[i]);

        *bit_ofs += 32;


    }








    for (size_t i=0; i < 128; i++) {




        canardDecodeScalar(transfer, *bit_ofs, 8, false, &msg->payload_ciphertext_tiny[i]);

        *bit_ofs += 8;


    }






    return false; /* success */

}
#endif
#ifdef CANARD_DSDLC_TEST_BUILD
struct hyp_aes_Encryption_Hyp sample_hyp_aes_Encryption_Hyp_msg(void);
#endif
#ifdef __cplusplus
} // extern "C"

#ifdef DRONECAN_CXX_WRAPPERS
#include <canard/cxx_wrappers.h>


BROADCAST_MESSAGE_CXX_IFACE(hyp_aes_Encryption_Hyp, HYP_AES_ENCRYPTION_HYP_ID, HYP_AES_ENCRYPTION_HYP_SIGNATURE, HYP_AES_ENCRYPTION_HYP_MAX_SIZE);


#endif
#endif
