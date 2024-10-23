#include "minge.h"
#include "raylib.h"
#include <algorithm>
#include <memory>

int jucator_scor = 0;
int cpu_scor = 0;

const Color Galben = {255, 255, 0, 255};

float Minge::getx() const { return x; }
float Minge::gety() const { return y; }
int Minge::getviteza_x() const { return viteza_x; }
int Minge::getviteza_y() const { return viteza_y; }
int Minge::getraza() const { return raza; }
void Minge::setx(float X) { x = X; }
void Minge::sety(float Y) { y = Y; }
void Minge::setviteza_x(int Viteaza_x) { viteza_x = Viteaza_x; }
void Minge::setviteza_y(int Viteaza_y) { viteza_y = Viteaza_y; }
void Minge::setraza(int Raza) { raza = Raza; }
void Minge::invertvitezax() { viteza_x = -viteza_x; }

void Minge::Deseneaza()
{
    DrawCircle(x, y, raza, Galben);
}

void Minge::Update()
{
    x += viteza_x;
    y += viteza_y;

    // Actualizarea particulelor de urmă
    for (auto &particula : particuleUrma)
    {
        particula->Update(GetFrameTime());
    }
    particuleUrma.erase(std::remove_if(particuleUrma.begin(), particuleUrma.end(),
                                       [](const std::unique_ptr<particulaUrma> &p)
                                       { return !p->EsteVie(); }),
                        particuleUrma.end());

    particuleUrma.emplace_back(std::make_unique<particulaUrma>(Vector2{x, y}, Galben, 0.5f));

    // Coliziunea cu marginile ecranului
    if (y + raza >= GetScreenHeight() || y - raza <= 0)
    {
        viteza_y *= -1;
    }
    if (x + raza >= GetScreenWidth()) // CPU câștigă punct
    {
        cpu_scor++;
        ResetMinge();
    }
    if (x - raza <= 0) // Jucătorul câștigă punct
    {
        jucator_scor++;
        ResetMinge();
    }
}

void Minge::ResetMinge()
{
    x = GetScreenWidth() / 2;
    y = GetScreenHeight() / 2;
    int viteza_decizie[2] = {-1, 1};
    viteza_x *= viteza_decizie[GetRandomValue(0, 1)];
    viteza_y *= viteza_decizie[GetRandomValue(0, 1)];
}

Minge::Minge(float X, float Y, int Viteza_x, int Viteza_y, int Raza) : x(X), y(Y), viteza_x(Viteza_x), viteza_y(Viteza_y), raza(Raza) {}

void Minge::DeseneazaUrma()
{
    for (const auto &particula : particuleUrma)
    {
        particula->Deseneaza();
    }
}