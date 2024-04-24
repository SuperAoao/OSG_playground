# CMakeList.txt : CMake project for OSGPlayground, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


project ("OSGPlayground")


find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB osgGA osgUtil osgViewer)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

add_executable(Output4KImg output4kimg.cpp)

target_link_libraries(Output4KImg PRIVATE ${OPENSCENEGRAPH_LIBRARIES})

# TODO: Add tests and install targets if needed.
