add_library(libcount STATIC src/libcount.c)

target_include_directories(libcount PUBLIC include)

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()