# SICK_Lidar_Localization

## Introduction

to be conti

## build on native linux
to run LiDAR_localization 
### 1. install libcurl and jsoncpp

```
sudo apt-get install libcurl-dev
sudo apt-get install libjsoncpp-dev
```
### 2. clone repository

```
git clone https://github.com/SICKAG/sick_lidar_localization.git
```
### 3. build project sick_lidar_localization with cmake:
```
cd sick_lidar_localization
if [ -d ./build ] ; then rm -rf ./build ; fi 
mkdir -p ./build 
pushd ./build
cmake -DROS_VERSION=0 -G "Unix Makefiles" ..
make -j4
popd
```
`if [ -d ./build ] ; then rm -rf ./build ; fi ` create a build directory if there exist any, delete it and recreate it.

`cmake -DROS_VERSION=0 -G "Unix Makefiles" ..` set parameter "ROS_VERSION" = 0, and generate a make file by "Unix Makefiles"

`make -j4` build the project, using up to 4 parallel jobs

## Run sick_lidar_localization
to run sick_lidar_localization in native linux without ros, please enter commands below:
```
cd ./build
./sick_lidar_localization ../launch/sick_lidar_localization.launch [options]
```

## Print out the localization result

### 1. open the "verbose" in launch file

open `sick_lidar_localization.launch`

![未命名](https://github.com/user-attachments/assets/22f150ec-3732-4e33-b2d0-c1640d16523b)

After edit "verbose" to 1, run the sick_lidar_localization again, it'll print out the message type of 0502 in the terminal if the sensor connected successfully.

## record the raw data to the text file

Take message type 0502 for example, include the <fstream> library in the top of `udp_message_parser.cpp` and add a global variable called `outputFile`.

![image](https://github.com/user-attachments/assets/c95eb392-d516-47a1-8133-1fc07a075ef9)

in the funtion `sick_lidar_localization::UDPMessage::printPayload(const sick_lidar_localization::UDPMessage::LocalizationControllerResultPayload0502& payload, bool print_sync_time)`, add the code below:
```
std::ofstream appendFile("output.txt", std::ios::app);
if (appendFile.is_open()) { // check if the file was opened successfully
appendFile << "x = " << payload.x << ", y = " << payload.y << "\n"; // write data to the file
appendFile.close(); // close the file when done
std::cout << "Data was written to output.txt\n";
}
else {
    std::cerr << "Error opening file\n";
}
```
 ![image](https://github.com/user-attachments/assets/8aab15e9-546f-43f8-91f1-8fb6cf5a9738)

When running the `sick_lidar_localization`, you will get the `output.txt` file in `build` directory.

## LiDAR LOC

LiDAR_LOC is designed for industrial automation and robotics navigation. It can provide different types of messages for various applications.

### 1. Creating a map
First of all, uploading a map that


```
./build/gen_service_call LocInitializeAtPose POST "{\"data\": {\"pose\":{\"x\":10300, \"y\":-5200, \"yaw\":30000}, \"searchRadius\":1000}}" -d=2
```






