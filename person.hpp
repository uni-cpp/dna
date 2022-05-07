#pragma once

#include "sequence_buffer.hpp"

namespace dna
{

template < typename T >
concept HelixStream = requires( T a )
{
    { a.seek( 1000L ) };
    {
        a.read( )
        } -> sequence_buffer< ByteBuffer >;
    {
        a.size( )
        } -> std::convertible_to< std::size_t >;
};

template < HelixStream T >
concept Person = requires( T a )
{
    {
        a.chromosome( 1 )
        } -> HelixStream;
    {
        a.chromosomes( )
        } -> std::convertible_to< std::size_t >;
};

}  // namespace dna
