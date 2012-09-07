set(the_target "rcam_server")

add_definitions(-Wall)

file(GLOB p_src RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

add_executable(${the_target} ${p_src})

target_link_libraries(${the_target} ${OpenCV_LIBS} ${LIBXS_LIBRARIES})

