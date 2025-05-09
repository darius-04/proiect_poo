#ifndef ARTIST_H
#define ARTIST_H

#include <string>
#include <vector>
#include <memory>
#include "Album.h"

class Artist : public ObiectMuzical {
private:
    std::string nume;
    std::vector<std::shared_ptr<Album>> albume;

public:
    Artist(const std::string& nume);
    void adaugaAlbum(std::shared_ptr<Album> album);
    void afiseazaDetalii() const override;
    std::string getNume() const;
    const std::vector<std::shared_ptr<Album>>& getAlbume() const;
    std::shared_ptr<ObiectMuzical> clone() const override;
    static std::shared_ptr<Artist> getArtistTop(const std::vector<std::shared_ptr<ObiectMuzical>>& obiecte);
    void sortAlbume();
    std::shared_ptr<Melodie> cautaMelodieDupaNume(const std::string& numeMelodie);
    static void adaugaRecenzieArtist(std::vector<std::shared_ptr<ObiectMuzical>>& obiecte, const std::string& numeArtist, const std::string& numeMelodie, const std::string& comentariu, double nota);
};

#endif
