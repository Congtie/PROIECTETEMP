#pragma once
#include "paleta.h"

class PaletaCpu : public Paleta
{
public:
    void Update(int minge_y);
    PaletaCpu(float X, float Y, float Latime, float Inaltime, int Viteza);
};