#include "UnboundedBuffer.h"
#include "string"

UnboundedBuffer::UnboundedBuffer() {
    pthread_mutex_init(&m1, nullptr);
    sem_init(&full, 0, 0);
}

//using semaphore and mutex to prevent race condition.
void UnboundedBuffer::insert(string &s) {
    pthread_mutex_lock(&m1);
    myBuffer.push(s);
    pthread_mutex_unlock(&m1);
    sem_post(&full);
}

queue<string> UnboundedBuffer::getMyBuffer() {
    return myBuffer;
}

//using semaphore and mutex to prevent race condition.
string UnboundedBuffer::remove() {
    sem_wait(&full);
    pthread_mutex_lock(&m1);
    string s = myBuffer.front();
    myBuffer.pop();
    pthread_mutex_unlock(&m1);
    return s;
}