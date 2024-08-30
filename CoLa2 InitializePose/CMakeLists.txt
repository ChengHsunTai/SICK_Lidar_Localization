# CMakeList.txt: CMakeTest 的 CMake 專案，在此包含來源及定義
# 專案專屬邏輯。
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeTest")

add_subdirectory(sick_lidar_localization)

# 將來源新增到此專案的可執行檔。
add_executable (CMakeTest 
"tcpclient_main.cpp" 
"lidarFormat.cpp" 
"lidarFormat.h" 
"lidarFlow.cpp" 
"lidarFlow.h"
"lidarThread.cpp" 
"lidarThread.h")


#target_link_libraries(CMakeTest PRIVATE sick_localization_lib)
