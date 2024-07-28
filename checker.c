#include <assert.h>
#include <stdio.h>
#include "battery.h"

int main() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
    assert(!batteryIsOk(30, 85, 0));
    assert(!batteryIsOk(25, 70, 0.9));
    
    // Warning test cases
    assert(batteryIsOk(2.15, 70, 0.7)); // Should give a temperature low warning but pass the check
    assert(batteryIsOk(44.85, 70, 0.7)); // Should give a temperature high warning but pass the check
    assert(batteryIsOk(25, 23.95, 0.7)); // Should give a SoC low warning but pass the check
    assert(batteryIsOk(25, 76.05, 0.7)); // Should give a SoC high warning but pass the check
    assert(batteryIsOk(25, 70, 0.76)); // Should give a charge rate high warning but pass the check

    printf("All tests passed!\n");
    return 0;
}
