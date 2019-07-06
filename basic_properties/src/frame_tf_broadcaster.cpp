#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){

  ros::init(argc, argv, "carrot_frame");
  ros::NodeHandle node;

  tf::TransformBroadcaster br;
  tf::Transform transform;

  ros::Rate rate(10.0);

  while(node.ok()){

    // the constant transform between turtle1 and carrot
    //transform.setOrigin(tf::Vector3(0, 2, 0));
    // dynamic transform
    transform.setOrigin(tf::Vector3(2.0*sin(ros::Time::now().toSec()), 4.0*cos(ros::Time::now().toSec()), 0.0));
    transform.setRotation(tf::Quaternion(0, 0, 0, 1));

    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "turtle1", "carrot1"));

    rate.sleep();
  }

  return 0;
}
