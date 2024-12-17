#include "user.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    // Demande à l'utilisateur de saisir un mot de passe
    std::string raw_password;
    std::cout << "Saisir un mot de passe : ";
    std::cin >> raw_password;

    // Crée un mot de passe avec le mot de passe saisi
    auto password = std::make_unique<Password>(raw_password);

    std::cout << "Mot de passe chiffré : " << password->str() << std::endl;

    // Récupère les id existants en base de données afin d'incrémenter l'id
    std::ifstream db_file("users.db");
    int id = 0;
    std::string line;
    while (std::getline(db_file, line)) {
        std::istringstream line_stream(line);
        std::string token;
        if (std::getline(line_stream, token, '|')) {
            id = std::stoi(token);
        }
    }
    db_file.close();
    id++;

    // Crée un nouvel utilisateur avec le mot de passe
    User user(id, std::move(password));
    // Enregistre l'utilisateur
    user.save();

    // Récupère l'utilisateur
    User &retrieved_user = User::get(id);

    // Demande à l'utilisateur de saisir un mot de passe pour se connecter
    std::string raw_password2;
    std::cout << "Saisir un mot de passe pour se connecter : ";
    std::cin >> raw_password2;

    // Connecte l'utilisateur
    user.login(raw_password2.c_str());


    return 0;
};
