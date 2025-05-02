#ifndef OBIECTMUZICAL_H
#define OBIECTMUZICAL_H

#include <memory>
#include <string>
#include <iostream>

class ObiectMuzical {
public:
    virtual ~ObiectMuzical() = default;

    virtual void afiseazaDetalii() const = 0;
    virtual std::shared_ptr<ObiectMuzical> clone() const = 0;
};

#endif
