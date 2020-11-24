cmake_minimum_required(VERSION 2.8.3)
project(camera_test)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_definitions(-std=c++11 -g -O1 -ftree-vectorize -march=native)

find_package(catkin REQUIRED COMPONENTS
    roscpp
    tf
    message_filters
    cv_bridge
    sensor_msgs
    image_transport
    message_generation
    std_msgs
    geometry_msgs
)


add_message_files(
  FILES
  zzw.msg
)


generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
)





find_package(OpenCV REQUIRED)

find_package(Eigen3 REQUIRED)

catkin_package(
    CATKIN_DEPENDS message_runtime
)


include_directories(${catkin_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${EIGEN3_INCLUDE_DIRS})

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})
add_definitions(${EIGEN_DEFINITIONS})

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(camera_test src/camera_test.cpp)
add_dependencies(camera_test        ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(camera_test ${OpenCV_LIBS} ${catkin_LIBRARIES} )

add_executable(camera_detect_aruco src/camera_detect_aruco.cpp)
add_dependencies(camera_detect_aruco        ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(camera_detect_aruco ${OpenCV_LIBS} ${catkin_LIBRARIES} )


add_executable(camera_generate_aruco src/camera_generate_aruco.cpp)
add_dependencies(camera_generate_aruco        ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS} )
target_link_libraries(camera_generate_aruco ${OpenCV_LIBS} ${catkin_LIBRARIES} )


