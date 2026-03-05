# Hardware Setup

## Core Components

- Microcontroller board compatible with Arduino `Wire`.
- PCA9685 servo driver board (I2C).
- 12 servos (6 base joints, 6 knee joints).
- External 5V-6V servo power supply sized for stall current.

## Wiring

- MCU `SDA` -> PCA9685 `SDA`
- MCU `SCL` -> PCA9685 `SCL`
- MCU `GND` -> PCA9685 `GND`
- Servo PSU `+` -> PCA9685 `V+` rail
- Servo PSU `-` -> PCA9685 `GND`

Always share ground between MCU and servo PSU.

## Servo Channel Map

### Base Servos

- 0: `frontLeftBase`
- 1: `leftBase`
- 2: `backLeftBase`
- 3: `backRightBase`
- 4: `rightBase`
- 5: `frontRightBase`

### Knee Servos

- 6: `frontLeftKnee`
- 7: `leftKnee`
- 8: `backLeftKnee`
- 9: `backRightKnee`
- 10: `rightKnee`
- 11: `frontRightKnee`

## Power Notes

- Do not drive servos from the MCU 5V pin.
- Add bulk capacitance near the PCA9685 servo rail if brownouts appear.
- Start with low step/lift values and robot suspended off ground.
