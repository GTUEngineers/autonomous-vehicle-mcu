#!/bin/bash
if ping -q -c 1 -W 1 192.168.1.201 >/dev/null; then
  echo "IPv4 is up"
else
  exit 1
fi

source /home/gtu-hazine/catkin_ws/devel/setup.bash
/usr/bin/python3 /home/gtu-hazine/Desktop/AllRepos_15.09.2019/autonomous-vehicle/Linux_Codes/Scripts/lidar_req.py
roslaunch velodyne_pointcloud VLP16_points.launch &
/home/gtu-hazine/catkin_ws/src/depth_clustering/build/devel/lib/depth_clustering/show_objects_node --num_beams 16 

