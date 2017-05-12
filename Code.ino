//ENCODER STUFF



// Red - 5V
// Black - GND
const int encoder_a = 2; // use one white wire here
const int encoder_b = 3; // use the other white wire here
long encoder = 0;

void setup() {
Serial.begin(9600);
pinMode(encoder_a, INPUT_PULLUP);
pinMode(encoder_b, INPUT_PULLUP);

attachInterrupt(0, encoderPinChangeA, CHANGE);
attachInterrupt(1, encoderPinChangeB, CHANGE);
}

void loop() {
Serial.println(encoder);
}

void encoderPinChangeA() {
encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? -1 : 1;
}

void encoderPinChangeB() {
encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? -1 : 1;
}




// MOTOR STUFF

/*******************************************************************************
 * IO DEFINITION                                                                *
 *******************************************************************************/

// PWM is connected to pin 3.
const int pinPwm = 3;

// DIR is connected to pin 2.
const int pinDir = 2;



/*******************************************************************************
 * PRIVATE GLOBAL VARIABLES                                                     *
 *******************************************************************************/

// Speed of the motor.
static int iSpeed = 0;

// Acceleration of the motor.
static int iAcc = 1;


/*******************************************************************************
 * FUNCTIONS                                                                    *
 *******************************************************************************/

// The setup routine runs once when you press reset.
void setup() {                
  // Initialize the PWM and DIR pins as digital outputs.
  pinMode(pinPwm, OUTPUT);
  pinMode(pinDir, OUTPUT);
}



// The loop routine runs over and over again forever.
void loop() {
  
  // Control the motor according to the speed value.
  // Positive speed value = CW,
  // Negative speed value = CCW.
  if (iSpeed >= 0) {
    analogWrite(pinPwm, iSpeed);
    digitalWrite(pinDir, LOW);
  } 
  else {
    analogWrite(pinPwm, -iSpeed);
    digitalWrite(pinDir, HIGH);
  }
  
  // Increase/Decrease the speed according to the acceleration.
  iSpeed += iAcc;
  
  // Change the acceleration sign when full speed is reached.
  if ((iSpeed >= 255) || (iSpeed <= -255)) {
    iAcc = -iAcc;
  }
  
  
  delay(10);
}







///////FINAL CODE///////////////


//Values to enter//

long slow_distance_1 = ;    ////INSERT BEGINNING SLOW DISTANCE////
long fast_distance_1 = ;    ////INSERT MIDDLE FAST DISTANCE////
long slow_distance_1 = ;    ////INSERT END SLOW DISTANCE////
long final_distance = ;     ////INSERT FINAL DISTANCE////

//Wiring Information//

//Encoder//

// Red - 5V
// Black - GND
//Signal A in D2
const int encoder_a = 2; 
//Signal B in D3
const int encoder_b = 3; 

//Motor Shield//

// Motor PWM is connected to pin 5 (Check jumper).
const int pinPwm = 5;
// Motor DIR is connected to pin 2 (Check jumper).
const int pinDir = 4;

long encoder = 0;

//Actual Code//
void setup() {
Serial.begin(9600);
pinMode(encoder_a, INPUT_PULLUP);
pinMode(encoder_b, INPUT_PULLUP);

attachInterrupt(0, encoderPinChangeA, CHANGE);
attachInterrupt(1, encoderPinChangeB, CHANGE);

pinMode(pinPwm, OUTPUT);
pinMode(pinDir, OUTPUT);
}

void loop() {
Serial.println(encoder);
}

void encoderPinChangeA() {
encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? -1 : 1;
}

void encoderPinChangeB() {
encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? -1 : 1;
}

while encoder < slow_distance_1


