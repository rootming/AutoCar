// def.h

#ifndef _DEF_h
#define _DEF_h

//#if defined(ARDUINO) && ARDUINO >= 100
//	#include "arduino.h"
//#else
//	#include "WProgram.h"
//#endif
#include <stdint.h>
////enum PACKAGE_FLAG {	COMMAND, VALUE };
#define _PKGSTART	'0'
#define _PKGEND		'1'

#define _EEPROM_FLAG		0x16
#define _LEFT_MOTOR_SPEED	128
#define _RIGHT_MOTOR_SPEED	128
#define _ROTATE_SPEED		128

#define COMMAND_START 10
#define COMMAND_COUNT 11

enum COMMAND_LIST {
    CAR_GL = COMMAND_START,		CAR_FORWARD,
    CAR_GR,		CAR_LEFT,
    CAR_BRAKE,      CAR_RIGHT,
    CAR_BL,         CAR_BACK,
    CAR_BR,
    CAR_CW,		CAR_CCW,
    SET_LEFT_SPEED,		SET_RIGHT_SPEED,
    SET_ROTATE_SPEED,	SAVE_CONFIG
};

typedef enum { LEFT_MOTOR_SPEED = 1,
               RIGHT_MOTOR_SPEED = sizeof(uint32_t) * 1 + 1,
               ROTATE_SPEED = sizeof(uint32_t) * 2 + 1
             } ARG_ADDR;

typedef struct _Package
{
    uint8_t		start;
    uint8_t		command;
    uint8_t		value;
    uint8_t		end;
} Package;

//struct Config
//{
//	uint8_t leftMotorSpeed;
//	uint8_t rightMotorSpeed;
//	uint8_t rotateSpeed;
//};


#endif

