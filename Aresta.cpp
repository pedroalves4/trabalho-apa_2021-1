#include "No.h"
#include "Aresta.h"
#include <vector>

using namespace std;

Aresta::Aresta()
{

}

Aresta::Aresta(No *no1, No *no2)
{
    no1->arestas.push_back(this);
    no2->arestas.push_back(this);

    no1->nosAdjacentes.push_back(no2);
    no2->nosAdjacentes.push_back(no1);

    no1->grau++;
    no2->grau++;

    this->no2 = no2;
    this->no1 = no1;

}

Aresta::Aresta(No *no1, No *no2, int peso)
{
    no1->arestas.push_back(this);
    no2->arestas.push_back(this);

    no1->nosAdjacentes.push_back(no2);
    no2->nosAdjacentes.push_back(no1);

    no1->grau++;
    no2->grau++;

    this->no2 = no2;
    this->no1 = no1;
    this->peso = peso;

}
