# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "cat: 1 messages, 0 services")

set(MSG_I_FLAGS "-Icat:/home/hjk/Desktop/zzw/cat/src/cat/msg;-Istd_msgs:/opt/ros/melodic/share/std_msgs/cmake/../msg;-Igeometry_msgs:/opt/ros/melodic/share/geometry_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(geneus REQUIRED)
find_package(genlisp REQUIRED)
find_package(gennodejs REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(cat_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg" NAME_WE)
add_custom_target(_cat_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "cat" "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg" "geometry_msgs/Pose:geometry_msgs/Point:geometry_msgs/Quaternion:std_msgs/Header"
)

#
#  langs = gencpp;geneus;genlisp;gennodejs;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(cat
  "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cat
)

### Generating Services

### Generating Module File
_generate_module_cpp(cat
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cat
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(cat_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(cat_generate_messages cat_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg" NAME_WE)
add_dependencies(cat_generate_messages_cpp _cat_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cat_gencpp)
add_dependencies(cat_gencpp cat_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cat_generate_messages_cpp)

### Section generating for lang: geneus
### Generating Messages
_generate_msg_eus(cat
  "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cat
)

### Generating Services

### Generating Module File
_generate_module_eus(cat
  ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cat
  "${ALL_GEN_OUTPUT_FILES_eus}"
)

add_custom_target(cat_generate_messages_eus
  DEPENDS ${ALL_GEN_OUTPUT_FILES_eus}
)
add_dependencies(cat_generate_messages cat_generate_messages_eus)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg" NAME_WE)
add_dependencies(cat_generate_messages_eus _cat_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cat_geneus)
add_dependencies(cat_geneus cat_generate_messages_eus)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cat_generate_messages_eus)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(cat
  "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cat
)

### Generating Services

### Generating Module File
_generate_module_lisp(cat
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cat
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(cat_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(cat_generate_messages cat_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg" NAME_WE)
add_dependencies(cat_generate_messages_lisp _cat_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cat_genlisp)
add_dependencies(cat_genlisp cat_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cat_generate_messages_lisp)

### Section generating for lang: gennodejs
### Generating Messages
_generate_msg_nodejs(cat
  "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cat
)

### Generating Services

### Generating Module File
_generate_module_nodejs(cat
  ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cat
  "${ALL_GEN_OUTPUT_FILES_nodejs}"
)

add_custom_target(cat_generate_messages_nodejs
  DEPENDS ${ALL_GEN_OUTPUT_FILES_nodejs}
)
add_dependencies(cat_generate_messages cat_generate_messages_nodejs)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg" NAME_WE)
add_dependencies(cat_generate_messages_nodejs _cat_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cat_gennodejs)
add_dependencies(cat_gennodejs cat_generate_messages_nodejs)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cat_generate_messages_nodejs)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(cat
  "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Pose.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Point.msg;/opt/ros/melodic/share/geometry_msgs/cmake/../msg/Quaternion.msg;/opt/ros/melodic/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cat
)

### Generating Services

### Generating Module File
_generate_module_py(cat
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cat
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(cat_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(cat_generate_messages cat_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/hjk/Desktop/zzw/cat/src/cat/msg/zzw.msg" NAME_WE)
add_dependencies(cat_generate_messages_py _cat_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(cat_genpy)
add_dependencies(cat_genpy cat_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS cat_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cat)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/cat
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(cat_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()
if(TARGET geometry_msgs_generate_messages_cpp)
  add_dependencies(cat_generate_messages_cpp geometry_msgs_generate_messages_cpp)
endif()

if(geneus_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cat)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${geneus_INSTALL_DIR}/cat
    DESTINATION ${geneus_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_eus)
  add_dependencies(cat_generate_messages_eus std_msgs_generate_messages_eus)
endif()
if(TARGET geometry_msgs_generate_messages_eus)
  add_dependencies(cat_generate_messages_eus geometry_msgs_generate_messages_eus)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cat)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/cat
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(cat_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()
if(TARGET geometry_msgs_generate_messages_lisp)
  add_dependencies(cat_generate_messages_lisp geometry_msgs_generate_messages_lisp)
endif()

if(gennodejs_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cat)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gennodejs_INSTALL_DIR}/cat
    DESTINATION ${gennodejs_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_nodejs)
  add_dependencies(cat_generate_messages_nodejs std_msgs_generate_messages_nodejs)
endif()
if(TARGET geometry_msgs_generate_messages_nodejs)
  add_dependencies(cat_generate_messages_nodejs geometry_msgs_generate_messages_nodejs)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cat)
  install(CODE "execute_process(COMMAND \"/usr/bin/python2\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cat\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/cat
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(cat_generate_messages_py std_msgs_generate_messages_py)
endif()
if(TARGET geometry_msgs_generate_messages_py)
  add_dependencies(cat_generate_messages_py geometry_msgs_generate_messages_py)
endif()
