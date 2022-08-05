/*
 * minCircle.h
 * Authors: Noa Amit & Tomer Hadar
 */
#ifndef MINCIRCLE_H_
#define MINCIRCLE_H_

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

// you can add here additional methods

Circle helperFindMinCircle(Point**& points, vector<Point*> defineCircle,size_t size);

Circle findCircleFromUpToThreePoints(vector<Point*>& points ,size_t size);

Circle findCircleFromThreePoints(vector<Point*>& points ,size_t size);

Circle findCircleFromTwoPoints(vector<Point*>& points ,size_t size);

bool checkSinglePoint(Circle a, Point*& p);

Circle createCircleFromThreePoints(vector<Point*>& points ,size_t size);

Point findCuttingPoint(Point one, Point two, float inclineOne, float inclineTwo);

#endif /* MINCIRCLE_H_ */
