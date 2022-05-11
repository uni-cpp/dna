#pragma once

#include <dna/sequence_buffer.hpp>

#include <atomic>
#include <cstddef>
#include <string_view>
#include <vector>

namespace detail
{

class binary_traits
{
public:
    using char_type = std::byte;

    static std::size_t
    length( const std::byte* /* len */ )
    {
        throw std::logic_error( "length of a binary string can't be determined. It must be explicitly supplied" );
    }
};

}  // namespace detail

class fake_stream
{
    std::vector< std::byte > data_{ };
    size_t chunk_size_{ 1U };
    mutable std::atomic< size_t > offset_{ 0U };

public:
    using byte_view = std::basic_string_view< std::byte, detail::binary_traits >;

    fake_stream( ) = default;
    fake_stream( const fake_stream& other );
    fake_stream( fake_stream&& other ) noexcept;
    fake_stream( std::vector< std::byte > data, std::size_t chunksize );

    fake_stream& operator=( const fake_stream& other );
    fake_stream& operator=( fake_stream&& other ) noexcept;

    void seek( size_t offset ) const;
    [[nodiscard]] size_t size( ) const;
    [[nodiscard]] dna::sequence_buffer< byte_view > read( ) const;
};
