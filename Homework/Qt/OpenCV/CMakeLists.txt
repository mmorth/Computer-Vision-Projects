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
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(OpenCV
  main.cpp

  OpenCV_Course/submission.cpp

  HW2_2013/p1_opencv_code.cpp
  HW2_2013/p2_opencv_code.cpp
  HW2_2013/trackbar_example.cpp

  HW2_2017/p1_matlab_code.cpp
  HW2_2017/p2_opencv_code.cpp
  HW2_2017/p3_opencv_code.cpp

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
  HW2_2020/p3b_opencv_code.cpp
  HW2_2020/p4a_opencv_code.cpp
  HW2_2020/p4b_opencv_code.cpp
  HW2_2020/p5a_opencv_code.cpp
  HW2_2020/p5b_opencv_code.cpp
  HW2_2020/chess_piece_template_finder.cpp

  HW3_2017/p1a_opencv_code.cpp
  HW3_2017/p1b_opencv_code.cpp
  HW3_2017/p2_opencv_code.cpp
  HW3_2017/p2b_opencv_code.cpp
  HW3_2017/p2c_opencv_code.cpp
  HW3_2017/p3_opencv_code.cpp
  HW3_2017/hw4_opencv_code.cpp
  HW3_2017/image_inspector.cpp
  HW3_2017/color_detector.cpp

  HW3_2018/p1a_opencv_code.cpp
  HW3_2018/p1b_opencv_code.cpp
  HW3_2018/p2a_opencv_code.cpp
  HW3_2018/p2b_opencv_code.cpp
  HW3_2018/p3a_opencv_code.cpp
  HW3_2018/p3b_opencv_code.cpp
  HW3_2018/p4_opencv_code.cpp
  HW3_2018/create_pacmman_template.cpp

  HW3_2019/p1a_opencv_code.cpp
  HW3_2019/p1b_opencv_code.cpp
  HW3_2019/p1c_opencv_code.cpp
  HW3_2019/p1d_opencv_code.cpp
  HW3_2019/p2a_opencv_code.cpp
  HW3_2019/p2b_opencv_code.cpp
  HW3_2019/p2c_opencv_code.cpp
  HW3_2019/create_display_templates.cpp

  HW3_2020/p1a_opencv_code.cpp
  HW3_2020/p1b_opencv_code.cpp
  HW3_2020/p1c_opencv_code.cpp
  HW3_2020/p2a_opencv_code.cpp
  HW3_2020/p2b_opencv_code.cpp
  HW3_2020/p2c_opencv_code.cpp
  HW3_2020/p3_opencv_code.cpp
  HW3_2020/create_mario_template.cpp

  HW5_2020/p10_training_nanohmm.c
  HW5_2020/nanohmm.c
  HW5_2020/nanohmm.h

  Final_Project/video_capture.cpp
  Final_Project/color_filter_finder.cpp
  Final_Project/experiment.cpp
  Final_Project/mainwindow.cpp
  Final_Project/mainwindow.h
  Final_Project/mainwindow.ui
  Final_Project/main.cpp
  Final_Project/drillwindow.cpp
  Final_Project/drillwindow.h
  Final_Project/drillwindow.ui
  Final_Project/player.cpp
  Final_Project/player.h
)
include_directories(${OpenCV_INCLUDE_DIRS})

target_link_libraries(OpenCV Qt5::Core)
target_link_libraries(OpenCV ${OpenCV_LIBS})
target_link_libraries(OpenCV Qt5::Widgets)
