cmake_minimum_required(VERSION 3.13)
set(PROJECT ds3231_cpp)

# Pull in SDK (must be before project)
include(pico_sdk_import.cmake)

project(${PROJECT} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico_w)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

pico_sdk_init()

add_subdirectory(ds3231)
include_directories(./ds3231)

add_executable(${PROJECT} main.cpp)

# pull in common dependencies and additional rtc hardware support
target_link_libraries(${PROJECT} pico_stdlib hardware_i2c ds3231)

pico_enable_stdio_uart(${PROJECT} 1)

# create map/bin/hex file etc.
pico_add_extra_outputs(${PROJECT})
