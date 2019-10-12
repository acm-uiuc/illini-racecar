#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

/**
 * /cmd_vel (Twist) -> /rc_msg (AckermannCmd)
 **/
class DriveController{

  private:

    double input_v, input_w;
    const double wheelbase = 0.3302; //m
    const int pwm_max = 180, pwm_min = 0, pwm_neutral = 90;
    const double speed_max = 3;
    const double theoretical_speed_max = 13;
    const double angle_max = 1.6;

    ros::NodeHandle node;
    ros::Publisher output_pub;
    ros::Subscriber cmd_vel_sub;
    ros::Timer timer;

    void sub_callback(const geometry_msgs::Twist &msg);
    void timer_callback(const ros::TimerEvent &timer_event);
    int convert_to_pwm(double value, double min_val, double max_val);

  public:
    DriveController(double dt);
};
