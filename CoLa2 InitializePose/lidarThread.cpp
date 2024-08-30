#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "lidarThread.h"

lidarThread::lidarThread(){

}

lidarThread::~lidarThread(){

}


void lidarThread::openUDPsocket(){
    int port = 5010;
    
}