// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rtabmap_msgs:msg/EnvSensor.idl
// generated code does not contain a copyright notice

#ifndef RTABMAP_MSGS__MSG__DETAIL__ENV_SENSOR__STRUCT_H_
#define RTABMAP_MSGS__MSG__DETAIL__ENV_SENSOR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'TYPE_UNDEFINED'.
/**
  * Environmental sensor
  * built-in types
 */
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_UNDEFINED = 0l
};

/// Constant 'TYPE_WIFI_SIGNAL_STRENGTH'.
/**
  * dBm
 */
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_WIFI_SIGNAL_STRENGTH = 1l
};

/// Constant 'TYPE_AMBIENT_TEMPERATURE'.
/**
  * Celcius
 */
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_AMBIENT_TEMPERATURE = 2l
};

/// Constant 'TYPE_AMBIENT_AIR_PRESSURE'.
/**
  * hPa
 */
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_AMBIENT_AIR_PRESSURE = 3l
};

/// Constant 'TYPE_AMBIENT_LIGHT'.
/**
  * lx
 */
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_AMBIENT_LIGHT = 4l
};

/// Constant 'TYPE_AMBIENT_RELATIVE_HUMIDITY'.
/**
  * %
 */
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_AMBIENT_RELATIVE_HUMIDITY = 5l
};

/// Constant 'TYPE_CUSTOM1'.
/**
  * user types
 */
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM1 = 100l
};

/// Constant 'TYPE_CUSTOM2'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM2 = 101l
};

/// Constant 'TYPE_CUSTOM3'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM3 = 102l
};

/// Constant 'TYPE_CUSTOM4'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM4 = 103l
};

/// Constant 'TYPE_CUSTOM5'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM5 = 104l
};

/// Constant 'TYPE_CUSTOM6'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM6 = 105l
};

/// Constant 'TYPE_CUSTOM7'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM7 = 106l
};

/// Constant 'TYPE_CUSTOM8'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM8 = 107l
};

/// Constant 'TYPE_CUSTOM9'.
enum
{
  rtabmap_msgs__msg__EnvSensor__TYPE_CUSTOM9 = 108l
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"

/// Struct defined in msg/EnvSensor in the package rtabmap_msgs.
typedef struct rtabmap_msgs__msg__EnvSensor
{
  std_msgs__msg__Header header;
  int32_t type;
  double value;
} rtabmap_msgs__msg__EnvSensor;

// Struct for a sequence of rtabmap_msgs__msg__EnvSensor.
typedef struct rtabmap_msgs__msg__EnvSensor__Sequence
{
  rtabmap_msgs__msg__EnvSensor * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rtabmap_msgs__msg__EnvSensor__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RTABMAP_MSGS__MSG__DETAIL__ENV_SENSOR__STRUCT_H_
