cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

project(CalcPlot)

find_package(Qt5Widgets REQUIRED)
find_package(Boost 1.64 COMPONENTS regex REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(CalcPlot GUI ${Boost_INCLUDE_DIRS})

set(CXX_SRCS
  main.cpp
  Calculator.cpp
  GUI/MainWindow.cpp
  GUI/TipsWindow.cpp
  GUI/Graph_2D_Window.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g -Og -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE -O2 -Wall -Wextra -Werror")

add_executable(CalcPlot ${CXX_SRCS})
target_link_libraries(CalcPlot Qt5::Widgets Qt5::Gui Boost::regex)

#Copy QT dll files to binary directory
add_custom_command(
    TARGET CalcPlot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE:Boost::regex>
        $<TARGET_FILE_DIR:CalcPlot>
)
