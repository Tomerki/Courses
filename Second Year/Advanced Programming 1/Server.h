/*
 * Server.h
 * Authors: Noa Amit & Tomer Hadar
 */
#ifndef SERVER_H_
#define SERVER_H_

#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include "CLI.h"

using namespace std;

class socketIO:public DefaultIO{
    int clientID;
public:
    socketIO(int clientID):clientID(clientID){}
    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);
};
// edit your ClientHandler interface here:
class ClientHandler{
public:
    virtual void handle(int clientID)=0;
};
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(int clientID){
        socketIO socketIo(clientID);
        CLI cli(&socketIo);
        cli.start();
    }
};

class Server {
    thread* t; // the thread to run the start() method in
    int fileD;
    struct sockaddr_in s;
    struct sockaddr c;
    bool stopThread;

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};

#endif /* SERVER_H_ */
