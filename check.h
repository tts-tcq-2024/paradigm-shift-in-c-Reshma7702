#ifndef CHECK_H
#define CHECK_H

typedef int (*CheckFunc)(float, float);

typedef struct {
    CheckFunc check;
    float value;
    float tolerance;
    const char *message;
    const char *warningLowMessage;
    const char *warningHighMessage;
} Check;

void printMessage(const char *message);
int isTemperatureInRange(float temperature, float tolerance);
int isSocInRange(float soc, float tolerance);
int isChargeRateInRange(float chargeRate, float tolerance);
int performCheck(const Check* check);

#endif // CHECK_H
