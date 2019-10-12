import rospy

from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist


"""
ROS node that listens for sensor_msgs/Joy and converts them into geometry_msgs/Twist for arcade drive.
"""

LEFT_Y_IDX = 1
RIGHT_X_IDX = 3

# joystick input [-1, 1] -> meters/sec
SCALE_FACTOR = 13.0

def callback(data):
    twist = Twist()

    twist.linear.x = data.axes[LEFT_Y_IDX] * SCALE_FACTOR
    twist.angular.z = data.axes[RIGHT_X_IDX] * SCALE_FACTOR * -1;
    pub.publish(twist)

def main():
    global pub
    pub = rospy.Publisher('/cmd_vel', Twist)

    rospy.Subscriber('joy', Joy, callback)

    rospy.init_node('teleop_drive')
    rospy.spin()

if __name__ == '__main__':
    main()
