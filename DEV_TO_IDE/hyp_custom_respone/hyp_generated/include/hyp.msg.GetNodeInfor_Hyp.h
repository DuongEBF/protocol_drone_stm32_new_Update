

#pragma once
#include <hyp.msg.GetNodeInfor_Hyp_req.h>
#include <hyp.msg.GetNodeInfor_Hyp_res.h>

#define HYP_MSG_GETNODEINFOR_HYP_ID 10
#define HYP_MSG_GETNODEINFOR_HYP_SIGNATURE (0x510F865F0FC110CFULL)


#if defined(__cplusplus) && defined(DRONECAN_CXX_WRAPPERS)
#include <canard/cxx_wrappers.h>
SERVICE_MESSAGE_CXX_IFACE(hyp_msg_GetNodeInfor_Hyp, HYP_MSG_GETNODEINFOR_HYP_ID, HYP_MSG_GETNODEINFOR_HYP_SIGNATURE, HYP_MSG_GETNODEINFOR_HYP_REQUEST_MAX_SIZE, HYP_MSG_GETNODEINFOR_HYP_RESPONSE_MAX_SIZE);
#endif
