/*
 * anomaly_detection_util.cpp
 * Authors: Noa Amit 315231274 & Tomer Hadar 207651027
 */
#include <stdexcept>
#include <math.h>
#include "anomaly_detection_util.h"

/**
 * nullArrayError - checking if the array doesnt null
 * @param p an array
 */
void nullArrayError (float* p){
    if(p == nullptr){
        throw std::runtime_error("No parameters\n");
    }
}
/**
 * nullArrayError - checking if the size of the array is valid
 * @param size - the array size
 */
void sizeZeroError (int size){
    if(size == 0){
        throw std::runtime_error("can not divide by zero\n");
    }
}

/**
 * avg - calculate the avg of the numbers in the array
 * @param x - an array
 * @param size the array size
 * @return the avg of x
 */
float avg(float* x, int size){

    sizeZeroError(size);
    nullArrayError(x);

    float sum = 0;
    for ( int i=0 ; i<size ; i++) {
        sum += x[i];
    }
    return (sum/size);
}

/**
 * var - calculate the variance of X
 * @param x - an array
 * @param size the array size
 * @return the variance of X
 */
float var(float* x, int size){

    sizeZeroError(size);
    nullArrayError(x);

    float sum = 0;
    float result = 0;
    for (int i=0 ; i<size ; i++) {
        sum += (x[i]*x[i]);
    }
    sum = sum/size;
    result = sum - (avg(x, size)*avg(x, size));
    return result;
}

/**
 * multiArr - function that helps to the cov function. multiply array x and y.
 * @param x - one of the two array the are multiplied.
 * @param y - one of the two array the are multiplied.
 * @param z - the multiplication array.
 * @param size - the array size of x, y and z.
 */
void multiArr(float* x, float* y, float* z, int size){
    for (int i=0 ; i<size ; i++) {
        z[i] = x[i] * y[i];
    }
}

/**
 * cov - calculate the covariance of X and Y
 * @param x - the first array
 * @param y - the second array
 * @param size - the array size of x and y.
 * @return the covariance of X and Y
 */
float cov(float* x, float* y, int size){

    sizeZeroError(size);
    nullArrayError(x);
    nullArrayError(y);

    float z[size];
    multiArr(x, y, z, size);
    return (avg(z, size) - (avg(x, size) * avg(y, size)));
}

/**
 * pearson - calculate the Pearson correlation coefficient of X and Y
 * @param x - the first array
 * @param y - the second array
 * @param size - the array size of x and y.
 * @return the Pearson correlation coefficient of X and Y
 */
float pearson(float* x, float* y, int size){

    sizeZeroError(size);
    nullArrayError(x);
    nullArrayError(y);

    float sqrtXY = sqrt(var(x,size))*sqrt(var(y,size));
    if(sqrtXY == 0){
        throw std::runtime_error("can not divide by zero\n");
    }
    return (cov(x,y,size)/sqrtXY);
}
/**
 * createSubArray - function that helps to the cov function. creates two separate arrays - one for the X values
 * of the points and the second for the Y values of the points.
 * @param points - arrays which contains points.
 * @param size - the array size of x and y and points.
 * @param subX - an array for the X values of the points.
 * @param subY - an array for the Y values of the points.
 */
void createSubArray(Point** points, int size, float* subX, float* subY){
    for (int i=0 ; i<size ; i++) {
        subX[i] = points[i]->x;
        subY[i] = points[i]->y;
    }
}

/**
 * linear_reg - performs a linear regression between
 * @param points - arrays which contains points.
 * @param size - the array size of points.
 * @return the line equation
 */
Line linear_reg(Point** points, int size){

    if(points == nullptr ){
        throw std::runtime_error("No parameters\n");
    }
    sizeZeroError(size);

    float x[size];
    float y[size];
    createSubArray(points,size,x,y);
    if(var(x,size) == 0){
        throw std::runtime_error("can not divide by zero\n");
    }
    float a = (cov(x,y,size)) / (var(x,size));
    float b = avg(y,size) - (a * avg(x,size));

    return Line(a,b);
}

/**
 * dev - calculate the deviation between point p and the line equation of the points
 * @param p - a point
 * @param points - arrays which contains points.
 * @param size - the array size of points.
 * @return the deviation between point p and the line equation of the points
 */
float dev(Point p,Point** points, int size){

    if(points == nullptr){
        throw std::runtime_error("No parameters\n");
    }
    sizeZeroError(size);

    Line line = linear_reg(points, size);
    float fx = line.f(p.x);
    if ((fx-p.y)>=0) {
        return (fx-p.y);
    } else {
        return (p.y-fx);
    }
}

/**
 * dev - calculate the deviation between point p and the line
 * @param p - a point
 * @param l - a line
 * @return the deviation between point p and the line
 */
float dev(Point p,Line l){

    float fx = l.f(p.x);
    if ((fx-p.y)>=0) {
        return (fx-p.y);
    } else {
        return (p.y-fx);
    }
}