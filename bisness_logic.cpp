#include <bisness_logic.h>

FuncReturningValue read_csv(std::string path);
FuncReturningValue is_normal_metric(QString text);

FuncReturningValue entryPoint(FuncType ft, FuncArgument* fa)
{
    FuncReturningValue result;
    switch(ft)
    {
        case calculateMetrics:
            calculate_metrics(fa->arr, fa->minimum, fa->maximum, fa->medium);
            break;
        case readCsv:
            result = read_csv(fa->path);
            break;
        case isNormalMetric:
            result = is_normal_metric(fa->text);
        default:
            break;
    }
    return result;
}

void calculate_metrics(std::vector<float> arr, float* minimum, float* maximum, float* medium){
    sort(arr.begin(), arr.end());
    *minimum = arr[0];
    *maximum = arr[arr.size() - 1];
    *medium = 0;
    if (arr.size() % 2 == 0){
        *medium = (arr[arr.size() / 2] + arr[arr.size() / 2 - 1]) / 2.0;
    } else {
        *medium = arr[arr.size() / 2];
    }
}


FuncReturningValue is_normal_metric(QString text){
    FuncReturningValue frv;
    bool ok;
    text.toFloat(&ok);
    frv.isok = ok;
    return frv;
}

std::vector<std::string> split_line(std::string line){
    std::vector<std::string> result;
    std::string word = "";
    for (int i = 0; i < line.length(); ++i){
        char symbol = line[i];
        if ((symbol == ',') || symbol == '\n'){
            result.push_back(word);
            word = "";
            continue;
        }
        word += symbol;
    }
    result.push_back(word);
    return result;
}

FuncReturningValue read_csv(std::string path){
    FuncReturningValue frv;
    //std::vector<std::vector<std::string>> result;
    std::string line;
    std::ifstream myFile(path);
    if (!myFile.is_open()) throw std::runtime_error("Could not open file");

    while(getline(myFile, line)){
        std::vector<std::string> line_model = split_line(line);
        frv.result.push_back(line_model);
    }
    return frv;
}

