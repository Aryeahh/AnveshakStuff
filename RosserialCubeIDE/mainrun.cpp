#include <mainrun.h>
#include <ros.h>
#include <std_msgs/Empty.h>
#include <std_msgs/String.h>

// Node:
ros::NodeHandle nh;

// Publisher:
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

// Subscriber:
void led_callback(const std_msgs::Empty &msg) {
  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
}
ros::Subscriber<std_msgs::Empty> led_sub("toggle_led", &led_callback);

// Setup node:
void setup(void) {
  nh.initNode();
  nh.advertise(chatter);
  nh.subscribe(led_sub);
}

// Loop:
char hello[] = "Hello world!";
void loop(void) {
  // Publish message:
  str_msg.data = hello;
  chatter.publish(&str_msg);

  nh.spinOnce();
  HAL_Delay(500);
}

