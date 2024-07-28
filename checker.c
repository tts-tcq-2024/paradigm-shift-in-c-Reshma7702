#include <assert.h>
#include <stdio.h>
#include "battery.h"

int main() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
    assert(!batteryIsOk(30, 85, 0));
    assert(!batteryIsOk(25, 70, 0.9));
    assert(!batteryIsOk(2.3, 70, 0.7));
    printf("All tests passed!\n");
    return 0;
}
