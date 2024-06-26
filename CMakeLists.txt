cmake_minimum_required(VERSION 3.12)

# Change your executable name to something creative!
set(NAME simple_motor) # <-- Name your project/executable here!
#set(PICO_BOARD pico_w)

include(pimoroni_pico_import.cmake)
include(pico_sdk_import.cmake)

# Gooey boilerplate
project(${NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Add your source files
add_executable(${NAME}
        src/main.cpp # <-- Add source files here!
        )

target_include_directories(${NAME} PRIVATE include)

# include libraries
include(common/pimoroni_bus)
include(drivers/button/button)
include(drivers/pwm/pwm)
include(drivers/motor/motor)
include(drivers/analog/analog)
include(drivers/encoder/encoder)
include(drivers/pid/pid)
include(drivers/plasma/plasma)
#include(libraries/pico_explorer/pico_explorer)
include(libraries/bitmap_fonts/bitmap_fonts)
include(libraries/hershey_fonts/hershey_fonts)
include(libraries/pico_explorer/pico_explorer)


# Don't forget to link the libraries you need!
target_link_libraries(${NAME}
        pico_stdlib
        pico_explorer
        pico_graphics
        st7789
        button
        motor
        analog
        encoder
        pid
        plasma
        )

# create map/bin/hex file etc.
pico_add_extra_outputs(${NAME})
pico_enable_stdio_usb(${NAME} 1)
pico_enable_stdio_uart(${NAME} 0)

# Set up files for the release packages
install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/${NAME}.uf2
        ${CMAKE_CURRENT_LIST_DIR}/README.md
        DESTINATION .
        )

set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_GENERATOR "ZIP" "TGZ")
include(CPack)