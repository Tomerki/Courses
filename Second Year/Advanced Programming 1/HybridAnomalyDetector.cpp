/*
 * HybridAnomalyDetector.cpp
 * Authors: Noa Amit & Tomer Hadar
 */
#include "HybridAnomalyDetector.h"

void HybridAnomalyDetector:: updateCorrelatedFeatures (const TimeSeries& ts, string f1, string f2, float correlation, Point** points) {
    SimpleAnomalyDetector:: updateCorrelatedFeatures(ts, f1, f2, correlation, points);
    float precision = 1.1;
    if (correlation > 0.5 && correlation < threshold) {
        struct correlatedFeatures newPair;
        newPair.feature1 = std::move(f1);
        newPair.feature2 = std::move(f2);
        newPair.corrlation = correlation ;
        newPair.lin_reg = Line();
        Circle c = findMinCircle(points, ts.getColumnSize());
        newPair.center = c.center;
        newPair.threshold = precision * c.radius;
        cf.push_back(newPair);
    }
}
