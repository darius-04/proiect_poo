#include "Melodie.h"
#include <iostream>

Melodie::Melodie(const std::string& nume) : nume(nume) {}

void Melodie::adaugaRecenzie(std::shared_ptr<Recenzie> recenzie) {
    recenzii.push_back(recenzie);
}

void Melodie::afiseazaDetalii() const {
    std::cout << "Melodie: " << nume << std::endl;
    for (const auto& recenzie : recenzii) {
        recenzie->afiseazaDetalii();
    }
}

std::shared_ptr<ObiectMuzical> Melodie::clone() const {
    return std::make_shared<Melodie>(*this);
}

std::string Melodie::getNume() const {
    return nume;
}
