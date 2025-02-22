# Copyright (c) 2025 TAS
# All rights reserved

set(project_name tas_utils_exprtk)

set(headers_dir ${CMAKE_CURRENT_LIST_DIR}/include)

set(headers
    ${headers_dir}/exprtk.hpp
)

add_library(${project_name} STATIC ${sources} ${headers})

set_target_properties(${project_name} PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
)

target_include_directories(${project_name} PUBLIC ${tas_dir})
