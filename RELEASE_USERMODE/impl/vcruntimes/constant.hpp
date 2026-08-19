#pragma once

typedef std::uint32_t hash_t;

namespace constant {

    static constexpr hash_t basis = 14695981039346656037ull;
    static constexpr hash_t prime = 1099511628211ull;

    inline hash_t hash_rt( const char* str ) {
        hash_t hash = basis;
        while ( *str ) {
            hash ^= static_cast< hash_t >( *str );
            hash *= prime;
            ++str;
        }
        return hash;
    }

}

#define RHASH(s) constant::hash_rt(s)
#define HASH_EQUAL(hash, str) (hash == str)