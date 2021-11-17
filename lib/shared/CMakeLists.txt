add_library(libshared src/libshared.c)

target_include_directories(libshared PUBLIC include)
target_link_libraries(libshared libcount pthread)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
