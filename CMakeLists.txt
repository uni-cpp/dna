project( cog-dna )

set( HEADERS
    "base.hpp"
    "person.hpp"
    "sequence_buffer.hpp"
)

set( SOURCES
)

add_library(cogdna INTERFACE
    ${HEADERS}
    ${SOURCES}
)

target_include_directories( cogdna INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

#add_subdirectory( test )
