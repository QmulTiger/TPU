 // X-axis pins (CNC Shield)
  #define X_STEP 2
  #define X_DIR 5

  // Y-axis pins (CNC Shield)
  #define Y_STEP 3
  #define Y_DIR 6

  // Movement parameters
  const int stepsPerMove = 200;        // Adjust (200 = 1 full rotation)
  const int stepDelay = 1000;          // Microseconds between steps

  void setup() {
    pinMode(X_STEP, OUTPUT);
    pinMode(X_DIR, OUTPUT);
    pinMode(Y_STEP, OUTPUT);
    pinMode(Y_DIR, OUTPUT);
  }

  void moveMotor(int stepPin, int dirPin, bool direction, int steps) {
    digitalWrite(dirPin, direction ? HIGH : LOW);
    for (int i = 0; i < steps; i++) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepDelay);
    }
    delay(1000); // pause after movement
  }

  void loop() {
    // X-axis forward
    moveMotor(X_STEP, X_DIR, true, stepsPerMove);
    // X-axis backward
    moveMotor(X_STEP, X_DIR, false, stepsPerMove);

    // Y-axis forward
    moveMotor(Y_STEP, Y_DIR, true, stepsPerMove);
    // Y-axis backward
    moveMotor(Y_STEP, Y_DIR, false, stepsPerMove);
  }