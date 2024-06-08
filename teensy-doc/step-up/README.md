# micro-ROS-Arduino

# Build
``` cmd
pio lib install
pio run
```
# Upload
1. PC と Teensy の接続
2. Teensy 上のボタンを一回押す
3. 以下のコマンド実行
    ``` cmd
    pio run --target upload
    ```

# Serial
``` cmd
pio device monitor -p /dev/ttyACM0 -b 115200
```

!!! Warning
    他の端末などで `micro_ros_agent` を起動している場合は、PC と Teensy が `Connect!` と `Disconnected!` を反復横飛びするので注意

# 動作確認方法
1. micro-ROS Agent を起動
2. PC と Teensy の接続

# micro-ROS Agent
``` cmd
ros2 run micro_ros_agent micro_ros_agent serial -b 115200 --dev /dev/ttyACM0 -v6
```

# 既知の問題
## `rclc_support_init()` 関数が `RCL_RET_ERROR` を返し、プログラムが動作しない
`main.cpp`
``` C++
rclc_support_init(&support, 0, NULL, &allocator);
```

`rclc > init.h > rclc_support_init()`
``` C++
/**
 * Initializes rcl and creates some support data structures.
 * Initializes clock as RCL_STEADY_TIME.
 * * <hr>
 * Attribute | Adherence
 * --------- | ---------
 * Allocaters Memory | Yes ( in RCL )
 * Thread-Safe | No
 * Users Atomics | No
 * Lock-Free | Yes
 * \param[input] support a zero-initialized rclc_support_t
 * \param[in] argc number of args of main
 * \param[in] argv array of arguments of main
 * \param[in] allocator allocator for allocating memory
 * \return `RCL_RET_OK` if RCL was initialized successfully
 * \return `RCL_RET_INVALID_ARGUMENT` if any null pointer as argument
 * \return `RCL_RET_ERROR` in case of failure
 */
rcl_ret_t rclc_support_init(rclc_support_t * support, int argc, char const * const * argv, rcl_allocator_t * allocator);
```

`rclc_support_init()` の中身の処理が見つからない。

