/*
 * minCircle.cpp
 * Authors: Noa Amit 315231274 & Tomer Hadar 207651027
 */
#include <cmath>
#include "minCircle.h"
#include <algorithm>
Point findCuttingPoint(Point one, Point two, float inclineOne, float inclineTwo) {

    float bOne = one.y - (one.x * inclineOne);
    float bTwo = two.y - (two.x * inclineTwo);

    float xCut= (bTwo - bOne) / (inclineOne - inclineTwo);
    float yCut = (inclineOne * xCut) + bOne;

    return {xCut, yCut};
}
bool checkSinglePoint(Circle a, Point*& p) {
    float result = ( ( p->x - a.center.x) * (p->x - a.center.x) ) +
                   ( (p->y - a.center.y) * (p->y - a.center.y) );

    if (result <= ((a.radius) * (a.radius))) {
        return true;
    }
    return false;
}

Circle createCircleFromThreePoints(vector<Point*>& points ,size_t size) {
    Point* one = points[0];
    Point* two = points[1];
    Point* three = points[2];

    float xMiddleOneAndTwo = (one->x + two->x) / 2;
    float yMiddleOneAndTwo = (one->y + two->y) / 2;
    Point middleOneAndTwo = Point (xMiddleOneAndTwo, yMiddleOneAndTwo);
    float xMiddleOneAndThree = (one->x + three->x) / 2;
    float yMiddleOneAndThree = (one->y + three->y) / 2;
    Point middleOneAndThree = Point (xMiddleOneAndThree, yMiddleOneAndThree);

    float inclineOneAndTwo = -1/((one->y - two->y) / (one->x - two->x));
    float inclineOneAndThree = -1/((one->y - three->y) / (one->x - three->x));

    Point cutPoint = findCuttingPoint(middleOneAndTwo, middleOneAndThree, inclineOneAndTwo, inclineOneAndThree);

    float radius = sqrt(((one->x-cutPoint.x)*(one->x-cutPoint.x))+((one->y-cutPoint.y)*(one->y-cutPoint.y)));

    return {cutPoint, radius};


}

Circle findCircleFromTwoPoints(vector<Point*>& points ,size_t size){
    Point* one = points[0];
    Point* two = points[1];

    float distance = sqrt(((one->x-two->x)*(one->x-two->x))+((one->y-two->y)*(one->y-two->y)));
    float radius = distance / 2;

    float newX = (one->x+two->x) / 2;
    float newY = (one->y+two->y) / 2;
    return {Point(newX, newY), radius};
}

Circle findCircleFromThreePoints(vector<Point*>& points ,size_t size){

    for(int i=0; i<3; i++){
        for(int k=i+1; k<3; k++) {
            vector <Point*> twoPoints;
            twoPoints.push_back(points[i]);
            twoPoints.push_back(points[k]);
            Circle c = findCircleFromTwoPoints(twoPoints, size);
            if (checkSinglePoint(c, points[3-(i+k)])) {
                return c;
            }
        }
    }
    return createCircleFromThreePoints(points, size);
}

Circle findCircleFromUpToThreePoints(vector<Point*>& points ,size_t size){
    if (size == 0) {
        return {Point(0,0), 0};
    }
    if (size == 1) {
        return {*points[0], 0};
    }
    if (size == 2) {
        return findCircleFromTwoPoints(points ,size);
    }
    return findCircleFromThreePoints(points ,size);

}

Circle helperFindMinCircle(Point**& points, vector<Point*> defineCircle,size_t size) {
    if (size == 0 || defineCircle.size() == 3) {
        return findCircleFromUpToThreePoints(defineCircle, defineCircle.size());
    }
    Point* p = points[size-1];

    Circle c = helperFindMinCircle(points, defineCircle, size-1);

    if(checkSinglePoint(c, p)) {
        return  c;
    }

    defineCircle.push_back(p);

    return helperFindMinCircle(points, defineCircle, size - 1);
}

Circle findMinCircle(Point** points,size_t size) {
    vector <Point*> defineCircle;
    Circle c = helperFindMinCircle(points, defineCircle, size);
    return c;
}