# Copyright (c) 2025 TAS
# All rights reserved

set(project_name tas_module_decoder)

set(sources_dir ${CMAKE_CURRENT_LIST_DIR}/src)
set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(sources
    ${sources_dir}/decoder.cpp
)
set(headers
    ${headers_dir}/decoder.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${tas_dir})

target_link_libraries(${project_name} LINK_PUBLIC
    tas_module_instruction
)