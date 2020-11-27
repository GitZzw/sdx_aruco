## Ros自定义步骤
[官方文档](http://wiki.ros.org/ROS/Tutorials/CreatingMsgAndSrv#Common_step_for_msg_and_srv)

* 1.首先在创建软件包目录下创建msg文件夹，然后创建.msg文件

* 2.在.msg文件中定义需要的消息类型，如
```make
string first_name
string last_name
uint8 age
uint32 score
```

* 3.在package.xml文件中添加ros消息生成和运行时依赖
```make
  <build_depend>message_generation</build_depend>
  <exec_depend>message_runtime</exec_depend>
```

* 4.在CMakelist.txt文件中添加package需求：message_generation和对应的消息类型如std_msgs
```make
# Do not just add this to your CMakeLists.txt, modify the existing text to add message_generation before the closing parenthesis
find_package(catkin REQUIRED COMPONENTS
   roscpp
   rospy
   std_msgs
   message_generation
)
```

* 5.在CMakelist.txt文件中添加运行时依赖
```make
catkin_package(
  ...
  CATKIN_DEPENDS message_runtime ...
  ...)
```

* 6.在CMakelist.txt文件中添加你的msg文件
```make
add_message_files(
  FILES
  Num.msg
)
```

* 7.在CMakelist.txt文件中添加需要的消息依赖
```make
generate_messages(
  DEPENDENCIES
  std_msgs
)
```
* 8.catkin_make

> 注意：Any .msg file in the msg directory will generate code for use in all supported languages. The C++ message header file will be generated in ~/catkin_ws/devel/include/beginner_tutorials/. The Python script will be created in ~/catkin_ws/devel/lib/python2.7/dist-packages/beginner_tutorials/msg. The lisp file appears in ~/catkin_ws/devel/share/common-lisp/ros/beginner_tutorials/msg/.


## 使用定义的消息类型
[参考](https://blog.csdn.net/jinking01/article/details/79620911)  
>  在使用该消息的软件包中添加如下头文件即可，同时要把devel/include目录下的Any_msg整体复制到使用该消息的include目录下,package_name为生成该消息的软件包名字
   `#include <package_name/Any_msg.h>`
