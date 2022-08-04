/*
 * Server.cpp
 * Authors: Noa Amit 315231274 & Tomer Hadar 207651027
 */
#include "Server.h"

string socketIO::read() {
    char buffer = 0;
    string s;
    while(buffer!='\n'){
        recv(clientID,&buffer,sizeof(char),0);
        s = s + buffer;
    }
    return s;
}
void socketIO::write(string text) {
    size_t size_buffer = strlen((const char*)(text.c_str()));
    send(clientID,(const char*)(text.c_str()),size_buffer,0);
}

void socketIO::write(float f){
    stringstream s;
    s << f ;
    string newS(s.str());
    write(newS);
}

void socketIO::read(float* f) {
    recv(clientID,f,sizeof(float),0);
}

Server::Server(int port)throw (const char*) {
    fileD = socket(AF_INET, SOCK_STREAM, 0);
    if(fileD<0) {
        throw "connection failed";
    }
    s.sin_port = htons(port);
    s.sin_family = AF_INET;
    s.sin_addr.s_addr = INADDR_ANY;
    int bindNum = bind(fileD, (struct sockaddr*)&s, sizeof(s));
    if(bindNum<0) {
        throw "bind connection failed";
    }
    int ListenNum = listen(fileD, 100);
    if(ListenNum<0) {
        throw "listen connection failed";
    }
    stopThread = false;

}
void sig_handler(int signum){
    return;
}

void Server::start(ClientHandler& ch)throw(const char*){
    t = new thread([&ch, this]() {
        signal(SIGALRM,sig_handler);
        while (!stopThread) {
            alarm(1);
            socklen_t clientSize = sizeof(c);
            int clientId = accept(fileD, (struct sockaddr *) &c, &clientSize);
            if (clientId > 0) {
                ch.handle(clientId);
                close(clientId);
            }
            alarm(0);
        }
        close(fileD);
    });
}

void Server::stop(){
    stopThread = true;
    t->join(); // do not delete this!

}
Server::~Server() {
}