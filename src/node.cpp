#include "extract.h"

int main(int argc, char** argv) {

    ros::init(argc, argv, "extract_video_node");

    video_extraction::Extract extract;
    std::cout << extract.sub_.getTopic() << std::endl;

    ros::spin();

    return 0;


}