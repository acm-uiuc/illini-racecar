#include <ros.h>
#include <Servo.h>
#include <std_msgs/String.h>
#include <illini_racecar/AckermannCmd.h>

ros::NodeHandle nh;

Servo throttle, steer;

const int kSteerPort = 11;
const int kThrottlePort = 9;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

int clip(int val) {
  return min(180, max(0, val));
}

void messageCb( const illini_racecar::AckermannCmd &msg) {
  steer.write(clip(msg.steering_angle));
  throttle.write(clip(msg.throttle));
  str_msg.data = "Hello";
  chatter.publish(&str_msg);
}

ros::Subscriber<illini_racecar::AckermannCmd> sub("ackermann_cmd", &messageCb );

void setup()
{
  steer.attach(kSteerPort);

  throttle.attach(kThrottlePort);
  for (int pos = 90; pos <= 100; pos += 1) {
    throttle.write(pos);
    delay(150);
  }
  throttle.write(90);
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(10);
}
