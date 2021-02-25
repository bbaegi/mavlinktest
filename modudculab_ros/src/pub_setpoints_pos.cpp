#include <ros/ros.h>
#include <std_msgs/String.h> 
#include <stdio.h>
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/Vector3Stamped.h"
#include <geometry_msgs/Twist.h>

//add by ihb 2020.1.15

float cmd_x(0),cmd_y(0),cmd_z(0);

void chatterCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
   ROS_INFO("Receive l.x: %f", msg->linear.x);
   ROS_INFO("Receive l.y: %f", msg->linear.y);
   ROS_INFO("Receive l.z: %f", msg->linear.z);
   cmd_x = msg->linear.x;
   cmd_y = msg->linear.y;
   cmd_z = msg->linear.z;
   //ROS_INFO("Receive a.x: %f", msg->angular.x);
   //ROS_INFO("Receive a.y: %f", msg->angular.y);
   //ROS_INFO("Receive a.z: %f", msg->angular.z);

}
//


int main(int argc, char **argv)
{
   ros::init(argc, argv, "pub_setpoints");
   ros::NodeHandle n;

   ros::Publisher chatter_pub = n.advertise<geometry_msgs::PoseStamped>("/mavros/setpoint_position/local",100);
   

   //add by ihb 2020.01.15.
   ros::Subscriber sub = n.subscribe("cmd_drone", 100, chatterCallback);
   //

   ros::Rate loop_rate(100);
   ros::spinOnce();

   geometry_msgs::PoseStamped msg;
   geometry_msgs::Twist cmd;
   int count = 1;
	
		//PositionReciever qp;:
		//Body some_object;
		//qp.connect_to_server();

	
   while(ros::ok()){
	   //some_object = qp.getStatus();
		// some_object.print();
		//printf("%f\n",some_object.position_x);

       msg.header.stamp = ros::Time::now();
       msg.header.seq=count;
       msg.header.frame_id = 1;
       msg.pose.position.x = cmd_x;//0.0;//0.001*some_object.position_x;
       msg.pose.position.y = cmd_y;//0.0;//0.001*some_object.position_y;
       msg.pose.position.z = cmd_z;//1.0;//0.001*some_object.position_z;
       msg.pose.orientation.x = 0;
       msg.pose.orientation.y = 0;
       msg.pose.orientation.z = 0;
       msg.pose.orientation.w = 1;

       chatter_pub.publish(msg);
       ros::spinOnce();
       count++;
       loop_rate.sleep();
   }
   
      
   return 0;
}
