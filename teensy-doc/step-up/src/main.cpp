#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>

#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
#error This example is only avaliable for Arduino framework with serial transport.
#endif

#define LED 13

rcl_publisher_t publisher;
std_msgs__msg__Int32 msg;

rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;
rcl_timer_t timer;

#define RCCHECK(fn, index) { rcl_ret_t tmp_rc = fn; if((tmp_rc != RCL_RET_OK)){error_loop(index, tmp_rc);}}
#define RCSOFTCHECK(fn) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){}}

// Error handle loop
void error_loop(unsigned short int index, rcl_ret_t tmp_rc)
{
    printf("[MAIN][Error Loop] Starting Error Loop ...\r\n");
    printf("\r\n[MAIN][Error Loop] ----- Debug -----\r\n");
    printf("[MAIN][Error Loop] Unexcepted Error Occurred ! x_x ! : Index(%d), %s\r\n", index, tmp_rc == RCL_RET_INVALID_ARGUMENT ? "RCL_RET_INVALID_ARGUMENT ( 引数にヌルポインタが存在します )" : "RCL_RET_ERROR ( rclc_support_init_with_options の失敗 )");
    printf("[MAIN][Error Loop][types.h] //! Unspecified error return code.\r\n");
    printf("[MAIN][Error Loop][types.h] #define RCL_RET_ERROR RMW_RET_ERROR\r\n");
    printf("[MAIN][Error Loop][rmw/ret_types.h] //!\r\n");
    printf("[MAIN][Error Loop][rmw/ret_types.h] #define RMW_RET_ERROR 1\r\n");
    printf("[MAIN][Error Loop] ----- ----- -----\r\n\r\n");

    while(1)
    {
        digitalWrite(LED, !digitalRead(LED));
        delay(500);
    }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
    RCLC_UNUSED(last_call_time);
    if (timer != NULL)
    {
        RCSOFTCHECK(rcl_publish(&publisher, &msg, NULL));
        msg.data++;
    }
}

void setup()
{
    // Configure PIN Mode
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    // Configure serial transport
    Serial.begin(115200);
    set_microros_serial_transports(Serial);

    delay(2000);

    allocator = rcl_get_default_allocator();

    //create init_options
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator), 62);

    // create node
    RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support), 65);

    // create publisher
    RCCHECK(rclc_publisher_init_default(
        &publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "micro_ros_platformio_node_publisher"), 68);

    // create timer,
    const unsigned int timer_timeout = 1000;
    RCCHECK(rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback), 80);

    // create executor
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator), 83);
    RCCHECK(rclc_executor_add_timer(&executor, &timer), 84);

    msg.data = 0;
}

void loop()
{
    delay(100);
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)));
}


