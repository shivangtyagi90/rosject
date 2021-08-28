#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
int main(int argc, char** argv){
    ros::init(argc, argv, "move_turtlebot");
    MoveBaseClient ac("move_base", true);
    while(!ac.waitForServer(ros::Duration(5.0))){
        ROS_INFO("wating for thhe move_base action server to come up");

    }
    move_base_msgs::MoveBaseGoal goal;
    goal.target_pose.header.frame_id = "map";
    goal.target_pose.header.stamp = ros::Time::now();

float goals[4][3] = {{10.0,3.0,50.0},{-10.0,3.0,50.0},{-10.0,-3.0,50.0},{10.0,-3.0,50.0}};
for (int i = 0; i < 4; i++)
{

    goal.target_pose.pose.position.x=goals[i][0];
    goal.target_pose.pose.position.y=goals[i][1];
    goal.target_pose.pose.orientation.w=goals[i][2];
    ROS_INFO("Sending goal");
    ac.sendGoal(goal);
    ac.waitForResult();
    ros::Duration(1.0).sleep();
    if (i==3)
    {
        i=-3;
    }
    
}

if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, reched drop off zone");
    

else
    ROS_INFO("The base failed to move forward");
    return 0;
}