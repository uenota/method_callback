#ifndef INCLUDED_base_node_hpp_
#define INCLUDED_base_node_hpp_

#include <ros/ros.h>

class BaseNode
{
  protected:
    BaseNode(int argc, char** argv, const char* node_name)
    {
      ros::init(argc, argv, node_name);
    }
};

#endif