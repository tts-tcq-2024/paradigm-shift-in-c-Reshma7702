#include <stdio.h>
#include <assert.h>
 
int batteryIsOk(float temperature, int soc, float chargeRate) {
  return (temperature < 0 || temperature > 45) ? (printf("Temperature out of range!\n"), 0) :
           (soc < 20 || soc > 80) ? (printf("State of Charge out of range!\n"), 0) :
           (chargeRate > 0.8) ? (printf("Charge Rate out of range!\n"), 0) : 1;
}
 
int main() {
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 85, 0));
}
