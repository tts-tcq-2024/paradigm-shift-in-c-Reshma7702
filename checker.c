#include <stdio.h>
#include <assert.h>

typedef int (*CheckFunc)(float, float*);

typedef struct {
    CheckFunc check;
    float value;
    float tolerance;
    const char *message;
    const char *warningMessage;
} Check;

void printMessage(const char *message) {
    printf("%s", message);
}

int isTemperatureInRange(float temperature, float *tolerance) {
    if (temperature >= 0 && temperature <= 45) {
        if (temperature <= *tolerance || temperature >= (45 - *tolerance)) {
            printMessage("Warning: Approaching temperature limits!\n");
        }
        return 1;
    }
    return 0;
}

int isSocInRange(float soc, float *tolerance) {
    if (soc >= 20 && soc <= 80) {
        if (soc <= (20 + *tolerance) || soc >= (80 - *tolerance)) {
            printMessage("Warning: Approaching SoC limits!\n");
        }
        return 1;
    }
    return 0;
}

int isChargeRateInRange(float chargeRate, float *tolerance) {
    if (chargeRate <= 0.8) {
        if (chargeRate >= (0.8 - *tolerance)) {
            printMessage("Warning: Approaching charge rate limit!\n");
        }
        return 1;
    }
    return 0;
}

int performCheck(const Check* check) {
    if (!check->check(check->value, &check->tolerance)) {
        printMessage(check->message);
        return 0;
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    Check checks[] = {
        {isTemperatureInRange, temperature, 2.25, "Temperature out of range!\n", "Warning: Approaching temperature limits!\n"},
        {isSocInRange, soc, 4.0, "State of Charge out of range!\n", "Warning: Approaching SoC limits!\n"},
        {isChargeRateInRange, chargeRate, 0.04, "Charge Rate out of range!\n", "Warning: Approaching charge rate limit!\n"}
    };

    for (int i = 0; i < sizeof(checks) / sizeof(checks[0]); ++i) {
        if (!performCheck(&checks[i])) {
            return 0;
        }
    }

    return 1;
}

int main() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
    assert(!batteryIsOk(30, 85, 0));
    assert(!batteryIsOk(25, 70, 0.9));
    printf("All tests passed!\n");
    return 0;
}
