#pragma once
#include "raylib.h"

class Paleta
{
protected:
    float x, y;
    float latime, inaltime;
    int viteza;

    void LimitareaMiscarii();

public:
    float getx() const;
    float gety() const;
    float getlatime() const;
    float getinaltime() const;
    int getviteza() const;
    void setx(float X);
    void sety(float Y);
    void setlatime(float Latime);
    void setinaltime(float Inaltime);
    void setviteza(int Viteza);

    void Deseneaza();
    void Update();
    Paleta(float X, float Y, float Latime, float Inaltime, int Viteza);
};