#include <iostream>
#include <sick_lidar_localization/sick_lidar_localization.h>
#include <thread>
#include <limits>

int main(int argc, char** argv){

    std::cout << "hello, this is Lidar" << std::endl;
    
    rosNodePtr node = 0;
    bool launchfile_ok = sick_lidar_localization::API::parseLaunchfileSetParameter(node, argc,argv);
    
    
    sick_lidar_localization::Config config; // default configuration
 
    sick_lidar_localization::API lidar_loc_api;
    if (!lidar_loc_api.init(node, config))
    {
        ROS_ERROR_STREAM("## ERROR sick_lidar_localization::API::init() failed, aborting... ");
        exit(EXIT_FAILURE);
    }

    std::this_thread::sleep_for(std::chrono::seconds(std::numeric_limits<int>::max()));

    ROS_INFO_STREAM("sick_lidar_localization finished.");
    lidar_loc_api.close();

}
