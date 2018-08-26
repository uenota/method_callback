cmake_minimum_required(VERSION 2.8.3)
project(method_callback)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  dynamic_reconfigure
)

generate_dynamic_reconfigure_options(
  cfg/MethodCallback.cfg
)

catkin_package(
  INCLUDE_DIRS include
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(talker src/talker.cpp)
target_link_libraries(talker
  ${catkin_LIBRARIES}
)

add_executable(method_callback_node src/method_callback_node.cpp)
add_dependencies(method_callback_node ${PROJECT_NAME}_gencfg)
target_link_libraries(method_callback_node
  ${catkin_LIBRARIES}
)