cmake_minimum_required(VERSION 2.8.3)
project(simple_speech)
find_package(catkin REQUIRED COMPONENTS 
  roscpp 
  std_msgs
  message_generation
)

################################################
## Declare ROS messages, services and actions ##
################################################
add_service_files(
  FILES
  script.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

###################################
## catkin specific configuration ##
###################################
catkin_package(
   CATKIN_DEPENDS std_msgs message_runtime
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(simple_speech src/simple_speech.cpp)
add_dependencies(simple_speech DEPENDS simple_speech_gencpp)
target_link_libraries(simple_speech ${catkin_LIBRARIES})

add_executable(simple_speech_client src/simple_speech_client.cpp)
add_dependencies(simple_speech_client DEPENDS simple_speech_gencpp)
target_link_libraries(simple_speech_client ${catkin_LIBRARIES})

