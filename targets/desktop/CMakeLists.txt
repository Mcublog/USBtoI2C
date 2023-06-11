include(${PROJECT_SOURCE_DIR}/config/common.cmake)
include(${PROJECT_SOURCE_DIR}/config/desktop.cmake)

add_executable(${DESKTOP_TARGET}
    main.cpp
    ${APP_SOURCES}
    ${PROJECT_SOURCE_DIR}/cobs-c/cobs.c
    ${PROJECT_SOURCE_DIR}/cobs-c/cobsr.c
    ${PROJECT_SOURCE_DIR}/Ring-Buffer/ringbuffer.c)

include_directories(${APP_INCLUDES} ${PROJECT_SOURCE_DIR}/cobs-c ${PROJECT_SOURCE_DIR}/Ring-Buffer)