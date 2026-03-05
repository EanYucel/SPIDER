# SPIDER

Firmware workspace for a 12-servo hexapod driven by a PCA9685 board.

## Highlights

- Modular controller code (`HexapodController.*`) instead of one long sketch.
- Centralized servo/channel/tuning configuration (`HexapodConfig.h`).
- Live serial command interface for stepping and gait tuning.
- Safety and calibration docs for first bring-up.

## Repository Layout

- `hexapod-firmware.ino`: sketch entrypoint and serial command parser.
- `HexapodConfig.h`: channel map, default angles, trim offsets, gait defaults.
- `HexapodController.h/.cpp`: gait primitives and tripod step sequencing.
- `Makefile`: convenience targets for compile/upload/monitor.
- `docs/hardware.md`: wiring and servo channel mapping.
- `docs/calibration.md`: safe calibration procedure.
- `docs/development.md`: local workflow and coding conventions.

## Quick Start (Arduino IDE)

1. Install libraries:
   - `Adafruit PWM Servo Driver Library`
2. Open `hexapod-firmware.ino`.
3. Verify servo power is external and grounds are shared.
4. Upload and open Serial Monitor at `115200`.

## Quick Start (CLI)

```bash
make compile
make upload PORT=/dev/tty.usbmodemXXXX
make monitor PORT=/dev/tty.usbmodemXXXX
```

Defaults:

- `FQBN=arduino:avr:uno`
- `BAUD=115200`

## Serial Commands

- `help`
- `status`
- `stand`
- `step`
- `walk on`
- `walk off`
- `walk <count>`
- `set step <deg>` (range clamped to `1..45`)
- `set lift <deg>` (range clamped to `1..45`)
- `set delay <ms>` (range clamped to `20..1000`)

## First Bring-Up

1. Read [docs/hardware.md](docs/hardware.md).
2. Read [docs/calibration.md](docs/calibration.md).
3. Start with the robot lifted off the ground.
4. Use `walk off`, then `step` while tuning.

## License

MIT, see [LICENSE](LICENSE).
