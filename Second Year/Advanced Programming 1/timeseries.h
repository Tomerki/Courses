/*
 * timeseries.h
 * Authors: Noa Amit & Tomer Hadar
 */
#ifndef TIMESERIES_H_
#define TIMESERIES_H_
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class TimeSeries{
    vector<pair<string, vector<float>>> table;

public:
    explicit TimeSeries(const char* CSVfileName);
    ~TimeSeries() = default;
    vector<pair<string, vector<float>>> loadCSV(const char* CSVfileName);
    string getFeatureName(int col) const;
    const int getTableSize() const;
    const int getColumnSize() const;
    vector<float> getColumn(int col) const;
};

#endif /* TIMESERIES_H_ */
