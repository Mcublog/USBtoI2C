#ifndef PROTO_H
#define PROTO_H

#ifdef __cplusplus
extern "C" {
#endif

#define PROTO_MAX_DATA_SIZE (256)

typedef enum
{
    VERSION_V1
} proto_version_t;

typedef enum
{
    CMD_READ,
    CMD_WRITE
} command_type_t;

typedef enum
{
    NACK = -1,
    ACK
} proto_result_t;

typedef struct
{
    proto_version_t version;
    proto_result_t result;
    uint8_t device_address;
    command_type_t cmd;
    uint8_t register_address;
    uint8_t data_size;
    uint8_t data[]
} __attribute__((packed)) message_v1_t;

#ifdef __cplusplus
}
#endif

#endif  // PROTO_H