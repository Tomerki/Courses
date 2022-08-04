#ifndef EX3_PRODUCER_H
#define EX3_PRODUCER_H
#include "BoundedBuffer.h"


class Producer {
    int serialNumber;
    int numOfProducts;
    int sport, weather, news;
    BoundedBuffer myBuffer;
    bool isDone;
    int countMyWork;

public:
    Producer(int serial, int amount, int bufferSize);
    int getSerialNumber() const;
    int getNumberOfProducts() const;
    BoundedBuffer& getQueue();
    void increase(int num);
    int getAmount(int num) const;
    void setisDone();
    bool getisDone();
    int getWorkCounter();
    void increaseWorkCounter();

};
#endif //EX3_PRODUCER_H