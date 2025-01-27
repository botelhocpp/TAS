# Copyright (c) 2025 TAS
# All rights reserved

cmake_minimum_required(VERSION ${CMAKE_VERSION})

project("Simple MIPS Assembler" C CXX)

set(tas_dir ${PROJECT_SOURCE_DIR})

add_subdirectory(${tas_dir}/app)
add_subdirectory(${tas_dir}/module)
add_subdirectory(${tas_dir}/utils)
