#  A smart delivery cart



# Handheld lidar mapping

This function needs to start the program in the slam_gmapping function package. The source code is located in the [rplidar_ws] source code. Here we use the supporting virtual machine to explain how to start the program. If you want to put it on your own motherboard, you need to put [slam_gmapping] and [openslam_gmapping] in the src directory of the workspace to compile.

## Start gmapping mapping

Terminal input
```
ros2 launch rplidar_ros test_gmapping.launch.py
```
[link](https://photos.google.com/photo/AF1QipPt1PcGm9cOzbyYILMKcHNFHPSgXC7eah9KfOwm)
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
## launch file analysis

File path (combined with virtual machine):

```
/home/yahboom/rplidar_ws/src/rplidar_ros-dev-ros2/launch/test_gmapping.launch.py
```

test_gmapping.launch.py
```
from launch import LaunchDescription
from launch_ros.actions import Node
import os
from launch.actions import IncludeLaunchDescription
from launch.conditions import
LaunchConfigurationEquals,LaunchConfigurationNotEquals
from launch.launch_description_sources import
PythonLaunchDescriptionSource,AnyLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
from launch.actions import DeclareLaunchArgument
import os
def generate_launch_description():
LIDAR_TYPE = os.getenv('LIDAR_TYPE')
lidar_type_arg = DeclareLaunchArgument(name='lidar_type',
default_value=LIDAR_TYPE, description='The type of lidar')
lidar_launch =
IncludeLaunchDescription(PythonLaunchDescriptionSource([os.path.join(get_package
_share_directory('rplidar_ros'), 'launch'),'/lidar.launch.py']))
s2_gmapping_launch =
IncludeLaunchDescription(PythonLaunchDescriptionSource([os.path.join(get_package
_share_directory('slam_gmapping'),
'launch'),'/s2_gmapping_launch.py']),condition=LaunchConfiguration
