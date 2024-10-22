#ifndef PISTA_HPP
#define PISTA_HPP

#include <string>

class Pista {
    int id;
    int localidadId;
    int numero;
    std::string descripcion;
    bool correcta;

public:
    Pista() : id(0), localidadId(0), numero(0), descripcion(""), correcta(false) {}

    Pista(int id, int localidadId, int numero, const std::string& descripcion, bool correcta)
        : id(id), localidadId(localidadId), numero(numero), descripcion(descripcion), correcta(correcta) {}

    int getId() const { return id; }
    int getLocalidadId() const { return localidadId; }
    int getNumero() const { return numero; }
    std::string getDescripcion() const { return descripcion; }
    bool esCorrecta() const { return correcta; }

    void setLocalidadId(int localidadId) { this->localidadId = localidadId; }
    void setNumero(int numero) { this->numero = numero; }
    void setDescripcion(const std::string& descripcion) { this->descripcion = descripcion; }
    void setEsCorrecta(bool correcta) { this->correcta = correcta; }
};

#endif // PISTA_HPP
