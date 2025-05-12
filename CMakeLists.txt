cmake_minimum_required(3.01)
add_library(workLoad, )
add_executable(app , "service.cpp")

target_link_libraries(workload, "Advapi32.lib")