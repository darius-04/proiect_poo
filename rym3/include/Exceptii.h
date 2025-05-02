#ifndef EXCEPTII_H
#define EXCEPTII_H

#include <exception>
#include <string>

class MuzicaException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Eroare generala in muzica";
    }
};

class NotaInvalidaException : public MuzicaException {
public:
    const char* what() const noexcept override {
        return "Nota invalida! Trebuie sa fie intre 1 si 10.";
    }
};

class FisierInvalidException : public MuzicaException {
public:
    const char* what() const noexcept override {
        return "Fisier invalid!";
    }
};

#endif
