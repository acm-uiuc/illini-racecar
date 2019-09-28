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
    const double speed_max = 0.001, speed_min = -0.001; // m/s, hardcoded atm
    const double angle_max = 0.349066, angle_min = -0.349066; //radians, hardcoded atm

    ros::NodeHandle node;
    ros::Publisher output_pub;
    ros::Subscriber cmd_vel_sub;
    ros::Timer timer;

    void sub_callback(const geometry_msgs::Twist &msg);
    void timer_callback(const ros::TimerEvent &timer_event);
    uint16_t convert_to_pwm(double value, double min_val, double max_val);

  public:
    DriveController(double dt);
};
