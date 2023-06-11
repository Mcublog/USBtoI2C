# region MCU GLOBAL PROPERTY
set(F205_TARGET               f205_fw)
set(PRINTER_TARGET            f205_printer_fw)
set(F205_BOOT_TARGET          f205_boot)
set(GD_MEM_TEST_TARGET        mem_test)
set(SD_CARD_TEST_TARGET       sd_card_test)
set(FRAM_DUMPER_TARGET        fram_dumper)

set_property(GLOBAL PROPERTY STM32F205_TARGET_NAME_PROPERTY         ${F205_TARGET})
set_property(GLOBAL PROPERTY STM32F205_BOOT_TARGET_NAME_PROPERTY    ${F205_BOOT_TARGET})

# Put here your symbols (preprocessor defines), one in each line
# Encapsulate them with double quotes for safety purpose
set(symbols_SYMB
    $<$<CONFIG:DEBUG>:"DEBUG">
    $<$<CONFIG:RELASE>:"NDEBUG">
    $<$<CONFIG:RelWithDebInfo>:"DEBUG">
    "ARM_MATH_CM3"
    "STM32FXX"
    "USE_STDPERIPH_DRIVER"
    "NAND"
    "PSRAM"
)

set_property(GLOBAL PROPERTY STM32_DEFINES_PROPERTY
    ${symbols_SYMB}
)

set(CPU_PARAMETERS -mthumb
    # This needs attention to properly set for used MCU
    -mcpu=cortex-m3

    # None for M3
    # -mfpu=fpv5-d16
    -mfloat-abi=soft)

set(ARM_NONE_EABI_FLAGS
    ${CPU_PARAMETERS}
    # -Wall
    # -Wextra
    -Wpedantic
    -funsigned-char
    -fdata-sections
    -ffunction-sections
    -fdiagnostics-color=always
    -fno-common
    -fmessage-length=0
    # Full debug configuration
    $<$<CONFIG:DEBUG>: -Og -g3 -ggdb>
    # Release
    $<$<CONFIG:RELEASE>:-Os -s>
    # Release with DEBUG
    $<$<CONFIG:RelWithDebInfo>:-Os -g3 -ggdb>
)

set_property(GLOBAL PROPERTY ARM_NONE_EABI_FLAGS_PROPERTY
    ${ARM_NONE_EABI_FLAGS}
)

# Set linker script
set(STM32F205_BOOT_LINKER_SCRIPT        ${PROJECT_SOURCE_DIR}/targets/stm32f205/bootloader/STM32F205RGTx_FLASH.ld)
set(STM32F205_FW_LINKER_SCRIPT          ${PROJECT_SOURCE_DIR}/targets/stm32f205/fw/STM32F205RGTx_FLASH.ld)
set(STM32F205_TEST_HW_LINKER_SCRIPT     ${PROJECT_SOURCE_DIR}/targets/stm32f205/test_hw/GD32F425RGT_FLASH.ld)

set(MCU_COMMON_LINKER_OPTION
    ${CPU_PARAMETERS}
    -specs=nano.specs
    -specs=nosys.specs
    # -u _printf_float                # STDIO float formatting support
    -Wl,--start-group
    -lc
    -lm
    -fno-exceptions
    -fno-rtti
    -Wl,--end-group
    -Wl,--gc-sections # removed unused functions
    -Wl,--print-memory-usage
)

set_property(GLOBAL PROPERTY COMMON_MCU_LINKER_OPTIONS_PROPERTY ${MCU_COMMON_LINKER_OPTION})

set(STM32F205_BOOT_LINKER_OPTION
    -T${STM32F205_BOOT_LINKER_SCRIPT}
    ${MCU_COMMON_LINKER_OPTION}
    -Wl,-Map=${F205_BOOT_TARGET}.map
)

set(STM32F205_FW_LINKER_OPTION
    -T${STM32F205_FW_LINKER_SCRIPT}
    ${MCU_COMMON_LINKER_OPTION}
    -Wl,-Map=${F205_TARGET}.map
)
# endregion