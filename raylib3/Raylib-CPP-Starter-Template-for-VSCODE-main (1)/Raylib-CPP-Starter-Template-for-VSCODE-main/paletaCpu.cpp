#include "paletaCpu.h"

void PaletaCpu::Update(int minge_y)
{
    if (gety() + getinaltime() / 2 > minge_y)
        y -= viteza;
    if (gety() + getinaltime() / 2 < minge_y)
        y += viteza;
    LimitareaMiscarii();
}

PaletaCpu::PaletaCpu(float X, float Y, float Latime, float Inaltime, int Viteza) : Paleta(X, Y, Latime, Inaltime, Viteza) {}