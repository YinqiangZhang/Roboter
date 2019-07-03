#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <turtlesim/Pose.h>

// after build, you can find the a binary file in the folder "ros_ws/devel/lib/basic_properties/"
using namespace std;

string turtle_name;

void poseCallback(const turtlesim::PoseConstPtr& msg){

  // declare a transformbroadcaster
  static tf::TransformBroadcaster br;
  // declare a transform class
  tf::Transform transform;
  // set the origin positon of the transform
  transform.setOrigin(tf::Vector3(msg->x, msg->y, 0));
  // set a quaternion
  tf::Quaternion q;
  q.setRPY(0, 0, msg->theta);
  // transmit the quternion into the transform class
  // to set the parameter of its rotation
  transform.setRotation(q);
  // send the transform:
  // there are four parameters: 1. the transform itself
  // 2. the time stamp 3. the parent frame 4. the child frame
  br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", turtle_name));

}

// argc: the number of the system initial parameters, argv: the array, where the system initial parameters are.
int main(int argc, char** argv){

  // init ros
  ros::init(argc, argv, "my_tf_broadcaster");

  if (argc != 2){ROS_ERROR("need turtle name as argument"); return -1;};
  turtle_name = argv[1];

  ros::NodeHandle node;

  ros::Subscriber sub = node.subscribe(turtle_name+"/pose", 10, &poseCallback);

  ros::spin();
  return 0;

}
