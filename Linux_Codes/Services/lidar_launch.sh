#!/bin/sh

#source /home/gtu-hazine/catkin_ws/devel/setup.bash

roslaunch velodyne_pointcloud VLP16_points.launch &
/home/gtu-hazine/Desktop/AllRepos_15.09.2019/depth_clustering/build/devel/lib/depth_clustering/show_objects_node --num_beams 16 &

