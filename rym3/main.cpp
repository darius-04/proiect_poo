#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include "Artist.h"
#include "Album.h"
#include "Melodie.h"
#include "Recenzie.h"
#include "Exceptii.h"

int main() {
    std::ifstream in("date.txt");
    if (!in.is_open()) {
        std::cerr << "Eroare la deschiderea fisierului date.txt\n";
        return 1;
    }

    try {
        int nArtisti;
        in >> nArtisti;
        std::vector<std::shared_ptr<ObiectMuzical>> obiecte;

        for (int i = 0; i < nArtisti; ++i) {
            std::string numeArtist;
            std::getline(in >> std::ws, numeArtist);
            auto artist = std::make_shared<Artist>(numeArtist);

            int nrAlbume;
            in >> nrAlbume;
            for (int j = 0; j < nrAlbume; ++j) {
                std::string titluAlbum;
                std::getline(in >> std::ws, titluAlbum);
                auto album = std::make_shared<Album>(titluAlbum);

                int nrMelodii;
                in >> nrMelodii;
                for (int k = 0; k < nrMelodii; ++k) {
                    std::string numeMelodie;
                    std::getline(in >> std::ws, numeMelodie);
                    auto melodie = std::make_shared<Melodie>(numeMelodie);

                    album->adaugaMelodie(melodie);
                }

                artist->adaugaAlbum(album);
            }

            obiecte.push_back(artist);
        }

        for (auto& obiect : obiecte) {
            auto artist = std::dynamic_pointer_cast<Artist>(obiect);
            if (!artist) continue;

            for (const auto& album : artist->getAlbume()) {
                for (const auto& melodie : album->getMelodii()) {
                    try {
                        std::string comentariu = "Recenzie pentru " + melodie->getNume() + "\n";
                        double nota = 7.0 + (rand() % 30) / 10.0;
                        auto recenzie = std::make_shared<Recenzie>(comentariu, nota);
                        melodie->adaugaRecenzie(recenzie);
                    } catch (const NotaInvalidaException& e) {
                        std::cerr << "Eroare recenzie: " << e.what() << " la melodia " << melodie->getNume() << '\n';
                    }
                }
            }
        }

        for (const auto& obiect : obiecte) {
            obiect->afiseazaDetalii();
            std::cout << "-----------------------------\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Exceptie: " << e.what() << '\n';
    }

    return 0;
}
