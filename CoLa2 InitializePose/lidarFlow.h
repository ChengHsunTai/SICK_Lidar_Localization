#pragma once

class lidarFlow 
{
public:
    lidarFlow();
    ~lidarFlow();
    
    int openTCPsocket();

    void closeTCPsocket(int sock);

    char *getSessionID(char response[1024]);


private:

};