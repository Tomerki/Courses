/*
 * timeseries.cpp
 * Authors: Noa Amit 315231274 & Tomer Hadar 207651027
 */
#include "timeseries.h"
/**
 * constructor
 * @param CSVfileName - a table of features
 */
TimeSeries::TimeSeries(const char* CSVfileName) {
    this->table = loadCSV(CSVfileName);
}

/**
 * loadCSV - the function creates an vector of pairs of the features and there values
 * @param CSVfileName -  a table of features
 * @return table - vector of pairs of the features and there values
 */
vector<pair<string, vector<float>>> TimeSeries::loadCSV(const char* CSVfileName) {
    fstream f;
    f.open(CSVfileName);
    if(f.fail()) {
        throw std::runtime_error("problem with file's opening\n");
    }

    string feature, line;
    float data;

    if (f.good()) {
        getline(f, line);
        stringstream a(line);
        while (getline(a, feature, ',')) {
            this->table.push_back({feature, {}});
        }
    }

    while (getline(f,line)) {
        stringstream a(line);
        int columNum = 0;

        while (a >> data) {
            this->table.at(columNum).second.push_back(data);
            if (a.peek() == ',') {
                a.ignore();
            }
            columNum ++;
        }
    }

    f.close();
    return table;
}
/**
 * getFeatureName
 * @param col - number of column
 * @return the name of the feature in this column
 */
string TimeSeries::getFeatureName(int col) const {
    return this->table.at(col).first;
}

/**
 * getTableSize
 * @return the number of features
 */
const int TimeSeries::getTableSize () const{
    return this->table.size();
}

/**
 * getColumnSize
 * @return the number of rows in the table (number of samples)
 */
const int TimeSeries::getColumnSize () const {
    return this->table.at(0).second.size();
}

/**
 * getColumn
 * @param col the number of the wanted column
 * @return vector of the values of the wanted features
 */
vector<float> TimeSeries::getColumn(int col) const{
    return this->table.at(col).second;
}