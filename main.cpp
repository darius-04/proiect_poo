#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <ios>
#include "Artist.h"
#include "Album.h"
#include "Melodie.h"
#include "Recenzie.h"
#include "Exceptii.h"
#include "Topuri.h"
#include "SortStrategy.h"
#include "FactoryObiectMuzical.h"

template <typename T>
void afiseazaToateRecenziileColectie(const std::vector<std::shared_ptr<Recenzie<T>>>& recenzii)
{
    if (recenzii.empty())
    {
        std::cout << "Nu exista recenzii in colectie.\n";
        return;
    }
    std::cout << "\n--- Recenzii Colectie ---\n";
    for (const auto& recenzie : recenzii)
    {
        recenzie->afiseazaDetalii();
    }
    std::cout << "------------------------\n";
}

void afiseazaNumeAlbumSiArtist(const std::vector<std::shared_ptr<ObiectMuzical>>& colectie)
{
    std::cout << "\n--- Lista Albume si Artisti ---\n";
    for (const auto& obiect : colectie)
    {
        auto artist = std::dynamic_pointer_cast<Artist>(obiect);
        if (artist)
        {
            for (const auto& album : artist->getAlbume())
            {
                std::cout << "Album: " << album->getTitlu() << " de Artist: " << artist->getNume() << std::endl;
            }
        }
    }
    std::cout << "-------------------------------\n";
}

void afiseazaMeniu()
{
    std::cout << "\n--- Meniu Principal RYM ---" << std::endl;
    std::cout << "1. Afiseaza Top 5 Melodii (dupa nota medie)" << std::endl;
    std::cout << "2. Afiseaza Top 5 Albume (dupa rating)" << std::endl;
    std::cout << "3. Afiseaza Top 5 Artisti (dupa nota medie)" << std::endl;
    std::cout << "4. Afiseaza Top Albume dintr-un an specific" << std::endl;
    std::cout << "5. Afiseaza toti artistii" << std::endl;
    std::cout << "6. Afiseaza toate albumele" << std::endl;
    std::cout << "7. Afiseaza toate melodiile" << std::endl;
    std::cout << "8. Adauga recenzie pentru o melodie" << std::endl;
    std::cout << "9. Afiseaza Recenziile unei Melodii" << std::endl;
    std::cout << "10. Iesire" << std::endl;
    std::cout << "Alege o optiune: ";
}


