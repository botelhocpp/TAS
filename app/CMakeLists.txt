# Copyright (c) 2025 TAS
# All rights reserved

set(project_name tas_app)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)

set(sources
    ${sources_dir}/main.cpp
)

set(tas_executable tas)

add_executable(${tas_executable} ${sources})

target_link_libraries(${tas_executable} LINK_PUBLIC
    tas_module_instruction
    tas_module_decoder
    tas_module_parser
    tas_utils_getopt
)