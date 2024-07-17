#include <stdio.h>
#include <assert.h>

typedef int (*CheckFunc)(float);

typedef struct {
    CheckFunc check;
    float value;
    const char *message;
} Check;

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

int performCheck(const Check* check) {
    if (!check->check(check->value)) {
        printMessage(check->message);
        return 0;
    }
    return 1;
}

int checkAllParameters(const Check checks[], int numChecks) {
    for (int i = 0; i < numChecks; ++i) {
        if (!performCheck(&checks[i])) {
            return 0;
        }
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    Check checks[] = {
        {isTemperatureInRange, temperature, "Temperature out of range!\n"},
        {isSocInRange, soc, "State of Charge out of range!\n"},
        {isChargeRateInRange, chargeRate, "Charge Rate out of range!\n"}
    };
    return checkAllParameters(checks, sizeof(checks) / sizeof(checks[0]));
}

void runTests() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
    assert(!batteryIsOk(30, 85, 0));
    assert(!batteryIsOk(25, 70, 0.9));
    printf("All tests passed!\n");
}

int main() {
    runTests();
    return 0;
}
