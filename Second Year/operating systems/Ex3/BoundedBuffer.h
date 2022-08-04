#ifndef EX3_BOUNDEDBUFFER_H
#define EX3_BOUNDEDBUFFER_H
#include <semaphore.h>
#include "queue"
#include "string"
using namespace std;

class BoundedBuffer {
    pthread_mutex_t m;
    sem_t full;
    sem_t empty;
    queue<pair<int,string>> myQueue;

public:
    BoundedBuffer();
    void insert(int num, string& s);
    pair<int,string> remove();
    void setSize(int size);
};


#endif //EX3_BOUNDEDBUFFER_H