#ifndef DATABASE_HANDLER_HPP
#define DATABASE_HANDLER_HPP

#include <string>

class DatabaseHandler {
public:
    DatabaseHandler(const std::string& db_path);
    bool autenticar_usuario(const std::string& username, const std::string& password);

private:
    std::string db_path;
};

#endif
