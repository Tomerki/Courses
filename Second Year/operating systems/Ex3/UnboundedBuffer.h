#ifndef EX3_UNBOUNDEDBUFFER_H
#define EX3_UNBOUNDEDBUFFER_H
#include <semaphore.h>
#include "queue"
#include "string"
using namespace std;

class UnboundedBuffer {
public:
    pthread_mutex_t m1;
    sem_t full;
    queue<string> myBuffer;
public:
    UnboundedBuffer();
    void insert(string& s);
    string remove();
    queue<string> getMyBuffer();

};


#endif //EX3_UNBOUNDEDBUFFER_H