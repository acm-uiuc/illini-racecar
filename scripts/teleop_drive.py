import rospy

from sensor_msgs.msg import Joy
from geometry_msgs.msg import Twist


"""
ROS node that listens for sensor_msgs/Joy and converts them into geometry_msgs/Twist for arcade drive.
"""

LEFT_Y_IDX = 0
RIGHT_X_IDX = 1

def callback(data):
    twist = Twist()

    # TODO: figure out actual indices from joystick data + conversion equation
    twist.linear.x = data.axes[LEFT_Y_IDX]
    twist.angular.z = data.axes[RIGHT_Y_IDX]
    pub.publish(twist)

def main():
    global pub
    pub = rospy.Publisher('illini-racecar/cmd_vel', Twist)

    rospy.Subscriber('joy', Joy, callback)

    rospy.init_node('teleop_drive')
    rospy.spin()

if __name__ == '__main__':
    main()
