#include <SimpleFOC.h>

BLDCMotor motor = BLDCMotor(11);  // GM4108: 11 pole pairs
BLDCDriver3PWM driver = BLDCDriver3PWM(5, 9, 6, 8); // A, B, C, EN

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);  // Enable motor driver

  driver.voltage_power_supply = 12;
  driver.init();
  motor.linkDriver(&driver);

  motor.controller = MotionControlType::velocity_openloop;
  motor.voltage_limit = 6;
  motor.init();
  motor.initFOC();

  Serial.println("Motor initialized, running open-loop...");
}

void loop() {
  motor.loopFOC();
  motor.move(3.0);  // positive = forward
}
