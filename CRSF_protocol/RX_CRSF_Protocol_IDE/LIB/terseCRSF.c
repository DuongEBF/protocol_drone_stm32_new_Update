#include "terseCRSF.h"
#include <string.h>

// ==== CRC8 DVB-S2 ====
uint8_t crsf_crc8_dvb_s2(uint8_t crc, uint8_t a) {
    crc ^= a;
    for (int ii = 0; ii < 8; ++ii) {
        if (crc & 0x80) {
            crc = (crc << 1) ^ 0xD5;
        } else {
            crc = crc << 1;
        }
    }
    return crc;
}

uint8_t crsf_crc8_dvb_s2_sbuf_accum(const void *data, uint8_t frm_lth) {
    uint8_t crc = 0;
    const uint8_t *p = (const uint8_t *)data;
    const uint8_t *pend = p + frm_lth;
    for (; p != pend; p++) {
        crc = crsf_crc8_dvb_s2(crc, *p);
    }
    return crc;
}

// ==== Byte convert ====
int32_t crsf_bytes2int32(uint8_t *byt) {
    return ((byt[3] << 0) & 0xFF) + ((byt[2] << 8) & 0xFFFF)
         + ((byt[1] << 16) & 0xFFFFFF) + ((byt[0] << 24) & 0xFFFFFFFF);
}
uint16_t crsf_bytes2uint16(uint8_t *byt) {
    return ((byt[1] << 0) & 0xFF) + ((byt[0] << 8) & 0xFFFF);
}
int16_t crsf_bytes2int16(uint8_t *byt) {
    return ((byt[1] << 0) & 0xFF) + ((byt[0] << 8) & 0xFFFF);
}

// ==== RC Channels Packed Payload (22 bytes) -> 16 channel x 11bit ====
void crsf_decode_channels(const uint8_t* payload, uint16_t* channels) {
    int bits = 0;
    for (int ch = 0; ch < CRSF_MAX_CHANNELS; ch++) {
        int byte_pos = bits / 8;
        int bit_in_byte = bits % 8;
        uint32_t buff = (payload[byte_pos] | (payload[byte_pos+1] << 8) | (payload[byte_pos+2] << 16));
        buff >>= bit_in_byte;
        channels[ch] = buff & 0x7FF;
        bits += 11;
    }
}

// ==== Telemetry decode (ch? ví d? ph? bi?n) ====
void crsf_decode_gps(const uint8_t* payload, crsf_gps_t* gps) {
    gps->latitude    = crsf_bytes2int32((uint8_t*)&payload[0]);
    gps->longitude   = crsf_bytes2int32((uint8_t*)&payload[4]);
    gps->groundspeed = crsf_bytes2uint16((uint8_t*)&payload[8]);
    gps->heading     = crsf_bytes2uint16((uint8_t*)&payload[10]);
    gps->altitude    = crsf_bytes2uint16((uint8_t*)&payload[12]);
    gps->satellites  = payload[14];
}
void crsf_decode_battery(const uint8_t* payload, crsf_battery_t* bat) {
    bat->voltage       = crsf_bytes2uint16((uint8_t*)&payload[0]);
    bat->current       = crsf_bytes2uint16((uint8_t*)&payload[2]);
    bat->capacity_used = payload[4] | (payload[5]<<8) | (payload[6]<<16);
    bat->remaining     = payload[7];
}
void crsf_decode_attitude(const uint8_t* payload, crsf_attitude_t* att) {
    att->pitch = crsf_bytes2int16((uint8_t*)&payload[0]);
    att->roll  = crsf_bytes2int16((uint8_t*)&payload[2]);
    att->yaw   = crsf_bytes2int16((uint8_t*)&payload[4]);
}
void crsf_decode_linkstats(const uint8_t* payload, crsf_linkstats_t* link) {
    link->up_rssi_ant1      = payload[0];
    link->up_rssi_ant2      = payload[1];
    link->up_link_quality   = payload[2];
    link->up_snr            = (int8_t)payload[3];
    link->active_antenna    = payload[4];
    link->rf_profile        = payload[5];
    link->up_rf_power       = payload[6];
    link->down_rssi         = payload[7];
    link->down_link_quality = payload[8];
    link->down_snr          = (int8_t)payload[9];
}

// ==== Helper ====
uint16_t crsf_wrap360(int16_t ang) {
    if (ang < 0)
        ang += 360;
    if (ang > 359)
        ang -= 360;
    return ang;
}

// ==== Check frame CRC ====
bool crsf_check_frame(uint8_t* buf, uint8_t frm_len) {
    if (frm_len < 4) return false;
    uint8_t calc_crc = crsf_crc8_dvb_s2_sbuf_accum(&buf[2], frm_len - 3);
    uint8_t embed_crc = buf[frm_len - 1];
    return (calc_crc == embed_crc);
}
