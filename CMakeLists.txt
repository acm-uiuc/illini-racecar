cmake_minimum_required(VERSION 2.8.3)
project(illini_racecar)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  message_generation
)

add_message_files( FILES AckermannCmd.msg )

generate_messages()

catkin_package(
    CATKIN_DEPENDS roscpp rospy message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_library(drive_controller src/drive_controller.cpp)
target_link_libraries(drive_controller ${catkin_LIBRARIES})

add_executable(drive_controller_node src/drive_controller_node.cpp)
target_link_libraries(drive_controller_node drive_controller ${catkin_LIBRARIES})
