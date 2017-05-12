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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///FINAL CODE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//VERY IMPORTANT SETUP INFO FIRST///////////////////////////////////////////////////////////////////////////////
  //Values to enter//

const long change_speed_distance = ;    ////Distance at where the car should switch from fast to slow (8.5m) ////
const long final_distance = ;     ////INSERT FINAL DISTANCE ////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Wiring Information///////////////////////////////////////////////////////////////////////////////////////////////
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
    // Motor DIR is connected to pin 4 (Check jumper).
    const int pinDir = 4;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Setting initial values to zero//
long encoder = 0;
long REAL_DISTANCE = 0;

//Setting everything up//
void setup() {
Serial.begin(9600); // Prepares the seriel outputter //
pinMode(encoder_a, INPUT_PULLUP); //Configures the encoder signal as an input//
pinMode(encoder_b, INPUT_PULLUP); //Configures the encoder signal as an input//

attachInterrupt(0, encoderPinChangeA, CHANGE); //Configures the encoder signal as an "interrupt"//
attachInterrupt(1, encoderPinChangeB, CHANGE); //Configures the encoder signal as an "interrupt"//

pinMode(pinPwm, OUTPUT); //Configures motor speed as output//
pinMode(pinDir, OUTPUT); //Configures motor direction as output//
}

//Repeats over and over again//
void loop() {
Serial.println("Encoder value"); //Prints label//
Serial.print(encoder); //Prints encoder value//
REAL_DISTANCE = ((encoder/600)*(2*3.14159*0.123825)) ///Conversion///
Serial.println("Real Distance value (m)"); //Prints label//
Serial.print(REAL_DISTANCE); //Prints distance value//
}
///////////////////////////////////////////////////////////////////////////////////////////
/// DO NOT EDIT///
/// Used to update encoder values ///
void encoderPinChangeA() {
encoder += digitalRead(encoder_a) == digitalRead(encoder_b) ? -1 : 1;
}

void encoderPinChangeB() {
encoder += digitalRead(encoder_a) != digitalRead(encoder_b) ? -1 : 1;
}
///////////////////////////////////////////////////////////////////////////////////////////

//Controlling the motor based on the encoder value//
while(REAL_DISTANCE < change_speed_distance){ ////When the car is at a distance smaller than the changing_speed_location, the motor will go fast////
  analogWrite(pinPwm, 200); //fast speed//
  digitalWrite(pinDir, LOW);
}

while(REAL_DISTANCE >= change_speed_distance){ ////When the car is at a distance greater than the changing_speed_location, the motor will go slowly////
  analogWrite(pinPwm, 50); //slow speed//
  digitalWrite(pinDir, LOW);
}

if (REAL_DISTANCE >= final_distance)
{
  delay(10000);
}

