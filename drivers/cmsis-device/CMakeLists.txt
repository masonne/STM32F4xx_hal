# 添加静态库目标
add_library(cmsis-device STATIC)

# 添加源文件
target_sources(cmsis-device PRIVATE
    system_stm32f4xx.c
)

# 指定包含目录
target_include_directories(cmsis-device PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# 添加 cmsis-core 作为公共依赖
target_link_libraries(cmsis-device PUBLIC cmsis-core)

# 定义编译宏
target_compile_definitions(cmsis-device PUBLIC
    STM32F429xx
)
