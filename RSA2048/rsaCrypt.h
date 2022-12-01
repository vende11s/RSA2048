#pragma once
#include "rsaKeys.h"
#include "uintwide_t.h"

using uint2048 = ::math::wide_integer::uintwide_t<2048U, std::uint32_t>;

namespace rsaCrypt {
	uint2048 encrypt(uint2048 to_encrypt, rsaKeys::publicKey key);
	uint2048 decrypt(uint2048 to_decrypt, rsaKeys::privateKey key);
}  // namespace rsaCrypt 