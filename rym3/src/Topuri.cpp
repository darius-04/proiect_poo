#include "Topuri.h"
#include "Album.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void Topuri::topMelodii(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int topN)
{
    std::vector<std::shared_ptr<Melodie>> melodii;

    for (const auto& obiect : obiecte)
    {
        auto artist = std::dynamic_pointer_cast<Artist>(obiect);
        if (!artist) continue;

        for (const auto& album : artist->getAlbume())
        {
            for (const auto& melodie : album->getMelodii())
            {
                melodii.push_back(melodie);
            }
        }
    }

    std::sort(melodii.begin(), melodii.end(), [](const auto& a, const auto& b)
    {
        return a->getNotaMedie() > b->getNotaMedie();
    });

    std::cout << "\nTop " << topN << " Melodii:\n";
    for (int i = 0; i < std::min(topN, (int)melodii.size()); ++i)
    {
        std::cout << i + 1 << ". " << melodii[i]->getNume() << " - Nota medie: " << melodii[i]->getNotaMedie() << "\n";
    }
}

void Topuri::topAlbume(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int topN)
{
    struct AlbumScor
    {
        std::shared_ptr<Album> album;
        double notaMedie;
    };

    std::vector<AlbumScor> albume;

    for (const auto& obiect : obiecte)
    {
        auto artist = std::dynamic_pointer_cast<Artist>(obiect);
        if (!artist) continue;

        for (const auto& album : artist->getAlbume())
        {
            double total = 0, count = 0;
            for (const auto& melodie : album->getMelodii())
            {
                double nota = melodie->getNotaMedie();
                if (nota > 0)
                {
                    total += nota;
                    count++;
                }
            }
            double medie = 0;
            if (count > 0)
            {
                medie = total / count;
            }
            albume.push_back({album, medie});
        }
    }

    std::sort(albume.begin(), albume.end(), [](const auto& a, const auto& b)
    {
        return a.notaMedie > b.notaMedie;
    });

    std::cout << "\nTop " << topN << " Albume:\n";
    for (int i = 0; i < std::min(topN, (int)albume.size()); ++i)
    {
        std::cout << i + 1 << ". " << albume[i].album->getTitlu() << " - Nota medie: " << albume[i].notaMedie << "\n";
    }
}

void Topuri::topArtisti(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int topN)
{
    struct ArtistScorat
    {
        std::shared_ptr<Artist> artist;
        double notaMedie;
    };

    std::vector<ArtistScorat> artisti;

    for (const auto& obiect : obiecte)
    {
        auto artist = std::dynamic_pointer_cast<Artist>(obiect);
        if (!artist) continue;

        double total = 0, count = 0;
        for (const auto& album : artist->getAlbume())
        {
            for (const auto& melodie : album->getMelodii())
            {
                double nota = melodie->getNotaMedie();
                if (nota > 0)
                {
                    total += nota;
                    count++;
                }
            }
        }
        if (count > 0)
            artisti.push_back({artist, total / count});
    }

    std::sort(artisti.begin(), artisti.end(), [](const auto& a, const auto& b)
    {
        return a.notaMedie > b.notaMedie;
    });

    std::cout << "\nTop " << topN << " Artisti:\n";
    for (int i = 0; i < std::min(topN, (int)artisti.size()); ++i)
    {
        std::cout << i + 1 << ". " << artisti[i].artist->getNume() << " - Nota medie: " << artisti[i].notaMedie << "\n";
    }

}

void Topuri::topAlbumeDinAn(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, int an)
{
    std::vector<std::shared_ptr<Album>> albumeDinAn;
    for (const auto& obiect : obiecte)
    {
        auto artist = std::dynamic_pointer_cast<Artist>(obiect);
        if (!artist) continue;

        for (const auto& album : artist->getAlbume())
        {
            if (album->getAnLansare() == an)
            {
                albumeDinAn.push_back(album);
            }
        }
    }

    if (albumeDinAn.empty())
    {
        std::cout << "\nNu există albume din anul " << an << ".\n";
        return;
    }

    std::sort(albumeDinAn.begin(), albumeDinAn.end(), [](const std::shared_ptr<Album>& a, const std::shared_ptr<Album>& b)
    {
        double notaMedieA = 0, notaMedieB = 0;
        int totalRecenziiA = 0, totalRecenziiB = 0;

        for (const auto& melodie : a->getMelodii())
        {
            for (const auto& recenzie : melodie->getRecenzii())
            {
                notaMedieA += recenzie->getNota();
                totalRecenziiA++;
            }
        }
        if (totalRecenziiA > 0)
            notaMedieA /= totalRecenziiA;

        for (const auto& melodie : b->getMelodii())
        {
            for (const auto& recenzie : melodie->getRecenzii())
            {
                notaMedieB += recenzie->getNota();
                totalRecenziiB++;
            }
        }
        if (totalRecenziiB > 0)
            notaMedieB /= totalRecenziiB;


        return notaMedieA > notaMedieB;
    });

    std::cout << "\nTop albume din anul " << an << ":\n";
    for (size_t i = 0; i < albumeDinAn.size(); ++i)
    {
        double notaMedie = 0.0;
        int totalRecenzii = 0;

        for (const auto& melodie : albumeDinAn[i]->getMelodii())
        {
            for (const auto& recenzie : melodie->getRecenzii())
            {
                notaMedie += recenzie->getNota();
                totalRecenzii++;
            }
        }

        if (totalRecenzii > 0)
            notaMedie /= totalRecenzii;

        std::cout << i + 1 << ". " << albumeDinAn[i]->getTitlu() << " - Nota medie: " << notaMedie << "\n";
    }
}
