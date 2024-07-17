cmake_minimum_required(VERSION 3.5)
project(sick_lidar_localization)

    add_compile_options(-g -Wall -Wno-reorder -Wno-sign-compare -Wno-unused-local-typedefs -Wno-unused-parameter -Wno-unused-function -Wno-unused-result)
    # add_compile_options(-Wshadow) # Note: compiler option -Wshadow generates a lot of warnings in ros header files. Therefore it's deactivated by default, but can be usefull for development and testing.
    set(LINUX_LIBRARIES pthread)    # gcc maps std::thread to pthread, using std::thread requires linking with pthread
   
#######################
## Required packages ##
#######################

find_package(CURL REQUIRED)
find_package(jsoncpp REQUIRED)


###########
## Build ##
###########

include_directories(include include/tinyxml ${catkin_INCLUDE_DIRS} ${CURL_INCLUDE_DIRS})

add_library(sick_localization_lib ${LIB_TYPE}
    src/curl_wrapper.cpp
    src/json_parser.cpp
    src/launchparser/launchparser.cpp
    src/sick_lidar_localization.cpp
    src/sick_ros_wrapper.cpp
    src/sick_services.cpp
    src/SoftwarePLL.cpp
    src/udp_message_parser.cpp
    src/udp_receiver_thread.cpp
    src/udp_sender.cpp
    src/tinyxml/tinystr.cpp
    src/tinyxml/tinyxml.cpp
    src/tinyxml/tinyxmlerror.cpp
    src/tinyxml/tinyxmlparser.cpp    
)
target_link_libraries(sick_localization_lib ${CURL_LIBRARIES} jsoncpp_lib ${catkin_LIBRARIES} ${LINUX_LIBRARIES} ${WIN_LIBRARIES})

## Executables
add_executable(sick_lidar_localization_main src/sick_lidar_localization_main.cpp)
set_target_properties(sick_lidar_localization_main PROPERTIES OUTPUT_NAME sick_lidar_localization)
target_link_libraries(sick_lidar_localization_main sick_localization_lib ${CURL_LIBRARIES} jsoncpp_lib ${catkin_LIBRARIES})

add_executable(gen_service_call src/gen_service_call.cpp)
target_link_libraries(gen_service_call sick_localization_lib ${CURL_LIBRARIES} jsoncpp_lib ${catkin_LIBRARIES})

add_dependencies(sick_lidar_localization_main sick_localization_lib)

#############
## Install ##
#############

install(DIRECTORY launch DESTINATION ${CMAKE_BINARY_DIR})
