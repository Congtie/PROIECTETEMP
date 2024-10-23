#include "particulaUrma.h"

particulaUrma::particulaUrma(Vector2 poz, Color cul, float timp) : pozitie(poz), culoare(cul), timpViata(timp) {}

void particulaUrma::Deseneaza() const
{
    DrawCircle(pozitie.x, pozitie.y, 3, culoare);
}

void particulaUrma::Update(float timpDelta)
{
    timpViata -= timpDelta;
}

bool particulaUrma::EsteVie() const
{
    return timpViata > 0;
}