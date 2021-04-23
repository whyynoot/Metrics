#ifndef BISNESS_LOGIC_H
#define BISNESS_LOGIC_H
#include <mainwindow.h>

std::vector<std::vector<std::string>> read_csv(std::string path);
void calculate_metrics(std::vector<float>, float* minimum, float* maximum, float* medium);
bool is_normal_metric(QString text);


#endif // BUISNESS_H
