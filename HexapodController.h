#ifndef HEXAPOD_CONTROLLER_H
#define HEXAPOD_CONTROLLER_H

#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

#include "HexapodConfig.h"

namespace hexapod {

class HexapodController {
 public:
  explicit HexapodController(Adafruit_PWMServoDriver& driver);

  void begin();
  void stand(uint16_t settleDelayMs = kStandSettleDelayMs);
  void tripodStep();
  void walkSteps(uint16_t stepCount);

  void setStepDelta(int valueDeg);
  void setLiftDelta(int valueDeg);
  void setStepDelay(uint16_t valueMs);

  int stepDelta() const;
  int liftDelta() const;
  uint16_t stepDelay() const;

  void printStatus(Stream& out) const;

 private:
  Adafruit_PWMServoDriver& pwm_;
  int homeDeg_[kServoCount];
  int stepDeltaDeg_;
  int liftDeltaDeg_;
  uint16_t stepDelayMs_;

  void setServoDeg(ServoChannel channel, int angleDeg);
  void setTripodKnees(const ServoChannel (&group)[3], bool up);
  void setTripodBase(const ServoChannel (&group)[3], bool forward);
  int baseTargetDeg(ServoChannel channel, bool forward) const;
  int kneeTargetDeg(ServoChannel channel, bool up) const;
  bool isLeftBase(ServoChannel channel) const;
  bool isLeftKnee(ServoChannel channel) const;
  void applyDelay() const;
};

}  // namespace hexapod

#endif
