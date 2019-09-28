#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

/**
 * /cmd_vel (Twist) -> /rc_msg (AckermannCmd)
 **/
class DriveController{

  private:

    double input_v, input_w;

    ros::NodeHandle node;
    ros::Publisher output_pub;
    ros::Subscriber cmd_vel_sub;
    ros::Timer timer;

    void sub_callback(const geometry_msgs::Twist &msg);
    void timer_callback(const ros::TimerEvent &timer_event);

  public:
    DriveController(double dt);
};
