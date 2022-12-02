# Depth2Uart
#### 双目测距------双目相机V1.0，将双目相机采集到任意一点的深度数据进行串口传输

##  使用方法
### 一、安装Ubuntu
推荐Ubuntu 18/20 LTS版本，兼容Ubuntu 22 LTS，本文部分依赖（如Intel Realsense SDK）官方文档暂未支持Ubuntu22，但实测可行，在未来会慢慢适配新版本。

### 二、安装ROS/ROS2
根据Ubuntu版本安装ROS/ROS2，安装方法可前往观看古月居/鱼香ROS相关视频，可使用一键安装脚本：https://github.com/fishros/install 。
本版本双目测距理论上不需要安装ROS系统，但安装ROS比较方便解决相关依赖，同时后续版本肯定也会使用到就直接安装好了

### 三、安装Intel Realsense SDK
如出现问题可查看[Linux官方安装文档](https://github.com/IntelRealSense/librealsense/blob/master/doc/installation.md)

####  1. 安装依赖
```
sudo apt-get install git libssl-dev libusb-1.0-0-dev libudev-dev pkg-config libgtk-3-dev libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
```
#### 2. 下载Intel Realsense SDK
``` 
git clone  https://github.com/IntelRealSense/librealsense.git
```
这行代码默认是下载的最新稳定版的SDK，现在只支持ROS2了，可以前往github仓库查看具体要求。
下载指定版本在git clone后加上-b，如Ubuntu18/20一般安装ROS，v2.50.0版本为支持ROS1的最后版本，就使用下面这个代码
``` 
git clone  -b v2.50.0 https://github.com/IntelRealSense/librealsense.git
```
#### 3. 安装Intel Realsense SDK
```
cd librealsense
./scripts/setup_udev_rules.sh
mkdir build && cd build
cmake ..
make -j8
sudo make install
```
测试可以输入命令 realsense-viewer，可以看到一个软件打开，可以在此测试相机是否正常。

### 四、编译depth2uart.cpp
在depth2uart.cpp所在目录打开终端，输入以下代码编译cpp文件，生成depth2uart可执行文件，部分硬件可能会报错，可以根据报错查看缺少什么库文件，比如Jetson Nano需要添加
```
g++ depth2uart.cpp -o depth2uart -lrealsense2 -lboost_system
```

### 五、给串口添加权限
输入以下命令可查询串口所在USB口。
```
ls -l /dev/ttyUSB* 
```
默认是USB0，输入以下命令给串口添加权限，如果是其他USB则需要修改USB后面数字。
```
sudo chmod 777 /dev/ttyUSB0
```

### 六、运行depth2uart
```
./depth2uart 
```
可以看到输出摄像头最中央一点的深度信息，串口传输至STM32端接收。