#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
using namespace sensor_msgs;
#include "geometry_msgs/Vector3.h"
using namespace geometry_msgs;
#include "model31_func.h"
#include "model31_func_terminate.h"
#include <ros/console.h>
#include "visualization_msgs/Marker.h"
using namespace visualization_msgs;

// Include Files
#include <stdint.h>
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>
#include <stdint.h>

#include <sstream>
#include <mutex> // std::mutex
std::mutex mtx;  // mutex for critical section

LaserScan msg_new;
ros::Publisher *pubPntr;

static float rngs[16];
static float rngs_tmp[16]={0};
static bool initDone = true;
ros::Publisher *rl_pub_ptr = NULL;
ros::Publisher *rl_pub_mrkr_ptr = NULL;
ros::Publisher *rl_proc_ls_ptr = NULL;
Marker *V_ptr;
LaserScan *rl_ls_ptr;
static uint32_t nsec = 0;
// static int ord[] = {8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7};
#define MIN_DIST 0.08f
// #define PRINT2CONSL

void infere_ls();
void infere_ls_timer(const ros::TimerEvent &e);
void ls_callback(const LaserScan::ConstPtr &msg);

// Function Definitions
//
// Arguments    : float result[16]
// Return Type  : void
//
static void argInit_1x16_real32_T(float result[16])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 16; idx1++)
  {
    // Set the value of the array element.
    // Change this value to the value that the application requires.
    result[idx1] = (float)result[idx1]; // argInit_real32_T();
  }
}

//
// Arguments    : void
// Return Type  : float
//
static float argInit_real32_T()
{
  return 0.0F;
}

//
// Arguments    : void
// Return Type  : void
//
static float main_model31_func(float const *fv, float *out)
{
  // float out[3];
  // Initialize function 'model31_func' input arguments.
  // Initialize function input argument 'in'.
  // Call the entry-point 'model31_func'.
  // argInit_1x16_real32_T(fv);
  model31_func(fv, out);
}

void ls_callback(const LaserScan::ConstPtr &msg)
{
#ifdef PRINT2CONSL
  ROS_INFO("Got Laser Scan");
#endif
  float r_tmp;
  if(mtx.try_lock()){
    for (int i = 0; i < 16; i++)
    {
      r_tmp = msg->ranges[i];
      rngs_tmp[i] = r_tmp>0.0001f?r_tmp:rngs_tmp[i];  // check LS communication validity
      rngs[i] = rngs_tmp[i] > MIN_DIST ? rngs_tmp[i] : 3.999f;  // check LS physical validity
    }
    mtx.unlock();
  }
  return;
}

void class2cmd(float *clss, float *cmd)
{
  // def category_to_velocity(self, action :int):

  //   # action must be max total_bins
  //   if action==0:
  //       x = self.x/2
  //       y = -self.y
  //   elif action==1:
  //       x = self.x
  //       y = 0
  //   else:
  //       x = self.x/2
  //       y = self.y

  //   return x, y

  cmd[2] = 0.0f;
  if (clss[0] > clss[1] && clss[0] > clss[2])
  {
    // action == 0
    cmd[0] = 0.5f;
    cmd[1] = -0.5f;
  }
  else if (clss[1] > clss[0] && clss[1] > clss[2])
  {
    // action == 1
    cmd[0] = 1.0f;
    cmd[1] = 0.0f;
  }
  else
  {
    cmd[0] = 0.5f;
    cmd[1] = 0.5f;
  }
}

