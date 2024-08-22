#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    const char* server_ip = "192.168.0.100"; // Replace with actual IP address
    int port = 2122;                        // LiDAR-LOC port number

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    printf("sock = %d\n", sock);
    if (sock < 0) {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_address.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return 1;
    }

    if (connect(sock, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return 1;
    }

    std::cout << "Connected to " << server_ip << ":" << port << std::endl;

    // Step 2: Open CoLa2 session
    const char* cola2_open_session = "\x02\x02\x02\x02" // STX
                                     "\x00\x00\x00\x0E"  // Length: 13 bytes
                                     "\x00\x00"          // Hub and NoC
                                     "\x00\x00\x00\x00"  // SessionID
                                     "\x00\x01"          // ReqID
                                     "\x4F\x58"          // Cmd = "O", Mode = "X"
                                     "\x1E"              // Timeout = 30 sec
                                     "\x00\x01"
                                     "\x00";         // ClientID Length = 0, ClientID Flexstring = 0

    send(sock, cola2_open_session, 22, 0);

    // Receive the LiDAR-LOC response (confirm the session and get SessionID)
    char response[1024];
    int bytes_received = recv(sock, response, sizeof(response), 0);
    printf("byte = %d\n", bytes_received);
    if (bytes_received > 0) {
        std::cout << "Received response for session open: ";
        for (int i = 0; i < bytes_received; ++i) {
            printf("%02X ", (unsigned char)response[i]);
        }
        std::cout << std::endl;
    }

    // Step 3: Call LocInitializeAtPose
    char *session_id = (char *)malloc(10 * sizeof(char));
    for (int i = 10; i <= 13; i++){
        session_id[i-10] = response[i];
    }
    session_id[4] = '\0';
    printf("session = %c", session_id[0]);
    const char *initial_data = "\x02\x02\x02\x02"  // STX
                               "\x00\x00\x00\x2C"  // Length: 44 bytes
                               "\x00\x00";          // Hub and NoC
    const char *last_data = "\x00\x02"          // ReqID
                            "\x4D\x4E"          // Cmd = "M", Mode = "N"
                            "\x4C\x6F\x63\x49\x6E\x69\x74\x69\x61\x6C\x69\x7A\x65\x41\x74\x50\x6F\x73\x65"  // Method name: "LocInitializeAtPose"
                            "\x20"              // Space
                            "\x00\x00\x04\x06"  // X coordinate: 10.3 m = 10 300 mm (Big-endian)
                            "\xFF\xFF\xEB\xB0"  // Y coordinate: -5.2 m = -5 200 mm
                            "\x00\x00\x75\x30"  // Yaw angle: 30 deg = 30 000 mdeg
                            "\x03\xE8"; 
    // size_t initial_length = std::strlen(initial_data);
    // char *initialize_pose = (char *)malloc(initial_length);

    send(sock, initial_data, 10, 0);
    send(sock, session_id, 4, 0);
    send(sock, last_data, 38, 0);

    // Receive the LiDAR-LOC response (confirm the method call-up)
    bytes_received = recv(sock, response, sizeof(response), 0);
    if (bytes_received > 0) {
        std::cout << "Received response for LocInitializeAtPose: ";
        for (int i = 0; i < bytes_received; ++i) {
            printf("%02X ", (unsigned char)response[i]);
        }
        std::cout << std::endl;
    }

    // Step 4: Close CoLa2 session
    const char* cola2_close_session_front_data = "\x02\x02\x02\x02"  // STX
                                      "\x00\x00\x00\x0A"  // Length: 10 bytes
                                      "\x00\x00";          // Hub and NoC

    const char *cola2_close_session_subsequent_data= "\x00\x03"          // ReqID
                                               "\x43\x58";         // Cmd = "C", Mode = "X"

    send(sock, cola2_close_session_front_data, 10, 0);
    send(sock, session_id, 4, 0);
    send(sock, cola2_close_session_subsequent_data, 4,0);

    // Receive the LiDAR-LOC response (confirm session close)
    bytes_received = recv(sock, response, sizeof(response), 0);
    if (bytes_received > 0) {
        std::cout << "Received response for session close: ";
        for (int i = 0; i < bytes_received; ++i) {
            printf("%02X ", (unsigned char)response[i]);
        }
        std::cout << std::endl;
    }

    // Close the socket
    close(sock);

    return 0;
}
