cmake_minimum_required(VERSION 3.15.4)

cmake_policy(SET CMP0074 NEW)

project(TradingBot)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "Export compile commands")

option(BUILD_GTESTS "build libst google-test suite" ON)
option(DEBUG_SYMBOL "add debug information" ON)

message(STATUS "BUILD_GTESTS: ${BUILD_GTESTS}")
message(STATUS "DEBUG_SYMBOL: ${DEBUG_SYMBOL}")

if(DEBUG_SYMBOL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
endif()

option(USE_CLANG_TIDY "use clang-tidy" OFF)
option(LINT_AS_ERRORS "clang-tidy warnings as errors" OFF)

find_package(Boost REQUIRED)
if(Boost_FOUND)
  message(STATUS "Boost library found !!")
  include_directories(${Boost_INCLUDE_DIRS})
endif(Boost_FOUND)

find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
)
if(USE_CLANG_TIDY)
    if(CLANG_TIDY_EXE)
        set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}")
        if(LINT_AS_ERRORS)
            set(DO_CLANG_TIDY "${DO_CLANG_TIDY}" "-warnings-as-errors=*")
        endif()
        message(STATUS "use clang-tidy with DO_CLANG_TIDY: ${DO_CLANG_TIDY}")
    else()
        message(FATAL_ERROR "USE_CLANG_TIDY is on but clang-tidy is not found")
    endif()
else()
    message(STATUS "not use clang-tidy")
endif()

include_directories("include")

set(TRADING_BOT_HEADER
  include/option.hpp
)

string(REPLACE "include/" "${CMAKE_CURRENT_SOURCE_DIR}/include/"
       TRADING_BOT_HEADER "${TRADING_BOT_HEADER}"
)

# target_compile_options(
#     _libtb PRIVATE
#     #-Werror -Wall -Wextra
#     -Wno-unused-value # for PYBIND11_EXPAND_SIDE_EFFECTS in pybind11.h
#     -Wno-noexcept-type # GCC
# )
#
# if(CLANG_TIDY_EXE AND USE_CLANG_TIDY)
#     set_target_properties(
#         _libtb PROPERTIES
#         CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
#     )
# endif()

if(BUILD_GTESTS)
    add_subdirectory(gtests)
endif()

# vim: set ff=unix fenc=utf8 nobomb et sw=4 ts=4:
