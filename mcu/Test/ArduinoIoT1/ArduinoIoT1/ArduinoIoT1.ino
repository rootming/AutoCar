#include <stdint.h>
#include <EEPROM.h>
#include "control.h"
#include "def.h"

uint8_t *temp;
Package rec;
uint32_t values[3] = { 0, 0, 0 };
void(*autoExec)();


void motorStopLeft() 
{
	digitalWrite(_LEFT_INT1, LOW);
	digitalWrite(_LEFT_INT2, LOW);
}

void motorStopRight() 
{

	digitalWrite(_RIGHT_INT1, LOW);
	digitalWrite(_RIGHT_INT2, LOW);
}

void motorStopAll()
{
	digitalWrite(_LEFT_INT1, LOW);
	digitalWrite(_LEFT_INT2, LOW);
	digitalWrite(_RIGHT_INT1, LOW);
	digitalWrite(_RIGHT_INT2, LOW);
}

void motorSpeedLeft(uint8_t speed)
{
	analogWrite(_M_L_SPEED_PIN, speed);
}

void motorSpeedRight(uint8_t speed)
{
	analogWrite(_M_R_SPEED_PIN, speed);
}

void motorSpeedAll(uint8_t speed)
{
	analogWrite(_M_L_SPEED_PIN, speed);
	analogWrite(_M_R_SPEED_PIN, speed);
}


void motorLeftForward() 
{
	digitalWrite(_RIGHT_INT1, HIGH);
	digitalWrite(_RIGHT_INT2, LOW);
}

void motorRightForward() 
{
	
	digitalWrite(_LEFT_INT1, HIGH);
	digitalWrite(_LEFT_INT2, LOW);
}

void motorLeftBack() 
{
	digitalWrite(_RIGHT_INT1, LOW);
	digitalWrite(_RIGHT_INT2, HIGH);
}

void motorRightBack() 
{
	
	digitalWrite(_LEFT_INT1, LOW);
	digitalWrite(_LEFT_INT2, HIGH);
}


void carForward() 
{
	motorRightForward();
	motorLeftForward();
}

void carBack()
{
	motorRightBack();
	motorLeftBack();
}

void carLeft() 
{
	motorStopRight();
	motorLeftForward();
}

void carRight() 
{
	motorStopLeft();
	motorRightForward();
}

void carRotateCW()
{
	motorLeftBack();
	motorRightForward();
}

void carRotateCCW()
{
	motorRightBack();
	motorLeftForward();
}

void carBrake() {
	digitalWrite(_LEFT_INT1, HIGH);
	digitalWrite(_LEFT_INT2, HIGH);
	digitalWrite(_RIGHT_INT1, HIGH);
	digitalWrite(_RIGHT_INT2, HIGH);
}

void standby()
{
	digitalWrite(_LED_PIN, HIGH);
	//carBrake();
}

void busy()
{
	digitalWrite(_LED_PIN, LOW);
}

void setPin()
{
	pinMode(_LEFT_INT1, OUTPUT);
	pinMode(_LEFT_INT2, OUTPUT);
	pinMode(_RIGHT_INT1, OUTPUT);
	pinMode(_RIGHT_INT2, OUTPUT);
	pinMode(_TRIG_PIN, OUTPUT);
	pinMode(_LED_PIN, OUTPUT);
	pinMode(_M_L_SPEED_PIN, OUTPUT);
	pinMode(_M_R_SPEED_PIN, OUTPUT);
	pinMode(_DS_PIN, INPUT);
	//pinMode(ALARM_PIN, OUTPUT); 

	digitalWrite(_LEFT_INT1, LOW);
	digitalWrite(_LEFT_INT2, LOW);
	digitalWrite(_RIGHT_INT1, LOW);
	digitalWrite(_RIGHT_INT2, LOW);
	//digitalWrite(ALARM_PIN, LOW);
	//analogWrite(_M_L_SPEED_PIN, 255);
	//analogWrite(_M_R_SPEED_PIN, 255);
	//digitalWrite(IR_PIN, HIGH);
}

void setLeftMotorSpeed()
{
	analogWrite(_M_L_SPEED_PIN, values[(LEFT_MOTOR_SPEED - 1) / 4]);
	//analogWrite(_M_R_SPEED_PIN, 255);
}

