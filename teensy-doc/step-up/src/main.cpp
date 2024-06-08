#include "Arduino.h"
#include <micro_ros_arduino.h>

#include <stdio.h>
#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>

#define LED 13  // LEDのピン

rclc_support_t support;
rcl_allocator_t allocator;
rcl_node_t node;

#define RCCHECK(fn, index) { rcl_ret_t tmp_rc = fn; if((tmp_rc != RCL_RET_OK)){error_loop(index, tmp_rc);}}

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
        delay(100);
    }

    printf("[MAIN][Error Loop] Starting Error Loop ...\r\n");
}

void setup()
{
    printf("[MAIN][Setup] Starting Setup ...\r\n");

    printf("[MAIN][Setup] Set PIN Mode ... \r\n");
    pinMode(LED, OUTPUT);
    printf("[MAIN]{Setup] Set micro-ROS Transports ... \r\n");
    set_microros_transports();
    printf("[MAIN][Setup] Get Default Allocator ...\r\n");
    allocator = rcl_get_default_allocator();

    printf("[MAIN][Setup] Create Init Options ...\r\n");
    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator), 44);

    printf("[MAIN][Setup] Create Node ...\r\n");
    RCCHECK(rclc_node_init_default(&node, "micro_ros_arduino_node", "", &support), 47);

    printf("[MaAIN][Setup] The End of Setup ..\r\n");
}

void loop()
{
    digitalWrite(LED, HIGH);
    delay(1000);
    digitalWrite(LED, LOW);
    printf("Hello, World!\r\n");
    delay(100);
}


