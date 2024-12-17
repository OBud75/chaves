#include "user.hpp"
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <sstream>

User::User(int id, std::unique_ptr<Password> password_)
    : id(id), password(std::move(password_)), is_logged_in(false) {}

void User::save() {
    // In a file (or DB)
    // id | password (hashed)

    // Sauvegarde dans un fichier "users.db" (simple simulation d'une base de données)
    std::ofstream db_file("users.db", std::ios::app);
    if (!db_file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier de base de données." << std::endl;
        return;
    }

    db_file << id << "|" << password->str() << "\n";
    db_file.close();
    std::cout << "Utilisateur enregistré avec succès." << std::endl;
};

int User::login(const char *raw_password) {
    // Compare raw_password with password in DB
    // for user with id this.id
    // is_logged_in = true; // If passwords match

    Password input_password(raw_password);
    if (*password == input_password) {
        is_logged_in = true;
        std::cout << "Connexion réussie !" << std::endl;
        return 0; // Succès
    } else {
        std::cerr << "Mot de passe incorrect." << std::endl;
        return 1; // Échec
    }
};

User& User::get(int id) {
    std::ifstream db_file("users.db");
    if (!db_file.is_open()) {
        throw std::runtime_error("Erreur : Impossible d'ouvrir le fichier de base de données.");
    }

    std::string line;
    while (std::getline(db_file, line)) {
        std::istringstream line_stream(line);
        std::string token;
        int stored_id;
        std::string stored_password;

        if (std::getline(line_stream, token, '|')) {
            stored_id = std::stoi(token); // Convertit la chaîne en entier
        }
        if (std::getline(line_stream, stored_password)) {
            if (stored_id == id) {
                db_file.close();
                Password password(stored_password, true);
                auto user = new User(id, std::make_unique<Password>(password));
                
                return *user;
            }
        }
    }

    db_file.close();
    throw std::runtime_error("Utilisateur non trouvé.");
};
