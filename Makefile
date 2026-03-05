ARDUINO_CLI ?= arduino-cli
FQBN ?= teensy:avr:teensy41
SKETCH_DIR ?= .
PORT ?= /dev/ttyACM0
BAUD ?= 115200

.PHONY: compile upload monitor

compile:
	$(ARDUINO_CLI) compile --fqbn $(FQBN) $(SKETCH_DIR)

upload:
	$(ARDUINO_CLI) upload --fqbn $(FQBN) --port $(PORT) $(SKETCH_DIR)

monitor:
	$(ARDUINO_CLI) monitor --port $(PORT) --config baudrate=$(BAUD)
