# micro-ROS-Arduino

# Build
``` cmd
pio lib install
pio run
pio run --target upload
```

# Serial
``` cmd
pio device monitor -p /dev/ttyACM0 -b 115200
```

# micro-ROS Agent
``` cmd
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0 -v6
```

# ポイント
- `ROS_DOMAIN_ID` は明示的に指定してはいけない
- `ROS_LOCALHOST_ONLY` は `0`

# Teensy 4.1 ピン配置
- [Teensy 4.1 Develoment Board - PJRC Electronic Projects Components Available Worldwide](https://www.pjrc.com/store/teensy41.html)


