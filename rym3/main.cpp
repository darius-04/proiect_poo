#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Artist.h"
#include "Album.h"
#include "Melodie.h"
#include "Recenzie.h"
#include "Exceptii.h"
#include "Topuri.h"

int main()
{
    std::ifstream in("date.txt");
    if (!in.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului\n";
        return 1;
    }

    try
    {
        int nArtisti;
        in >> nArtisti;
        std::vector<std::shared_ptr<ObiectMuzical>> obiecte;

        for (int i = 0; i < nArtisti; ++i)
        {
            std::string numeArtist;
            std::getline(in >> std::ws, numeArtist);
            auto artist = std::make_shared<Artist>(numeArtist);

            int nrAlbume;
            in >> nrAlbume;
            for (int j = 0; j < nrAlbume; ++j)
            {
                std::string titluAlbum;
                int anLansare;
                in >> std::ws;
                std::getline(in, titluAlbum);
                in >> anLansare;
                auto album = std::make_shared<Album>(titluAlbum, anLansare);
                int nrMelodii;
                in >> nrMelodii;
                for (int k = 0; k < nrMelodii; ++k)
                {
                    std::string numeMelodie;
                    std::getline(in >> std::ws, numeMelodie);
                    auto melodie = std::make_shared<Melodie>(numeMelodie);
                    album->adaugaMelodie(melodie);
                }

                artist->adaugaAlbum(album);
            }

            obiecte.push_back(artist);
        }
        Artist::adaugaRecenzieArtist(obiecte, "Future", "712PM", "Super piesa!", 9.6);
        Artist::adaugaRecenzieArtist(obiecte, "Futur", "712PM", "Super piesa!", 9.6);
        Artist::adaugaRecenzieArtist(obiecte, "Future", "71PM", "Super piesa!", 9.6);

        Artist::adaugaRecenzieArtist(obiecte, "Kanye West", "Runaway", "Cea mai buna", 10);
        for (auto& obiect : obiecte)
        {
            auto artist = std::dynamic_pointer_cast<Artist>(obiect);
            if (!artist) continue;
            for (const auto& album : artist->getAlbume())
            {
                for (const auto& melodie : album->getMelodii())
                {
                    try
                    {
                        std::string comentariu = "Recenzie pentru melodia " + melodie->getNume() + "\n";
                        double nota = 5.0 + (rand() % 50) / 10.0;
                        auto recenzie = std::make_shared<Recenzie>(comentariu, nota);
                        melodie->adaugaRecenzie(recenzie);
                    }
                    catch (const NotaInvalidaException& e)
                    {
                        std::cerr << "Eroare recenzie: " << e.what() << " la melodia " << melodie->getNume() << '\n';
                    }
                }
            }
        }

        for (const auto& obiect : obiecte)
        {
            obiect->afiseazaDetalii();
            std::cout << "-----------------------------\n";
        }
        auto artistTop = Artist::getArtistTop(obiecte);
        if (artistTop)
        {
            std::cout << "Artistul cel mai bine cotat este: " << artistTop->getNume() << '\n';
        }
        else
        {
            std::cout << "Nu s-a gasit niciun artist cu recenzii.\n";
        }

        for (auto& obiect : obiecte)
        {
            auto artist = std::dynamic_pointer_cast<Artist>(obiect);
            if (artist)
            {
                artist->sortAlbume();
            }
        }
        Topuri::topMelodii(obiecte, 10);
        Topuri::topAlbume(obiecte, 10);
        Topuri::topArtisti(obiecte, 10);
        Topuri::topAlbumeDinAn(obiecte, 2022);
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exceptie: " << e.what() << '\n';
    }

    return 0;
}
