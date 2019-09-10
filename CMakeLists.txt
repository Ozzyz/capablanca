cmake_minimum_required(VERSION 3.12)
project(capablanca)
set(CMAKE_CXX_STANDARD 14)

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()



file(GLOB all_SRCs
        "${PROJECT_SOURCE_DIR}/src/board/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/board/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/communication/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/communication/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/evaluation/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/evaluation/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/hashing/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/hashing/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/utils/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/utils/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/*.cpp"
        )

file(GLOB all_SRCs_TEST
        "${PROJECT_SOURCE_DIR}/src/board/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/board/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/communication/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/communication/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/evaluation/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/evaluation/*.cpp"
        "${PROJECT_SOURCE_DIR}/tests/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/hashing/*.hpp"
        "${PROJECT_SOURCE_DIR}/src/hashing/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/utils/*.cpp"
        "${PROJECT_SOURCE_DIR}/src/utils/*.hpp"
        )

enable_testing()
add_executable(capablanca ${all_SRCs})
add_executable(capablanca_test ${all_SRCs_TEST} tests/ucitest.cpp tests/board_moves_test.cpp tests/generate_moves_test.cpp tests/castling_test.cpp tests/board_evaluation_test.cpp)
# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(capablanca_test gtest_main)
add_test(UnitTests capablanca_test)
include_directories(${PROJECT_SOURCE_DIR}/src)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/.travis/cmake)
