add_subdirectory(libcount)

if (BUILD_SHARED)
    add_subdirectory(shared)
else()
    add_subdirectory(static)
endif()