#include "Artist.h"
#include "Exceptii.h"
#include <iostream>
#include <algorithm>

Artist::Artist(const std::string& nume) : nume(nume) {}

void Artist::adaugaAlbum(std::shared_ptr<Album> album)
{
    albume.push_back(album);
}

void Artist::afiseazaDetalii() const
{
    std::cout << "Artist: " << nume << std::endl;
    for (const auto& album : albume)
    {
        album->afiseazaDetalii();
    }
}

std::string Artist::getNume() const
{
    return nume;
}

const std::vector<std::shared_ptr<Album>>& Artist::getAlbume() const
{
    return albume;
}

std::shared_ptr<Artist> Artist::getArtistTop(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte)
{
    std::shared_ptr<Artist> artistTop = nullptr;
    double notaMax = -1;

    for (const auto& obiect : obiecte)
    {
        auto artist = std::dynamic_pointer_cast<Artist>(obiect);
        if (!artist) continue;

        double total = 0, cnt = 0;
        for (const auto& album : artist->getAlbume())
        {
            for (const auto& melodie : album->getMelodii())
            {
                double notaMedie = melodie->getNotaMedie();
                if (notaMedie > 0)
                {
                    total += notaMedie;
                    cnt++;
                }
            }
        }

        if (cnt > 0)
        {
            double mediaArtist = total / cnt;
            if (mediaArtist > notaMax)
            {
                notaMax = mediaArtist;
                artistTop = artist;
            }
        }
    }

    return artistTop;
}

void Artist::sortAlbume()
{
    std::sort(albume.begin(), albume.end(), [](const std::shared_ptr<Album>& a, const std::shared_ptr<Album>& b)
    {
        double totalA = 0, countA = 0;
        for (const auto& m : a->getMelodii())
        {
            double nota = m->getNotaMedie();
            if (nota > 0)
            {
                totalA += nota;
                countA++;
            }
        }
        double medieA = 0;
        if (countA > 0)
        {
            medieA = totalA / countA;
        }

        double totalB = 0, countB = 0;
        for (const auto& m : b->getMelodii())
        {
            double nota = m->getNotaMedie();
            if (nota > 0)
            {
                totalB += nota;
                countB++;
            }
        }
        double medieB = 0;
        if (countB > 0)
        {
            medieB = totalB / countB;
        }

        return medieA > medieB;
    });
}

std::shared_ptr<Melodie> Artist::cautaMelodieDupaNume(const std::string& numeMelodie)
{
    for (const auto& album : albume)
    {
        for (const auto& melodie : album->getMelodii())
        {
            if (melodie->getNume() == numeMelodie)
            {
                return melodie;
            }
        }
    }
    return nullptr;
}

void Artist::adaugaRecenzieArtist(std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, const std::string& numeArtist, const std::string& numeMelodie, const std::string& comentariu, double nota)
{
    for (auto& obiect : obiecte)
    {
        auto artist = std::dynamic_pointer_cast<Artist>(obiect);
        if (!artist || artist->getNume() != numeArtist)
            continue;

        for (auto& album : artist->albume)
        {
            for (auto& melodie : album->getMelodii())
            {
                if (melodie->getNume() == numeMelodie)
                {
                    try
                    {
                        auto recenzie = std::make_shared<Recenzie>(comentariu, nota);
                        melodie->adaugaRecenzie(recenzie);
                        std::cout << "Recenzie adaugata pentru \"" << numeMelodie << "\" la artistul \"" << numeArtist << "\".\n";
                        return;
                    }
                    catch (const NotaInvalidaException& e)
                    {
                        std::cerr << "Nota invalida: " << e.what() << '\n';
                        return;
                    }
                }
            }
        }

        std::cerr << "Melodia " << numeMelodie << " nu a fost gasita la artistul " << numeArtist << ".\n";
        return;
    }

    std::cerr << "Artistul " << numeArtist << " nu a fost gasit.\n";
}


std::shared_ptr<ObiectMuzical> Artist::clone() const
{
    return std::make_shared<Artist>(*this);
}