template <typename T>
T citesteNumar(const std::string& mesaj)
{
    T valoare;
    std::cout << mesaj;
    while (!(std::cin >> valoare))
    {
        std::cout << "Intrare invalida. Va rugam introduceti un numar: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return valoare;
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::ifstream fisierIntrare("date.txt");
    if (!fisierIntrare.is_open())
    {
        std::cerr << "Eroare la deschiderea fisierului date.txt\n";
        return 1;
    }

    std::vector<std::shared_ptr<ObiectMuzical>> colectieObiecteMuzicale;

    try
    {
        int numarArtisti;
        fisierIntrare >> numarArtisti;

        for (int i = 0; i < numarArtisti; ++i)
        {
            std::string numeArtist;
            std::getline(fisierIntrare >> std::ws, numeArtist);
            auto artistCurent = std::make_shared<Artist>(numeArtist);

            int numarAlbume;
            fisierIntrare >> numarAlbume;
            for (int j = 0; j < numarAlbume; ++j)
            {
                std::string titluAlbum;
                int anLansare;
                fisierIntrare >> std::ws;
                std::getline(fisierIntrare, titluAlbum);
                fisierIntrare >> anLansare;
                auto albumCurent = std::make_shared<Album>(titluAlbum, anLansare);
                int numarMelodii;
                fisierIntrare >> numarMelodii;
                for (int k = 0; k < numarMelodii; ++k)
                {
                    std::string numeMelodie;
                    std::getline(fisierIntrare >> std::ws, numeMelodie);
                    FactoryMelodie factoryMelodie;
                    std::shared_ptr<ObiectMuzical> melodieCurenta_ptr = factoryMelodie.creeazaObiectMuzical("Melodie", numeMelodie);
                    std::shared_ptr<Melodie> melodieCurenta = std::dynamic_pointer_cast<Melodie>(melodieCurenta_ptr);
                    if (melodieCurenta)
                    {
                        albumCurent->adaugaMelodie(melodieCurenta);
                    }
                    else
                    {
                        std::cerr << "Eroare la crearea melodiei '" << numeMelodie << "' prin factory.\n";
                    }
                }
                artistCurent->adaugaAlbum(albumCurent);
            }
            colectieObiecteMuzicale.push_back(artistCurent);
        }
        fisierIntrare.close();
        for (auto& obiect : colectieObiecteMuzicale)
        {
            auto artist = std::dynamic_pointer_cast<Artist>(obiect);
            if (!artist) continue;
            for (const auto& album : artist->getAlbume())
            {
                for (auto& melodie : album->getMelodii())
                {
                    try
                    {
                        std::string comentariuGenerat = "Recenzie generata pentru melodia " + melodie->getNume();
                        double notaAleatorie = 1.0 + (rand() % 90) / 10.0;

                        auto recenzieNoua = std::make_shared<Recenzie<double>>(comentariuGenerat, notaAleatorie);
                        melodie->adaugaRecenzie(recenzieNoua);

                     /*   if (melodie->getNume() == "Runaway")
                        {
                            recenzieNoua->actualizeazaNota(9.9);
                        }
                        */
                    }
                    catch (const NotaInvalidaException& e)
                    {
                        std::cerr << "Eroare recenzie: " << e.what() << " la melodia " << melodie->getNume() << '\n';
                    }
                }
            }
        }
        int optiune;
        do
        {
            afiseazaMeniu();
            optiune = citesteNumar<int>("");

            switch (optiune)
            {
            case 1:
            {
                Topuri::topMelodii(colectieObiecteMuzicale, 5, std::make_shared<SortareMelodiiDupaNotaDescendent>());
                break;
            }
            case 2:
            {
                Topuri::topAlbume(colectieObiecteMuzicale, 5, std::make_shared<SortareAlbumeDupaRatingDescendent>());
                break;
            }
            case 3:
            {
                Topuri::topArtisti(colectieObiecteMuzicale, 5, std::make_shared<SortareArtistiDupaNotaMedieDescendent>());
                break;
            }
            case 4:
            {
                int an = citesteNumar<int>("Introduceti anul pentru topul albumelor: ");
                Topuri::topAlbumeDinAn(colectieObiecteMuzicale, an);
                break;
            }
            case 5:
            {
                std::cout << "\n--- Toti Artistii ---\n";
                for (const auto& obiect : colectieObiecteMuzicale)
                {
                    if (auto artist = std::dynamic_pointer_cast<Artist>(obiect))
                    {
                        artist->afiseazaDetalii();
                        std::cout << std::endl;
                    }
                }
                std::cout << "---------------------\n";
                break;
            }
            case 6:
            {
                std::cout << "\n--- Toate Albumele ---\n";
                for (const auto& obiect : colectieObiecteMuzicale)
                {
                    if (auto artist = std::dynamic_pointer_cast<Artist>(obiect))
                    {
                        for (const auto& album : artist->getAlbume())
                        {
                            std::cout << "   De la Artist: " << artist->getNume() << " - ";
                            album->afiseazaDetalii();
                            std::cout << std::endl;
                        }
                    }
                }
                std::cout << "----------------------\n";
                break;
            }
            case 7:
            {
                std::cout << "\n--- Toate Melodiile ---\n";
                for (const auto& obiect : colectieObiecteMuzicale)
                {
                    if (auto artist = std::dynamic_pointer_cast<Artist>(obiect))
                    {
                        for (const auto& album : artist->getAlbume())
                        {
                            for (const auto& melodie : album->getMelodii())
                            {
                                std::cout << "   De la Artist: " << artist->getNume()
                                          << ", Album: " << album->getTitlu() << " - ";
                                melodie->afiseazaDetalii();
                                std::cout << std::endl;
                            }
                        }
                    }
                }
                std::cout << "-----------------------\n";
                break;
            }
            case 8:
            {
                std::vector<std::shared_ptr<Melodie>> toateMelodiile;
                int indexMelodie = 1;
                std::cout << "\n--- Selecteaza o melodie pentru recenzie ---\n";
                for (const auto& obiect : colectieObiecteMuzicale)
                {
                    if (auto artist = std::dynamic_pointer_cast<Artist>(obiect))
                    {
                        for (const auto& album : artist->getAlbume())
                        {
                            for (const auto& melodie : album->getMelodii())
                            {
                                toateMelodiile.push_back(melodie);
                                std::cout << indexMelodie++ << ". " << melodie->getNume()
                                          << " (Album: " << album->getTitlu()
                                          << ", Artist: " << artist->getNume() << ")\n";
                            }
                        }
                    }
                }

                if (toateMelodiile.empty())
                {
                    std::cout << "Nu exista melodii la care sa adaugi recenzii.\n";
                    break;
                }

                int alegereMelodie = citesteNumar<int>("Introduce numarul melodiei: ");

                if (alegereMelodie < 1 || alegereMelodie > toateMelodiile.size())
                {
                    std::cout << "Selectie invalida. Melodia nu exista.\n";
                    break;
                }

                std::shared_ptr<Melodie> melodieSelectata = toateMelodiile[alegereMelodie - 1];

                std::string comentariu;
                double nota;

                std::cout << "Introdu comentariul (fara spatii): ";
                std::cin >> comentariu;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                nota = citesteNumar<double>("Introdu nota (intre 1.0 si 10.0): ");

                try
                {
                    auto recenzieNoua = std::make_shared<Recenzie<double>>(comentariu, nota);
                    melodieSelectata->adaugaRecenzie(recenzieNoua);
                    std::cout << "Recenzie adaugata cu succes pentru melodia " << melodieSelectata->getNume() << "!\n";
                }
                catch (const NotaInvalidaException& e)
                {
                    std::cerr << "Eroare la adaugarea recenziei: " << e.what() << '\n';
                }
                break;
            }
            case 9:   // Afiseaza Recenziile unei Melodii
            {
                std::vector<std::shared_ptr<Melodie>> toateMelodiile;
                int indexMelodie = 1;
                std::cout << "\n--- Selecteaza o melodie pentru a-i vedea recenziile ---\n";
                for (const auto& obiect : colectieObiecteMuzicale)
                {
                    if (auto artist = std::dynamic_pointer_cast<Artist>(obiect))
                    {
                        for (const auto& album : artist->getAlbume())
                        {
                            for (const auto& melodie : album->getMelodii())
                            {
                                toateMelodiile.push_back(melodie);
                                std::cout << indexMelodie++ << ". " << melodie->getNume()
                                          << " (Album: " << album->getTitlu()
                                          << ", Artist: " << artist->getNume() << ")\n";
                            }
                        }
                    }
                }

                if (toateMelodiile.empty())
                {
                    std::cout << "Nu exista melodii cu recenzii.\n";
                    break;
                }

                int alegereMelodie = citesteNumar<int>("Introduce numarul melodiei: ");

                if (alegereMelodie < 1 || alegereMelodie > toateMelodiile.size())
                {
                    std::cout << "Selectie invalida. Melodia nu exista.\n";
                    break;
                }

                std::shared_ptr<Melodie> melodieSelectata = toateMelodiile[alegereMelodie - 1];

                std::cout << "\n--- Recenzii pentru Melodia: " << melodieSelectata->getNume() << " ---\n";
                const auto& recenziiMelodie = melodieSelectata->getRecenzii();
                if (recenziiMelodie.empty())
                {
                    std::cout << "Melodia nu are recenzii.\n";
                }
                else
                {
                    for (const auto& recenzie : recenziiMelodie)
                    {
                        recenzie->afiseazaDetalii();
                    }
                }
                std::cout << "-------------------------------------------\n";
                break;
            }
            case 10:
            {
                std::cout << "Iesire din program\n";
                break;
            }
            default:
            {
                std::cout << "Optiune invalida. Va rugam incercati din nou.\n";
                break;
            }
            }
            std::cout << "\nEnter pentru a continua...";
            std::cin.get();
        }
        while (optiune != 10);

    }
    catch (const std::exception& e)
    {
        std::cerr << "Exceptie: " << e.what() << '\n';
    }

    return 0;
}
