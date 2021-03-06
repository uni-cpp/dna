#pragma once

#include "base.hpp"

#include <concepts>
#include <cstddef>

namespace dna
{

template < typename T >
concept ByteBuffer = requires( T a )
{
    {
        a.size( )
        } -> std::same_as< size_t >;
    {
        a[ 0 ]
        } -> std::convertible_to< std::byte >;
};

template < ByteBuffer T >
class sequence_buffer;

template < ByteBuffer T >
class sequence_buffer_iterator
{
    const sequence_buffer< T >* buf_{ nullptr };
    size_t index_{ 0U };

public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = base;
    using difference_type = long;

    constexpr sequence_buffer_iterator( ) noexcept = default;

    constexpr sequence_buffer_iterator( const sequence_buffer< T >* buffer, size_t index = 0 ) noexcept
        : buf_( buffer )
        , index_( index )
    {
    }

    constexpr sequence_buffer_iterator( const sequence_buffer_iterator& other ) noexcept
        : buf_( other.buf_ )
        , index_( other.index_ )
    {
    }

    constexpr sequence_buffer_iterator&
    operator=( const sequence_buffer_iterator& other ) noexcept
    {
        if( this != &other )
        {
            buf_ = other.buf_;
            index_ = other.index_;
        }

        return *this;
    }

    constexpr value_type operator*( ) const;

    constexpr sequence_buffer_iterator&
    operator++( ) noexcept
    {
        ++index_;
        return *this;
    }

    constexpr sequence_buffer_iterator
    operator++( int ) noexcept
    {
        sequence_buffer_iterator result = *this;
        ++index_;
        return result;
    }

    constexpr sequence_buffer_iterator&
    operator+=( size_t diff ) noexcept
    {
        index_ += diff;
        return *this;
    }

    constexpr sequence_buffer_iterator
    operator+( size_t diff ) const noexcept
    {
        return sequence_buffer_iterator( buf_, index_ + diff );
    }

    constexpr sequence_buffer_iterator&
    operator--( ) noexcept
    {
        --index_;
        return *this;
    }

    constexpr sequence_buffer_iterator
    operator--( int ) noexcept
    {
        sequence_buffer_iterator result = *this;
        --index_;
        return result;
    }

    constexpr int64_t
    operator-( const sequence_buffer_iterator& other ) const noexcept
    {
        return static_cast< int64_t >( index_ - other.index_ );
    }

    constexpr sequence_buffer_iterator&
    operator-=( size_t diff ) noexcept
    {
        index_ -= diff;
        return *this;
    }

    constexpr sequence_buffer_iterator
    operator-( size_t diff ) const noexcept
    {
        return sequence_buffer_iterator( buf_, index_ - diff );
    }

    constexpr bool
    operator==( const sequence_buffer_iterator& other ) const noexcept
    {
        return buf_ == other.buf_ && index_ == other.index_;
    }

    constexpr bool
    operator!=( const sequence_buffer_iterator& other ) noexcept
    {
        return !operator==( other );
    }
};

template < ByteBuffer T >
class sequence_buffer
{
    T buffer_;
    size_t size_{ 0U };

public:
    using iterator = sequence_buffer_iterator< T >;

    constexpr sequence_buffer( T buffer, size_t size = 0 )
        : buffer_( std::forward< T >( buffer ) )
        , size_( size )
    {
        if( size_ == 0 )
        {
            size_ = static_cast< size_t >( buffer_.size( ) * packed_size::value );
        }
    }

    constexpr base
    at( size_t index ) const
    {
        auto byte_offset = index / packed_size::value;
        auto tuple_idx = index - ( byte_offset * packed_size::value );

        return unpack( buffer_[ byte_offset ] )[ tuple_idx ];
    }

    constexpr base
    operator[]( size_t index ) const
    {
        return at( index );
    }

    constexpr size_t
    size( ) const noexcept
    {
        return size_;
    }

    constexpr iterator
    begin( ) const noexcept
    {
        return iterator( this, 0 );
    }

    constexpr iterator
    end( ) const noexcept
    {
        return iterator( this, size_ );
    }

    constexpr const T&
    buffer( ) const noexcept
    {
        return buffer_;
    }

    constexpr T&
    buffer( ) noexcept
    {
        buffer_;
    }
};


template < ByteBuffer T >
constexpr typename sequence_buffer_iterator< T >::value_type
sequence_buffer_iterator< T >::operator*( ) const
{
    if( buf_ != nullptr )
    {
        return buf_->at( index_ );
    }
    return A;
}

template < ByteBuffer T >
std::ostream&
operator<<( std::ostream& os, const sequence_buffer< T >& buf )
{
    for( auto i : buf )
    {
        os << i;
    }
    return os;
}

}  // namespace dna
