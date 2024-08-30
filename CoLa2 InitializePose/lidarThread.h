#pragma once

class lidarThread{

public:
    lidarThread();
    ~lidarThread();

    void openUDPsocket();
    void closeUDPsocket(int sock);
    char *InitializedPose(int64_t x, int64_t y, int32_t heading);
private:

};
