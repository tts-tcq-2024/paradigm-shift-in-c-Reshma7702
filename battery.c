#include "battery.h"
#include "check.h"

int batteryIsOk(float temperature, float soc, float chargeRate) {
    Check checks[] = {
        {isTemperatureInRange, temperature, 2.25, "Temperature out of range!\n", "Warning: Approaching low temperature limit!\n", "Warning: Approaching high temperature limit!\n"},
        {isSocInRange, soc, 4.0, "State of Charge out of range!\n", "Warning: Approaching low SoC limit!\n", "Warning: Approaching high SoC limit!\n"},
        {isChargeRateInRange, chargeRate, 0.04, "Charge Rate out of range!\n", NULL, "Warning: Approaching high charge rate limit!\n"}
    };

    for (int i = 0; i < sizeof(checks) / sizeof(checks[0]); ++i) {
        if (!performCheck(&checks[i])) {
            return 0;
        }
    }

    return 1;
}
