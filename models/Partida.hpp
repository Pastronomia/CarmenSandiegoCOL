// Cabecera añadida automáticamente por torquemada.py
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm.h>
#ifndef PARTIDA_HPP
#define PARTIDA_HPP

#include <string>

class Partida {
public:
    Partida(int id, int usuarioId, int secuazId, const std::string& estado, int intentos);

    int getId() const;
    int getUsuarioId() const;
    int getSecuazId() const;
    std::string getEstado() const;
    int getIntentos() const;

    void setUsuarioId(int usuarioId);
    void setSecuazId(int secuazId);
    void setEstado(const std::string& estado);
    void setIntentos(int intentos);

private:
    int id;
    int usuarioId;
    int secuazId;
    std::string estado;
    int intentos;
};

#endif // PARTIDA_HPP

