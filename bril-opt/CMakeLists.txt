cmake_minimum_required(VERSION 3.10)

PROJECT(bril-opt)

set(SOURCE_FILES_OPT src/opt.cc src/opt_internal.cc)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

add_executable(bril-opt ${SOURCE_FILES_OPT})
target_include_directories(bril-opt PUBLIC
                           "${PROJECT_SOURCE_DIR}/include"
                           "${PROJECT_SOURCE_DIR}/json/include")
set_target_properties(bril-opt PROPERTIES LINKER_LANGUAGE CXX)

install(TARGETS bril-opt DESTINATION ${CMAKE_INSTALL_PREFIX})