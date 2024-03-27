#include <iostream>
#include <string>

using namespace std;

class Vig {
public:
	string k;
	Vig(string k) {
		for (int i = 0; i < k.size(); ++i) {
			if (isalpha(k[i])) {
				this->k += toupper(k[i]);
			}
		}
	}

	string encryption(string t) {
		string output;
		for (int i = 0, j = 0; i < t.length(); ++i) {
			if (isalpha(t[i])) {
				char c = toupper(t[i]);
				output += (c + k[j] - 2 * 'A') % 26 + 'A';
				j = (j + 1) % k.length();
			}
			else {
				output += t[i]; // Preserve the non-alphabetic character
			}
		}
		return output;
	}

	string decryption(string t) {
		string output;
		for (int i = 0, j = 0; i < t.length(); ++i) {
			if (isalpha(t[i])) {
				char c = toupper(t[i]);
				output += (c - k[j] + 26) % 26 + 'A';
				j = (j + 1) % k.length();
			}
			else {
				output += t[i]; // Preserve the non-alphabetic character
			}
		}
		return output;
	}
};

int main() {
	Vig v("WELCOME");
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