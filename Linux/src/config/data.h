#pragma once

#include <inttypes.h>

#define DEF_MAGIC_NUM      0x16
#define DEF_BUFFER_SIZE    10240
#define DEF_CONNECT_LIMIT  10
#define DEF_SERVER_PORT    23333
#define DEF_UDP_PORT       2333

enum CMD_LIST { _CMD_DISCONNECT , _CMD_POST };

typedef struct _PackageHead
{
    uint8_t magic;
    uint8_t command;
    uint16_t length;
} PackageHead;

#define DEF_HEAD_LENGTH sizeof(PackageHead)

