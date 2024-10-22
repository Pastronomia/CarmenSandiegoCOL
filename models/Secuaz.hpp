// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef SECUAZ_HPP
#define SECUAZ_HPP

#include <string>
#include <memory>
#include "Localidad.hpp" // Asegúrate de que esta clase esté definida

class Secuaz {
private:
    int id;
    std::string nombre;
    std::string habilidad;
    int peligrosidad;
    std::shared_ptr<Localidad> localidad;
    bool capturado;

public:
    // Constructor con parámetros
    Secuaz(int id, const std::string& nombre, const std::string& habilidad, int peligrosidad, std::shared_ptr<Localidad> localidad, bool capturado)
        : id(id), nombre(nombre), habilidad(habilidad), peligrosidad(peligrosidad), localidad(localidad), capturado(capturado) {}

    // Constructor por defecto
    Secuaz() : id(0), nombre(""), habilidad(""), peligrosidad(0), localidad(nullptr), capturado(false) {}

    // Getters
    int getId() const {
        return id;
    }

    std::string getNombre() const {
        return nombre;
    }

    std::string getHabilidad() const {
        return habilidad;
    }

    int getPeligrosidad() const {
        return peligrosidad;
    }

    std::shared_ptr<Localidad> getLocalidad() const {
        return localidad;
    }

    bool isCapturado() const {
        return capturado;
    }

    // Setters
    void setNombre(const std::string& nombre) {
        this->nombre = nombre;
    }

    void setHabilidad(const std::string& habilidad) {
        this->habilidad = habilidad;
    }

    void setPeligrosidad(int peligrosidad) {
        this->peligrosidad = peligrosidad;
    }

    void setLocalidad(std::shared_ptr<Localidad> localidad) {
        this->localidad = localidad;
    }

    void setCapturado(bool capturado) {
        this->capturado = capturado;
    }
};

#endif // SECUAZ_HPP

