#include <iostream>
#include <raylib.h>
#include <vector>
#include <algorithm>
#include <memory>

using namespace std;

// Definirea culorilor
Color Verde = Color{38, 185, 154, 255};
Color Intunecat_Verde = Color{20, 160, 133, 255};
Color Luminat_Verde = Color{129, 204, 184, 255};
Color Galben = Color{243, 213, 91, 255};

// Dimensiunile ecranului
const int latime_ecran = 1280;
const int inaltime_ecran = 800;

// Scorurile jucătorilor
int jucator_scor = 0;
int cpu_scor = 0;

// Declarația claselor
class particulaUrma;
class Minge;
class Paleta;
class PaletaCpu;

// Implementarea claselor
class particulaUrma
{
private:
    Vector2 pozitie;
    Color culoare;
    float timpViata;

public:
    particulaUrma(Vector2 poz, Color cul, float timp) : pozitie(poz), culoare(cul), timpViata(timp) {}

    void Deseneaza() const
    {
        DrawCircle(pozitie.x, pozitie.y, 3, culoare);
    }

    void Update(float timpDelta)
    {
        timpViata -= timpDelta;
    }

    bool EsteVie() const
    {
        return timpViata > 0;
    }
};

class Minge
{
private:
    float x, y;
    int viteza_x, viteza_y;
    int raza;
    std::vector<std::unique_ptr<particulaUrma>> particuleUrma;

public:
    float getx() const { return x; }
    float gety() const { return y; }
    int getviteza_x() const { return viteza_x; }
    int getviteza_y() const { return viteza_y; }
    int getraza() const { return raza; }
    void setx(float X) { x = X; }
    void sety(float Y) { y = Y; }
    void setviteza_x(int Viteaza_x) { viteza_x = Viteaza_x; }
    void setviteza_y(int Viteaza_y) { viteza_y = Viteaza_y; }
    void setraza(int Raza) { raza = Raza; }
    void invertvitezax() { viteza_x = -viteza_x; }

    void Deseneaza()
    {
        DrawCircle(x, y, raza, Galben);
    }

    void Update()
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

        particuleUrma.emplace_back(make_unique<particulaUrma>(Vector2{x, y}, Galben, 0.5f));

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

    void ResetMinge()
    {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        int viteza_decizie[2] = {-1, 1};
        viteza_x *= viteza_decizie[GetRandomValue(0, 1)];
        viteza_y *= viteza_decizie[GetRandomValue(0, 1)];
    }

    Minge(float X, float Y, int Viteza_x, int Viteza_y, int Raza) : x(X), y(Y), viteza_x(Viteza_x), viteza_y(Viteza_y), raza(Raza) {}

    void DeseneazaUrma()
    {
        for (const auto &particula : particuleUrma)
        {
            particula->Deseneaza();
        }
    }
};

class Paleta
{
protected:
    float x, y;
    float latime, inaltime;
    int viteza;

    void LimitareaMiscarii()
    {
        if (y <= 0)
            y = 0;
        if (y + inaltime >= GetScreenHeight())
            y = GetScreenHeight() - inaltime;
    }

public:
    float getx() const { return x; }
    float gety() const { return y; }
    float getlatime() const { return latime; }
    float getinaltime() const { return inaltime; }
    int getviteza() const { return viteza; }
    void setx(float X) { x = X; }
    void sety(float Y) { y = Y; }
    void setlatime(float Latime) { latime = Latime; }
    void setinaltime(float Inaltime) { inaltime = Inaltime; }
    void setviteza(int Viteza) { viteza = Viteza; }

    void Deseneaza()
    {
        DrawRectangleRounded(Rectangle{x, y, latime, inaltime}, 0.8, 0, WHITE);
    }

    void Update()
    {
        if (IsKeyDown(KEY_UP))
            y -= viteza;
        if (IsKeyDown(KEY_DOWN))
            y += viteza;
        LimitareaMiscarii();
    }

    Paleta(float X, float Y, float Latime, float Inaltime, int Viteza) : x(X), y(Y), latime(Latime), inaltime(Inaltime), viteza(Viteza) {}
};

class PaletaCpu : public Paleta
{
public:
    void Update(int minge_y)
    {
        if (gety() + getinaltime() / 2 > minge_y)
            y -= viteza;
        if (gety() + getinaltime() / 2 < minge_y)
            y += viteza;
        LimitareaMiscarii();
    }
    PaletaCpu(float X, float Y, float Latime, float Inaltime, int Viteza) : Paleta(X, Y, Latime, Inaltime, Viteza) {}
};

// Utilizare smart pointers pentru obiectele de joc
shared_ptr<Minge> minge = make_shared<Minge>(latime_ecran / 2, inaltime_ecran / 2, 7, 7, 20);
shared_ptr<Paleta> jucator = make_shared<Paleta>(latime_ecran - 25 - 10, inaltime_ecran / 2 - 60, 25, 120, 6);
shared_ptr<PaletaCpu> cpu = make_shared<PaletaCpu>(10, inaltime_ecran / 2 - 60, 25, 120, 6);

int main()
{
    cout << "Incepem jocul" << endl;
    InitWindow(latime_ecran, inaltime_ecran, "Jocul meu pong!");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();

        minge->Update();
        jucator->Update();
        cpu->Update(minge->gety());

        // Verificam pentru coliziune
        if (CheckCollisionCircleRec(Vector2{minge->getx(), minge->gety()}, minge->getraza(), Rectangle{jucator->getx(), jucator->gety(), jucator->getlatime(), jucator->getinaltime()}))
        {
            minge->invertvitezax();
        }
        if (CheckCollisionCircleRec(Vector2{minge->getx(), minge->gety()}, minge->getraza(), Rectangle{cpu->getx(), cpu->gety(), cpu->getlatime(), cpu->getinaltime()}))
        {
            minge->invertvitezax();
        }

        ClearBackground(Intunecat_Verde);
        DrawRectangle(latime_ecran / 2, 0, latime_ecran / 2, inaltime_ecran, Verde);
        DrawCircle(latime_ecran / 2, inaltime_ecran / 2, 150, Luminat_Verde);
        DrawLine(latime_ecran / 2, 0, latime_ecran / 2, inaltime_ecran, WHITE);
        minge->Deseneaza();
        minge->DeseneazaUrma();
        cpu->Deseneaza();
        jucator->Deseneaza();
        DrawText(TextFormat("%i", cpu_scor), latime_ecran / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", jucator_scor), 3 * latime_ecran / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}