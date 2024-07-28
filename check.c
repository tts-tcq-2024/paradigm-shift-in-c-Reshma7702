#include "check.h"
#include <stdio.h>
#include <stddef.h>

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

int performCheck(const Check* check, float minLimit, float maxLimit) {
    if (!check->check(check->value)) {
        printMessage(check->message);
        return 0;
    } else {
        if (check->warningLowMessage && check->value <= minLimit + check->tolerance) {
            printMessage(check->warningLowMessage);
        }
        if (check->warningHighMessage && check->value >= maxLimit - check->tolerance) {
            printMessage(check->warningHighMessage);
        }
    }
    return 1;
}
