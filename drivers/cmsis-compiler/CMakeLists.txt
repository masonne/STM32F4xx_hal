add_library(cmsis-compiler STATIC)

target_sources(cmsis-compiler PRIVATE
    retarget_syscalls.c
)

target_link_libraries(cmsis-compiler PUBLIC
    cmsis-core
)