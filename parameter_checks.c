#include "parameter_checks.h"
#include <stdio.h>

void printMessage(const char *message) {
    printf("%s", message);
}

int isTemperatureInRange(float temperature) {
    return (temperature >= 0 && temperature <= 45);
}

int isSocInRange(float soc) {
    return (soc >= 20 && soc <= 80);
}

int isChargeRateInRange(float chargeRate) {
    return (chargeRate <= 0.8);
}

void checkLowWarning(const ParameterCheck* check, float minLimit) {
    if (check->warningLowMessage && check->value <= minLimit + check->tolerance) {
        printMessage(check->warningLowMessage);
    }
}

void checkHighWarning(const ParameterCheck* check, float maxLimit) {
    if (check->warningHighMessage && check->value >= maxLimit - check->tolerance) {
        printMessage(check->warningHighMessage);
    }
}

int performCheck(const ParameterCheck* check, float minLimit, float maxLimit) {
    if (check->check(check->value) == 0) {
        printMessage(check->message);
        return 0;
    }
    checkLowWarning(check, minLimit);
    checkHighWarning(check, maxLimit);
    return 1;
}
