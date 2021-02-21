#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED
#include "No.h"
#include <vector>
#include <iostream>
#include <stack>
#include <time.h>
#include <fstream>

using namespace std;

class Grafo
{
public:
    Grafo();
    ~Grafo();
    vector<No*> listaNo;
    vector<Aresta*> arestas;
    int getOrdem();
    void setOrdem(int val);
    int getGrau();
    void setGrau(int val);
    void printMatrizAdjacencia();
    void matrizAdjacencia(bool val);
    void printListaAdjacencia();
    void printNos();
    void adicionaVertice(No *no);
    bool verificaId(int id);
    No * getNo(int id);

    void algoritmoGuloso(ofstream &arquivoDeSaida);
    void algoritmoGuloso();
    vector<No*> atualizaNosCandidatos(No* candidatoSelecionado, vector<No*> nosCandidatos);
    No* getNoDeMenorGrau(vector<No*>);
    void printSolucaoGulosa(vector<int> solucao, ofstream &arquivoDeSaida, float tempo);
    void printSolucaoGulosa(vector<int> solucao);

    void algoritmoForcaBruta(ofstream &arquivoDeSaida);
    void algoritmoForcaBruta();
    void printSolucaoForcaBruta(int solucao, ofstream& arquivoDeSaida, float tempo);
    void printSolucaoForcaBruta(int solucao);

private:
    int ordem;
    int grau;
    bool noPonderado;

};

#endif // GRAFO_H_INCLUDED
