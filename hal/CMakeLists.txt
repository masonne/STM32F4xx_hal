add_library(hal STATIC)

file(GLOB hal_src "src/*.c")
file(GLOB legacy_src "src/legacy/*.c")
list(APPEND hal_src ${legacy_src})

target_sources(hal PRIVATE
    ${hal_src}
)

target_include_directories(hal PUBLIC
    inc
    inc/legacy
)

target_link_libraries(hal PUBLIC
    apl
    cmsis-device
)

target_compile_definitions(hal PUBLIC
    USE_HAL_DRIVER
)