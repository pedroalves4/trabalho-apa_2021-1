#ifndef ARESTA_H_INCLUDED
#define ARESTA_H_INCLUDED

#include "No.h"

class No;

class Aresta
{
public:
    Aresta();
    ~Aresta();

    explicit Aresta(No* no1, No *no2);
    explicit Aresta(No *no1, No* no2,int peso);

    No *no1;
    No *no2;
    int peso;
};

#endif // ARESTA_H_INCLUDED
