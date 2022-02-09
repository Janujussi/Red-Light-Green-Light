// FILE: main.cpp
//
// Author: Jan Morrison

#include <Arduino.h>
#include <Stepper.h>
#include <SegmentDisplay.h>
#include <Wire.h>
#include <MPU6050_light.h>
#include <HCSR04.h>
#include <Servo.h>

// Defines //
#define BUZZER_PIN 10               	// Buzzer pin
#define RED_LIGHT 12                	// Red light to show red light state
#define GREEN_LIGHT 13              	// Green light to show green light state
#define DISPLAY_PIN_A 31            	// Segment display pin A
#define DISPLAY_PIN_B 33            	// Segment display pin B
#define DISPLAY_PIN_C 35            	// Segment display pin C
#define DISPLAY_PIN_D 37            	// Segment display pin D
#define DISPLAY_PIN_E 39            	// Segment display pin E
#define DISPLAY_PIN_F 41            	// Segment display pin F
#define DISPLAY_PIN_G 43            	// Segment display pin G
#define START_BUTTON_PIN 47         	// Start button pin
#define USENSOR_TRIGGER_PIN 22      	// Ultrasonic sensor trigger pin
#define USENSOR_ECHO_PIN 24         	// Ultrasonic sensor echo pin
#define PLAY_DISTANCE 100           	// Max read distance of ultrasonic sensor
#define SERVO_SENSOR_PIN 6          	// Servo which holds the ultrasonic sensor pin
#define SERVO_HITTER_PIN 7          	// Servo which hits the player pin
#define red_light true              	// Red light
#define green_light false           	// Green light
#define MOTOR_STEP 10					// Stepper motor step

// Object declarations //
Stepper motor(1024, 2, 3, 4, 5);     	// Step motor
SegmentDisplay display(             	// 7 segment display
  DISPLAY_PIN_A,
  DISPLAY_PIN_B,
  DISPLAY_PIN_C,
  DISPLAY_PIN_D,
  DISPLAY_PIN_E,
  DISPLAY_PIN_F,
  DISPLAY_PIN_G
);
MPU6050 mpu(Wire);                  	// IMU sensor
UltraSonicDistanceSensor usensor(   	// Ultrasonic sensor
  USENSOR_TRIGGER_PIN,
  USENSOR_ECHO_PIN,
  PLAY_DISTANCE
);
Servo servo_sensor, servo_hitter;   	// Servos

// Variable declarations //
bool firstRun;
bool startGame;                       	// Game start flag
float stateTimer = 0;         		  	// Time for each state
bool gameState;                       	// State of the game, red light or green light
unsigned long timer;                  	// Time for the round, max time of 60 seconds
float sumToAverageDistance;           	// Sum to average 10 distances to counter random values from ultrasonic sensor
float redLightDistance;               	// Distance from sensor when red light starts
float redLightDistanceBuffer = .3;    	// Help with sensor precision
unsigned long startTime = 0;			// Starting time of the game for reference. Comparing to 60 seconds
unsigned long endLoopTime = 0;			// Used to compare with startTime of the game
unsigned long startStateTime = 0;		// Start time of red light or green light state
unsigned long endStateTime = 0;			// To compare with start state time to check for state change
float checkDistanceSum;					// Sum of distance readings from distance sensor
float checkDistanceAverage;				// Average of readings from distance sensor

// Functions //
// Check mpu angle and move motor
void mpuMove(int step, MPU6050 mpu) {
	mpu.update();
	Serial.println(mpu.getAngleY());

	if (mpu.getAngleY() > 45) {
		motor.step(step);
		Serial.println("MOVING");
	} else if (mpu.getAngleY() < -45) {
		motor.step(-step);
		Serial.println("MOVING");
	}
}

// Check how much time is left in round and update segment display
int checkTimer(unsigned long timer, SegmentDisplay display) {
	if (timer >= 60000) {			// Zero seconds
		display.zero();
		Serial.println("Game over!");
		return 1;
	} else if (timer >= 50000) {	// 10 seconds
		display.one();
	} else if (timer >= 40000) {	// 20 seconds
		display.two();
	} else if (timer >= 30000) {	// 30 seconds
		display.three();
	} else if (timer >= 20000) {	// 40 seconds
		display.four();
	} else if (timer >= 10000) {	// 50 seconds
		display.five();
	} else if (timer >= 0) {		// 60 seconds
		display.six();
	}

	return 0;
}

// Random time generator
int randTime() {
	return random(1, 4);
}

