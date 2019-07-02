cmake_minimum_required(VERSION 2.8.3)
project(example_dynamixel)

find_package(catkin REQUIRED COMPONENTS dynamixel_sdk roscpp)

catkin_package(CATKIN_DEPENDS dynamixel_sdk roscpp)

include_directories( ${dynamixel_sdk_INCLUDE_DIRS}
                     ${catkin_INCLUDE_DIRS}       )

add_executable(read_write src/read_write.cpp)
target_link_libraries(read_write ${catkin_LIBRARIES}
                                 ${dynamixel_sdk_LIBRARIES})

add_executable(ping src/ping.cpp)
target_link_libraries(ping ${catkin_LIBRARIES}
                           ${dynamixel_sdk_LIBRARIES})
