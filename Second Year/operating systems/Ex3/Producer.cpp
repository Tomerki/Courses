#include "Producer.h"
using namespace std;

Producer::Producer(int serial, int amount, int bufferSize) {
    serialNumber = serial;
    numOfProducts = amount;
    sport = 0;
    weather = 0;
    news = 0;
    myBuffer = BoundedBuffer();
    myBuffer.setSize(bufferSize);
    isDone = false;
    countMyWork = 0;
}

int Producer::getSerialNumber() const {
    return serialNumber;
}

int Producer::getNumberOfProducts() const {
    return numOfProducts;
}

BoundedBuffer& Producer::getQueue() {
    return myBuffer;
}

void Producer::increase(int num) {
    if(!num)
        sport++;
    else if(num == 1)
        weather++;
    else
        news++;
}

int Producer::getAmount(int num) const{
    if(!num)
        return sport;
    else if(num == 1)
        return weather;
    else
        return news;
}

bool Producer::getisDone() {
    return isDone;
}

void Producer::setisDone() {
    isDone = !isDone;
}

int Producer::getWorkCounter() {
    return countMyWork;
}

void Producer::increaseWorkCounter() {
    countMyWork++;
}