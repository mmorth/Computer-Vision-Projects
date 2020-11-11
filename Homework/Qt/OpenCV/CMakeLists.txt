cmake_minimum_required(VERSION 3.14)

project(OpenCV LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package( OpenCV REQUIRED )

add_executable(OpenCV
  main.cpp

  HW2_2018/p1_opencv_code.cpp
  HW2_2018/p2_opencv_code.cpp
  HW2_2018/p3a_opencv_code.cpp
  HW2_2018/p3b_opencv_code.cpp
  HW2_2018/p3c_opencv_code.cpp
  HW2_2018/chess_piece_template_finder.cpp

  HW2_2019/p1_opencv_code.cpp
  HW2_2019/p2_opencv_code.cpp
  HW2_2019/p3_opencv_code.cpp
  HW2_2019/p4_opencv_code.cpp
  HW2_2019/p5_opencv_code.cpp
  HW2_2019/p6_opencv_code.cpp
  HW2_2019/p7_opencv_code.cpp
  HW2_2019/p8_opencv_code.cpp
  HW2_2019/p9_opencv_code.cpp
  HW2_2019/p10_opencv_code.cpp

  HW2_2020/p1a_opencv_code.cpp
  HW2_2020/p1b_opencv_code.cpp
  HW2_2020/p2a_opencv_code.cpp
  HW2_2020/p2b_opencv_code.cpp
  HW2_2020/p2c_opencv_code.cpp
  HW2_2020/p3a_opencv_code.cpp
  HW2_2020/chess_piece_template_finder.cpp
)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(OpenCV Qt5::Core)
target_link_libraries(OpenCV ${OpenCV_LIBS})
