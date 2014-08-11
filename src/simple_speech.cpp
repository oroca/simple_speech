///-----------------------------------------------------------------------------
/// @FileName simple_speech
/// @Date 2014.08.10 / 2013.01.27
/// @author Yoonseok Pyo (passionvirus@gmail.com)
///-----------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include <ros/ros.h>
#include <stdlib.h>
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
  int  retval_tts;
  int  retval_say;

  strcpy(cmd,"pico2wave --wave ~/say.wav ");
  strcpy(say,"aplay ~/say.wav");

  snprintf(tts, 128, "%s\"%s\"", cmd, req.script.c_str());
  retval_tts = system(tts);
  retval_say = system(say);

  if(retval_tts == 127 || retval_say == 127) {        // shell invoke error
    res.result = 127;
  } else if (retval_tts ==  0 || retval_say ==  0) {  // null error
    res.result = 0;
  } else if (retval_tts == -1 || retval_say == -1) {  // error
    res.result = -1;
  } else
    res.result = 1;
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
