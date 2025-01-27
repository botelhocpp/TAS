# Copyright (c) 2025 TAS
# All rights reserved

set(project_name tas_utils_getopt)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(sources
    ${sources_dir}/getopt.c
)
set(headers
    ${headers_dir}/getopt.h
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE C
    C_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${tas_dir})
