#include <iostream>
#include <string>
#include "rsaKeys.h"
#include "rsaCrypt.h"
#include "uintwide_t.h"

using uint2048 = ::math::wide_integer::uintwide_t<2048U, std::uint32_t>;

void invalidArgs() {
	std::cerr << "invalid arguments, check --help\n";
}

// UX IS TOTALLY WRONG
int main(int argc, char* argv[]) {
	if (argc < 2) {
		invalidArgs();
		return 1;
	}

	std::string option = argv[1];

	if (option == "--help" or option == "-h") {
		std::cout << "IT'S SCHOOL PROJECT, NOT EVERYTHING IS IDEAL" << std::endl
			<< "Usage: " << argv[0] << " [OPTIONS] [VALUE]\n" << std::endl
			<< "\t-k, --keys\t\treturns public key, private key and n" << std::endl
			<< "\t-e, --encrypt\t\ttakes public key and n, returns encrypted value" << std::endl
			<< "\t-d, --decrypt\t\ttakes private key and n, returns decrypted value";

		return 0;
	}

	if (option == "--keys" or option == "-k") {
		auto keys = rsaKeys::getKeys();
		std::cout << "n value: " << std::endl << keys.privateK.n << std::endl << std::endl;
		std::cout << "public key: " << std::endl << keys.publicK.e << std::endl << std::endl;
		std::cout << "private key: " << std::endl << keys.privateK.d << std::endl << std::endl;

		return 0;
	}

	if (option == "--encrypt" or option == "-e") {
		if (argc < 4) {
			invalidArgs();
			return 1;
		}

		rsaKeys::publicKey pk;
		pk.e = argv[2];
		pk.n = argv[3];

		std::cout << "\nEncrypted value:\n";
		std::cout << rsaCrypt::encrypt(argv[4], pk) << std::endl;
		return 0;
	}

	if (option == "--decrypt" or option == "-d") {
		if (argc < 4) {
			invalidArgs();
			return 1;
		}

		rsaKeys::privateKey pk;
		pk.d = argv[2];
		pk.n = argv[3];

		std::cout << "\nDecrypted value:\n";
		std::cout << rsaCrypt::decrypt(argv[4], pk) << std::endl;

		return 0;
	}

	invalidArgs();
	return 1;
}