// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef MISION_HPP
#define MISION_HPP

#include <string>

class Mision {
public:
    Mision(int id, const std::string& titulo, const std::string& descripcion, const std::string& objetivo, bool completada);

    int getId() const;
    std::string getTitulo() const;
    std::string getDescripcion() const;
    std::string getObjetivo() const;
    bool isCompletada() const;

    void setTitulo(const std::string& titulo);
    void setDescripcion(const std::string& descripcion);
    void setObjetivo(const std::string& objetivo);
    void setCompletada(bool completada);

private:
    int id;
    std::string titulo;
    std::string descripcion;
    std::string objetivo;
    bool completada;
};

#endif // MISION_HPP

