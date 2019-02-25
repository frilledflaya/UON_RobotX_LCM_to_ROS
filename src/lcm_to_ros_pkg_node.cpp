// %Tag(FULLTEXT)%
#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Imu.h>

#include <lcm/lcm-cpp.hpp>

#include <lcm_types.hpp>

class App{
	public:
	  App(ros::NodeHandle node_);
	  ~App();
	  int handle();

	private:
	  lcm::LCM lcm_;
	  ros::NodeHandle node_;
	  
	  ros::Publisher  drive_left_pub_;
	  ros::Publisher  drive_right_pub_;
	  void drive_cb(const lcm::ReceiveBuffer* rbuf,
		   const std::string& chan, 
		   const STM::control_msg_t* msg);
};

App::App(ros::NodeHandle node_):
  node_(node_){

  std::cout << "Initialising Translator\n";
  if(!lcm_.good()){
	std::cerr <<"ERROR: lcm is not good()" <<std::endl;
  }

 
// %Tag(SUBSCRIBER)%
  lcm_.subscribe("STM_CONTROL_RESPONSE", &App::drive_cb, this);
// %EndTag(SUBSCRIBER)%
// %Tag(PUBLISHER)%
  drive_left_pub_  = node_.advertise<std_msgs::Float32>("left_thrust_cmd",1000);
  drive_right_pub_ = node_.advertise<std_msgs::Float32>("right_thrust_cmd",1000);
// %EndTag(PUBLISHER)%

};

App::~App() {
};

int App::handle(){
//  std::cout << "handle\n";
  return lcm_.handle();
}

// %Tag(CALLBACK)%
void App::drive_cb(const lcm::ReceiveBuffer* rbuf,
		   const std::string& chan, 
		   const STM::control_msg_t* msg){
std_msgs::Float32 left_msg, right_msg;

left_msg.data = (float)(msg->port_motor) / 1000.0f;
right_msg.data = (float)(msg->starboard_motor) / 1000.0f;

drive_left_pub_.publish(left_msg);
drive_right_pub_.publish(right_msg);

}
// %EndTag(CALLBACK)%

int main(int argc, char **argv){
// init LCM

  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  App* lcmapp = new App(n);
  
  std::cout << "lcm to ros translator ready\n";
// %Tag(SPIN)%
  while((0 == lcmapp->handle()) && (ros::ok()));
// %EndTag(SPIN)%

  return 0;
}
// %EndTag(FULLTEXT)%

