# Development Notes

## Code Structure

- `hexapod-firmware.ino` owns runtime wiring and serial command parsing.
- `HexapodController.*` owns gait and servo actuation logic.
- `HexapodConfig.h` owns constants, channel map, and per-servo calibration defaults.

## Design Rules

- Keep hardware constants in config, not scattered in motion code.
- Keep one method responsible for one motion primitive.
- Prefer explicit naming over compact but unclear math.

## Testing Workflow

1. Bench test with robot suspended.
2. Validate `stand`, `step`, and `walk 1`.
3. Validate runtime tuning commands.
4. Move to short floor tests.

## CLI Build Target

Default compile target is Teensy 4.1:

- `FQBN=teensy:avr:teensy41`

## Near-Term Backlog

- Add additional gaits (ripple, wave).
- Add per-joint velocity smoothing.
- Add runtime save/load of calibration to EEPROM.
- Add optional IMU-based body stabilization loop.
