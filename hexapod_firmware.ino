#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Generated from Hexapod Gait Visualizer
// speed=1.20, stride=58, lift=34, duty=0.62
// yawGain=1.00, kneeGain=1.00, tripodStepMs=200

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN 150
#define SERVOMAX 600

const int frontLeftBase = 0;
const int leftBase = 1;
const int backLeftBase = 2;
const int backRightBase = 3;
const int rightBase = 4;
const int frontRightBase = 5;

const int frontLeftKnee = 6;
const int leftKnee = 7;
const int backLeftKnee = 8;
const int backRightKnee = 9;
const int rightKnee = 10;
const int frontRightKnee = 11;

const int HOME = 135;
const int STEP_DELTA = 15;
const int LIFT_DELTA = 15;
const int GEN_DELAY = 167;

const int LEFT_FORWARD = HOME + STEP_DELTA;
const int LEFT_BACKWARD = HOME - STEP_DELTA;
const int RIGHT_FORWARD = HOME - STEP_DELTA;
const int RIGHT_BACKWARD = HOME + STEP_DELTA;

const int LEFT_KNEE_UP = HOME + LIFT_DELTA;
const int RIGHT_KNEE_UP = HOME - LIFT_DELTA;

void setServoDeg(int channel, int angle) {
  angle = constrain(angle, 0, 180);
  int pulse = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(channel, 0, pulse);
}

void applyDelay() {
  delay(GEN_DELAY);
}

void stand() {
  for (int i = 0; i < 12; i++) {
    setServoDeg(i, HOME);
  }
  delay(300);
}

void liftKneesB1B2B3() {
  setServoDeg(frontLeftKnee, LEFT_KNEE_UP);
  setServoDeg(rightKnee, RIGHT_KNEE_UP);
  setServoDeg(backLeftKnee, LEFT_KNEE_UP);
  applyDelay();
}

void liftKneesB4B5B6() {
  setServoDeg(frontRightKnee, RIGHT_KNEE_UP);
  setServoDeg(leftKnee, LEFT_KNEE_UP);
  setServoDeg(backRightKnee, RIGHT_KNEE_UP);
  applyDelay();
}

void setKneesDownB1B2B3() {
  setServoDeg(frontLeftKnee, HOME);
  setServoDeg(rightKnee, HOME);
  setServoDeg(backLeftKnee, HOME);
  applyDelay();
}

void setKneesDownB4B5B6() {
  setServoDeg(frontRightKnee, HOME);
  setServoDeg(leftKnee, HOME);
  setServoDeg(backRightKnee, HOME);
  applyDelay();
}

void moveLegsB1B2B3Forward() {
  setServoDeg(frontLeftBase, LEFT_FORWARD);
  setServoDeg(rightBase, RIGHT_FORWARD);
  setServoDeg(backLeftBase, LEFT_FORWARD);
  applyDelay();
}

void moveLegsB1B2B3Backwards() {
  setServoDeg(frontLeftBase, LEFT_BACKWARD);
  setServoDeg(rightBase, RIGHT_BACKWARD);
  setServoDeg(backLeftBase, LEFT_BACKWARD);
  applyDelay();
}

void moveLegsB4B5B6Forward() {
  setServoDeg(backRightBase, RIGHT_FORWARD);
  setServoDeg(leftBase, LEFT_FORWARD);
  setServoDeg(frontRightBase, RIGHT_FORWARD);
  applyDelay();
}

void moveLegsB4B5B6Backwards() {
  setServoDeg(backRightBase, RIGHT_BACKWARD);
  setServoDeg(leftBase, LEFT_BACKWARD);
  setServoDeg(frontRightBase, RIGHT_BACKWARD);
  applyDelay();
}

void tripodStep() {
  liftKneesB1B2B3();
  moveLegsB1B2B3Forward();
  setKneesDownB1B2B3();
  liftKneesB4B5B6();
  moveLegsB1B2B3Backwards();
  liftKneesB4B5B6();
  moveLegsB4B5B6Forward();
  setKneesDownB4B5B6();
  liftKneesB1B2B3();
  moveLegsB4B5B6Backwards();
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(50);
  stand();
}

void loop() {
  tripodStep();
}
