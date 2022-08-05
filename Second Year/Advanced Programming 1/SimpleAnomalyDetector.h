/*
 * SimpleAnomalyDetector.cpp
 * Authors: Noa Amit & Tomer Hadar
 */
#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

struct correlatedFeatures{
    string feature1,feature2;  // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Point center = Point {0,0};
    bool high = false;
};

class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector {
protected:
    vector<correlatedFeatures> cf;
    float threshold = 0.9;
public:
    SimpleAnomalyDetector() = default;
    virtual ~SimpleAnomalyDetector() = default;
    virtual void learnNormal(const TimeSeries& ts);
    void arrFromVec(vector<float> v,const int size, float* arr);
    void createPointArray(vector<float> x, vector<float> y, const int size, Point** points);
    float calculateThreshold(Point** p, const TimeSeries& ts, const correlatedFeatures& newPair);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel() {
        return cf;
    }
    void emptyNormalModel() {
        cf.clear();
    }
    virtual void updateCorrelatedFeatures (const TimeSeries& ts, string f1, string f2, float correlation, Point** points);
    void setThreshold(float newThreshold){
        this->threshold = newThreshold;
    }
};

#endif /* SIMPLEANOMALYDETECTOR_H_ */
