#include <iostream>
#include <string>
#include <cctype> // Inclua este cabeçalho para usar as funções isalpha e toupper

using namespace std;

class Vig {
public:
	string k;
	Vig(string k) {
		for (int i = 0; i < k.size(); ++i) {
			if (isalpha(k[i])) {
				this->k += toupper(k[i]); // Converte a chave para maiúsculas
			}
		}
	}

	string encryption(string t) {
		string output;
		for (int i = 0, j = 0; i < t.length(); ++i) {
			if (isalpha(t[i])) {
				char c = t[i];
				// Converte para maiúsculas apenas para a criptografia
				output += (toupper(c) + toupper(k[j]) - 2 * 'A') % 26 + (isupper(c) ? 'A' : 'a');
				j = (j + 1) % k.length();
			}
			else {
				output += t[i]; // Preserva o caractere não alfabético
			}
		}
		return output;
	}

	string decryption(string t) {
		string output;
		for (int i = 0, j = 0; i < t.length(); ++i) {
			if (isalpha(t[i])) {
				char c = t[i];
				// Converte para maiúsculas apenas para a descriptografia
				output += (toupper(c) - toupper(k[j]) + 26) % 26 + (isupper(c) ? 'A' : 'a');
				j = (j + 1) % k.length();
			}
			else {
				output += t[i]; // Preserva o caractere não alfabético
			}
		}
		return output;
	}
};

int main() {
	string key;
	cout << "Enter the key: ";
	getline(cin, key);
	Vig v(key); // Corrigido para passar a chave para o construtor
	string emessage;
	string encrypt;
	string decrypt;
	string dmessage;
	char condition;

	cout << "Original Message: ";
	getline(cin, emessage);
	encrypt = v.encryption(emessage);
	cout << "Encrypted Message: " << encrypt << endl;

	cout << "Do you want to decrypt a message? (\"Y/N\") ";
	cin >> condition;
	cin.ignore();

	if (condition == 'Y' || condition == 'y') {
		cout << "Message to decrypt: ";
		getline(cin, dmessage);
		decrypt = v.decryption(dmessage);
		cout << "Decrypted Message: " << decrypt << endl;
	}
	else if (condition == 'N' || condition == 'n') {
		cout << "End of program." << endl;
	}
	else {
		cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
	}
}
