set(STM32F401_CUBE_PATH           ${PROJECT_SOURCE_DIR}/CubeMX/STM32F401CxUx)
set(STM32F407_CUBE_PATH           ${PROJECT_SOURCE_DIR}/CubeMX/STM32F407VE)
set(DESKTOP_TARGET_PATH           ${PROJECT_SOURCE_DIR}/targets/desktop)

# Include utils
include(${PROJECT_SOURCE_DIR}/config/utils.cmake)

# region COMMON
set(APP_DIR ${PROJECT_SOURCE_DIR}/App)

set(APP_INCLUDES
    ${PROJECT_SOURCE_DIR}
    ${APP_DIR}
    ${APP_DIR}/debug
)

file(GLOB APP_SOURCES ${APP_DIR}/*.cpp ${APP_DIR}/debug/*.c)

set(LIBS_DIR ${PROJECT_SOURCE_DIR}/libs)

set(HAL_INCLUDE_DIRS
    # Put here your include dirs, one in each line,
    # relative to CMakeLists.txt file location
    ${LIBS_DIR}/STM32F2xx_StdPeriph_Driver/inc
    ${LIBS_DIR}/CMSIS
)
# endregion

# region RTT
set(RTT_ENABLE true)
if(CMAKE_BUILD_TYPE STREQUAL Release)
    set(RTT_ENABLE false)
endif()

if(${RTT_ENABLE})
    # LOG_INFO("RTT is enabled")
    set(RTT_VERSION SEGGER_RTT_V762c)
    set(RTT_DIR ${LIBS_DIR}/${RTT_VERSION})
    set(RTT_INCLUDE_DIRS
        ${RTT_DIR}/Config
        ${RTT_DIR}/RTT)
    # Add sources
    file(GLOB_RECURSE RTT_SOURCES
        ${RTT_DIR}/RTT/*.c
        ${RTT_DIR}/RTT/*.S
        ${RTT_DIR}/Syscalls/SEGGER_RTT_Syscalls_GCC.c
    )
endif()
# endregion
