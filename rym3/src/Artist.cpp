#include "Artist.h"
#include <iostream>

Artist::Artist(const std::string& nume) : nume(nume) {}

void Artist::adaugaAlbum(std::shared_ptr<Album> album) {
    albume.push_back(album);
}

void Artist::afiseazaDetalii() const {
    std::cout << "Artist: " << nume << std::endl;
    for (const auto& album : albume) {
        album->afiseazaDetalii();
    }
}

const std::vector<std::shared_ptr<Album>>& Artist::getAlbume() const {
    return albume;
}

std::shared_ptr<ObiectMuzical> Artist::clone() const {
    return std::make_shared<Artist>(*this);
}
