#include <string>
#include "BoundedBuffer.h"


BoundedBuffer::BoundedBuffer() {
    pthread_mutex_init(&m, nullptr);
    sem_init(&full, 0, 0);
}

//using semaphore and mutex to prevent race condition.
pair<int,string> BoundedBuffer::remove() {
    sem_wait(&full);
    pthread_mutex_lock(&m);
    pair<int,string> res = myQueue.front();
    myQueue.pop();
    pthread_mutex_unlock(&m);
    sem_post(&empty);

    return res;
}

//using semaphore and mutex to prevent race condition.
void BoundedBuffer::insert(int num, string& s) {
    sem_wait(&empty);
    pthread_mutex_lock(&m);
    pair<int, string> p = make_pair(num, s);
    myQueue.push(p);
    pthread_mutex_unlock(&m);
    sem_post(&full);
}

//using semaphore to easily bound the queue size.
void BoundedBuffer::setSize(int size) {
    sem_init(&empty, 0, size);
}