#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"
//TODO: Include the ball_chaser "DriveToTarget" header file

// ROS::Publisher motor commands;
//ros::Publisher motor_command_publisher;

// TODO: Create a handle_drive_request callback function that executes whenever a drive_bot service is requested
// This function should publish the requested linear x and angular velocities to the robot wheel joints
// After publishing the requested velocities, a message feedback should be returned with the requested wheel velocities
class SubscribeAndPublish
{
    public:
        SubscribeAndPublish()
        {
            ROS_INFO_STREAM("In Constructor");
            motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
            service = n.advertiseService("/ball_chaser/command_robot", &SubscribeAndPublish::handle_drive_request, this);
        }

        bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res)
        {
            
            geometry_msgs::Twist motor_command;

            motor_command.linear.x = req.linear_x;
            motor_command.angular.z = req.angular_z;
            motor_command_publisher.publish(motor_command);

            res.msg_feedback = "Motor Command sent - Linear X: " + std::to_string(req.linear_x) + ", Angular Z: " + std::to_string(req.angular_z);

            return true;

        }

    private:
        ros::NodeHandle n;
        ros::Publisher motor_command_publisher; 
        ros::ServiceServer service; 
};

int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    //motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function

    // TODO: Delete the loop, move the code to the inside of the callback function and make the necessary changes to publish the requested velocities instead of constant values
    
    SubscribeAndPublish SAPObject;

    // TODO: Handle ROS communication events
    ros::spin();

    return 0;
}