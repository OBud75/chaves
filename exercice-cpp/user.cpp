#include "user.hpp"
#include <sqlite3.h>
#include <iostream>
#include <fstream>
#include <sstream>

User::User(int id, std::unique_ptr<Password> password_)
    : id(id), password(std::move(password_)), is_logged_in(false) {}

void User::save() {
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
                // Pour éviter d'avoir à gérer la mémoire, on préfère souvent renvoyer un smart pointer.
                // En fonction des cas, on peut penser à un vecteur/map contenant des User ou des unique_ptr<User>
                // Cela permet d'avoir un conteneur qui gère la mémoire automatiquement
                // puis de renvoyer une référence ou un pointeur vers l'élément souhaité
                // et ainsi de ne pas avoir à se soucier de la libération de la mémoire
                
                // std::vector<std::unique_ptr<User>> users;
                // users.push_back(std::make_unique<User>(id, std::move(password)));
                // return users.back();

                // Regardez également du côté de std::move pour utiliser les mêmes blocs mémoire des 2 cotés du return
            }
        }
    }

    db_file.close();
    throw std::runtime_error("Utilisateur non trouvé.");
};
