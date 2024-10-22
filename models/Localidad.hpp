// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef LOCALIDAD_HPP
#define LOCALIDAD_HPP

#include <string>

class Localidad {
public:
    // Constructor por defecto
    Localidad() : id(0), nombre(""), descripcion(""), latitud(0.0), longitud(0.0) {}

    // Constructor con parámetros
    Localidad(int id, const std::string& nombre, const std::string& descripcion, double latitud, double longitud);

    // Getters
    int getId() const;
    const std::string& getNombre() const;
    const std::string& getDescripcion() const;
    double getLatitud() const;
    double getLongitud() const;

    // Setters
    void setNombre(const std::string& nombre);
    void setDescripcion(const std::string& descripcion);
    void setLatitud(double latitud);
    void setLongitud(double longitud);

    // Sobrecarga del operador ==
    bool operator==(const Localidad& other) const;

private:
    int id;
    std::string nombre;
    std::string descripcion;
    double latitud;
    double longitud;
};

#endif // LOCALIDAD_HPP

