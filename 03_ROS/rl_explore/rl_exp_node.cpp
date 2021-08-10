#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
using namespace sensor_msgs;
#include "geometry_msgs/Vector3.h"
using namespace geometry_msgs;
#include "model31_func.h"
#include "model31_func_terminate.h"
#include <ros/console.h>

// Include Files
#include <stdint.h>
#include "rtwtypes.h"
#include <cstddef>
#include <cstdlib>
#include <stdint.h>

#include <sstream>
#include <mutex>          // std::mutex
std::mutex mtx;           // mutex for critical section

LaserScan msg_new;
ros::Publisher *pubPntr;

static float rngs[16];
static bool initDone = false;
ros::Publisher* rl_pub_ptr=NULL;

#define MIN_DIST 0.08f

// Function Definitions
//
// Arguments    : float result[16]
// Return Type  : void
//
static void argInit_1x16_real32_T(float result[16])
{
  // Loop over the array to initialize each element.
  for (int idx1{0}; idx1 < 16; idx1++) {
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
    ROS_INFO("Got Laser Scan");

    if (mtx.try_lock()){
      for (int i=0; i<16; i++){
        rngs[i] = msg->ranges[i]<MIN_DIST?msg->ranges[i]:5.0f;
      }
      mtx.unlock();
      initDone = true;
    }
    return;
}

void infere_ls(const ros::TimerEvent& e)
{
    float out_[3]={0};
    Vector3 V;
    ROS_INFO("*  Infering");

    if (initDone){
      mtx.lock();
      main_model31_func(rngs, out_);
      mtx.unlock();
    }
    
    V.x=out_[0];
    V.y=out_[1];
    V.z=out_[2];

    rl_pub_ptr->publish(V);

    ROS_INFO("*  Infering and publishing done");

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
  ROS_INFO("Node initialized");
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
  ROS_INFO("Pre subscribe");

  ros::Subscriber sub = n.subscribe("/fa_node/mr18", 10, ls_callback);
   
  ros::Publisher rl_pub = n.advertise<Vector3>("/rl_out", 10);
  rl_pub_ptr = &rl_pub;

  ros::Timer timer = n.createTimer(ros::Duration(0.3), infere_ls);


  ros::spin();


  return 0;
}