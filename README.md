# Using C++ Class in ROS Publisher-Subscriber Tutorial

## Branch
- master  
  Using Boost to make callback of subscriber
- bare_pointer  
  Using bare pointer for assigning callback to subscriber
- compile_error  
  Code on this branch causes an error while compilation
  
## Usage
### Build
```
cd ~/catkin_ws/src
git clone https://github.com/uenota/method_callback.git
cd ..
catkin build
```

### Run
Run roscore and talker
```
roscore &
rosrun method_callback talker
```
Run listener
```
rosrun method_callback method_callback_node
```

## Use method as callback of subscriber
There are two options to use method as callback of subscriber

- Use member function pointer
- Use boost::function object

### Use member function pointer
There is `nh.subscribe<T>()` function that can be used with member function pointer.

```cpp
sub = nh.subscribe<T>("topicname", queueSize, &NodeClass::callback, this);
```

### Use boost::function object
There is also `nh.subscribe<T>()` that can be used with boost::function object.
In case of `nh.subscribe<T>()` with member function pointer, `this` is given as an argument.
`this` is not required in this case.
However `this` must be given to an argument of `boost::bind()` .

```cpp
auto cb = boost::bind(&NodeClass::callback, this, _1);
sub = nh.subscribe<T>("topicname", queueSize, cb)
```

### Reference
- http://docs.ros.org/kinetic/api/roscpp/html/classros_1_1NodeHandle.html
- http://adragoona.hatenablog.com/entry/2015/09/06/191737

## Trouble shooting

### "You must call ros::init() before creating the first NodeHandle"
This error occurs when a variable of `ros::NodeHandle` is created before calling `ros::init()`.
You need to create variables of `ros::NodeHandle` afeter calling `ros::init()`.

For example, the following class has a variable of `ros::NodeHandle` in its member and calls `ros::init()`
 in constructor.
 
```cpp
class NodeClass
{
...
private:
    ros::NodeHandle nh;
public:
    NodeClass(int argc, char** argv);
...
};

NodeClass::NodeClass(int argc, char** argv)
{
...
    ros::init(argc, argv, "node_name");
...
}
```

### Subscriber not working
A local variable containing subscriber instance like the following expires when leaving constructor.

```cpp
class NodeClass
{
...
public:
    NodeClass(int argc, char** argv);
...
};

NodeClass::NodeClass(int argc, char** argv)
{
...
ros::Subscriber sub = nh.subscribe<T>("topicname", queueSize, &NodeClass::callback, this);
...
}
```

A subscriber instance needs to be contained a member variable.

```cpp
class NodeClass
{
...
public:
    NodeClass(int argc, char** argv);

private:
    ros::Subscriber sub;
...
};

NodeClass::NodeClass(int argc, char** argv)
{
...
sub = nh.subscribe<T>("topicname", queueSize, &NodeClass::callback, this);
...
}
```
Publishers and servers of dynamic reconfigure need to be contained a member variable too.
The example for dynamic reconfigure is also available in this repository.

### Reference
- https://answers.ros.org/question/216509/subscribe-and-publish-using-a-class/
