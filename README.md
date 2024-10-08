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
### 1. Log in LiDAR_LOC
* 1. connect the device properly like the image shown below.And enter SIM1000 IP address into the browser's address line. The default IP address is "192.168.0.1".

picture!!!!!!!!!!

![alt text](image/image-12.png)

### 2. Uploading a map
First of all, we need to upload a map so that LiDAR_LOC can start to loclaization and navigation. following the step below to create a map.

* 1. Open LiDAR_LOC and log in with "service" (Password: servicelevel). And Click "Maps" in the device

![alt text](image/image.png)


Click on 'Record Data' and move the Lidar sensor around to start recording a map. After finishing the map recording, download the file from 'Map Recording File'.

![alt text](image/image-1.png)

* 2. Open SMET (SICK Map Engineering Tool), which requires a license to convert a map file into '.vmap' file needed by LiDAR_LOC.

![alt text](image/image-2.png)

* 3. Open the map file you have recorded, and click 'import SC'.

![alt text](image/image-3.png) 

* 4. Click 'find loop closure' in 'find loop closure' dropdown.

![alt text](image/image-6.png)

* 5. You can change the map's position and orientation to a certain place in 'Graph position' dropdown

![alt text](image/image-7.png)

* 6. Finally, click on 'Export VMAP' to download the map.

* 7. Go back to the LiDAR_LOC and upload the '.vmap' file you just downloaded.

![alt text](image/image-9.png)

* 8. After uploading the map, you can input it to visualize and use for localization.

![alt text](image/image-10.png)

## 2. Initialize pose

I'll indroduce three ways to initialize pose for relocalization. 

### 1. initialize pose with LiDAR_LOC
Turn on 'Pose Initialization,' then click on the position and drag it to align with the sensor's orientation.

![alt text](image/image-8.png)

### 2. REST API

LiDAR-LOC can be configured using a JSON REST API.

in the `build` directory, open a terminal and enter the command below:

```
/gen_service_call LocInitializeAtPose POST "{\"data\": {\"pose\":{\"x\":10300, \"y\":-5200, \"yaw\":30000}, \"searchRadius\":1000}}" -d=2
```

Then turn back to see the visual map in LIDAR_LOC, as you can see, the sensor's postion will be at (10.3, -5.2). And orientation is 30 degree.

### 3.  Communication via CoLa2

Please see the directory `CoLa2 InitializePose`

