#ifndef INCLUDED_talker_hpp_
#define INCLUDED_talker_hpp_

#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>

#include <base_node.hpp>

class Talker : BaseNode
{
private:
  ros::NodeHandle nh;
  ros::Publisher pub;
  ros::Rate rate;
  int count;

public:
  Talker(int argc, char** argv);
  void run();
};

#endif