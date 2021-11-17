cmake_minimum_required(VERSION 3.20)
project(C_DZ2)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX STANDARD 14)

add_compile_options(-Wall -Wextra -pedantic)

if (CMAKE_BUILD_TYPE=Release)
    add_compile_options(-O3)
elseif(CMAKE_BUILD_TYPE=Debug)
    add_compile_options(-g)
endif()

if (COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

if (ANALYSERS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    if(BUILD_STATIC)
        file(
                GLOB ALL_SOURCE_FILES
                src/main.c
                lib/static/src/*.c
                lib/static/include/*.c
                lib/libcount/src/*.c
                lib/libcount/include/*.c
        )
    else()
        file(
                GLOB ALL_SOURCE_FILES
                src/main.c
                lib/shared/src/*.c
                lib/shared/include/*.c
                lib/libcount/src/*.c
                lib/libcount/include/*.c
        )
    endif()

    add_custom_target(
            analysers

            COMMAND echo ------------------------------------- clang-format -------------------------------------
            COMMAND clang-format
            -style=Google
            -i
            ${ALL_SOURCE_FILES}
            COMMAND echo  done: clang-format

            COMMAND echo --------------------------------------- cppcheck ---------------------------------------
            COMMAND cppcheck
            --language=c
            --inconclusive
            --enable=all
            ${ALL_SOURCE_FILES}
            COMMAND echo  done: cppcheck

            COMMAND echo -------------------------------------- clang-tidy --------------------------------------
            COMMAND clang-tidy
            -p .
            ${ALL_SOURCE_FILES}
            --checks=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
            COMMAND echo  done: clang-tidy

            COMMAND echo -------------------------------------- scan-build --------------------------------------
            COMMAND scan-build make

            COMMAND echo ---------------------------------------- infer -----------------------------------------
            COMMAND infer run --compilation-database ./compile_commands.json

            #        COMMAND echo ---------------------------------------- cpplint ---------------------------------------
            #        COMMAND python3 -m cpplint
            #        ${ALL_SOURCE_FILES}
    )
endif()

if (WPADDED)
    add_compile_options(-Wpadded)
endif()

if (TESTS OR SANITIZERS OR COVERAGE OR VALGRIND)
    find_package(GTest REQUIRED)
    enable_testing()
    set(BUILD_TESTS 1)
endif()

if (BUILD_LIB)
    set(BUILD_SHARED 1)
else()
    add_executable(main src/main.c)
endif()

add_subdirectory(lib)

if (BUILD_SHARED AND NOT BUILD_LIB)
    find_package(libshared CONFIG REQUIRED)
    target_link_libraries(main LIBSHARED::libshared)
elseif(NOT BUILD_LIB)
    target_link_libraries(main libstatic)
endif()