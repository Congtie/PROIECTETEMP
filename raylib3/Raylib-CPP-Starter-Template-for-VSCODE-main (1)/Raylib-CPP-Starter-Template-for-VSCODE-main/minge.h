#pragma once
#include <vector>
#include <memory>
#include "particulaUrma.h"

class Minge
{
private:
    float x, y;
    int viteza_x, viteza_y;
    int raza;
    std::vector<std::unique_ptr<particulaUrma>> particuleUrma;

public:
    float getx() const;
    float gety() const;
    int getviteza_x() const;
    int getviteza_y() const;
    int getraza() const;
    void setx(float X);
    void sety(float Y);
    void setviteza_x(int Viteaza_x);
    void setviteza_y(int Viteaza_y);
    void setraza(int Raza);
    void invertvitezax();

    void Deseneaza();
    void Update();
    void ResetMinge();
    Minge(float X, float Y, int Viteza_x, int Viteza_y, int Raza);
    void DeseneazaUrma();
};