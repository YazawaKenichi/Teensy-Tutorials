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

