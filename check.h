#ifndef CHECK_H
#define CHECK_H

typedef int (*CheckFunc)(float);

typedef struct {
    CheckFunc check;
    float value;
    float tolerance;
    const char *message;
    const char *warningLowMessage;
    const char *warningHighMessage;
} Check;

void printMessage(const char *message);
int isTemperatureInRange(float temperature);
int isSocInRange(float soc);
int isChargeRateInRange(float chargeRate);
int performCheck(const Check* check, float minLimit, float maxLimit);
void checkLowWarning(const Check* check, float minLimit);
void checkHighWarning(const Check* check, float maxLimit);

#endif // CHECK_H
