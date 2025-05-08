#include <SoftwareSerial.h>

// Connect screen TX to Arduino pin 10
// (leave screen RX disconnected for now to avoid accidental writes)
SoftwareSerial screenSerial(10, 11); // RX, TX (TX not used here)

void setup() {
  Serial.begin(115200);         // USB serial to PC
  screenSerial.begin(115200);   // Change this if needed (9600, 250000, etc.)

  Serial.println("Listening to screen...");
}

void loop() {
  // Read from screen and print to Serial Monitor
  if (screenSerial.available()) {
    char c = screenSerial.read();
    Serial.write(c); // Use write() to preserve binary data
  }
}
