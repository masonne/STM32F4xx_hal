cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE) 

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# 指定工具链文件
# 需要在project()之前
include("cmake/gcc-arm-none-eabi.cmake")
project(STM32F429_Project C ASM)

# 定义包含所有子目录的列表
set(SUBDIRECTORIES
    drivers/cmsis-core
    drivers/cmsis-device
    drivers/cmsis-compiler
    hal
    apl
)
# 遍历列表，为每个子目录调用 add_subdirectory
foreach(subdir IN LISTS SUBDIRECTORIES)
    add_subdirectory(${subdir})
endforeach()

# 列出源文件

# 添加可执行文件
add_executable(${PROJECT_NAME} start.s)

target_sources(${PROJECT_NAME} PRIVATE
    apl/src/main.c
)

# 链接静态库
target_link_libraries(${PROJECT_NAME} PRIVATE
    cmsis-core
    cmsis-device
    cmsis-compiler
    hal
    apl
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -Oihex ${PROJECT_NAME}.elf               ${CMAKE_SOURCE_DIR}/image/firmware.hex
    COMMAND ${CMAKE_OBJCOPY} -Obinary ${PROJECT_NAME}.elf             ${CMAKE_SOURCE_DIR}/image/firmware.bin
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_NAME}.elf ${CMAKE_SOURCE_DIR}/image/firmware.elf
)

add_custom_target(flash
    COMMAND openocd -f interface/cmsis-dap.cfg -f target/stm32f4x.cfg
    -c "program ${CMAKE_SOURCE_DIR}/image/firmware.elf verify reset exit"
)

add_custom_target(erase
    COMMAND openocd -f interface/cmsis-dap.cfg -f target/stm32f4x.cfg
    -c "init; halt; stm32f4x mass_erase 0; exit"
)