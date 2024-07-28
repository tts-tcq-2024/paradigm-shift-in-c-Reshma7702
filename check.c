#include "check.h"
#include <stdio.h>

void printMessage(const char *message) {
    printf("%s", message);
}

int isTemperatureInRange(float temperature, float tolerance) {
    if (temperature <= tolerance) {
        printMessage("Warning: Approaching low temperature limit!\n");
    } else if (temperature >= (45 - tolerance)) {
        printMessage("Warning: Approaching high temperature limit!\n");
    }
    return (temperature >= 0 && temperature <= 45);
}

int isSocInRange(float soc, float tolerance) {
    if (soc <= (20 + tolerance)) {
        printMessage("Warning: Approaching low SoC limit!\n");
    } else if (soc >= (80 - tolerance)) {
        printMessage("Warning: Approaching high SoC limit!\n");
    }
    return (soc >= 20 && soc <= 80);
}

int isChargeRateInRange(float chargeRate, float tolerance) {
    if (chargeRate >= (0.8 - tolerance)) {
        printMessage("Warning: Approaching high charge rate limit!\n");
    }
    return (chargeRate <= 0.8);
}

int performCheck(const Check* check) {
    if (!check->check(check->value, check->tolerance)) {
        printMessage(check->message);
        return 0;
    }
    return 1;
}