void setRightMotorSpeed()
{
	analogWrite(_M_R_SPEED_PIN, values[(RIGHT_MOTOR_SPEED - 1) / 4]);
}

void execCMD(Package cmd)
{
	switch (cmd.command) {
	case CAR_FORWARD:
		//Serial.println("GO");
		autoExec = carForward;
		break;
	case CAR_BACK:
		autoExec = carBack;
		break;
	case CAR_RIGHT:
		autoExec = carRight;
		break;
	case CAR_LEFT:
		autoExec = carLeft;
		break;
	case CAR_BRAKE:
		autoExec = carBrake;
		break;
	case CAR_GR:
		autoExec = motorRightForward;
		break;
	case CAR_GL:
		autoExec = motorLeftForward;
		break;
	case CAR_BR:
		autoExec = motorRightBack;
		break;
	case CAR_BL:
		autoExec = motorLeftBack;
		break;
	case CAR_CW:
		autoExec = carRotateCW;
		break;
	case CAR_CCW:
		autoExec = carRotateCCW;
		break;
	case SET_LEFT_SPEED:
		break;
	case SET_RIGHT_SPEED:
		break;
	case SET_ROTATE_SPEED:
		break;
	case SAVE_CONFIG:
		break;
	default:
		Serial.print("Undefine command, Raw:0x");
		Serial.println(cmd.command, HEX);
		break;
	}
}
void saveConfig(ARG_ADDR addr)
{
	uint8_t *point = (uint8_t *)&values[(addr - 1) / 4];
	for (int i = addr, j = 3; i < addr + 4; i++, j--) {
		EEPROM.write(i, point[j]);
	}

}

void readConfig(ARG_ADDR addr)
{
	uint8_t *point = (uint8_t *)&values[(addr - 1) / 4];
	for (int i = addr, j = 3; i < addr + 4; i++, j--) {
		point[j] = EEPROM.read(i);
	}
}

void autoRun()
{
	autoExec();
}

void checkInit(void)
{
	if (EEPROM.read(0) != _EEPROM_FLAG) {
		Serial.println("EEPROM need init, Now init.");
		EEPROM.write(0, _EEPROM_FLAG);
		values[0] = _LEFT_MOTOR_SPEED;
		values[1] = _RIGHT_MOTOR_SPEED;
		values[2] = _ROTATE_SPEED;

		saveConfig(LEFT_MOTOR_SPEED);
		saveConfig(RIGHT_MOTOR_SPEED);
		saveConfig(ROTATE_SPEED);
	}
	else {
		readConfig(LEFT_MOTOR_SPEED);
		readConfig(RIGHT_MOTOR_SPEED);
		readConfig(ROTATE_SPEED);
		Serial.println("EEPROM: inited.");
		Serial.print("Left Motor Speed:");
		Serial.println(values[0]);
		Serial.print("Right Motor Speed:");
		Serial.println(values[1]);
		Serial.print("Rotate Speed:");
		Serial.println(values[2]);
	}
}

void setup()
{
	Serial.begin(9600);
	Serial.println("Design by rootming.");
	checkInit();
	setPin();
	setLeftMotorSpeed();
	setRightMotorSpeed();
	autoExec = standby;
	/*Serial.println(sizeof(Package));*/
	//temp = (uint8_t *)&rec;
	/*for (int i = 0; i < 13; i++) {
		Serial.print(EEPROM.read(i));
		Serial.print(" ");
	}*/
	
}


void loop()
{
	if (Serial.available()) {
		if (Serial.peek() == _PKGSTART) {
			Serial.readBytes((uint8_t *)&rec, sizeof(Package));
			if (rec.end == _PKGEND) {
				Serial.println("ACCEPT");
				Serial.print("Raw:0x");
				Serial.println(rec.command, HEX);
				execCMD(rec);
				//autoExec = busy;

			}
			else {
				Serial.println("Recived Head, but check error");
				memset(&rec, 5, 0);
				//autoExec = standby;
			}
		}
		else {
			Serial.println("Drop");
			Serial.read();	
		}
	}
	else {
		autoExec = motorStopAll;
		delay(200);
	}
	autoRun();
	//delay(100);
	//autoExec = motorStopAll;
	//delay(100);
	//autoExec = standby;
	
}