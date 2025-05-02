#include "Recenzie.h"
#include "Exceptii.h"
#include <stdexcept>

Recenzie::Recenzie(const std::string& comentariu, double nota) : comentariu(comentariu), nota(nota) {
    if (nota < 1.0 || nota > 10.0) {
        throw NotaInvalidaException();
    }
}

Recenzie::Recenzie(const Recenzie& other) : comentariu(other.comentariu), nota(other.nota) {}

Recenzie& Recenzie::operator=(Recenzie other) {
    swap(*this, other);
    return *this;
}

void swap(Recenzie& first, Recenzie& second) {
    std::swap(first.comentariu, second.comentariu);
    std::swap(first.nota, second.nota);
}

double Recenzie::getNota() const {
    return nota;
}

void Recenzie::afiseazaDetalii() const {
    std::cout << "Nota: " << nota << ", Comentariu: " << comentariu << std::endl;
}

std::shared_ptr<ObiectMuzical> Recenzie::clone() const {
    return std::make_shared<Recenzie>(*this);
}
