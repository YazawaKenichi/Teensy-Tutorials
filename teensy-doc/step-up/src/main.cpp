#include <Arduino.h>
#include <micro_ros_platformio.h>

#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>

#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>

/*
#if !defined(MICRO_ROS_TRANSPORT_ARDUINO_SERIAL)
#error This example is only avaliable for Arduino framework with serial transport.
#endif
*/

#define LED 13

rcl_allocator_t allocator;
rclc_support_t support;
rcl_node_t node;
rclc_executor_t executor;

rcl_publisher_t num_publisher;
std_msgs__msg__Int32 msg_num;

rcl_publisher_t string_publisher;
std_msgs__msg__String msg_string;

rcl_timer_t timer;

#define RCCHECK(fn, index) { rcl_ret_t tmp_rc = fn; if((tmp_rc != RCL_RET_OK)){error_loop(index, tmp_rc);}}
#define RCSOFTCHECK(fn, index) { rcl_ret_t temp_rc = fn; if((temp_rc != RCL_RET_OK)){error_loop_soft(index, temp_rc);}}

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
        printf("[MAIN][Error Loop] In Setup Error Loop ...\r\n");
        digitalWrite(LED, !digitalRead(LED));
        delay(500);
    }
}

void error_loop_soft(unsigned short int index, rcl_ret_t tmp_rc)
{
    printf("[MAIN][Error Loop] Starting Error Loop ...\r\n");

    /*
    printf("\r\n[MAIN][Error Loop] ----- Debug -----\r\n");
    printf("[MAIN][Error Loop] Unexcepted Error Occurred ! x_x ! : Index(%d), %s\r\n", index, tmp_rc == RCL_RET_INVALID_ARGUMENT ? "RCL_RET_INVALID_ARGUMENT ( 引数にヌルポインタが存在します )" : "RCL_RET_ERROR ( rclc_support_init_with_options の失敗 )");
    printf("[MAIN][Error Loop][types.h] //! Unspecified error return code.\r\n");
    printf("[MAIN][Error Loop][types.h] #define RCL_RET_ERROR RMW_RET_ERROR\r\n");
    printf("[MAIN][Error Loop][rmw/ret_types.h] //!\r\n");
    printf("[MAIN][Error Loop][rmw/ret_types.h] #define RMW_RET_ERROR 1\r\n");
    printf("[MAIN][Error Loop] ----- ----- -----\r\n\r\n");
    */

    while(1)
    {
        printf("[MAIN][Error Loop] In Loop Error Loop ...\r\n");
        digitalWrite(LED, !digitalRead(LED));
        delay(500);
    }
}

void timer_callback(rcl_timer_t * timer, int64_t last_call_time)
{
    RCLC_UNUSED(last_call_time);
    if (timer != NULL)
    {
        RCSOFTCHECK(rcl_publish(&num_publisher, &msg_num, NULL), 78);
        msg_num.data++;
    }
}

void setup()
{
    printf("[MAIN][Setup] Starting Setup ...\r\n");

    printf("[MAIN][Setup] Configure PIN Mode ...\r\n");
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);

    printf("[MAIN][Setup] Configure Serial Transport ...\r\n");
    Serial.begin(115200);
    set_microros_serial_transports(Serial);

    delay(2000);

    printf("[MAIN][Setup] Get Default Allocator ...\r\n");
    allocator = rcl_get_default_allocator();

    printf("[MAIN][Setup] Configure Initialize Options ...\r\n");
    rcl_init_options_t init_options = rcl_get_zero_initialized_init_options();
    RCCHECK(rcl_init_options_init(&init_options, allocator), 102);

    printf("[MAIN][Setup] Set ROS_DOMAIN_ID ...\r\n");
    //! ROS_DOMAIN_ID
    RCCHECK(rcl_init_options_set_domain_id(&init_options, 65), 106);

    printf("[MAIN][Setup] Create Support Init ...\r\n");
    //! Replacement : RCCHECK(rclc_support_init(&support, 0, NULL, &allocator), 62);
    RCCHECK(rclc_support_init_with_options(&support, 0, NULL, &init_options, &allocator), 95);

    printf("[MAIN][Setup] Create Node ...\r\n");
    RCCHECK(rclc_node_init_default(&node, "micro_ros_platformio_node", "", &support), 81);

    printf("[MAIN][Setup] Create Publisher ...\r\n");
    RCCHECK(rclc_publisher_init_default(
        &num_publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Int32),
        "Number_Publisher"), 68);
    RCCHECK(rclc_publisher_init_default(
        &string_publisher,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String),
        "String_Publisher"), 68);

    printf("[MAIN][Setup] Create Timer ...\r\n");
    const unsigned int timer_timeout = 1000;
    /*
    RCCHECK(rclc_timer_init_default(
        &timer,
        &support,
        RCL_MS_TO_NS(timer_timeout),
        timer_callback), 80);
    */

    printf("[MAIN][Setup] Create Executor ...\r\n");
    RCCHECK(rclc_executor_init(&executor, &support.context, 1, &allocator), 83);
    RCCHECK(rclc_executor_add_timer(&executor, &timer), 84);

    printf("[MAIN][Setup] Set Parameters ...\r\n");
    msg_num.data = 0;

    printf("[MAIN][Setup] The End of Setup ...\r\n");
}

void loop()
{
    printf("[MAIN][Loop] Top of Loop ...\r\n");

    /*
    delay(100);
    printf("[MAIN][Loop] Executor Spin ...\r\n");
    RCSOFTCHECK(rclc_executor_spin_some(&executor, RCL_MS_TO_NS(100)), 145);
    */

    String s = "Hello, World!\r\n";
    char strBuf[64]; s.toCharArray(strBuf, 13);
    msg_string.data.size = s.length();
    msg_string.data.data = strBuf;
    RCSOFTCHECK(rcl_publish(&string_publisher, &msg_string, NULL), 166);;
    delay(100);

    printf("[MAIN][Loop] Last of Loop ...\r\n");
}

