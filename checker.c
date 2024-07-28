#include <stdio.h>
#include <assert.h>

typedef int (*CheckFunc)(float, float);

typedef struct {
    CheckFunc check;
    float value;
    float tolerance;
    const char *message;
    const char *warningLowMessage;
    const char *warningHighMessage;
} Check;

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

int batteryIsOk(float temperature, float soc, float chargeRate) {
    Check checks[] = {
        {isTemperatureInRange, temperature, 2.25, "Temperature out of range!\n", "Warning: Approaching low temperature limit!\n", "Warning: Approaching high temperature limit!\n"},
        {isSocInRange, soc, 4.0, "State of Charge out of range!\n", "Warning: Approaching low SoC limit!\n", "Warning: Approaching high SoC limit!\n"},
        {isChargeRateInRange, chargeRate, 0.04, "Charge Rate out of range!\n", "", "Warning: Approaching high charge rate limit!\n"}
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
    assert(!batteryIsOk(2.3, 70, 0.9));
    printf("All tests passed!\n");
    return 0;
}
