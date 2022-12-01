#pragma once
#include "uintwide_t.h"

using uint2048 = ::math::wide_integer::uintwide_t<2048U, std::uint32_t>;

namespace rsaKeys{
	struct publicKey {
		uint2048 n;
		uint2048 e;
	};

	struct privateKey {
		uint2048 n;
		uint2048 d;
	};

	struct rsaKeys {
		publicKey publicK;
		privateKey privateK;
	};


	rsaKeys getKeys();

} // namespace rsaKeys




