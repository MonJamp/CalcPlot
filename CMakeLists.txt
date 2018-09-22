cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)

project(CalcPlot)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include_directories(CalcPlot GUI)

set(CXX_SRCS
  main.cpp
  GUI/MainWindow.cpp
  GUI/TipsWindow.cpp
)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -g -Og -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DRELEASE -O2 -Wall -Wextra -Werror")

add_executable(CalcPlot ${CXX_SRCS})
target_link_libraries(CalcPlot Qt5::Widgets Qt5::Gui)

#Copy QT dll files to binary directory
add_custom_command(
    TARGET CalcPlot POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::Widgets>
        $<TARGET_FILE:Qt5::Gui>
        $<TARGET_FILE:Qt5::Core>
        $<TARGET_FILE_DIR:CalcPlot>
)
