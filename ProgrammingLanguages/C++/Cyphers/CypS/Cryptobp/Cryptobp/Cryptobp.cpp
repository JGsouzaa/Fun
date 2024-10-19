#include <iostream>
#include <string>
#include <algorithm>
#include <cryptlib.h>
#include <osrng.h>
#include <sha.h>
#include <hex.h>
#include <filters.h>
/*#include <bcrypt_wrapper.h>*/

void generateSHA256(const std::string& input) {
	CryptoPP::SHA256 hash;
	std::string digest;

	CryptoPP::StringSource(input, true,
		new CryptoPP::HashFilter(hash,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(digest)
			)
		)
	);

	std::transform(digest.begin(), digest.end(), digest.begin(), ::tolower);
	std::cout << "Hash SHA-256: " << digest << std::endl;
}

/*void generateBcrypt(const std::string& input) {
	std::string hash = bcrypt::generateHash(input);
	std::cout << "Hash bcrypt: " << hash << std::endl;
}*/

int main() {
	std::string input;
	char choice;
	bool continueHashing = true;

	while (continueHashing) {
		std::cout << "Digite a string para gerar o hash: ";
		std::getline(std::cin, input);

		std::cout << "Escolha o algoritmo de hash (1 para SHA-256, 2 para bcrypt): ";
		std::cin >> choice;
		std::cin.ignore(); // Limpar o buffer de entrada

		if (choice == '1') {
			generateSHA256(input);
		}
		else if (choice == '2') {
			/*generateBcrypt(input);*/
		}
		else {
			std::cout << "Escolha inválida!" << std::endl;
		}

		std::cout << "Deseja gerar um novo hash? (s/n): ";
		std::cin >> choice;
		std::cin.ignore(); // Limpar o buffer de entrada

		if (choice == 'n' || choice == 'N') {
			continueHashing = false;
		}
	}

	return 0;
}