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

char *lidarThread::InitializedPose(int64_t x, int64_t y, int32_t heading){
    const unsigned char *xstr = (const unsigned char *) &x;
    const unsigned char *ystr = (const unsigned char *) &y;
    const unsigned char *headingstr = (const unsigned char *) &heading;

    char *xstring = (char *) malloc(4 * sizeof(char));
    char *ystring = (char *) malloc(4 * sizeof(char));
    char *headingstring = (char *) malloc(4 * sizeof(char)); 
    for (int i = 0; i < 4; i++){
        xstring[i] = xstr[3-i];
        ystring[i] = ystr[3-i];
        headingstring[i] = headingstr[3-i];
    }
    char pose[1024];
    memcpy(&pose[0], xstring, 4);
    memcpy(&pose[4], ystring, 4);
    memcpy(&pose[8], headingstring, 4);
    
    char *finalpose = &pose[0];
    return finalpose;
}
