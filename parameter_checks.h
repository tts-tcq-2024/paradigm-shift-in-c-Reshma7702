#ifndef PARAMETER_CHECKS_H
#define PARAMETER_CHECKS_H

typedef int (*CheckFunc)(float);

typedef struct {
    CheckFunc check;
    float value;
    float tolerance;
    const char *message;
    const char *warningLowMessage;
    const char *warningHighMessage;
} ParameterCheck;

void printMessage(const char *message);
int performCheck(const ParameterCheck* check, float minLimit, float maxLimit);

int isTemperatureInRange(float temperature);
int isSocInRange(float soc);
int isChargeRateInRange(float chargeRate);

#endif // PARAMETER_CHECKS_H
