# Contributing

## Branching

- Use short-lived feature branches with prefix `codex/`.
- Keep each branch focused on one behavior change.

## Commit Style

- Write imperative commit subjects.
- Keep firmware changes and docs changes in separate commits when practical.

## Pull Request Checklist

- Explain the motion/control behavior change.
- Include test notes (bench test, dry run, hardware run).
- Call out any changed default constants in `HexapodConfig.h`.
- Include before/after videos for gait updates when possible.

## Safety Checklist

- Confirm external servo power is used (do not power servos from MCU 5V pin).
- Confirm common ground between MCU, PCA9685, and servo PSU.
- Validate commands in lifted-off-ground mode before floor tests.
