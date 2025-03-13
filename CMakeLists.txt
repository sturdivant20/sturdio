cmake_minimum_required(VERSION 3.6)
project(sturdio)

string(ASCII 27 Esc)
set(Reset       "${Esc}[m")
set(Bold        "${Esc}[1m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")
set(Magenta     "${Esc}[35m")
set(Cyan        "${Esc}[36m")
set(White       "${Esc}[37m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")
set(BoldBlue    "${Esc}[1;34m")
set(BoldMagenta "${Esc}[1;35m")
set(BoldCyan    "${Esc}[1;36m")
set(BoldWhite   "${Esc}[1;37m")

# --- Version Control ---
set(STURDIO_MAJOR_VERSION 0)
set(STURDIO_MINOR_VERSION 0)
set(STURDIO_PATCH_VERSION 1)
set(PROJECT_VERSION ${STURDIO_MAJOR_VERSION}.${STURDIO_MINOR_VERSION}.${STURDIO_PATCH_VERSION})
message(STATUS "${BoldCyan}${PROJECT_NAME} version ${PROJECT_VERSION}${Reset}")

# --- Compiler Flags ---
# set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_FLAGS "-Wall -Wextra")
# set(CMAKE_CXX_FLAGS_DEBUG "-g -W")
# # set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Ofast -ffast-math -fomit-frame-pointer -fstrict-aliasing -flto -DNDEBUG -march=native")
# set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Ofast -ffast-math")

# --- Add Dependencies ---
# find_package(spdlog REQUIRED)

set(STURDIO_HDRS
    include/sturdio/binary-file.hpp
    include/sturdio/io-tools.hpp
    include/sturdio/yaml-parser.hpp
)

set(STURDIO_SRCS
    src/binary-file.cpp
    src/io-tools.cpp
    src/yaml-parser.cpp
)

# --- Create the C++ Library ---
add_library(${PROJECT_NAME} ${STURDIO_HDRS} ${STURDIO_SRCS})
target_include_directories(
    ${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${Eigen3_INCLUDE_DIRS}>
    $<INSTALL_INTERFACE:${Eigen3_INCLUDE_DIRS}>
)
target_link_libraries(
    ${PROJECT_NAME} PUBLIC
    # spdlog::spdlog
)

# --- Add Executables ---
if (NOT DEFINED INSTALL_STURDIO_TESTS OR NOT INSTALL_STURDIO_TESTS)
else()
    file(GLOB testfiles "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")
    foreach(file ${testfiles})
        message(${file})
        get_filename_component(testname ${file} NAME_WE)
        add_executable(${testname} ${file})
        target_link_libraries( ${testname} PUBLIC ${PROJECT_NAME})
    endforeach(file ${testfiles})
endif()

# --- Make Library 'Findable' for other CMake Packages ---
include(CMakePackageConfigHelpers)

install(
    DIRECTORY include/ 
    DESTINATION include
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    INCLUDES DESTINATION include
)

export(
    TARGETS ${PROJECT_NAME} 
    FILE ${PROJECT_NAME}Targets.cmake
)

install(
    EXPORT ${PROJECT_NAME}Targets 
    FILE ${PROJECT_NAME}Targets.cmake 
    DESTINATION lib/cmake/${PROJECT_NAME}
)

configure_package_config_file(
    "${PROJECT_NAME}-config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    INSTALL_DESTINATION lib/cmake/${PROJECT_NAME}
    PATH_VARS PROJECT_NAME
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    DESTINATION lib/cmake/${PROJECT_NAME}
)