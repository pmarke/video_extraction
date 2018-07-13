#include "extract.h"

namespace video_extraction {

Extract::Extract() {

ROS_DEBUG_STREAM("Here 1234");
std::cout << "here0" << std::endl;

ros::NodeHandle nh_private("~");
image_transport::ImageTransport it(nh_);

// Set transport hints
std::string transport;
nh_private.param<std::string>("transport", transport, "raw");
image_transport::TransportHints th("compressed");
std::cout << th.getTransport() << std::endl;

// Subscribe to image
sub_ = it.subscribe("tracks_video/image_raw",1, &Extract::image_callback, this,th);

std::cout << sub_.getTopic() << std::endl;

// Get resize parameters
nh_private.param<bool>("resize", resize_, false);
nh_private.param<int>("resize_width", resize_width_, 640);
nh_private.param<int>("resize_height", resize_height_, 480);

// Get video parameters
nh_private.param<int>("fps", fps_, 30);
nh_private.param<std::string>("fourcc", fourcc_, "XVID");
nh_private.param<std::string>("filename", filename_, "output.avi");

ROS_DEBUG_STREAM("Here 789");

std::cout << "here1" << std::endl;
}


//--------------------------------------------------------------

void Extract::image_callback(const sensor_msgs::ImageConstPtr& msg) {

// Get the image into a mat object. 
cv::Mat frame;
frame = cv_bridge::toCvCopy(msg,"bgr8")->image;

// ROS_DEBUG_STREAM("Here");
// std::cout << "here2" << std::endl;

// Get the video image width and height. If the resize option was 
// selected, the image size changes to the resize size
if(!init_) {
    if(resize_) {
        image_width_ = resize_width_;
        image_height_ = resize_height_;
    }
    else
    {
        image_width_ = frame.cols;
        image_height_ = frame.rows;
    }
    init_ = true;

    // Start up video writer
    ROS_INFO_STREAM("Writing Video");
    const char *temp = fourcc_.c_str();
    int fourcc = cv::VideoWriter::fourcc(temp[0],temp[1],temp[2],temp[3]);
    video_out_ = cv::VideoWriter(filename_, fourcc, fps_, cv::Size(image_width_,image_height_), color_ );
} 

if(resize_) {
    cv::resize(frame,frame,cv::Size(image_width_,image_height_));
}
    
video_out_.write(frame);




}






}