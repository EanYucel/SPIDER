#ifndef HEXAPOD_CONFIG_H
#define HEXAPOD_CONFIG_H

#include <Arduino.h>

namespace hexapod {

constexpr uint8_t kServoCount = 12;
constexpr uint16_t kServoPulseMin = 150;
constexpr uint16_t kServoPulseMax = 600;

constexpr uint8_t kPwmI2cAddress = 0x40;
constexpr uint8_t kPwmFrequencyHz = 50;

constexpr uint16_t kStandSettleDelayMs = 300;
constexpr uint16_t kIdleLoopDelayMs = 15;

enum ServoChannel : uint8_t {
  FrontLeftBase = 0,
  LeftBase = 1,
  BackLeftBase = 2,
  BackRightBase = 3,
  RightBase = 4,
  FrontRightBase = 5,
  FrontLeftKnee = 6,
  LeftKnee = 7,
  BackLeftKnee = 8,
  BackRightKnee = 9,
  RightKnee = 10,
  FrontRightKnee = 11
};

constexpr ServoChannel kTripodABase[3] = {FrontLeftBase, RightBase, BackLeftBase};
constexpr ServoChannel kTripodAKnee[3] = {FrontLeftKnee, RightKnee, BackLeftKnee};

constexpr ServoChannel kTripodBBase[3] = {BackRightBase, LeftBase, FrontRightBase};
constexpr ServoChannel kTripodBKnee[3] = {FrontRightKnee, LeftKnee, BackRightKnee};

// Per-servo neutral angle (degrees). Tune each leg here first.
constexpr int kServoHomeDeg[kServoCount] = {
    135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135, 135,
};

// Fine trim added to kServoHomeDeg for alignment (-20..20 typical).
constexpr int kServoTrimDeg[kServoCount] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

constexpr int kDefaultStepDeltaDeg = 15;
constexpr int kDefaultLiftDeltaDeg = 15;
constexpr uint16_t kDefaultStepDelayMs = 167;

}  // namespace hexapod

#endif
