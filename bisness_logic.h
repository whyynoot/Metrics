#ifndef BISNESS_LOGIC_H
#define BISNESS_LOGIC_H
#include <mainwindow.h>

void calculate_metrics(std::vector<float> arr, float* minimum, float* maximum, float* medium);

enum FuncType
{
    calculateMetrics,
    readCsv,
    isNormalMetric
};

typedef struct
{
    std::string path;
    std::vector<float> arr;
    float* minimum;
    float* maximum;
    float*  medium;
    QString text;
} FuncArgument;


typedef struct
{
    std::vector<std::vector<std::string>> result;
    bool isok;
} FuncReturningValue;


FuncReturningValue entryPoint(FuncType ft, FuncArgument* fa);


#endif // BUISNESS_H