void infere_ls()
{
  float out_[3] = {0};
  float cmd[3];
  Vector3 V;
#ifdef PRINT2CONSL
  ROS_INFO("*  Infering");
#endif
  if (initDone)
  {
    mtx.lock();
    main_model31_func(rngs, out_);
    mtx.unlock();
#ifdef PRINT2CONSL
    ROS_INFO("modle out = %f, %f, %f\n", out_[0], out_[1], out_[2]);
#endif

    // 
  }

  class2cmd(out_, cmd);
  V.x = cmd[0];
  V.y = cmd[1];
  
  V_ptr->points[1].x = cmd[0];
  V_ptr->points[1].y = cmd[1];
  V_ptr->points[1].z = 0.0f;
  // Use point at 'z' coordinate for rotation command:
  if (cmd[1]>0.0f){
    V.z = 1.0f;
  }else if (cmd[1]<0.0f)
  {
    V.z = -1.0f;
  }else{
    V.z = 0.0f;
  }
  rl_pub_ptr->publish(V);  // publish raw classifier output

  
  rl_pub_mrkr_ptr->publish(*V_ptr);  // publish command converted from raw
  for (int i=0; i<16; i++){
    rl_ls_ptr->ranges[i]=rngs[i];
  }
  rl_proc_ls_ptr->publish(*rl_ls_ptr);
#ifdef PRINT2CONSL
  ROS_INFO("*  Infering and publishing done");
#endif
  return;
}

void infere_ls_timer(const ros::TimerEvent &e)
{
  infere_ls();
  return;
}
/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "rl_explore");
#ifdef PRINT2CONSL
  ROS_INFO("Node initialized");
#endif
  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;

  /**
   * The advertise() function is how you tell ROS that you want to
   * publish on a given topic name. This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing. After this advertise() call is made, the master
   * node will notify anyone who is trying to subscribe to this topic name,
   * and they will in turn negotiate a peer-to-peer connection with this
   * node.  advertise() returns a Publisher object which allows you to
   * publish messages on that topic through a call to publish().  Once
   * all copies of the returned Publisher object are destroyed, the topic
   * will be automatically unadvertised.
   *
   * The second parameter to advertise() is the size of the message queue
   * used for publishing messages.  If messages are published more quickly
   * than we can send them, the number here specifies how many messages to
   * buffer up before throwing some away.
   */

#ifdef PRINT2CONSL
  ROS_INFO("Pre subscribe");
#endif
  Marker V;
  V_ptr = &V;
  Point p0, p1;
  V.type = Marker::ARROW;
  V.action = Marker::MODIFY;
  V.header.frame_id = "mr18_frame";
  V.scale.x = 0.18;
  V.scale.y = 0.36;
  V.scale.z = 0;
  V.color.b = 0.7;
  V.color.a = 0.9;
  V.color.g = 0.3;
  V.color.r = 0.8;
  p0.x = 0;
  p1.x = 1;
  p0.y = 0;
  p1.y = 0;
  p0.z = 0;
  p1.z = 0;
  V.points.push_back(p0);
  V.points.push_back(p1);

  LaserScan rl_ls;
  rl_ls_ptr = &rl_ls;
  rl_ls.header.frame_id  = "mr18_frame";
  rl_ls.angle_min = 0;
  rl_ls.angle_max = 5.8905;
  rl_ls.angle_increment = 0.392699092627;
  rl_ls.range_min = 0.0500000007451;
  rl_ls.range_max = 4.0;
  for (int i=0; i<16; i++){
    rl_ls.ranges.push_back(0.0f);
  }
  ros::Publisher rl_pub = n.advertise<Vector3>("/rl_out", 10);
  rl_pub_ptr = &rl_pub;
  ros::Duration(1.0).sleep();

  ros::Publisher rl_pub_mrkr = n.advertise<Marker>("/rl_out_mrkr", 10);
  rl_pub_mrkr_ptr = &rl_pub_mrkr;
  ros::Publisher rl_proc_ls = n.advertise<LaserScan>("/rl_proc_ls", 10);
  rl_proc_ls_ptr = &rl_proc_ls;

  ros::Subscriber sub = n.subscribe("/fa_node/mr18", 10, ls_callback);
  ros::Timer timer = n.createTimer(ros::Duration(0.3), infere_ls_timer);

  ros::spin();

  return 0;
}