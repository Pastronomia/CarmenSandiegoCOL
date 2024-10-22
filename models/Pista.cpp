#include <sqlite3.h>
#include <iostream>
#include <string>

class Pistas {
public:
    Pistas() {
        sqlite3_open(DB_PATH, &db);
    }

    ~Pistas() {
        sqlite3_close(db);
    }

    void mostrarPistas() {
        const char* sql = "SELECT pista1, pista2, pista3 FROM pistas WHERE secuaz_id = ?1";
        sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

        // Lógica para elegir pistas y mostrar al usuario
    }

private:
    sqlite3* db;
    sqlite3_stmt* stmt;
};
