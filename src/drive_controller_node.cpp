#include <ros/ros.h>
#include "drive_controller.h"

int main(int argc, char **argv){
  ros::init(argc, argv, "drive_controller_node");
  DriveController d(0.01);
  ros::spin();
}
