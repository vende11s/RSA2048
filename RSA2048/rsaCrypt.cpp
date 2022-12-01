#include "rsaCrypt.h"
#include "uintwide_t.h"

using uint2048 = ::math::wide_integer::uintwide_t<2048U, std::uint32_t>;

namespace rsaCrypt {
	uint2048 encrypt(uint2048 to_encrypt, rsaKeys::publicKey key) {
		return math::wide_integer::powm(to_encrypt, key.e, key.n);
	}

	uint2048 decrypt(uint2048 to_decrypt, rsaKeys::privateKey key) {
		return math::wide_integer::powm(to_decrypt, key.d, key.n);
	}
}  // namespace rsaCrypt

