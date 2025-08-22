add_library(
        hash_table_lib_v2
        STATIC
        src/hash-table.h
        src/hash-table.c
)

add_executable(
        hash_table_v2
        main.c
)

target_link_libraries(
        hash_table_v2
        hash_table_lib_v2
)

