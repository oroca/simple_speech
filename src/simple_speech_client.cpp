#include <ros/ros.h>
#include <simple_speech/script.h>

int main(int argc, char **argv)
{
  //--------------------------------------------------------------------------
  ros::init(argc, argv, "simple_speech_client");
  ros::NodeHandle nh;
  simple_speech::script srv;
  ros::ServiceClient client = nh.serviceClient<simple_speech::script>("simple_speech");

  srv.request.script = "Hello, OROCA family.";

  if (client.call(srv))
  {
    ROS_INFO("Script: %s", srv.request.script.c_str());
  }
  else
  {
    ROS_ERROR("Failed to service call of simple_speech.");
    return 1;
  }

  return 0;
}