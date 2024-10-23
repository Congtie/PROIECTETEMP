#pragma once
#include "raylib.h"

class particulaUrma
{
private:
    Vector2 pozitie;
    Color culoare;
    float timpViata;

public:
    particulaUrma(Vector2 poz, Color cul, float timp);

    void Deseneaza() const;
    void Update(float timpDelta);
    bool EsteVie() const;
};