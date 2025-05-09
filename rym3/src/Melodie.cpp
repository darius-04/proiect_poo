#include "Melodie.h"
#include <iostream>
#include <iomanip>

Melodie::Melodie(const std::string& nume) : nume(nume) {}

void Melodie::adaugaRecenzie(std::shared_ptr<Recenzie> recenzie)
{
    recenzii.push_back(recenzie);
}

void Melodie::afiseazaDetalii() const
{
    std::cout << "Melodie: " << nume << std::endl;
    for (const auto& recenzie : recenzii)
    {
        recenzie->afiseazaDetalii();
    }
    std::cout << "Nota medie: " << std::fixed << std::setprecision(2) << getNotaMedie() << std::endl;
}

double Melodie::getNotaMedie() const
{
    if (recenzii.empty()) return 0.0;
    double suma = 0;
    for (const auto& r : recenzii)
    {
        suma += r->getNota();
    }
    return suma / recenzii.size();
}

const std::vector<std::shared_ptr<Recenzie>>& Melodie::getRecenzii() const
{
    return recenzii;
}

std::shared_ptr<ObiectMuzical> Melodie::clone() const
{
    return std::make_shared<Melodie>(*this);
}

std::string Melodie::getNume() const
{
    return nume;
}
