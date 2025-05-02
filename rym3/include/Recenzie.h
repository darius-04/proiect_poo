#ifndef RECENZIE_H
#define RECENZIE_H

#include <string>
#include <memory>
#include <iostream>
#include "ObiectMuzical.h"

class Recenzie : public ObiectMuzical {
private:
    std::string comentariu;
    double nota;

public:
    Recenzie(const std::string& comentariu, double nota);
    Recenzie(const Recenzie& other);
    Recenzie& operator=(Recenzie other);

    double getNota() const;
    void afiseazaDetalii() const override;
    std::shared_ptr<ObiectMuzical> clone() const override;

    friend void swap(Recenzie& first, Recenzie& second);
};

#endif
