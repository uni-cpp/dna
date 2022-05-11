#pragma once

#include "fake_stream.hpp"

#include <array>
#include <unordered_map>

enum class Chromosome : uint8_t
{
    CHROMOSOME_1,
    CHROMOSOME_2,
    CHROMOSOME_3,
    CHROMOSOME_4,
    CHROMOSOME_5,
    CHROMOSOME_6,
    CHROMOSOME_7,
    CHROMOSOME_8,
    CHROMOSOME_9,
    CHROMOSOME_10,
    CHROMOSOME_11,
    CHROMOSOME_12,
    CHROMOSOME_13,
    CHROMOSOME_14,
    CHROMOSOME_15,
    CHROMOSOME_16,
    CHROMOSOME_17,
    CHROMOSOME_18,
    CHROMOSOME_19,
    CHROMOSOME_20,
    CHROMOSOME_21,
    CHROMOSOME_22,
    CHROMOSOME_23_X,
    CHROMOSOME_23_Y,
};

constexpr std::initializer_list< Chromosome > ALL_CHROMOSOMES = { Chromosome::CHROMOSOME_1,  Chromosome::CHROMOSOME_2,  Chromosome::CHROMOSOME_3,    Chromosome::CHROMOSOME_4,
                                                                  Chromosome::CHROMOSOME_5,  Chromosome::CHROMOSOME_6,  Chromosome::CHROMOSOME_7,    Chromosome::CHROMOSOME_8,
                                                                  Chromosome::CHROMOSOME_9,  Chromosome::CHROMOSOME_10, Chromosome::CHROMOSOME_11,   Chromosome::CHROMOSOME_12,
                                                                  Chromosome::CHROMOSOME_13, Chromosome::CHROMOSOME_14, Chromosome::CHROMOSOME_15,   Chromosome::CHROMOSOME_16,
                                                                  Chromosome::CHROMOSOME_17, Chromosome::CHROMOSOME_18, Chromosome::CHROMOSOME_19,   Chromosome::CHROMOSOME_20,
                                                                  Chromosome::CHROMOSOME_21, Chromosome::CHROMOSOME_22, Chromosome::CHROMOSOME_23_X, Chromosome::CHROMOSOME_23_Y };

constexpr std::array< size_t, ALL_CHROMOSOMES.size( ) > BASE_PAIRS = { 247199719, 242751149, 199446827, 191263063, 180837866, 170896993, 158821424, 146274826,
                                                                       140442298, 135374737, 134452384, 132289534, 114127980, 106360585, 100338915, 88822254,
                                                                       78654742,  76117153,  63806651,  62435965,  46944323,  49528953,  154913754, 57741652 };

constexpr size_t CHROMOSOMES_COUNT{ 23U };
constexpr size_t SEX_CHROMOSOME_INDEX{ 22U };

// Started from 0 (based on existing test)
// constexpr size_t
// get_chromosome_index( Chromosome chrom )
//{
//    if( chrom == Chromosome::CHROMOSOME_23_Y )
//    {
//        return static_cast< size_t >( Chromosome::CHROMOSOME_23_X );
//    }

//    return static_cast< size_t >( chrom );
//}

// constexpr size_t
// get_chromosome_size( Chromosome chrom )
//{
//     return BASE_PAIRS[ static_cast< size_t >( chrom ) ];
// }

// constexpr bool
// is_sex_chromosome( Chromosome chrom )
//{
//     return chrom == Chromosome::CHROMOSOME_23_X || chrom == Chromosome::CHROMOSOME_23_Y;
// }

constexpr size_t DEFAULT_CHUNK_SIZE{ 512U };

class fake_person
{
    std::array< fake_stream, CHROMOSOMES_COUNT > chroms_{ };

public:
    template < typename T >
    explicit fake_person( const T& chromosome_data, size_t chunk_size = DEFAULT_CHUNK_SIZE )
    {
        if( chromosome_data.size( ) != chroms_.size( ) )
        {
            throw std::invalid_argument( "chromosome data does not match expected size" );
        }

        size_t index = 0;
        auto it = chromosome_data.cbegin( );
        for( ; index < chromosome_data.size( ) && it != chromosome_data.cend( ); ++index, ++it )
        {
            chroms_[ index ] = fake_stream( *it, chunk_size );
        }
    }

    [[nodiscard]] const fake_stream& chromosome( size_t chromosome_index ) const;

    [[nodiscard]] constexpr size_t
    chromosomes( ) const
    {
        return chroms_.size( );
    }
};
