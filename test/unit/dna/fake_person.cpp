#include "fake_person.hpp"

const fake_stream&
fake_person::chromosome( std::size_t chromosome_index ) const
{
    if( chromosome_index >= chroms_.size( ) )
    {
        throw std::invalid_argument( "index is out of range for the number of chromosomes available" );
    }

    return chroms_[ chromosome_index ];
}
