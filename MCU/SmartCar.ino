#include <IRremote.h>
#include <Servo.h> 
#include <stdint.h>
#include <stdbool.h>

#define LEFT_INT1		6
#define LEFT_INT2		7
#define RIGHT_INT1		5
#define RIGHT_INT2		4		//电机旋转控制
#define M_L_SPEED_PIN	9
#define M_R_SPEED_PIN	10		//电机转速
#define IR_PIN			8				//红外
#define TRIG_PIN		12
#define ECHO_PIN		13				//超声波
#define SERVO_PIN		11			//舵机
#define INT1_PIN		1			//for UNO,use digital 3
#define DS_PIN			3				
//#define ALARM_PIN 3				//指示灯

#define CONTROL_MODE	0			//0 Serial, 1 IRremote
#define DEBUG_MODE		0			//0 debug,1 disable


#define SIGNAL_FORWARD			0xFF629D
#define SIGNAL_BACK				0xFFA857
#define SIGNAL_LEFT				0xFF22DD
#define SIGNAL_RIGHT			0xFFC23D
#define SIGNAL_ROTATION_LEFT	0xFFE01F
#define SIGNAL_ROTATION_RIGHT	0xFF906F
#define SIGNAL_VOID				0xFFFFFF
#define SIGNAL_NONE				0x000000

//#define SIGNAL_FORWARD 0x41BED02F
//#define SIGNAL_BACK 0x41BE609F
//#define SIGNAL_LEFT 0x41BEB04F
//#define SIGNAL_RIGHT 0x41BE40BF		//红外指令定义

#define STOP_DELAY_1	2000
#define STOP_DELAY_2	200
#define DEF_ANGLE		90

enum SERIAL_COMMAND{
	COM_FORWARD = 'a',
	COM_LEFT,
	COM_RIGHT,
	COM_BACK,
	//COM_STOP,
	COM_BRAKE,
	COM_ROTATION_LEFT,
	COM_ROTATION_RIGHT,
	COM_NONE = -1,
};


#if CONTROL_MODE == 1
IRrecv irrecv (IR_PIN);
#endif
//Servo carservo;
decode_results results;
long temp, tmp;
char raw;
void (*autocar)();
//int distance;


void m_stop_left(){
	digitalWrite(LEFT_INT1, LOW);
	digitalWrite(LEFT_INT2, LOW);
}

void m_stop_right() {

	digitalWrite(RIGHT_INT1, LOW);
	digitalWrite(RIGHT_INT2, LOW);
}

void m_stop_all() {
	digitalWrite(LEFT_INT1, LOW);
	digitalWrite(LEFT_INT2, LOW);
	digitalWrite(RIGHT_INT1, LOW);
	digitalWrite(RIGHT_INT2, LOW);
}

void m_speed_left(uint8_t speed)
{
	analogWrite(M_L_SPEED_PIN, speed);
}

void m_speed_right(uint8_t speed)
{
	analogWrite(M_R_SPEED_PIN, speed);
}

void m_speed_all(uint8_t speed)
{
	analogWrite(M_L_SPEED_PIN, speed);
	analogWrite(M_R_SPEED_PIN, speed);
}


void m_left_forward(){
	digitalWrite(LEFT_INT1, HIGH);
	digitalWrite(LEFT_INT2, LOW);
}

void m_right_forward(){
	digitalWrite(RIGHT_INT1, HIGH);
	digitalWrite(RIGHT_INT2, LOW);
}

void m_left_back(){
	digitalWrite(LEFT_INT1, LOW);
	digitalWrite(LEFT_INT2, HIGH);
}

void m_right_back(){
	digitalWrite(RIGHT_INT1, LOW);
	digitalWrite(RIGHT_INT2, HIGH);
}


void car_forward(){
	m_right_forward();
	m_left_forward();
}

void car_back(){
	m_right_back();
	m_left_back();
}

void car_left(){
	m_stop_left();
	m_right_forward();
}

void car_right(){
	m_stop_right();
	m_left_forward();
}

void car_rotation_left()
{
	m_left_back();
	m_right_forward();
}

void car_rotation_right()
{
	m_right_back();
	m_left_forward();
}

void car_brake(){
	digitalWrite(LEFT_INT1, HIGH);
	digitalWrite(LEFT_INT2, HIGH);
	digitalWrite(RIGHT_INT1, HIGH);
	digitalWrite(RIGHT_INT2, HIGH);
#if DEBUG_MODE == 0
	Serial.println("Brake.");
#endif
	//digitalWrite(ALARM_PIN, HIGH);
	//delay(100);
	//digitalWrite(ALARM_PIN, LOW);
}

bool check_obstruct()
{
	if(digitalRead(DS_PIN) == LOW)
		return true;
	else
		return false;
}
#define car_stop() m_stop_all()

int get_distance(void)
{
	digitalWrite(TRIG_PIN, LOW); 
	delayMicroseconds(2); 
	digitalWrite(TRIG_PIN, HIGH); 
	delayMicroseconds(10);
	digitalWrite(TRIG_PIN, LOW); 
	return(pulseIn(ECHO_PIN, HIGH) / 58.00);
}

