#pragma once

class lidarThread{

public:
    lidarThread();
    ~lidarThread();

    void openUDPsocket();
    void closeTCPsocket(int sock);
private:

};