// Green light state
void greenLight() {
	tone(BUZZER_PIN, 1000);
	Serial.println("GREEN LIGHT!!!!!");
	servo_sensor.write(180);
	digitalWrite(RED_LIGHT, LOW);
	digitalWrite(GREEN_LIGHT, HIGH);
}

// Red light state
void redLight() {
	tone(BUZZER_PIN, 10000);
	Serial.println("RED LIGHT!!!!!");
	servo_sensor.write(0);
	delay(300);
	digitalWrite(RED_LIGHT, HIGH);
	digitalWrite(GREEN_LIGHT, LOW);
}

// Setup function //
void setup() {
	// Set baud rate
	Serial.begin(9600);

	// Set motor speed
	motor.setSpeed(15);

	// Set pinmodes of red light and green light
	pinMode(RED_LIGHT, OUTPUT);
	pinMode(GREEN_LIGHT, OUTPUT);

	// Display 0 on segment display
	display.zero();

	// Set pinmode of start button on controller
	pinMode(START_BUTTON_PIN, INPUT);

	// IMU initialization
	Wire.begin();
	mpu.begin();
	mpu.calcOffsets();
	Serial.println("IMU sensor calibrated.");

	// Servo initializations
	servo_sensor.attach(SERVO_SENSOR_PIN);
	servo_hitter.attach(SERVO_HITTER_PIN);
}

// Program loop function //
void loop() {
	startGame = digitalRead(START_BUTTON_PIN);		// Game starts if start button is pushed
	gameState = green_light;						// Initial game state
	timer = 60000;									// Timer at 60 seconds
	stateTimer = 0;									// Timer of current game state
	firstRun = true;								// Flag for first run
	servo_sensor.write(90);							// Initial angle of sensor servo
	servo_hitter.write(90);							// Initial angle of hitter servo
	tone(BUZZER_PIN, 0);							// Initial game buzzer sound

	mpuMove(MOTOR_STEP, mpu);

	// Game loop
	if (startGame) {
		startTime = millis();   	// Keep track of the starting time for reference
		endLoopTime = startTime;	// Initial time passed is 0 seconds, checked at beginning of game while loop

		while(startGame) {
			// Subtracting time to run through loop for time left and display
			timer = (endLoopTime - startTime);
			if (checkTimer(timer, display) == 1) {
				break;
			}

			mpuMove(MOTOR_STEP, mpu);

			// Time left in current state
			if (firstRun == true) {			// Ignore end of state time if first loop
				firstRun = false;
			} else {
				endStateTime = millis();	// Time used to check if state timer has ended
			}

			// If state timer is 0 then switch state
			if (endStateTime - startStateTime >= stateTimer) {
				if (gameState == red_light) {	// Switch state to green light
					gameState = green_light;
					greenLight();
				} else {						// Switch state to red light
					gameState = red_light;
					redLight();

					sumToAverageDistance = 0;

					// Averaging the distance collected to counter random outliers
					for (int i = 0; i < 100; i++) {
						sumToAverageDistance += usensor.measureDistanceCm();
					}
					redLightDistance = sumToAverageDistance / 100;	// Recording initial distance for from distance sensor to compare with player distance
					Serial.println(redLightDistance);
				}

				stateTimer = randTime() * 1000;		// Random time assigned to current state
				startStateTime = millis();			// Start time of state for reference
			}

			// Check if player moved
			if (gameState == red_light) {
				checkDistanceSum = 0;

				// Measuring distance
				for (int i = 0; i < 100; i++) {
					checkDistanceSum += usensor.measureDistanceCm();
				}
				checkDistanceAverage = checkDistanceSum / 100;

				if (checkDistanceAverage < 8.00) {	// If player is less than 8cm from distance sensor
					Serial.println("YOU WIN!!!");
					display.zero();

					// Celebration
					for (int i = 0; i < 10; i++) {
						digitalWrite(GREEN_LIGHT, HIGH);
						digitalWrite(RED_LIGHT, LOW);
						delay(100);

						digitalWrite(GREEN_LIGHT, LOW);
						digitalWrite(RED_LIGHT, HIGH);
						delay(100);
					}

					break;

				} else if (	// If player movement was detected
				checkDistanceAverage < redLightDistance - redLightDistanceBuffer
				|| checkDistanceAverage > redLightDistance + redLightDistanceBuffer
				) {
					display.zero();
					servo_hitter.write(180);
					delay(200);
					Serial.println("GAME OVER! YOU LOSE!");
					break;
				} // Else continue
			}

			endLoopTime = millis();
		}
	}
}
