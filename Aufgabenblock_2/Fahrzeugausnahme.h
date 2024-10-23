#ifndef FAHRZEUGAUSNAHME_H
#define FAHRZEUGAUSNAHME_H

#include <exception>
#include <iostream>
#include <string>

class Fahrzeug;
class Weg;

class Fahrzeugausnahme : public std::exception {
protected:
  Fahrzeug &p_Fahrzeug;
  const Weg &p_Weg;

public:
  Fahrzeugausnahme(Fahrzeug &fzg, const Weg &weg);

  virtual void vBearbeiten() const = 0;
};

class Losfahren : public Fahrzeugausnahme {
public:
  Losfahren(Fahrzeug &fzg, const Weg &weg) : Fahrzeugausnahme(fzg, weg) {}

  void vBearbeiten() const override;
};

class Streckenende : public Fahrzeugausnahme {
public:
  Streckenende(Fahrzeug &fzg, const Weg &weg) : Fahrzeugausnahme(fzg, weg) {}

  void vBearbeiten() const override;
};

#endif // FAHRZEUGAUSNAHME_H