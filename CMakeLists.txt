cmake_minimum_required(VERSION 3.23)
project(Litecode VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if(UNIX AND NOT APPLE)
  set(PLATFORM_SRCS src/platform/linux/linux_opengl.cpp src/platform/linux/linux_window.cpp)

  find_package(PkgConfig REQUIRED)
  pkg_check_modules(GTK REQUIRED gtk+-3.0)
endif(UNIX AND NOT APPLE)

if(MSVC)
  set(PLATFORM_SRCS src/platform/windows/win_opengl.cpp src/platform/windows/win_window.cpp)
endif(MSVC)

set(GUI_SRCS src/gui_components/frame.cpp src/gui_components/image.cpp src/gui_components/window.cpp)
set(UTIL_SRCS src/utilities/fs.cpp)
set(SRCS dependencies/glad/glad.c ${PLATFORM_SRCS} ${GUI_SRCS} ${UTIL_SRCS} src/main.cpp)

include_directories(dependencies)
include_directories(dependencies/glm)

add_executable(Litecode ${SRCS})

target_link_libraries(Litecode PRIVATE ${GTK_LIBRARIES} dl GL X11)
target_compile_definitions(Litecode PRIVATE ${GTK_FLAGS_OTHER})
target_include_directories(Litecode PRIVATE ${GTK_INCLUDE_DIRS})
target_link_directories(Litecode PRIVATE ${GTK_LIBRARY_DIRS})
