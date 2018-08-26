#include <method_callback_node.hpp>

MCClass::MCClass(int argc, char** argv) : BaseNode(argc, argv, "method_callback")
{
  auto msgcb = boost::bind(&MCClass::msgCallback, this, _1);
  sub = nh.subscribe<std_msgs::String>("chatter", 10, msgcb);

  dynamic_reconfigure::Server<method_callback::MethodCallbackConfig>::CallbackType cfgcb;
  cfgcb = boost::bind(&MCClass::cfgCallback, this, _1, _2);
  cfgServer.setCallback(cfgcb);
}

void MCClass::msgCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("Message: %s", msg->data.c_str());
}

void MCClass::cfgCallback(method_callback::MethodCallbackConfig& cfg, uint32_t level)
{
  ROS_INFO("Reconfigure Request: %d, %f, %s", cfg.param1, cfg.param2, cfg.param3?"True":"False");
}

void MCClass::run()
{
  ros::spin();
}

int main(int argc, char** argv)
{
  MCClass listener(argc, argv);
  listener.run();

  return 0;
}