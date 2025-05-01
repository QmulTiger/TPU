// X-axis motor pins
#define X_STEP 2
#define X_DIR 5

// Y-axis motor pins
#define Y_STEP 3
#define Y_DIR 6

// Limit switch pins (shared min+max per axis)
#define X_LIMIT 10
#define Y_LIMIT 9

// Step timing
const int stepDelay = 1000;  // microseconds

void setup() {
  pinMode(X_STEP, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(Y_STEP, OUTPUT);
  pinMode(Y_DIR, OUTPUT);

  pinMode(X_LIMIT, INPUT_PULLUP);
  pinMode(Y_LIMIT, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("XY Motor and Limit Test Started");
}

// V2 edit: Back off switch until it's no longer pressed
void backOffUntilReleased(int stepPin, int dirPin, int limitPin, bool moveAwayDir, const char* label) {
  if (digitalRead(limitPin) == LOW) {
    Serial.print(label); Serial.println(": Switch still pressed. Backing off until released...");
    digitalWrite(dirPin, moveAwayDir ? HIGH : LOW);
    int steps = 0;
    while (digitalRead(limitPin) == LOW) {
      digitalWrite(stepPin, HIGH);
      delayMicroseconds(stepDelay);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(stepDelay);
      steps++;
    }
    Serial.print(label); Serial.print(": Switch released after ");
    Serial.print(steps); Serial.println(" steps.");
//    delay(500); // optional pause
  }
}
// just move 
void moveToLimit(int stepPin, int dirPin, int limitPin, bool dir, const char* label) {
  backOffUntilReleased(stepPin, dirPin, limitPin, dir, label); // ensure switch is cleared
  digitalWrite(dirPin, dir ? HIGH : LOW);

  Serial.print("Moving ");
  Serial.print(label);
  Serial.println(dir ? " forward..." : " backward...");

  while (digitalRead(limitPin) == HIGH) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(stepDelay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(stepDelay);
  }

  Serial.print(label);
  Serial.println(" limit switch triggered. Stopping.");
  delay(500);
}

void loop() {
  moveToLimit(X_STEP, X_DIR, X_LIMIT, true, "X");
  delay(1000);
  moveToLimit(X_STEP, X_DIR, X_LIMIT, false, "X");

  delay(1000);

  moveToLimit(Y_STEP, Y_DIR, Y_LIMIT, true, "Y");
  delay(1000);
  moveToLimit(Y_STEP, Y_DIR, Y_LIMIT, false, "Y");

  delay(2000);
}
