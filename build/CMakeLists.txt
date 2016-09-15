cmake_minimum_required(VERSION 2.8)
project(cgim)

find_package(PkgConfig)
find_package(glfw3)
pkg_check_modules(GLEW glew)
pkg_check_modules(LIBTIFF libtiff-4)
pkg_check_modules(X11 x11)
pkg_check_modules(Xxf86vm xxf86vm)

add_executable(cgim
../src/cg_app.c
)

set(CMAKE_C_FLAGS "-std=c89")

target_link_libraries(cgim glfw)
target_link_libraries(cgim ${GLEW_LIBRARIES})
target_link_libraries(cgim ${LIBTIFF_LIBRARIES})
target_link_libraries(cgim ${TCLAP_LIBRARIES})
target_link_libraries(cgim ${X11_LIBRARIES})
target_link_libraries(cgim ${Xxf86vm_LIBRARIES})
target_link_libraries(cgim libpthread.so)
target_link_libraries(cgim libdl.so)
