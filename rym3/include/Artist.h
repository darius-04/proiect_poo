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
    const std::vector<std::shared_ptr<Album>>& getAlbume() const;
    std::shared_ptr<ObiectMuzical> clone() const override;
};

#endif
