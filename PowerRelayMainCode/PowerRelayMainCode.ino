#include <SoftwareSerial.h>

SoftwareSerial screenSerial(11, 10); // RX, TX (screen TX -> pin 10)

const int relayPins[4] = {4, 5, 6, 7};
bool relayStates[4] = {false, false, false, false};

void setup() {
  Serial.begin(115200);
  screenSerial.begin(115200);

  // Set relay pins as output
  for (int i = 0; i < 4; i++) {
    pinMode(relayPins[i], OUTPUT);
    digitalWrite(relayPins[i], HIGH); // HIGH = OFF on active-low relays
  }

  Serial.println("Relay control ready.");
}

void loop() {
  if (screenSerial.available()) {
    String line = screenSerial.readStringUntil('\n');
    line.trim();

    Serial.println("Received: " + line);

    if (line == "A21 X") toggleRelay(0);
    else if (line == "A21 Y") toggleRelay(1);
    else if (line == "A21 Z") toggleRelay(2);
    else if (line == "A21 C") toggleRelay(3);
  }
}

void toggleRelay(int index) {
  relayStates[index] = !relayStates[index];
  digitalWrite(relayPins[index], relayStates[index] ? LOW : HIGH); // LOW = ON for active-low relays

  Serial.print("Relay ");
  Serial.print(index + 1);
  Serial.println(relayStates[index] ? " ON" : " OFF");
}
