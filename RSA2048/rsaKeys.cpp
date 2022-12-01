// std includes
#include <cstdint>
#include <random>
#include <chrono>
#include <utility>
#include <iostream>

// project includes
#include "rsaKeys.h"

// external libaries
#include "uintwide_t.h"

#define PRINT(x) std::cout<<#x<<": "<<x<<std::endl;

using uint512 = ::math::wide_integer::uintwide_t<512U, std::uint32_t>;
using uint1024 = ::math::wide_integer::uintwide_t<1024U, std::uint32_t>;
using uint2048 = ::math::wide_integer::uintwide_t<2048U, std::uint32_t>;
using uint4096 = ::math::wide_integer::uintwide_t<4096U, std::uint32_t>;
using int2048 = math::wide_integer::int2048_t;

using random_engine = std::mt19937;
using distribution = ::math::wide_integer::uniform_int_distribution<1024U, std::uint32_t>;

template<typename IntegralTimePointType,
    typename ClockType = std::chrono::high_resolution_clock>
    auto time_point() -> IntegralTimePointType
{
    using local_integral_time_point_type = IntegralTimePointType;
    using local_clock_type = ClockType;

    const auto current_now =
        static_cast<std::uintmax_t>
        (
            std::chrono::duration_cast<std::chrono::nanoseconds>
            (
                local_clock_type::now().time_since_epoch()
                ).count()
            );

    return static_cast<local_integral_time_point_type>(current_now);
}


uint1024 getBigPrime() {
    random_engine generator(time_point<typename random_engine::result_type>());
    distribution d;

    uint1024 prime;

    while (true) {
        prime = d(generator);
        if (math::wide_integer::miller_rabin(prime, 25U, d, generator)) {
            return prime;
        }
    }
}

uint2048 getCoprime(uint2048 n) {
    random_engine generator(time_point<typename random_engine::result_type>());
    distribution d;

    uint2048 candidate;
    while (true) {
        candidate = d(generator);

        if (math::wide_integer::gcd(n, candidate) == 1)
            return candidate;
    }
}

// https://www.geeksforgeeks.org/multiplicative-inverse-under-modulo-m/
int2048 modInverse(int2048 A, int2048 M) {
    int2048 m0 = M;
    int2048 y = 0;
    int2048 x = 1;

    if (M == 1)
        return 0;

    while (A > 1) {
        int2048 q = A / M;
        int2048 t = M;

        M = A % M;
        A = t;
        t = y;

        y = x - q * y;
        x = t;
    }

    if (x < 0)
        x += m0;

    return x;
}

namespace rsaKeys {

    rsaKeys getKeys() {
        uint1024 p = getBigPrime();
        uint1024 q = getBigPrime();

        uint2048 n = p; n *= q;  // can't p*q 'cause of overflow
        uint2048 euler_n = (p - 1); euler_n *= (q - 1);
        
        uint2048 e = getCoprime(euler_n);
        uint2048 d = modInverse((int2048)e, (int2048)euler_n);
        return { {n,e},{n,d} };
    }

}  // namespace rsaKeys