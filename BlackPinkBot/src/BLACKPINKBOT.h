#ifndef BLACKPINKBOT_h
#define BLACKPINKBOT_h

#include <Arduino.h>

//used in some functions so you don't have to send a speed
#define DEFAULTSPEED 255  

// Modes
# define NO_LINE 0
# define FOLLOWING_LINE 1
# define FF 2
# define FL 3
# define FR 4
# define TURN_LEFT 5
# define TURN_RIGHT 6
# define GO_STRAIGHT 7

#define fwrd 1
#define bwd 2
#define r 3
#define l 4
#define fwd_xr 5
#define fwd_xl 6
#define bwd_xr 7
#define bwd_xl 8
#define tr 9
#define tl 10

// Motor
# define FRONT_LEFT_MOTOR_DIR_PIN1 4
# define FRONT_LEFT_MOTOR_DIR_PIN2 36
# define FRONT_LEFT_MOTOR_PWM_PIN 8

# define FRONT_RIGHT_MOTOR_DIR_PIN1 32
# define FRONT_RIGHT_MOTOR_DIR_PIN2 30
# define FRONT_RIGHT_MOTOR_PWM_PIN 10

# define REAR_LEFT_MOTOR_DIR_PIN1 26
# define REAR_LEFT_MOTOR_DIR_PIN2 28
# define REAR_LEFT_MOTOR_PWM_PIN 11

# define REAR_RIGHT_MOTOR_DIR_PIN1 22
# define REAR_RIGHT_MOTOR_DIR_PIN2 24
# define REAR_RIGHT_MOTOR_PWM_PIN 13

# define OFFSET_PIN 1
# define STBY_PIN1 9
# define STBY_PIN2 12 

#define port_buzzer 37
#define redLED 23
#define blueLED 27
#define greenLED 45

#define right_button 25
#define left_button 44

#define next dnext();

#include <Keypad.h>

// Keypad
extern Keypad keypad;

class Motor
{
  public:
    // Constructor. Mainly sets up pins.
    Motor(int In1pin, int In2pin, int PWMpin, int offset, int STBYpin);      

    // Drive in direction given by sign, at speed given by magnitude of the 
	//parameter.
    void drive(int speed);  
	
	// drive(), but with a delay(duration)
    void drive(int speed, int duration);  
	
	//currently not implemented
    //void stop();           // Stop motors, but allow them to coast to a halt.
    //void coast();          // Stop motors, but allow them to coast to a halt.
	
	//Stops motor by setting both input pins high
    void brake(); 
	
	//set the chip to standby mode.  The drive function takes it out of standby 
	//(forward, back, left, and right all call drive)
	void standby();	
	
  private:
    //variables for the 2 inputs, PWM input, Offset value, and the Standby pin
	int In1, In2, PWM, Offset,Standby;
	
	//private functions that spin the motor CC and CCW
	void fwd(int speed);
	void rev(int speed);


};

//Takes 2 motors and goes forward, if it does not go forward adjust offset 
//values until it does.  These will also take a negative number and go backwards
//There is also an optional speed input, if speed is not used, the function will
//use the DEFAULTSPEED constant.
void forward(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed);
void forward(Motor motor1, Motor motor2, Motor motor3, Motor motor4);

//Similar to forward, will take 2 motors and go backwards.  This will take either
//a positive or negative number and will go backwards either way.  Once again the
//speed input is optional and will use DEFAULTSPEED if it is not defined.
void back(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed);
void back(Motor motor1, Motor motor2, Motor motor3, Motor motor4);

//Left and right take 2 motors, and it is important the order they are sent.
//The left motor should be on the left side of the bot.  These functions
//also take a speed value
void left(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed);
void right(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speed);

//This function takes 2 motors and and brakes them
void brake(Motor motor1, Motor motor2, Motor motor3, Motor motor4);

// void motorDrivePID(Motor motor1, Motor motor2, Motor motor3, Motor motor4, int speedL, int speedR);

void servoAngkut(int dtime);
void servoTaruh(int dtime);
void servoReset(int dtime);

void eksbotInit();
void motorDrivePID(int speedL, int speedR);
void checkSensors();
void readSensors();
void calculatePID();
void motorPIDcontrol(int refSpeed);
void autolinefollow(int duration, int dbreaktime);
void line(int desiredMode, int desiredSpeed, int dbreaktime);
void turn(int action);

void StopMotors();
void buzzer(int num, int ton, int toff);
void findline(int speedL, int speedR, int dbreaktime);
void dnext();
void spinheading(int sudut);
void linedelay(int speed, int dtime, int dbreaktime);
void linefoll();
void move(int mspeed_FL, int mspeed_FR, int mspeed_RL, int mspeed_RR);

//Encoder
void handleEncoder();
bool allWheelsReachedTarget(float target);
int CMtoSteps(float distance_CM, float encoderTicksPerRevolution);
void EncoderConfig(int mode, int distanceCM, int mspeed, int encoderTicksPerRevolution);
void FWD(int distanceCM, int speed);
void BWD(int distanceCM, int speed);
void R(int distanceCM, int speed);
void L(int distanceCM, int speed);
void FWD_XR(int distanceCM, int speed);
void FWD_XL(int distanceCM, int speed);
void BWD_XR(int distanceCM, int speed);
void BWD_XL(int distanceCM, int speed);
void TR(int distanceCM=25, int speed=200);
void TL(int distanceCM=25, int speed=200);
void lineIntersect(int n);

#endif // BLACKPINKBOT_h