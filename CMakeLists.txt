project( cog-dna )

set( HEADERS
    "include/dna/base.hpp"
    "include/dna/person.hpp"
    "include/dna/sequence_buffer.hpp"
)

set( SOURCES
)

set( ADDITIONAL_FILES
    "README.md"
)

treat_all_warnings_as_errors()

add_library(cog-dna INTERFACE
    ${HEADERS}
    ${SOURCES}
    ${ADDITIONAL_FILES}
)

target_include_directories( cog-dna
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install( TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# The trailing slash is important
install( DIRECTORY ${CMAKE_INSTALL_INCLUDEDIR}/
         DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

add_subdirectory( test )

if( CODE_COVERAGE )
    generate_coverage( ${PROJECT_NAME} ${PROJECT_NAME}-unittests)

    install( DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/${COVERAGE_OUTPUT_DIR_NAME}/
             DESTINATION ${CMAKE_INSTALL_DOCDIR}/uni/cog-dna
    )
endif( )
