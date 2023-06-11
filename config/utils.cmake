function(LOG_INFO text)
    message("[INFO] " ${ARGV})
endfunction()

function(LOG_DEBUG text)
    message("[DEBUG] " ${ARGV})
endfunction()

function(LOG_WARN text)
    message("[WARN] " ${ARGV})
endfunction()

function(create_bootable_bin target postfix)
    set(OUTPUT_FILENAME PiritF_${postfix}_${VER_MAJOR}.${VER_MINOR}.${VER_PATCH})

    add_custom_command(TARGET ${target}
        POST_BUILD
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMAND ${CMAKE_OBJCOPY} ARGS -O ihex   -I elf32-littlearm ${target} ${target}.hex
        COMMAND ${CMAKE_OBJCOPY} ARGS -O binary -I elf32-littlearm ${target} ${target}.bin
    )

    if(${CMAKE_HOST_SYSTEM_NAME} MATCHES "Linux")
        add_custom_command(TARGET ${target}
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND cat ARGS ${target}.bin "${PROJECT_SOURCE_DIR}/scripts/end4.bin" > ../${OUTPUT_FILENAME}.bin
        )
    else()
        add_custom_command(TARGET ${target}
            POST_BUILD
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMAND copy ARGS /b ${target}.bin + "${PROJECT_SOURCE_DIR}/scripts/end4.bin" ${OUTPUT_FILENAME}.bin
        )
    endif()

endfunction()