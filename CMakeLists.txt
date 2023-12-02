cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

project(main C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

# Initialize the SDK

pico_sdk_init()

add_executable(main
		main.cpp
		lib/serial.cpp
		)

# Pull in our pico_stdlib which pulls in commonl
target_link_libraries(main pico_stdlib)
target_link_libraries(main pico_stdlib hardware_gpio)
target_link_libraries(main pico_stdlib hardware_adc)
target_link_libraries(main pico_stdlib hardware_pwm)
target_link_libraries(main pico_stdlib hardware_uart)


# create map/bin/hex file etc.
pico_add_extra_outputs(main)


