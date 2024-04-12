cmake_minimum_required(VERSION 3.10)

project(OSGPlayground)

set (CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB osgGA osgUtil osgViewer)

add_executable(Output4KImg output4kimg.cpp)

target_link_libraries(Output4KImg PRIVATE ${OPENSCENEGRAPH_LIBRARIES})