//Made by LUCAS
//This is open source, and only for the ARDUINO MEGA
//Free to use

#include <AFMotor.h>      //Includes the Adafruit Motor Shield Library


AF_DCMotor motor1(1); // DC motor is hooked up to M1                                          
AF_DCMotor motor2(2); // DC motor is hooked up to M2
//==================INSERT VALUES HERE \/ ====================================================================================================
int pin1 = 22;    // CHANGE 22 TO THE NUMBER OF PIN YOU ARE USING!!!!   Digital pins connected to the radio receiver ports =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int pin2 = 30;    //CHANGE 30 TO THE NUMBER OF PIN YOU ARE USING!!!!    ^ The receiver is the small black box w/ a red antenna=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int buzzpin = 40;
//Make sure that pin1 is hooked up to the throttle port on the receiver (port 2 on 9x)
//and that pin2 is hooked up to the rudder port on the receiver (port 4 on 9x)


int neutralh = 1500;//PUT YOUR HIGH NEUTRAL VALUE HERE. REPLACE 1500  =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int neutrall = 1420;//PUT YOUR LOW NEUTRAL VALUE HERE. REPLACE 1420  =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~
int maxval = 1870; //PUT YOUR MAX VALUE HERE   REPLACE 1870           =~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~==~=~==~=~==~=~==~=~==~=~==~=~=
int minval = 1050; // PUT YOUR MIN VALUE HERE           REPLACE 1050  =~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~=~==~
//==================INSERT VALUES HERE /\ ====================================================================================================

void setup() {
  Serial.begin(9600);           // set up Serial monitor at 9600 bps

motor1.run(RELEASE);
motor2.run(RELEASE);          //^ This is to make sure the motors dont start w/o control

  pinMode(pin1, INPUT); //Setting up RC input pins
  pinMode(pin2, INPUT); //Setting up RC input pins
  pinMode(buzzpin, OUTPUT);
  
}

void loop() {
  int sV1;    //These are all different speed values that will be mapped
  int sV2;
  int sV3;
  int sV4;
  int sV5;
  int sV6;

  int speedValue = pulseIn(pin1, HIGH); //Getting the pulse in value from pin 1 and defining pin1 as speed
  
  int directionValue = pulseIn(pin2, HIGH); //Getting the pulse in value from pin 2 and defining pin1 as turning

  //Serial.println(speedValue);
  //Serial.println(directionValue);
  //These can be printed for debugging


  

    if (speedValue >= 1420 && speedValue <= 1500) {     //If the sticks are Neutral, then stay still

      motor1.run(RELEASE);    //releases motors
      motor2.run(RELEASE);   // releases motors

      delay(50);            //checks again every 50 micro Seconds
    }


    if (speedValue > 1500 && directionValue >= 1420 && directionValue <= 1500) { //if the throttle is up and turning is neutral

      sV1 = map(speedValue, 1500, 1870, 140, 255);      //Maps the pulseIn speedvalue to numbers the motors can read
                                                   //Motor is set to 140-255 instead of 0-255 so that the motor doesnt stall if 
                                                   //it is powered at too low of a level
                                                   
      if(sV1 > 255){ //If the speed value is over 255 then set it to 255.                             .
        sV1 = 255;    //This prevents overpowering the motor if there is a pulsein glitch                          
      }
     
      motor1.setSpeed(sV1); // Sets the speed of motor1 to the speedValue
      motor2.setSpeed(sV1); // Sets the speed of motor2 to the speedValue
      motor1.run(FORWARD);  //Makes the motor go forward at the speed defined above
      motor2.run(FORWARD);  //Makes the motor go forward at the speed defined above
      delay(50);            //Repeat every 50 micro seconds
      
    }


    if (directionValue > neutralh && speedValue > neutralh) {     //Speed value is forward, direction is right

      sV2 = map(speedValue, neutralh, maxval, 140, 255);    //RIGHT FORWARD

      if(sV2 > 255){
        sV2 = 255;
      }

      motor1.setSpeed(0);
      motor2.setSpeed(sV2);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      Serial.println("B");
      delay(50);
    }

    if (directionValue < neutrall && speedValue > neutralh) { //Speed is forward, Direction is left

      sV3 = map(speedValue, neutralh, maxval, 140, 255);    //LEFT FORWARD

      if(sV3 > 255){
        sV3 = 255;
      }

      motor1.setSpeed(sV3);
      motor2.setSpeed(0);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
     Serial.println("C");

      delay(50);
    }

    if (speedValue < neutrall && directionValue >= neutrall && directionValue <= neutralh) {      //Speed is reverse and direction value is centered

      sV4 = map(speedValue, neutrall, minval, 140, 255);      //REVERSE

      if(sV4 > 255){
        sV4 = 255;
      }

      motor1.setSpeed(sV4);
      motor2.setSpeed(sV4);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      Serial.println("D");

      delay(50);
    }

    if (directionValue > neutralh && speedValue < neutrall) {

      sV5 = map(speedValue, neutralh, minval, 140, 255);  //BACK RIGHT

      if(sV5 > 255){
        sV5 = 255;
      }

      motor1.setSpeed(sV5);
      motor2.setSpeed(0);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      Serial.println("E");

      delay(50);
    }

    if (directionValue < neutrall && speedValue < neutrall) {

      sV6 = map(speedValue, neutralh, minval, 140, 255);    //BACK LEFT

      if(sV6 > 255){
        sV6 = 255;
      }

      motor1.setSpeed(0);
      motor2.setSpeed(sV6);
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
     Serial.println("F");

      delay(50);
    
  }
}
