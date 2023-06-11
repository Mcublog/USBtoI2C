cmake_minimum_required(VERSION 3.22)

# Setup compiler settings
set(CMAKE_TRY_COMPILE_TARGET_TYPE   "STATIC_LIBRARY")
set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              20)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)
if(NOT ${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
    set(CMAKE_SYSTEM_NAME           Generic) # workaround for Windows
endif()

set_property(GLOBAL PROPERTY RULE_MESSAGES OFF)

# Set defines
add_definitions(-DprojCOVERAGE_TEST=0)
add_definitions(-D_WINDOWS_)

project(USBtoI2C VERSION "0.3.0" LANGUAGES C CXX ASM)

include(config/common.cmake)
include(config/mcu.cmake)
include(config/desktop.cmake)
include(config/utils.cmake)

LOG_INFO("Version:.........." ${CMAKE_PROJECT_VERSION})
LOG_INFO("Host system:......" ${CMAKE_SYSTEM_NAME})
LOG_INFO("Build type:......." ${CMAKE_BUILD_TYPE})
LOG_INFO("MCU target:......." ${F205_BOOT_TARGET})
LOG_INFO("MCU target:......." ${F205_TARGET})
LOG_INFO("PC target:........" ${GD_MEM_TEST_TARGET})

add_subdirectory(config)
# add_subdirectory(pirit_2f)
# add_subdirectory(bootloader)
# add_subdirectory(test_hw)
# add_subdirectory(pirit_p)

# message("******* [Unit test list] *******")
# enable_testing()
# add_subdirectory(test)
