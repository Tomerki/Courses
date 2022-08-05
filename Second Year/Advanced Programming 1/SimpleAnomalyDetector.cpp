/*
 * SimpleAnomalyDetector.cpp
 * Authors: Noa Amit & Tomer Hadar
 */

#include "SimpleAnomalyDetector.h"
#include <utility>

/**
 * arrFromVec - the function get vector and create an array from the vector
 * @param v vector of floats
 * @param size the size of the vector
 * @param arr of floats
 */
void SimpleAnomalyDetector::arrFromVec(vector<float> v, const int size, float* arr) {
    for(int i = 0 ; i < size; i++) {
        arr[i] = v.at(i);
    }
}
/**
 * calculateThreshold - calculate the threshold between two features
 * @param p points array
 * @param ts object with the given table
 * @param newPair a struct of a correlated features
 * @return maxDev - the threshold between two features
 */
float SimpleAnomalyDetector::calculateThreshold(Point** p, const TimeSeries& ts, const correlatedFeatures& newPair) {
    float maxDev = 0;
    for (int k = 0; k < ts.getColumnSize(); ++k) {
        float currentDev = dev(*p[k], newPair.lin_reg);
        if (currentDev > maxDev) {
            maxDev = currentDev;
        }
    }
    return maxDev;
}

void SimpleAnomalyDetector:: updateCorrelatedFeatures (const TimeSeries& ts, string f1, string f2, float correlation, Point** points) {
    float precision = 1.1;
    if (correlation > threshold) {
        struct correlatedFeatures newPair;
        newPair.feature1 = std::move(f1);
        newPair.feature2 = std::move(f2);
        newPair.corrlation = correlation ;
        newPair.lin_reg = linear_reg(points,ts.getColumnSize());
        newPair.threshold = precision * calculateThreshold(points, ts, newPair);
        newPair.high = true;
        cf.push_back(newPair);
    }
}

/**
 * learnNormal - check correlation between all the features table
 * @param ts object with the given table
 */
void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts) {
    float p;
    int i,j;
    float first[ts.getColumnSize()];
    float second[ts.getColumnSize()];

    for(i = 0 ; i < ts.getTableSize(); i++) {
        float m = 0;
        int c = -1;
        for(j = i + 1; j < ts.getTableSize(); j++) {
            arrFromVec(ts.getColumn(i), ts.getColumnSize(), first);
            arrFromVec(ts.getColumn(j), ts.getColumnSize(), second);
            p = pearson(first, second , ts.getColumnSize());
            if (p < 0) {
                p = -p;
            }
            if(p > m) {
                m = p;
                c = j;
            }
        }
        if(c != -1){
            Point* points[ts.getColumnSize()];
            createPointArray(ts.getColumn(i), ts.getColumn(c), ts.getColumnSize(), points);
            updateCorrelatedFeatures(ts, ts.getFeatureName(i),  ts.getFeatureName(c), m, points);
        }
    }
}

/**
 * detect - checking deviations
 * @param ts object with the given table
 * @return vector with all the deviations
 */
vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries& ts) {

    vector<AnomalyReport> reports;
    string feature1, feature2;

    for (int i = 0; i < this->cf.size(); i++) {
        feature1 = cf.at(i).feature1;
        feature2 = cf.at(i).feature2;

        for (int j = 0; j < ts.getTableSize(); j++) {
            for (int k = j+1; k < ts.getTableSize(); k++) {
                if ((ts.getFeatureName(j) == feature1) && (ts.getFeatureName(k) == feature2)) {
                    Point* points[ts.getColumnSize()];
                    createPointArray(ts.getColumn(j), ts.getColumn(k), ts.getColumnSize(), points);
                    for (int l = 0; l < ts.getColumnSize(); l++) {
                        float currentDev;
                        if (cf.at(i).high) {
                            currentDev = dev(*points[l],cf.at(i).lin_reg);
                            if (cf.at(i).threshold < currentDev) {
                                string description;
                                description.append(feature1).append("-").append(feature2);
                                AnomalyReport newReport (description, l+1);
                                reports.push_back(newReport);
                            }
                        }
                        else {
                            Point center = cf.at(i).center;
                            Point p = *points[l];
                            currentDev = ((center.x - p.x) * (center.x - p.x)) + ((center.y - p.y) * (center.y - p.y));
                            if ((cf.at(i).threshold * cf.at(i).threshold) < currentDev ) {
                                string description;
                                description.append(feature1).append("-").append(feature2);
                                AnomalyReport newReport(description, l + 1);
                                reports.push_back(newReport);
                            }
                        }
                    }
                }
            }
        }
    }
    return reports;
}

/**
 * createPointArray - create an array of points from two vectors of x and y values.
 * @param x vector of x values
 * @param y vector of y values
 * @param size number of points
 * @param points arr from x and y values
 */
void SimpleAnomalyDetector::createPointArray(vector<float> x, vector<float> y, const int size, Point** points) {
    for(int i = 0 ; i < size; i++) {
        points[i] = new Point(x.at(i), y.at(i));
    }
}
