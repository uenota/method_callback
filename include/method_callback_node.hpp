#ifndef INCLUDED_method_callback_node_hpp_
#define INCLUDED_method_callback_node_hpp_

#include <ros/ros.h>

#include <std_msgs/String.h>

#include <base_node.hpp>

#include <dynamic_reconfigure/server.h>
#include <method_callback/MethodCallbackConfig.h>

class MCClass : BaseNode
{
private:
  ros::NodeHandle nh;
  ros::Subscriber sub;
  dynamic_reconfigure::Server<method_callback::MethodCallbackConfig> cfgServer;

private:
  void msgCallback(const std_msgs::String::ConstPtr& msg);
  void cfgCallback(method_callback::MethodCallbackConfig& cfg, uint32_t level);

public:
  MCClass(int argc, char** argv);
  void run();
};

#endif