#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "HexapodConfig.h"
#include "HexapodController.h"

namespace {

Adafruit_PWMServoDriver pwm(hexapod::kPwmI2cAddress);
hexapod::HexapodController robot(pwm);

bool autoWalkEnabled = true;
char serialBuffer[64];
size_t serialBufferLen = 0;

bool tokenEquals(const char* lhs, const char* rhs) {
  if (lhs == nullptr || rhs == nullptr) {
    return false;
  }

  while (*lhs != '\0' && *rhs != '\0') {
    if (tolower(static_cast<unsigned char>(*lhs)) !=
        tolower(static_cast<unsigned char>(*rhs))) {
      return false;
    }
    ++lhs;
    ++rhs;
  }

  return *lhs == '\0' && *rhs == '\0';
}

bool parseLong(const char* token, long& value) {
  if (token == nullptr || *token == '\0') {
    return false;
  }

  char* end = nullptr;
  value = strtol(token, &end, 10);
  return *end == '\0';
}

void printHelp() {
  Serial.println(F("Commands:"));
  Serial.println(F("  help"));
  Serial.println(F("  status"));
  Serial.println(F("  stand"));
  Serial.println(F("  step"));
  Serial.println(F("  walk on|off|<count>"));
  Serial.println(F("  set step <deg>"));
  Serial.println(F("  set lift <deg>"));
  Serial.println(F("  set delay <ms>"));
}

void printStatus() {
  robot.printStatus(Serial);
  Serial.print(F("autoWalk="));
  Serial.println(autoWalkEnabled ? F("on") : F("off"));
}

void handleCommand(char* line) {
  char* savePtr = nullptr;
  char* command = strtok_r(line, " \t", &savePtr);
  if (command == nullptr) {
    return;
  }

  if (tokenEquals(command, "help")) {
    printHelp();
    return;
  }

  if (tokenEquals(command, "status")) {
    printStatus();
    return;
  }

  if (tokenEquals(command, "stand")) {
    autoWalkEnabled = false;
    robot.stand();
    Serial.println(F("OK: standing"));
    return;
  }

  if (tokenEquals(command, "step")) {
    autoWalkEnabled = false;
    robot.tripodStep();
    Serial.println(F("OK: stepped once"));
    return;
  }

  if (tokenEquals(command, "walk")) {
    char* arg = strtok_r(nullptr, " \t", &savePtr);
    if (arg == nullptr || tokenEquals(arg, "on")) {
      autoWalkEnabled = true;
      Serial.println(F("OK: auto walk on"));
      return;
    }

    if (tokenEquals(arg, "off")) {
      autoWalkEnabled = false;
      Serial.println(F("OK: auto walk off"));
      return;
    }

    long stepCount = 0;
    if (parseLong(arg, stepCount) && stepCount > 0) {
      autoWalkEnabled = false;
      robot.walkSteps(static_cast<uint16_t>(stepCount));
      Serial.print(F("OK: walked steps="));
      Serial.println(stepCount);
      return;
    }

    Serial.println(F("ERR: walk expects on|off|<count>"));
    return;
  }

  if (tokenEquals(command, "set")) {
    char* field = strtok_r(nullptr, " \t", &savePtr);
    char* valueToken = strtok_r(nullptr, " \t", &savePtr);
    long value = 0;

    if (field == nullptr || valueToken == nullptr || !parseLong(valueToken, value)) {
      Serial.println(F("ERR: set expects <step|lift|delay> <value>"));
      return;
    }

    if (tokenEquals(field, "step")) {
      robot.setStepDelta(static_cast<int>(value));
      Serial.print(F("OK: stepDeltaDeg="));
      Serial.println(robot.stepDelta());
      return;
    }

    if (tokenEquals(field, "lift")) {
      robot.setLiftDelta(static_cast<int>(value));
      Serial.print(F("OK: liftDeltaDeg="));
      Serial.println(robot.liftDelta());
      return;
    }

    if (tokenEquals(field, "delay")) {
      robot.setStepDelay(static_cast<uint16_t>(value));
      Serial.print(F("OK: stepDelayMs="));
      Serial.println(robot.stepDelay());
      return;
    }

    Serial.println(F("ERR: set supports step|lift|delay"));
    return;
  }

  Serial.println(F("ERR: unknown command"));
}

void readSerialCommands() {
  while (Serial.available() > 0) {
    const char c = static_cast<char>(Serial.read());
    if (c == '\r') {
      continue;
    }

    if (c == '\n') {
      serialBuffer[serialBufferLen] = '\0';
      handleCommand(serialBuffer);
      serialBufferLen = 0;
      continue;
    }

    if (serialBufferLen + 1 < sizeof(serialBuffer)) {
      serialBuffer[serialBufferLen++] = c;
    }
  }
}

}  // namespace

void setup() {
  Serial.begin(115200);
  delay(100);

  robot.begin();
  robot.stand();

  printHelp();
  Serial.println(F("Auto walk is ON."));
}

void loop() {
  readSerialCommands();

  if (autoWalkEnabled) {
    robot.tripodStep();
  } else {
    delay(hexapod::kIdleLoopDelayMs);
  }
}
