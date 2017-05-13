/*
White Station High School Science Olympiad Electric Vehicle Code
  Written by Justin Du & Nilai Vemula 
*/

/* Stuff to change at competition */
// Distance where car should switch from fast to slow
const long CHANGE_SPEED_DISTANCE = 8.5;
// Final distance
const long FINAL_DISTANCE = 9.5;

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

// Set initial values
void reset() {
  long ENCODER_VALUE = 0;
  long REAL_DISTANCE = 0; 
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
  REAL_DISTANCE = abs( ( ( encoder / 600 ) * ( 3.14159 * 0.123825 ) ) )

  // Print real distance
  Serial.print("Real Distance in meters: ");
  Serial.println(REAL_DISTANCE);

  // Control motor based on the encoder value
  if ( REAL_DISTANCE < CHANGE_SPEED_DISTANCE ) {
    // Fast speed - ranges from 0(slow) to 255(fast)
    analogWrite(pinPwm, 200);
    digitalWrite(pinDir, LOW);
  }
  else {
    // Slow speed
    analogWrite(pinPwm, 50);
    digitalWrite(pinDir, LOW);
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

