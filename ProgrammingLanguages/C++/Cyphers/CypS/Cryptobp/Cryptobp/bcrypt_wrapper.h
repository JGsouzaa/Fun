#ifndef BCRYPT_WRAPPER_H
#define BCRYPT_WRAPPER_H

#include <string>
#include "bcrypt.h"

class BcryptWrapper {
public:
	// Gera um hash para a senha fornecida
	static std::string generateHash(const std::string& password, unsigned rounds = 10) {
		return bcrypt::generateHash(password, rounds);
	}

	// Valida a senha fornecida com o hash armazenado
	static bool validatePassword(const std::string& password, const std::string& hash) {
		return bcrypt::validatePassword(password, hash);
	}
};

#endif // BCRYPT_WRAPPER_H