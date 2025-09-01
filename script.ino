#include <elapsedMillis.h>
#include <IRremote.hpp>
#include <Servo.h>

#define IR_RECEIVE_PIN 2
#define motorPin 9
#define servoPin 8

#define POWER_BTN 0xBA45FF00
#define FUNC_BTN 0xB847FF00
#define UP_BTN 0xF609FF00
#define DOWN_BTN 0xF807FF00
#define LEFT_BTN 0xBB44FF00
#define RIGHT_BTN 0xBC43FF00
#define VOL_UP_BTN 0xB946FF00
#define VOL_DOWN_BTN 0xEA15FF00

#define OSC_DELTA 60
#define OSC_START 35
#define OSC_FINISH 100

#define CENTER 70

int angle;
int flag;
int osc;
int dir;
int pause;
Servo servo;
elapsedMillis oscTimer;
elapsedMillis pauseTimer;

void setup() {
  // IR setup
  Serial.begin(115200); 
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  pinMode(motorPin, OUTPUT); 
  flag = 0;
  osc = 0;
  pause = 0;
  angle = CENTER;
  dir = 1;
  // servo setup
  servo.attach(servoPin);
  servo.write(angle);
}

void loop() {
  if (IrReceiver.decode()) {
    unsigned long irValue = IrReceiver.decodedIRData.decodedRawData;
    switch (irValue) {
      case POWER_BTN:
        flag = flag ^ 1;
        osc = 0;
        break;
      case FUNC_BTN:
        osc = osc ^ 1;
        break;
    }
    if (irValue != 0) {
      Serial.println(irValue, HEX);
      Serial.println("power");
      Serial.println(flag);
      Serial.println("osc");
      Serial.println(osc);
    }
    digitalWrite(motorPin, flag == 1 ? HIGH : LOW);
    IrReceiver.resume();
  }
  // update oscillation (only if fan is on)
  if (flag == 1 && osc == 1) {
    updateOscillation();
  } else if (flag == 1) {
    servo.write(CENTER); // stay in the center
  }
}

void updateOscillation() {
  if (pause) {
    if (pauseTimer >= 500) {
      pause = false;
      pauseTimer = 0;
    }
    return;
  }
  if (oscTimer >= OSC_DELTA) {
    oscTimer = 0;
    servo.write(angle);
    angle += dir;
    if (angle >= OSC_FINISH || angle <= OSC_START) {
      dir *= -1;
      pause = true;
      pauseTimer = 0;
    }
  }
}