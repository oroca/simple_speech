///-----------------------------------------------------------------------------
/// @FileName simple_speech
/// @Date 2014.08.11 / 2013.01.27
/// @author Yoonseok Pyo (passionvirus@gmail.com)
///-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include <ros/ros.h>
#include <stdlib.h>
#include <signal.h> 
#include <string.h>
#include <stdio.h>
#include <simple_speech/script.h>

//------------------------------------------------------------------------------
bool speech(simple_speech::script::Request  &req,
            simple_speech::script::Response &res)
{
  char cmd[30];
  char say[30];
  char tts[200];
  int  ret;

  strcpy(cmd,"pico2wave --wave ~/say.wav ");
  strcpy(say,"aplay ~/say.wav");

  snprintf(tts, 200, "%s\"%s\"", cmd, req.script.c_str());

  ret = system(tts);  // make the wav file

  if (ret == -1 || ret == 127) { // fork failed and shell error
    res.result = 0;
    return false;
  }

  ret = system(say);  // play the wav file

  if (ret == -1 || ret == 127) { // fork failed and shell error
    res.result = 0;
    return false;
  }

  res.result = 1;
  return true;
}

//------------------------------------------------------------------------------
int main(int argc, char **argv)
{
  //--------------------------------------------------------------------------
  ros::init(argc, argv, "simple_speech");
  ros::NodeHandle nh;
  ros::ServiceServer service  = nh.advertiseService("simple_speech", speech);

  //--------------------------------------------------------------------------
  ros::Rate loop_rate(10); // 10Hz frequency (0.1 sec)    
  while (ros::ok()) {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}

//------------------------------------------------------------------------------
