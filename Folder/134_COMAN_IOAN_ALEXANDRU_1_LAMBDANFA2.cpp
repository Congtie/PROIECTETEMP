#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include <fstream>

using namespace std;

ofstream output("output.txt");
ifstream input("input.txt");

struct lambdaNFA
{
    int nrStari, nrLitere, stareInitiala, nrStariFinale, nrTranzitii;
    vector<int> stari;
    vector<char> litere;
    unordered_set<int> stariFinale;
    unordered_map<int, unordered_map<char, unordered_set<int>>> tranzitii;
    unordered_map<int, unordered_set<int>> lambdaTranzitii;

    void initializare(ifstream &fisierInput)
    {
        fisierInput >> nrStari;
        stari.resize(nrStari);
        for (int i = 0; i < nrStari; i++)
        {
            fisierInput >> stari[i];
        }

        fisierInput >> nrLitere;
        litere.resize(nrLitere);
        for (int i = 0; i < nrLitere; i++)
        {
            fisierInput >> litere[i];
        }

        fisierInput >> stareInitiala;

        fisierInput >> nrStariFinale;
        stariFinale.clear();
        int stare;
        for (int i = 0; i < nrStariFinale; i++)
        {
            fisierInput >> stare;
            stariFinale.insert(stare);
        }

        fisierInput >> nrTranzitii;
        tranzitii.clear();
        int deLaStare, panaLaStare;
        char litera;
        for (int i = 0; i < nrTranzitii; i++)
        {
            fisierInput >> deLaStare >> litera >> panaLaStare;
            if (litera == '.')
            {
                lambdaTranzitii[deLaStare].insert(panaLaStare);
            }
            else
            {
                tranzitii[deLaStare][litera].insert(panaLaStare);
            }
        }
    }

    void lambdaInchidere(int stare, unordered_set<int> &inchidere)
    {
        if (inchidere.find(stare) != inchidere.end())
        {
            return;
        }
        inchidere.insert(stare);
        for (int stareUrmatoare : lambdaTranzitii[stare])
        {
            lambdaInchidere(stareUrmatoare, inchidere);
        }
    }

    vector<pair<string, bool>> verificaCuvinte(vector<string> &cuvinte)
    {
        vector<pair<string, bool>> rezultate;
        for (const auto &cuvant : cuvinte)
        {
            rezultate.push_back({cuvant, esteAcceptat(cuvant)});
        }
        return rezultate;
    }

    bool esteAcceptat(string cuvant)
    {
        unordered_set<int> stariCurente;
        lambdaInchidere(stareInitiala, stariCurente);

        for (char litera : cuvant)
        {
            unordered_set<int> stariUrmatoare;
            for (int stare : stariCurente)
            {
                if (tranzitii[stare].find(litera) != tranzitii[stare].end())
                {
                    stariUrmatoare.insert(tranzitii[stare][litera].begin(), tranzitii[stare][litera].end());
                }
            }

            unordered_set<int> stariLambdaInchidere;
            for (int stare : stariUrmatoare)
            {
                lambdaInchidere(stare, stariLambdaInchidere);
            }
            stariCurente = stariLambdaInchidere;
        }
        for (int stare : stariCurente)
        {
            if (stariFinale.find(stare) != stariFinale.end())
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    lambdaNFA lambdaNFA;
    lambdaNFA.initializare(input);

    int nrCuvinte;
    input >> nrCuvinte;

    vector<string> cuvinte(nrCuvinte);
    for (int i = 0; i < nrCuvinte; i++)
    {
        input >> cuvinte[i];
    }

    vector<pair<string, bool>> rezultate = lambdaNFA.verificaCuvinte(cuvinte);

    for (const auto &rezultat : rezultate)
    {
        output << (rezultat.second ? "DA" : "NU") << "\n";
    }
    return 0;
}
