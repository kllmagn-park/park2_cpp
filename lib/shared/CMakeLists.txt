set(SOURCES src/libshared.c)
set(HEADERS include/count.h)

add_library(libshared SHARED ${SOURCES})
target_link_libraries(libshared $<BUILD_INTERFACE:libcount>)

install(TARGETS libshared EXPORT libshared_Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)

install(FILES ${HEADERS} DESTINATION include)
install(EXPORT libshared_Targets
        FILE libsharedConfig.cmake
        NAMESPACE LIBSHARED::
        DESTINATION lib/cmake/LIBSHARED)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
