#ifndef TERSECRSF_H
#define TERSECRSF_H

#include <stdint.h>
#include <stdbool.h>

#define CRSF_MAX_CHANNELS 16
#define CRSF_RC_PAYLOAD_SIZE 22
#define CRSF_FRAME_MAX_LEN 64

// Frame ID
#define GPS_ID                         0x02
#define CF_VARIO_ID                    0x07
#define BATTERY_ID                     0x08
#define BARO_ALT_ID                    0x09
#define HEARTBEAT_ID                   0x0B
#define LINK_ID                        0x14
#define CHANNELS_ID                    0x16
#define LINK_RX_ID                     0x1C
#define LINK_TX_ID                     0x1D
#define ATTITUDE_ID                    0x1E
#define FLIGHT_MODE_ID                 0x21
#define PING_DEVICES_ID                0x28
#define DEVICE_INFO_ID                 0x29
#define REQUEST_SETTINGS_ID            0x2A
#define COMMAND_ID                     0x32
#define RADIO_ID                       0x3A

typedef struct {
    int32_t latitude;
    int32_t longitude;
    uint16_t groundspeed;
    uint16_t heading;
    uint16_t altitude;
    uint8_t satellites;
} crsf_gps_t;

typedef struct {
    uint16_t voltage;
    uint16_t current;
    uint32_t capacity_used;
    uint8_t remaining;
} crsf_battery_t;

typedef struct {
    int16_t pitch;
    int16_t roll;
    int16_t yaw;
} crsf_attitude_t;

typedef struct {
    uint8_t up_rssi_ant1;
    uint8_t up_rssi_ant2;
    uint8_t up_link_quality;
    int8_t up_snr;
    uint8_t active_antenna;
    uint8_t rf_profile;
    uint8_t up_rf_power;
    uint8_t down_rssi;
    uint8_t down_link_quality;
    int8_t down_snr;
} crsf_linkstats_t;

// CRC & bytes convert
uint8_t crsf_crc8_dvb_s2(uint8_t crc, uint8_t a);
uint8_t crsf_crc8_dvb_s2_sbuf_accum(const void *data, uint8_t frm_lth);

int32_t crsf_bytes2int32(uint8_t *byt);
uint16_t crsf_bytes2uint16(uint8_t *byt);
int16_t crsf_bytes2int16(uint8_t *byt);

// RC channel decode (22 bytes -> 16 channels)
void crsf_decode_channels(const uint8_t* payload, uint16_t* channels);

// Telemetry decode
void crsf_decode_gps(const uint8_t* payload, crsf_gps_t* gps);
void crsf_decode_battery(const uint8_t* payload, crsf_battery_t* bat);
void crsf_decode_attitude(const uint8_t* payload, crsf_attitude_t* att);
void crsf_decode_linkstats(const uint8_t* payload, crsf_linkstats_t* link);

// Helper
uint16_t crsf_wrap360(int16_t ang);
bool crsf_check_frame(uint8_t* buf, uint8_t frm_len);

#endif // TERSECRSF_H
