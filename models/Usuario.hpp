// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <string>

class Usuario {
public:
    Usuario(int id, const std::string& nombre, const std::string& apellido, const std::string& contrasena, const std::string& rango, int capturas, const std::string& progreso);

    int getId() const;
    std::string getNombre() const;
    std::string getApellido() const;
    std::string getContrasena() const;
    std::string getRango() const;
    int getCapturas() const;
    std::string getProgreso() const;

    void setNombre(const std::string& nombre);
    void setApellido(const std::string& apellido);
    void setContrasena(const std::string& contrasena);
    void setRango(const std::string& rango);
    void setCapturas(int capturas);
    void setProgreso(const std::string& progreso);

private:
    int id;
    std::string nombre;
    std::string apellido;
    std::string contrasena;
    std::string rango;
    int capturas;
    std::string progreso;
};

#endif // USUARIO_HPP


