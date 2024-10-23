#include "paleta.h"
#include "raylib.h"

void Paleta::LimitareaMiscarii()
{
    if (y <= 0)
        y = 0;
    if (y + inaltime >= GetScreenHeight())
        y = GetScreenHeight() - inaltime;
}

float Paleta::getx() const { return x; }
float Paleta::gety() const { return y; }
float Paleta::getlatime() const { return latime; }
float Paleta::getinaltime() const { return inaltime; }
int Paleta::getviteza() const { return viteza; }
void Paleta::setx(float X) { x = X; }
void Paleta::sety(float Y) { y = Y; }
void Paleta::setlatime(float Latime) { latime = Latime; }
void Paleta::setinaltime(float Inaltime) { inaltime = Inaltime; }
void Paleta::setviteza(int Viteza) { viteza = Viteza; }

void Paleta::Deseneaza()
{
    DrawRectangleRounded(Rectangle{x, y, latime, inaltime}, 0.8, 0, WHITE);
}

void Paleta::Update()
{
    if (IsKeyDown(KEY_UP))
        y -= viteza;
    if (IsKeyDown(KEY_DOWN))
        y += viteza;
    LimitareaMiscarii();
}

Paleta::Paleta(float X, float Y, float Latime, float Inaltime, int Viteza) : x(X), y(Y), latime(Latime), inaltime(Inaltime), viteza(Viteza) {}