void setup()
{
#if CONTROL_MODE == 1
	irrecv.enableIRIn();

#endif
	//carservo.attach(SERVO_PIN);
	Serial.begin(9600);

	pinMode(LEFT_INT1, OUTPUT);
	pinMode(LEFT_INT2, OUTPUT);
	pinMode(RIGHT_INT1, OUTPUT);
	pinMode(RIGHT_INT2, OUTPUT);
	pinMode(TRIG_PIN, OUTPUT); 
	pinMode(ECHO_PIN, INPUT); 
	pinMode(M_L_SPEED_PIN, OUTPUT);
	pinMode(M_R_SPEED_PIN, OUTPUT);
	pinMode(DS_PIN, INPUT); 
	//pinMode(ALARM_PIN, OUTPUT); 

	digitalWrite(LEFT_INT1, LOW);
	digitalWrite(LEFT_INT2, LOW);
	digitalWrite(RIGHT_INT1, LOW);
	digitalWrite(RIGHT_INT2, LOW);
	//digitalWrite(ALARM_PIN, LOW);
	analogWrite(M_L_SPEED_PIN,255);
	analogWrite(M_R_SPEED_PIN,255);
	digitalWrite(IR_PIN, HIGH);
	//attachInterrupt(DS_PIN, car_brake, RISING);
	//for(int pos = 30; pos < 150; pos += 1){
	//	carservo.write(pos); 
	//	//Serial.print(get_distance()); 
	//	//Serial.println(); 
	//	delay(10);
	//} 
	//for(int pos = 150; pos>=30; pos-=1){                                
	//	carservo.write(pos); 
	//	Serial.print(get_distance()); 
	//	Serial.println(); 
	//	delay(10);
	//} 
	//carservo.write(DEF_ANGLE);

	Serial.println("Load success.");
#if CONTROL_MODE == 1
	Serial.println("Control Mode : IR");
#else
	Serial.println("Control Mode : Serial");
#endif

	//analogWrite(M_L_SPEED_PIN,255);
	//analogWrite(M_R_SPEED_PIN,255);
	//car_forward();
	//delay(2000);
	//analogWrite(M_L_SPEED_PIN,184);
	//analogWrite(M_R_SPEED_PIN,184);
	//car_forward();
	//delay(2000);
	//car_stop();

}

void loop()
{
#if CONTROL_MODE == 1
	if(irrecv.decode(&results)) {
		Serial.println(results.value, HEX);
		temp = results.value;
#else
	//if(Serial.available()){
	raw = Serial.read();
	switch(raw){
	case COM_NONE:
		temp = SIGNAL_NONE;
		break;
	case COM_FORWARD:
		temp = SIGNAL_FORWARD;
		break;
	case COM_LEFT:
		temp = SIGNAL_LEFT;
		break;
	case COM_RIGHT:
		temp = SIGNAL_RIGHT;
		break;
	case COM_BACK:
		temp = SIGNAL_BACK;
		break;
	case COM_ROTATION_LEFT:
		temp = SIGNAL_ROTATION_LEFT;
		break;
	case COM_ROTATION_RIGHT:
		temp = SIGNAL_ROTATION_RIGHT;
		break;
	default:
		temp = SIGNAL_VOID;
		break;
	}

#endif

	switch(temp){
	case SIGNAL_FORWARD:
#if DEBUG_MODE == 0
		Serial.println("Go");
#endif
		//car_forward();
		//delay(STOP_DELAY_1);
		//car_stop();
		if(check_obstruct() == true)
			autocar = car_brake;
		else
			autocar = car_forward;
		tmp = temp;
		autocar();
		break;
	case SIGNAL_BACK:
#if DEBUG_MODE == 0
		Serial.println("Back");
#endif
		//car_back();
		//delay(STOP_DELAY_1);
		//car_stop();
		autocar = car_back;
		tmp = temp;
		autocar();
		break;
	case SIGNAL_LEFT:
#if DEBUG_MODE == 0
		Serial.println("Turn left");
#endif
		//car_left();
		//delay(STOP_DELAY_2);
		//car_stop();
		autocar = car_left;
		tmp = temp;
		autocar();
		break;

	case SIGNAL_RIGHT:
#if DEBUG_MODE == 0
		Serial.println("Turn right");
#endif
		//car_right();
		//delay(STOP_DELAY_2);
		//car_stop();
		autocar = car_right;
		tmp = temp;
		autocar();
		break;
	case SIGNAL_ROTATION_LEFT:
#if DEBUG_MODE == 0
		Serial.println("Rotation Left");
#endif
		//car_rotation_left();
		//delay(1000);
		//car_stop();
		autocar = car_rotation_left;
		tmp = temp;
		autocar();
		break;
	case SIGNAL_ROTATION_RIGHT:
#if DEBUG_MODE == 0
		Serial.println("Rotation Right");
#endif
		//car_rotation_right();
		//delay(1000);
		//car_stop();
		autocar = car_rotation_right;
		tmp = temp;
		autocar();
		break;
	case SIGNAL_NONE:
		autocar = m_stop_all;
		break;

	default:
#if DEBUG_MODE == 0
		Serial.println("Void command");
#endif
		break;
	}

	//}
#if CONTROL_MODE == 1
}
irrecv.resume();
#endif
delay(40);
autocar = m_stop_all;
autocar();

}
