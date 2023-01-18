# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)


add_library(DireWolf direwolf/src/fcs_calc.c)

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(Pico-TNC C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Pico-TNC pico-tnc.c hdlc-afsk.c pwm-audio.c)

pico_set_program_name(Pico-TNC "Pico-TNC")
pico_set_program_version(Pico-TNC "0.1")

pico_enable_stdio_uart(Pico-TNC 1)
pico_enable_stdio_usb(Pico-TNC 0)

# Add the standard library to the build
target_link_libraries(Pico-TNC
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(Pico-TNC PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(Pico-TNC
        hardware_dma
        hardware_interp
        hardware_timer
        hardware_pwm
        pico_cyw43_arch_lwip_threadsafe_background
        )

pico_add_extra_outputs(Pico-TNC)

