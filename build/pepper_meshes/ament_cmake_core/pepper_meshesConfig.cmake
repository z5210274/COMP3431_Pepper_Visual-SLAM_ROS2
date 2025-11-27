# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_pepper_meshes_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED pepper_meshes_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(pepper_meshes_FOUND FALSE)
  elseif(NOT pepper_meshes_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(pepper_meshes_FOUND FALSE)
  endif()
  return()
endif()
set(_pepper_meshes_CONFIG_INCLUDED TRUE)

# output package information
if(NOT pepper_meshes_FIND_QUIETLY)
  message(STATUS "Found pepper_meshes: 3.0.0 (${pepper_meshes_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'pepper_meshes' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${pepper_meshes_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(pepper_meshes_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${pepper_meshes_DIR}/${_extra}")
endforeach()
