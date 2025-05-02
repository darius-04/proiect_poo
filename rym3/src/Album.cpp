#include "Album.h"
#include <iostream>

Album::Album(const std::string& titlu) : titlu(titlu) {}

void Album::adaugaMelodie(std::shared_ptr<Melodie> melodie) {
    melodii.push_back(melodie);
}

void Album::afiseazaDetalii() const {
    std::cout << "Album: " << titlu << std::endl;
    for (const auto& melodie : melodii) {
        melodie->afiseazaDetalii();
    }
}

std::shared_ptr<ObiectMuzical> Album::clone() const {
    return std::make_shared<Album>(*this);
}

const std::vector<std::shared_ptr<Melodie>>& Album::getMelodii() const {
    return melodii;
}

std::string Album::getTitlu() const {
    return titlu;
}
