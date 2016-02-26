#include "camera_sim.h"


CameraSimNode::CameraSimNode(int argc, char **argv, int rate){
	ros::Rate loop_rate(rate);
	CameraSimNode::ImageConverter();
	/* These are left over from when we just republished the camera feed
	 *
	subscriber = n.subscribe("/uwsim/camera1", 1000, &CameraSimNode::cameraCallBack, this);
	publisher = n.advertise<sensor_msgs::Image>("qubo/camera", 1000);
	*/

};


CameraSimNode::~CameraSimNode(){};

void CameraSimNode::update(){
	ros::spinOnce();
}

void CameraSimNode::publish(){
	//this doesn't need to be called, this node publishes everytime it subscribes
	//publisher.publish(msg);
}

void CameraSimNode::cameraCallBack(const sensor_msgs::Image sim_msg){
	msg.header = sim_msg.header;
	msg.height = sim_msg.height;
	msg.width = sim_msg.width;
	msg.encoding = sim_msg.encoding;
	msg.is_bigendian = sim_msg.is_bigendian;
	msg.step = sim_msg.step;
	msg.data = sim_msg.data;
}

CameraSimNode::ImageConverter::ImageConverter() : image_tran(n){
	image_sub = image_tran.subscribe("/uwsim/camera1", 1000, &CameraSimNode::ImageConverter::imageCallBack, this);
	image_pub = image_tran.advertise("qubo/cv_camera", 1000);
}

CameraSimNode::ImageConverter::~ImageConverter(){};

void CameraSimNode::ImageConverter::imageCallBack(const sensor_msgs::ImageConstPtr& msg){

	cv_bridge::CvImagePtr cv_ptr;
	try{
		//this may or may not be how we encode the camera data
		cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
	}catch(cv_bridge::Exception& e){
		ROS_ERROR("Image converting broke: %s", e.what());
		return;
	}
	image_pub.publish(cv_ptr->toImageMsg());
}