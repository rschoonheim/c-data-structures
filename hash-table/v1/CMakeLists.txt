add_library(
        hash_table_lib
        STATIC
        src/hash-table.h
        src/hash-table.c
)

add_executable(
        hash_table_v1
        main.c
)

target_link_libraries(
        hash_table_v1
        hash_table_lib
)
