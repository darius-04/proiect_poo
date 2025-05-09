#ifndef ALBUM_H
#define ALBUM_H

#include <string>
#include <vector>
#include <memory>
#include "Melodie.h"

class Album : public ObiectMuzical {
private:
    std::string titlu;
    std::vector<std::shared_ptr<Melodie>> melodii;
    int anLansare;

public:
    Album(const std::string& titlu, int anLansare);
    void adaugaMelodie(std::shared_ptr<Melodie> melodie);
    void afiseazaDetalii() const override;
    std::shared_ptr<ObiectMuzical> clone() const override;
    std::string getTitlu() const;
    int getAnLansare() const;
    const std::vector<std::shared_ptr<Melodie>>& getMelodii() const;
};

#endif
