#include "HexapodController.h"

namespace hexapod {

HexapodController::HexapodController(Adafruit_PWMServoDriver& driver)
    : pwm_(driver),
      stepDeltaDeg_(kDefaultStepDeltaDeg),
      liftDeltaDeg_(kDefaultLiftDeltaDeg),
      stepDelayMs_(kDefaultStepDelayMs) {
  for (uint8_t i = 0; i < kServoCount; ++i) {
    homeDeg_[i] = kServoHomeDeg[i] + kServoTrimDeg[i];
  }
}

void HexapodController::begin() {
  pwm_.begin();
  pwm_.setPWMFreq(kPwmFrequencyHz);
}

void HexapodController::stand(uint16_t settleDelayMs) {
  for (uint8_t i = 0; i < kServoCount; ++i) {
    setServoDeg(static_cast<ServoChannel>(i), homeDeg_[i]);
  }
  delay(settleDelayMs);
}

void HexapodController::tripodStep() {
  // Sequence kept intentionally close to the generated gait baseline.
  setTripodKnees(kTripodAKnee, true);
  applyDelay();

  setTripodBase(kTripodABase, true);
  applyDelay();

  setTripodKnees(kTripodAKnee, false);
  applyDelay();

  setTripodKnees(kTripodBKnee, true);
  applyDelay();

  setTripodBase(kTripodABase, false);
  applyDelay();

  setTripodKnees(kTripodBKnee, true);
  applyDelay();

  setTripodBase(kTripodBBase, true);
  applyDelay();

  setTripodKnees(kTripodBKnee, false);
  applyDelay();

  setTripodKnees(kTripodAKnee, true);
  applyDelay();

  setTripodBase(kTripodBBase, false);
  applyDelay();
}

void HexapodController::walkSteps(uint16_t stepCount) {
  for (uint16_t i = 0; i < stepCount; ++i) {
    tripodStep();
  }
}

void HexapodController::setStepDelta(int valueDeg) {
  stepDeltaDeg_ = constrain(valueDeg, 1, 45);
}

void HexapodController::setLiftDelta(int valueDeg) {
  liftDeltaDeg_ = constrain(valueDeg, 1, 45);
}

void HexapodController::setStepDelay(uint16_t valueMs) {
  stepDelayMs_ = constrain(valueMs, static_cast<uint16_t>(20),
                           static_cast<uint16_t>(1000));
}

int HexapodController::stepDelta() const { return stepDeltaDeg_; }

int HexapodController::liftDelta() const { return liftDeltaDeg_; }

uint16_t HexapodController::stepDelay() const { return stepDelayMs_; }

void HexapodController::printStatus(Stream& out) const {
  out.println(F("Controller status"));
  out.print(F("stepDeltaDeg="));
  out.println(stepDeltaDeg_);
  out.print(F("liftDeltaDeg="));
  out.println(liftDeltaDeg_);
  out.print(F("stepDelayMs="));
  out.println(stepDelayMs_);
}

void HexapodController::setServoDeg(ServoChannel channel, int angleDeg) {
  const int clampedDeg = constrain(angleDeg, 0, 180);
  const int pulse = map(clampedDeg, 0, 180, kServoPulseMin, kServoPulseMax);
  pwm_.setPWM(channel, 0, pulse);
}

void HexapodController::setTripodKnees(const ServoChannel (&group)[3], bool up) {
  for (uint8_t i = 0; i < 3; ++i) {
    const ServoChannel channel = group[i];
    setServoDeg(channel, kneeTargetDeg(channel, up));
  }
}

void HexapodController::setTripodBase(const ServoChannel (&group)[3],
                                      bool forward) {
  for (uint8_t i = 0; i < 3; ++i) {
    const ServoChannel channel = group[i];
    setServoDeg(channel, baseTargetDeg(channel, forward));
  }
}

int HexapodController::baseTargetDeg(ServoChannel channel, bool forward) const {
  const int sideDirection = isLeftBase(channel) ? 1 : -1;
  const int travelDirection = forward ? 1 : -1;
  return homeDeg_[channel] + (sideDirection * travelDirection * stepDeltaDeg_);
}

int HexapodController::kneeTargetDeg(ServoChannel channel, bool up) const {
  if (!up) {
    return homeDeg_[channel];
  }

  const int sideDirection = isLeftKnee(channel) ? 1 : -1;
  return homeDeg_[channel] + (sideDirection * liftDeltaDeg_);
}

bool HexapodController::isLeftBase(ServoChannel channel) const {
  switch (channel) {
    case FrontLeftBase:
    case LeftBase:
    case BackLeftBase:
      return true;
    default:
      return false;
  }
}

bool HexapodController::isLeftKnee(ServoChannel channel) const {
  switch (channel) {
    case FrontLeftKnee:
    case LeftKnee:
    case BackLeftKnee:
      return true;
    default:
      return false;
  }
}

void HexapodController::applyDelay() const { delay(stepDelayMs_); }

}  // namespace hexapod
