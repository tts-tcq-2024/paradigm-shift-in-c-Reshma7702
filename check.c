#include "check.h"
#include <stdio.h>

void printMessage(const char *message) {
    printf("%s", message);
}

int isTemperatureInRange(float temperature, float tolerance) {
    return (temperature >= 0 && temperature <= 45);
}

int isSocInRange(float soc, float tolerance) {
    return (soc >= 20 && soc <= 80);
}

int isChargeRateInRange(float chargeRate, float tolerance) {
    return (chargeRate <= 0.8);
}

int performCheck(const Check* check) {
    int result = check->check(check->value, check->tolerance);
    
    if (result) {
        if (check->value <= check->tolerance) {
            printMessage(check->warningLowMessage);
        } else if (check->value >= (45 - check->tolerance)) {
            printMessage(check->warningHighMessage);
        }
    } else {
        printMessage(check->message);
    }
    
    return result;
}
