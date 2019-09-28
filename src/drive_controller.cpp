#include "drive_controller.h"
#include "illini_racecar/AckermannCmd.h"

DriveController::DriveController(double dt){
  input_v = 0;
  input_w = 0;

  output_pub = node.advertise<illini_racecar::AckermannCmd>("/ackermann_cmd", 10);
  cmd_vel_sub = node.subscribe("/cmd_vel", 100, &DriveController::sub_callback, this);
  timer = node.createTimer(ros::Duration(dt), &DriveController::timer_callback, this);
}

void DriveController::timer_callback(const ros::TimerEvent &timer_event){
  illini_racecar::AckermannCmd output;
  double steering_angle = input_v == 0 ? 0 : atan(input_w * wheelbase / input_v);
  output.throttle = convert_to_pwm(input_v, speed_min, speed_max);
  output.steering_angle = convert_to_pwm(steering_angle, angle_min, angle_max);
  output_pub.publish(output);
}

void DriveController::sub_callback(const geometry_msgs::Twist &msg){
  input_v = msg.linear.x;
  input_w = msg.angular.z;
}

uint16_t DriveController::convert_to_pwm(double value, double min_val, double max_val){
  double perc = value/(max_val - min_val);
  return (uint16_t)(perc*(pwm_max-pwm_neutral) + pwm_neutral);
}
