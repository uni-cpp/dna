project( cog-dna-unittests )

set( HEADERS
)

set( SOURCES
    "dna/main.cpp"

    "dna/fake_person.hpp"
    "dna/fake_person.cpp"
    "dna/fake_stream.hpp"
    "dna/fake_stream.cpp"

    "dna/fake_stream_test.cpp"
    "dna/sequence_buffer_test.cpp"
)

treat_all_warnings_as_errors()

add_executable( ${PROJECT_NAME}
    ${HEADERS}
    ${SOURCES}
)

target_include_directories( ${PROJECT_NAME}
   PRIVATE
        ${SOURCE_DIR}/dna/include/
        ${SOURCE_DIR}/common/include/
)

target_link_libraries( ${PROJECT_NAME}
    PRIVATE
        cog-dna
        catch2
)

if( CODE_COVERAGE )
    add_custom_target( ${PROJECT_NAME}_run ALL
                        ${PROJECT_NAME}
                        DEPENDS ${PROJECT_NAME}
                        VERBATIM
                        USES_TERMINAL )
endif( )

install( TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
