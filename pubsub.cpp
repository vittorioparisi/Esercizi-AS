#include <memory>
#include <functional>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#define CODAMAX 10

class PubSub : public rclcpp::Node{
    public :
    PubSub()
    : Node("PubSubNode"){
        publisher_ = this->create_publisher<std_msgs::msg::Float64>("/test_out", rclcpp::QoS(CODAMAX));
        subscriber_=this->create_subscription<std_msgs::msg::Float64>("/test",rclcpp::QoS(CODAMAX), 
            std::bind(&PubSub::topic_callback, this, std::placeholders::_1))
;    }

    private : 
    void topic_callback (const std_msgs::msg::Float64::SharedPtr msg)
    {
       if(msg){
            auto message = std_msgs::msg::Float64();
            message.data=1.0;

            RCLCPP_INFO (this->get_logger(), "Publishing : '%f'",message.data);
            publisher_->publish(message);
       }
    }

    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr publisher_;
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscriber_;};

int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<PubSub>());
    rclcpp::shutdown();
    return 0;
}