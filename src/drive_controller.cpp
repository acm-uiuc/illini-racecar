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
  output.throttle = std::max(90, convert_to_pwm(input_v, speed_max, theoretical_speed_max));
  output.steering_angle = convert_to_pwm(steering_angle, angle_max, angle_max);
  output_pub.publish(output);
}

void DriveController::sub_callback(const geometry_msgs::Twist &msg){
  input_v = msg.linear.x;
  input_w = msg.angular.z;
}

int DriveController::convert_to_pwm(double value, double max_limit, double max_real){
  double perc = std::min(value, max_limit)/max_real;
  int rv = perc * pwm_neutral + pwm_neutral;
  return rv;
}
