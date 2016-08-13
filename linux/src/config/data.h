#pragma once

#include <inttypes.h>

#define MAGIC_NUM      0x16
#define BUFFER_SIZE    10240
#define CONNECT_LIMIT  10
#define SERVER_PORT    23333
#define UDP_PORT       2333

enum CMD_LIST { _CMD_DISCONNECT , _CMD_POST };

typedef struct _PackageHead
{
    uint8_t magic;
    uint8_t command;
    int16_t length;
} PackageHead;

#define HEAD_LENGTH sizeof(PackageHead)

