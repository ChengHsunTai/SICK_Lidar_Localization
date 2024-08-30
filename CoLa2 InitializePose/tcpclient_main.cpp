#include <stdio.h>
#include <chrono>
#include <iostream>
#include <cstring>
#include <thread>

#include "lidarFormat.h"
#include "lidarFlow.h"
#include "lidarThread.h"
// #include "sick_lidar_localization/include/sick_lidar_localization/sick_common.h"
// #include "sick_lidar_localization/include/sick_lidar_localization/udp_message_parser.h"

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

using namespace std::chrono_literals;

int main() {
    lidarFormat format;
    lidarFlow flow;
    lidarThread thread;

    int sock = flow.openTCPsocket();
    //open session to lidar
    const char *tte = format.opensession();
    
    send(sock, tte, 22, 0);
        
        
    //receive the response from lidar to get the session_id
    char response[1024];
    int bytes_received = recv(sock, response, sizeof(response), 0);
    
    //print out the return from lidar
    if (bytes_received > 0) {
        std::cout << "Received response for session open: ";
        for (int i = 0; i < bytes_received; ++i) {
            printf("%02X ", (unsigned char)response[i]);
        }
        std::cout << std::endl;
    }

    // get session id from lidar's response
    char *sessoin_id = flow.getSessionID(response);

    //function to get position and orientation value

    int64_t x, y;
    int32_t heading;
    char *pose = thread.InitializedPose(x, y, heading);
    
    //send LocInitializeAtPose command
    char *callinitializepose = format.callinitializepose(sessoin_id, pose);

    send(sock, callinitializepose, 52, 0);

    bytes_received = recv(sock, response, sizeof(response), 0);
    if (bytes_received > 0) {
    std::cout << "Received response for session open: ";
    for (int i = 0; i < bytes_received; ++i) {
        printf("%02X ", (unsigned char)response[i]);
    }
    std::cout << std::endl;
    }

    char *closesession = format.closesession(sessoin_id);

    send(sock, closesession, 18, 0);

    flow.closeTCPsocket(sock);

    return 0;
}
