#ifndef MELODIE_H
#define MELODIE_H

#include <string>
#include <vector>
#include <memory>
#include "Recenzie.h"

class Melodie : public ObiectMuzical
{
private:
    std::string nume;
    std::vector<std::shared_ptr<Recenzie>> recenzii;

public:
    Melodie(const std::string& nume);
    void adaugaRecenzie(std::shared_ptr<Recenzie> recenzie);
    void afiseazaDetalii() const override;
    std::shared_ptr<ObiectMuzical> clone() const override;
    const std::vector<std::shared_ptr<Recenzie>>& getRecenzii() const;
    std::string getNume() const;
    double getNotaMedie() const;
};

#endif
