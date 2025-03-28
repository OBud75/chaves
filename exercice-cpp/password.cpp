#include "password.hpp"

Password::Password(const std::string &password, bool is_encrypted):
	_raw_value(password) {
        if (is_encrypted) {
            _encrypted_value = password;
        } else {
            encrypt(password);
        };
};
void Password::encrypt(const std::string &password) {
        const int shift = 3; // Décalage pour le chiffrement César
    _encrypted_value = password; 

    for (auto &ch : _encrypted_value) {
        if (std::isalpha(ch)) { // Si c'est une lettre
            if (std::isupper(ch)) {
                ch = 'A' + (ch - 'A' + shift) % 26;
            } else {
                ch = 'a' + (ch - 'a' + shift) % 26;
            }
        }
    }
};
std::string Password::str() const {
	return _encrypted_value;
}
bool Password::operator==(const std::string &str) const {
    return str == _encrypted_value;
}
bool Password::operator==(const Password &other) const {
    return _encrypted_value == other._encrypted_value;
}
std::ostream &operator<<(std::ostream &os, const Password &p) {
    os << p._encrypted_value;
    return os;
}
