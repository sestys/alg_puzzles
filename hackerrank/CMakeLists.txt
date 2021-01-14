cmake_minimum_required(VERSION 3.8)
project(Optiver)

# ------------------------- Compilation flags ----------------------------------

# Some explanation of flags is in COMPILATION_NOTES.md

set(CMAKE_CXX_STANDARD 14)
#set(COMPILE_FLAGS_WARNINGS "-Wall -Wextra -Wshadow \
#                            -Wstrict-aliasing -pedantic -Werror")
# todo: make sure the code passes also other diagnostics
#                            -fmax-errors=5 -Wunreachable-code -Wcast-align \
#                            -Wcast-qual -Wctor-dtor-privacy \
#                            -Wdisabled-optimization -Wformat=2 \
#                            -Winit-self -Wlogical-op -Wmissing-include-dirs \
#                            -Wnoexcept -Wold-style-cast -Woverloaded-virtual \
#                            -Wredundant-decls -Wsign-promo -Wstrict-null-sentinel \
#                            -Wstrict-overflow=5 -Wswitch-default \
#                            -Wno-unused -Wno-variadic-macros -Wno-parentheses \
#                            -fdiagnostics-show-option")

# Note: -ffast-math can cause different outcomes of tests
#       for sampling algorithms if we use GCC or CLANG,
#       observed in test OOS::CheckExploitabilityInSmallDomain
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} \
                            -std=c++03 -m64 -O3 \
                            -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} \
                            -std=c++03 -m64 -O0 \
                            -g -fsanitize=address \
                            ${COMPILE_FLAGS_WARNINGS}")




# ------------------------- Build type (i.e Debug/Release) ---------------------

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' "
            " as none was previously specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING
            "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
else()
    message(STATUS "Using build type '${CMAKE_BUILD_TYPE}'.")
endif ()

ADD_CUSTOM_TARGET(Debug
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
        COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
        )

ADD_CUSTOM_TARGET(Release
        COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
        COMMENT "Switch CMAKE_BUILD_TYPE to Release"
        )

# ------------------------------ Executables -----------------------------------

# main
add_executable(shapes shapes.cpp)

add_executable(royalNames royalNames.cpp)

add_executable(carpenter carpenter.cpp)

add_executable(carpenter_old carpenter_old.cpp)

add_executable(royalNames_old royalNames_old.cpp)
