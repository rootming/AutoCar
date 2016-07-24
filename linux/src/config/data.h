#ifndef __DATA_H__
#define __DATA_H__


#include <stdint.h>

#define _MAGIC_NUM      0x16
#define _BUFFER_SIZE    10240
#define _CONNECT_LIMIT  10
#define _SERVER_PORT    23333
#define _UDP_PORT       2333

enum CMD_LIST { _CMD_DISCONNECT , _CMD_POST };

typedef struct _PackageHead
{
    uint8_t magic;
    uint8_t command;
    int16_t length;
} PackageHead;

#define _HEAD_LENGTH sizeof(PackageHead)
#endif
