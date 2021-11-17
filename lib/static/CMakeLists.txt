add_library(libstatic src/libstatic.c)

target_include_directories(libstatic PUBLIC include)
target_link_libraries(libstatic libcount)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
