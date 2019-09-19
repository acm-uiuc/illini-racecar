cmake_minimum_required(VERSION 2.8.3)
project(illini-racecar)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
)

catkin_package(
    CATKIN_DEPENDS roscpp rospy
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(drive_controller_node src/drive_controller.cpp)
target_link_libraries(drive_controller_node ${catkin_LIBRARIES})
