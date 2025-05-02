#define X_LIMIT 9   // Shared X-MIN and X-MAX
#define Y_LIMIT 10  // Shared Y-MIN and Y-MAX

void setup() {
  pinMode(X_LIMIT, INPUT_PULLUP);
  pinMode(Y_LIMIT, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Limit Switch Test (Shared X/Y Pins)");
  Serial.println("Press any X or Y limit switch to see output.");
}

void loop() {
  if (digitalRead(X_LIMIT) == LOW) {
    Serial.println("X limit switch triggered");
    delay(500);  // debounce delay
  }

  if (digitalRead(Y_LIMIT) == LOW) {
    Serial.println("Y limit switch triggered");
    delay(500);  // debounce delay
  }
}
