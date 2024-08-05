#include "battery_monitor.h"
#include "parameter_checks.h"
#include <stddef.h>

int performAllChecks(ParameterCheck parameterChecks[], float minLimits[], float maxLimits[], int size) {
    for (int i = 0; i < size; ++i) {
        if (performCheck(&parameterChecks[i], minLimits[i], maxLimits[i]) == 0) {
            return 0;
        }
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    ParameterCheck parameterChecks[] = {
        {isTemperatureInRange, temperature, 2.25, "Temperature out of range!\n", "Warning: Approaching low temperature limit!\n", "Warning: Approaching high temperature limit!\n"},
        {isSocInRange, soc, 4.0, "State of Charge out of range!\n", "Warning: Approaching low SoC limit!\n", "Warning: Approaching high SoC limit!\n"},
        {isChargeRateInRange, chargeRate, 0.04, "Charge Rate out of range!\n", NULL, "Warning: Approaching high charge rate limit!\n"}
    };

    float minLimits[] = {0, 20, 0};
    float maxLimits[] = {45, 80, 0.8};

    return performAllChecks(parameterChecks, minLimits, maxLimits, sizeof(parameterChecks) / sizeof(parameterChecks[0]));
}
