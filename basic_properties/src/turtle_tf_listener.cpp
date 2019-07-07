#include <ros/ros.h>

// to use transform listener, include this header file
#include <tf/transform_listener.h>

#include <geometry_msgs/Twist.h>
#include <turtlesim/Spawn.h>

int main(int argc, char** argv){

  ros::init(argc, argv, "tf_listener");
  ros::NodeHandle node;

  // spawn a second turtle in the control world
  ros::service::waitForService("spawn");
  ros::ServiceClient add_turtle = node.serviceClient<turtlesim::Spawn>("spawn");
  // add a turtle
  turtlesim::Spawn srv;
  add_turtle.call(srv);
  // define a publisher to publish the velocity message
  ros::Publisher turtle_vel = node.advertise<geometry_msgs::Twist>("turtle2/cmd_vel", 10);

  tf::TransformListener listener;

  ros::Rate rate(10.0);
  while(node.ok()){
    // a instance that save the transform between two frames
    tf::StampedTransform transform;
    try{
      // to find the lastest transform form turtle1 to turtle2
      //listener.lookupTransform("/turtle2", "/turtle1", ros::Time(0), transform);

      // the turtle is tracking a second target.
      //listener.lookupTransform("/turtle2", "/carrot1", ros::Time(0), transform);
      // find specific transform
      ros::Time now = ros::Time::now();
      ros::Time past = ros::Time::now() - ros::Duration(5.0);
      // wait for the specific frame transform (in this statement is now), maximal 3 second.
      listener.waitForTransform("/turtle2", now,  "/turtle1", past, "/world", ros::Duration(3.0));
      listener.lookupTransform("/turtle2",  now,  "/turtle1", past, "/world", transform);
    }

    catch(tf::TransformException &ex){
      ROS_ERROR("%s", ex.what());
      ros::Duration(1.0).sleep();
      continue;
    }

    // to declare the variable to save the velocity messages
    geometry_msgs::Twist vel_msg;

    vel_msg.angular.z = 2.0 * atan2(transform.getOrigin().y(), transform.getOrigin().x());
    vel_msg.linear.x = 0.5 * sqrt(pow(transform.getOrigin().x(), 2) + pow(transform.getOrigin().y(), 2));

    turtle_vel.publish(vel_msg);
    rate.sleep();
  }
  return 0;
};
