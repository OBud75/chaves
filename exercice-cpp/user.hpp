#include <memory>
#include "password.hpp"

class Password;

class User {
    private:
        int id;
        std::unique_ptr<Password> password;
        bool is_logged_in;

    public:
        explicit User(int id, std::unique_ptr<Password> password);
        void save();
        int login(const char *raw_password);
        static User &get(int id);
};
