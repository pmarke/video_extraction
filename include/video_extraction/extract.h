#pragma once
#include <ros/ros.h>
#include <ros/console.h>
#include <image_transport/image_transport.h>
#include <string>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <iostream>



namespace video_extraction {

class Extract {

public: 

    Extract();
    image_transport::Subscriber sub_;




private:

    // ROS communication
    ros::NodeHandle nh_;
    

    // Resize options
    bool resize_;
    int resize_width_;
    int resize_height_;

    // Opencv video writer
    std::string fourcc_;
    cv::VideoWriter video_out_;
    int fps_;
    int image_width_;
    int image_height_;
    std::string filename_;
    bool init_ = false;
    bool color_ = true;

    // Image callback. This will save the ros bag image as a video. 
    void image_callback(const sensor_msgs::ImageConstPtr& msg);






};


}