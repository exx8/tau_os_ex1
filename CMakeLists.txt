cmake_minimum_required(VERSION 3.17)
project(tau_os_ex1 C)
add_definitions( -DPT=1 )

set(CMAKE_C_STANDARD 11)

add_executable(tau_os_ex1 os.c)