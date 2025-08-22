add_library(
        skip_list_lib_v1
        STATIC
        src/skip-list.h
        src/skip-list.c
)

add_executable(
        skip_list_v1
        main.c
)

target_link_libraries(
        skip_list_v1
        skip_list_lib_v1
)
