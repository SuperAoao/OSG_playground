# CMakeList.txt : CMake project for OSGPlayground, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)


project ("OSGPlayground")


find_package(OpenSceneGraph REQUIRED COMPONENTS osg osgDB osgGA osgUtil osgViewer)

include_directories(${OPENSCENEGRAPH_INCLUDE_DIRS})

add_executable(output4KImg output4kimg.cpp )
add_executable(fixed_star "fixed_star/fixed_star.cpp")
add_executable(render_to_tex "render_to_tex/to_smaller_tex.cpp")
add_executable(rendering_relative_to_eye_artifact "rendering_relative_to_eye/artifact.cpp")
add_executable(rendering_relative_to_eye "rendering_relative_to_eye/solution.cpp")

target_link_libraries(output4KImg PRIVATE ${OPENSCENEGRAPH_LIBRARIES})
target_link_libraries(fixed_star PRIVATE ${OPENSCENEGRAPH_LIBRARIES})
target_link_libraries(render_to_tex PRIVATE ${OPENSCENEGRAPH_LIBRARIES})
target_link_libraries(rendering_relative_to_eye_artifact PRIVATE ${OPENSCENEGRAPH_LIBRARIES})
target_link_libraries(rendering_relative_to_eye PRIVATE ${OPENSCENEGRAPH_LIBRARIES})

# TODO: Add tests and install targets if needed.
