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
## micro-ROS Agent で何やらデータを取得していそうな感じは見えるが、実際の ROS システムとの通信ができている気がしない
micro-ROS Agent を起動したあとに Teensy と接続するとなんだかデータのやり取りが行われるが、そのやり取りされているデータの内容はバイナリになってるし、ros2 node list とかしても何も出てこないから、困ってる。

