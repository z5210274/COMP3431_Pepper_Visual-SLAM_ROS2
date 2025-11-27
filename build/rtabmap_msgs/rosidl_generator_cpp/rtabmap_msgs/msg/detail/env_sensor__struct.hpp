// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from rtabmap_msgs:msg/EnvSensor.idl
// generated code does not contain a copyright notice

#ifndef RTABMAP_MSGS__MSG__DETAIL__ENV_SENSOR__STRUCT_HPP_
#define RTABMAP_MSGS__MSG__DETAIL__ENV_SENSOR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__rtabmap_msgs__msg__EnvSensor __attribute__((deprecated))
#else
# define DEPRECATED__rtabmap_msgs__msg__EnvSensor __declspec(deprecated)
#endif

namespace rtabmap_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct EnvSensor_
{
  using Type = EnvSensor_<ContainerAllocator>;

  explicit EnvSensor_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0l;
      this->value = 0.0;
    }
  }

  explicit EnvSensor_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->type = 0l;
      this->value = 0.0;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _type_type =
    int32_t;
  _type_type type;
  using _value_type =
    double;
  _value_type value;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__type(
    const int32_t & _arg)
  {
    this->type = _arg;
    return *this;
  }
  Type & set__value(
    const double & _arg)
  {
    this->value = _arg;
    return *this;
  }

  // constant declarations
  static constexpr int32_t TYPE_UNDEFINED =
    0;
  static constexpr int32_t TYPE_WIFI_SIGNAL_STRENGTH =
    1;
  static constexpr int32_t TYPE_AMBIENT_TEMPERATURE =
    2;
  static constexpr int32_t TYPE_AMBIENT_AIR_PRESSURE =
    3;
  static constexpr int32_t TYPE_AMBIENT_LIGHT =
    4;
  static constexpr int32_t TYPE_AMBIENT_RELATIVE_HUMIDITY =
    5;
  static constexpr int32_t TYPE_CUSTOM1 =
    100;
  static constexpr int32_t TYPE_CUSTOM2 =
    101;
  static constexpr int32_t TYPE_CUSTOM3 =
    102;
  static constexpr int32_t TYPE_CUSTOM4 =
    103;
  static constexpr int32_t TYPE_CUSTOM5 =
    104;
  static constexpr int32_t TYPE_CUSTOM6 =
    105;
  static constexpr int32_t TYPE_CUSTOM7 =
    106;
  static constexpr int32_t TYPE_CUSTOM8 =
    107;
  static constexpr int32_t TYPE_CUSTOM9 =
    108;

  // pointer types
  using RawPtr =
    rtabmap_msgs::msg::EnvSensor_<ContainerAllocator> *;
  using ConstRawPtr =
    const rtabmap_msgs::msg::EnvSensor_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      rtabmap_msgs::msg::EnvSensor_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      rtabmap_msgs::msg::EnvSensor_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__rtabmap_msgs__msg__EnvSensor
    std::shared_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__rtabmap_msgs__msg__EnvSensor
    std::shared_ptr<rtabmap_msgs::msg::EnvSensor_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const EnvSensor_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->type != other.type) {
      return false;
    }
    if (this->value != other.value) {
      return false;
    }
    return true;
  }
  bool operator!=(const EnvSensor_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct EnvSensor_

// alias to use template instance with default allocator
using EnvSensor =
  rtabmap_msgs::msg::EnvSensor_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_UNDEFINED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_WIFI_SIGNAL_STRENGTH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_AMBIENT_TEMPERATURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_AMBIENT_AIR_PRESSURE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_AMBIENT_LIGHT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_AMBIENT_RELATIVE_HUMIDITY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM3;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM4;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM5;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM6;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM7;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM8;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr int32_t EnvSensor_<ContainerAllocator>::TYPE_CUSTOM9;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace rtabmap_msgs

#endif  // RTABMAP_MSGS__MSG__DETAIL__ENV_SENSOR__STRUCT_HPP_
