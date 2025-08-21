add_library(
        hash_table_lib
        STATIC
        src/hash-table.h
        src/hash-table.c
)

add_executable(
        hash_table
        main.c
)

target_link_libraries(
        hash_table
        hash_table_lib
)
