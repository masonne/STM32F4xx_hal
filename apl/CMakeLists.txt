# 添加静态库目标
add_library(apl STATIC)

# 指定包含目录
target_include_directories(apl PUBLIC
    inc
)

# 添加源文件
target_sources(apl PRIVATE
    src/led.c
)

target_link_libraries(apl PUBLIC
    hal
)