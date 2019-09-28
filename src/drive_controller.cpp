#include "drive_controller.h"
#include "illini_racecar/AckermannCmd.h"

DriveController::DriveController(double dt){
  input_v = 0;
  input_w = 0;

  output_pub = node.advertise<illini_racecar::AckermannCmd>("/ackerman_target", 10);
  cmd_vel_sub = node.subscribe("/cmd_vel", 100, &DriveController::sub_callback, this);
  timer = node.createTimer(ros::Duration(dt), &DriveController::timer_callback, this);
}

void DriveController::timer_callback(const ros::TimerEvent &timer_event){
  illini_racecar::AckermannCmd output;
  output.throttle = 0;
  output.steering_angle = 0;
  output_pub.publish(output);
}

void DriveController::sub_callback(const geometry_msgs::Twist &msg){
  input_v = msg.linear.x;
  input_w = msg.angular.z;
}
