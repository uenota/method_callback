#include <talker.hpp>

Talker::Talker(int argc, char** argv) : BaseNode(argc, argv, "talker"), rate(2)
{
  pub = nh.advertise<std_msgs::String>("chatter", 10);
  count = 0;
}

void Talker::run()
{
  std_msgs::String msg;

  std::stringstream ss;
  ss << "Hello world " << count;

  msg.data = ss.str();

  pub.publish(msg);
  ++count;

  ros::spinOnce();
  rate.sleep();
}

int main(int argc, char** argv)
{
  Talker  talker(argc, argv);

  while(ros::ok()){
    talker.run();
  }

  return 0;
}