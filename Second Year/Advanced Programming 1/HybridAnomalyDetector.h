/*
 * HybridAnomalyDetector.h
 * Authors: Noa Amit 315231274 & Tomer Hadar 207651027
 */

#ifndef HYBRIDANOMALYDETECTOR_H_
#define HYBRIDANOMALYDETECTOR_H_

#include "SimpleAnomalyDetector.h"
#include "minCircle.h"

class HybridAnomalyDetector:public SimpleAnomalyDetector {

public:
    HybridAnomalyDetector() : SimpleAnomalyDetector() {};
    virtual ~HybridAnomalyDetector() = default;
    virtual void updateCorrelatedFeatures (const TimeSeries& ts, string f1, string f2, float correlation, Point** points);
};

#endif /* HYBRIDANOMALYDETECTOR_H_ */