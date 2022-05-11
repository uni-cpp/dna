#include "fake_stream.hpp"

fake_stream::fake_stream( const fake_stream& other )
    : data_( other.data_ )
    , chunk_size_( other.chunk_size_ )
    , offset_( other.offset_.load( ) )
{
}

fake_stream::fake_stream( fake_stream&& other ) noexcept
    : data_( std::move( other.data_ ) )
    , chunk_size_( other.chunk_size_ )
    , offset_( other.offset_.exchange( 0 ) )
{
}

fake_stream::fake_stream( std::vector< std::byte > data, std::size_t chunksize )
    : data_( std::move( data ) )
    , chunk_size_( chunksize )
    , offset_( 0 )
{
}

fake_stream&
fake_stream::operator=( const fake_stream& other )
{
    if( this == &other )
    {
        return *this;
    }

    chunk_size_ = other.chunk_size_;
    data_ = other.data_;
    offset_ = other.offset_.load( );

    return *this;
}

fake_stream&
fake_stream::operator=( fake_stream&& other ) noexcept
{
    chunk_size_ = other.chunk_size_;
    data_ = std::move( other.data_ );
    offset_ = other.offset_.exchange( 0 );

    return *this;
}

void
fake_stream::seek( size_t offset )
{
    offset_.store( std::min( offset, data_.size( ) ) );
}

size_t
fake_stream::size( ) const
{
    return data_.size( );
}

dna::sequence_buffer< fake_stream::byte_view >
fake_stream::read( )
{
    auto offset = offset_.load( std::memory_order_consume );
    while( true )
    {
        auto len = std::min( chunk_size_, data_.size( ) - offset_ );
        if( len == 0 )
        {
            return byte_view( nullptr, 0 );
        }

        if( offset_.compare_exchange_weak( offset, offset + len, std::memory_order_release ) )
        {
            return byte_view( data_.data( ) + offset, len );
        }
    }
}
