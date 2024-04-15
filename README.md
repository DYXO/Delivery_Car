#  A smart delivery cart



# Handheld lidar mapping

This function needs to start the program in the slam_gmapping function package. The source code is located in the [rplidar_ws] source code. Here we use the supporting virtual machine to explain how to start the program. If you want to put it on your own motherboard, you need to put [slam_gmapping] and [openslam_gmapping] in the src directory of the workspace to compile.

## Start gmapping mapping

Terminal input
```
ros2 launch rplidar_ros test_gmapping.launch.py
```
![1](https://github.com/DYXO/Delivery_Car/assets/166942680/9c8a6f01-5e79-4253-9e8a-f528c8180a9b)

## View node communication

Terminal input
```
ros2 run rqt_graph rqt_graph
```

## View TF tree

Terminal input
```
ros2 run tf2_tools view_frames.py
```
A frames.pdf file will be generated in the directory where the command terminal is started.
# Navigation and obstacle avoidance

This chapter needs to be used with a car chassis and other sensors to operate. 


## Program function description

After the program is started, rviz will be opened to display the map. By setting the target point, single-point and multi-point navigation of the car can be achieved.

## Car chassis pictures

![2](https://github.com/DYXO/Delivery_Car/assets/166942680/90b629d5-17f5-4ee4-8a55-03e151761e9a)

## Introduction to Navigation2

Navigation2 file：**[link](https://navigation.ros.org/index.html)**
Plug-ins provided by Navigation2：**[link](https://navigation.ros.org/plugins/index.html#plugins)**
Navigation2 overall architecture diagram:
![image](https://github.com/DYXO/Delivery_Car/assets/166942680/2f04bb02-4c63-4513-8965-9336fa40771e)
Take ros2-foxy as an example, enter in the terminal,
```
sudo apt install ros-foxy-nav2-* -y
```

## code path

launch source code. The location of the function source code is located in the supporting virtual machine.
```
~/rplidar_ws/src/yahboomcar_nav/launch
```


# Program start


## Start rviz display


Terminal input,
```
ros2 launch yahboomcar_rviz yahboomcar_nav_launch.py
```
At this time, the map will not be displayed on the screen, and there is no need to worry about the red topics of each node on the left, because the navigation node has not been started yet.



## Start the radar chassis


Terminal input,
```
ros2 launch yahboomcar_nav laser_bringup_launch.py
```

## Start navigation node

Terminal input,
```
ros2 launch yahboomcar_nav navigation_dwb_launch.py
```
The DWB navigation algorithm is used here.
A map appears in rviz. Click [2D Pose Estimate] on rviz, then compare the pose of the car and mark an initial pose for the car on the map;
Compare the overlap between the radar scanning point and the obstacle, and set the initial pose of the car multiple times until the radar scanning point and the obstacle roughly overlap;

## Single point navigation


After the initial pose is set, you can click [2D Goal Pose] to set a navigation target point, and the car will start single-point navigation;


## Multi-point navigation


After the initial pose is set, click [Waypoint mode] in the lower left corner, and then click [Navigation2 Goal] on rviz to mark a target point on the map. Click [Navigation2 Goal] again to mark a second goal on the map. Click, and continue to cycle, you can mark multiple target points at one time
After marking multiple target points, click [Start Navigation] to start multi-point navigation;
