# 如果该模块只有头文件，没有源文件，可以使用 INTERFACE 库
add_library(cmsis-core INTERFACE)

# 指定包含目录
target_include_directories(cmsis-core INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)