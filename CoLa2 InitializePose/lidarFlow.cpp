#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#include "lidarFlow.h"


lidarFlow::lidarFlow(){

}

lidarFlow::~lidarFlow(){

}

int lidarFlow::openTCPsocket(){
    const char *server_ip = "192.168.0.1"; //sim1000 IP address
    int port = 2122; // cola2 communication port

    int tcpsocket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcpsocket < 0) {
        std::cerr << "Error creating tcp sender socket" << std::endl;
    }
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;

    }

    if (connect(tcpsocket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Connection failed" << std::endl;

    }

    return tcpsocket;

}

void lidarFlow::closeTCPsocket(int sock){
    close(sock);
}

char *lidarFlow::getSessionID(char response[1024]){
    char *session_id = (char *)malloc(10 * sizeof(char));
    for (int i = 10; i <= 13; i++){
        session_id[i-10] = response[i];
    }
    session_id[4] = '\0';

    return session_id;
}

