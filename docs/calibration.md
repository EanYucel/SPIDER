# Calibration Guide

## Goal

Make all joints sit at a consistent neutral pose before walking.

## 1. Safe Bring-Up

- Lift the robot so legs cannot strike the floor.
- Upload firmware and connect Serial Monitor (`115200`).
- Run:
  - `walk off`
  - `stand`

## 2. Tune Neutral Angles

Edit `kServoHomeDeg[]` in `HexapodConfig.h` to set each servo's mechanical neutral point.

Recommended approach:

1. Adjust one servo by small increments (`2-3` degrees).
2. Upload and run `stand`.
3. Repeat until leg geometry is symmetric.

## 3. Fine Trim

Use `kServoTrimDeg[]` for small offsets after rough neutral alignment.

- Typical range: `-20` to `+20`.
- Keep trim values small and revisit horn mounting if large offsets are needed.

## 4. Gait Tuning

Live tune via serial:

- `set step 12`
- `set lift 14`
- `set delay 140`
- `step`

After you find stable values, copy them into defaults in `HexapodConfig.h`.

## 5. Floor Test

- Start with `walk 1` and observe each cycle.
- Increase to `walk 5`, then `walk on`.
- Stop immediately if any leg drags, binds, or over-extends.
