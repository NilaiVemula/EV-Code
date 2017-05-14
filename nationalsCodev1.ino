/*
White Station High School Science Olympiad Electric Vehicle Code
  Written by Nilai Vemula & Justin Du 
*/

/* Stuff to change at competition */
// Distance where car should switch from fast to braking
const long CHANGE_SPEED_DISTANCE = 2;
//Distance to end the rapidly braking phase
const long END_BRAKING_DISTANCE = 2.1
// Final distance
const long FINAL_DISTANCE = 4;

/* Wiring Information */

  /* Encoder */
    // Red - 5V
    // Black - GND
    // Signal A in D2
    const int ENCODER_A = 2; 
    // Signal B in D3
    const int ENCODER_B = 3; 

  /* Motor Shield */

    // Motor PWM - connected to pin 5 (Check jumper).
    const int PIN_PWM = 5;
    // Motor DIR - connected to pin 4 (Check jumper).
    const int PIN_DIR = 4;

// Declare variables
long ENCODER_VALUE = 0;
long REAL_DISTANCE = 0;

// Set initial values
void reset() {
  ENCODER_VALUE = 0;
  REAL_DISTANCE = 0; 
}

// Setup function
void setup() {

  // Call the reset
  reset();

  // Error handling
  Serial.begin(9600);

  // Attach encoders
  pinMode( ENCODER_A, INPUT_PULLUP );
  pinMode( ENCODER_B, INPUT_PULLUP );

  // Attach encoder interrupt
  attachInterrupt(0, encoderPinChangeA, CHANGE );
  attachInterrupt(1, encoderPinChangeB, CHANGE );

  // Motor Speed
  pinMode(PIN_PWM, OUTPUT);

  // Motor Direction
  pinMode(PIN_DIR, OUTPUT);
}

// Loop - FOREVER
void loop() {

  // Print encoder value
  Serial.print("Encoder value: ");
  Serial.println(ENCODER_VALUE);

  // Calculate real distance
  // Convert to rotations (600 pulses per rotation)
  // .123825 is the diameter of the wheel
  REAL_DISTANCE = abs( ( float(ENCODER_VALUE) / 600 ) *  3.14159 * 0.123825 );

  // Print real distance
  Serial.print("Real Distance in meters: ");
  Serial.println(REAL_DISTANCE);

  // Control motor based on the encoder value
  if ( REAL_DISTANCE < CHANGE_SPEED_DISTANCE ) {
    // Fast speed - ranges from 0(slow) to 255(fast)
    Serial.println("FAST");
    analogWrite(PIN_PWM, 150);
    digitalWrite(PIN_DIR, LOW);
  }
  else if ( REAL_DISTANCE >= CHANGE_SPEED_DISTANCE && REAL_DISTANCE <= END_BRAKING_DISTANCE ) {
    // Rapidly brake by putting motor in opposite direction
    Serial.println("BRAKING");
    analogWrite(PIN_PWM, 25);
    digitalWrite(PIN_DIR, HIGH);
  }
  else if ( REAL_DISTANCE >= FINAL_DISTANCE) {
    // Start and stop really slowly
    Serial.println("FINISHING");
    analogWrite(PIN_PWM, 0); //Turn off motor
    digitalWrite(PIN_DIR, LOW); 
    delay(250) //Off for 0.25 seconds
    analogWrite(PIN_PWM, 50); //Slowly moving forward
    digitalWrite(PIN_DIR, LOW);
    delay(250) //Slow for 0.25 seconds
    analogWrite(PIN_PWM, 50); //Sets motor backward
    digitalWrite(PIN_DIR, LOW);
    delay(50) //Backward for 0.05 seconds
    return;
  }
}

/* DO NOT EDIT - USED TO UPDATE ENCODER VALUES */
void encoderPinChangeA() {
  // Check if encoders equal to each other
  ENCODER_VALUE += digitalRead(ENCODER_A) == digitalRead(ENCODER_B) ? -1 : 1;
}

void encoderPinChangeB() {
  // Check if encoders equal to each other
  ENCODER_VALUE += digitalRead(ENCODER_A) != digitalRead(ENCODER_B) ? -1 : 1;
}
