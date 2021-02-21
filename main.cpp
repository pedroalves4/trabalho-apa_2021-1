#include <istream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "No.h"
#include "Aresta.h"
#include "Grafo.h"
#include <vector>
#include <fstream>
#include <cstdio>
#include <chrono>

using namespace std;

int tipoDeRepresentacaoMenu()
{
    int opcao = 0;
    cout << "-------------------------------------------------------MENU--------------------------------------------------" << endl;
    cout << "Escolha o tipo de representacao: " << endl;
    cout << "[1] Matriz de Adjacencia" << endl;
    cout << "[2] Lista de Adjacencia" << endl;
    cout << "[-1] Para encerrar o programa" << endl;
    cout << endl;
    cin >> opcao;
    return opcao;
}

int noMenu()
{
    int opcao = 0;
    string opcoesMenu[] =
    {
        "[1] Adicionar No",
        "[2] Adicionar vizinhos a um No",
        "[3] Lista de vertices do grafo",
        "[4] Representar o grafo",
        "[5] Obter solucao pelo algoritmo guloso",
        "[6] Obter solucao pelo algoritmo forca bruta",
    };

    cout << endl << "Selecione uma das opcoes: " << endl;
    for(auto op : opcoesMenu)
    {
        cout << op << endl;
    }
    cin >> opcao;
    return opcao;
}

int main(int argc, char * argv[])
{
    int pesoVertice;
    int pesoAresta = 0;
    int id = 0;
    int idAdj = 0;
    int opcao = 0;
    bool direcionado = 0;
    vector< No > vertices;
    Grafo *grafo = new Grafo();


    ///************* CONSTRU��O DO GRAFO ******************///

    if(atoi(argv[5]) != 1)
    {
        /// Menu de op��es para o grafo
        cout << "Criando seu Grafo " << endl;
        while(id != -1)
        {
            opcao = noMenu();
            switch(opcao)
            {
            case 1:
            {
                cout << "Adicione um vertice informando seu id ou aperte [-1] para terminar o grafo" << endl;
                cin >> id;
                if(id == -1)
                    break;

                No *vertice = new No(id);
                grafo->adicionaVertice(vertice);
            }
            break;
            case 2:
                cout << "Digite o id do no que voce quer acessar: " << endl;
                cin >> id;
                if(id == -1)
                    break;
                while(!grafo->verificaId(id))
                {
                    cout << "Id invalido, esse no nao foi encontrado no grafo, digite outro id: " << endl;
                    cin >> id;
                    if(id == -1)
                        break;
                }
                cout << "Voce esta no vertice " << grafo->getNo(id)->id << ", digite um vertice adjacente a esse: " << endl;
                cin >> idAdj;
                if(id == idAdj)
                {
                    cout<<"Nao e permitido self-loop"<<endl;
                }
                else
                {
                    grafo->arestas.push_back(grafo->getNo(id)->adicionaNoAdjacente(grafo->getNo(idAdj),direcionado,pesoAresta));

                }
                break;
            case 3:
                grafo->printNos();
                break;
            case 4:
            {
                int opcaorepresenta = tipoDeRepresentacaoMenu();
                if(opcaorepresenta == 1)
                {
                    cout << "Matriz de adjacencia: " << endl;
                    grafo->matrizAdjacencia(direcionado);
                }
                else if(opcaorepresenta == 2)
                {
                    cout<<"Lista de adjacencia: "<<endl;
                    grafo->printListaAdjacencia();
                }
                else if(opcaorepresenta == -1)
                {
                    break;
                }
            }
            break;
            case 5:
                grafo->algoritmoGuloso();
                break;
            case 6:
                grafo->algoritmoForcaBruta();
                break;
            default:
                cout << "Digite uma opcao valida" << endl;
                break;
            }
        }
    }

    else if(atoi(argv[5]) == 1)
    {
        cout << argv[1] << endl;

        ifstream myfile (argv[1]);
        ofstream outfile;
        outfile.open(argv[2], std::ofstream::app);
        string aux;

        while(!myfile.eof())
        {
            getline (myfile, aux, ' ');
            int id1 = atoi (aux.c_str());
            No *vertice = new No(id1);
            grafo->adicionaVertice(vertice);
            aux.clear();
            getline (myfile, aux);
            int id2 = atoi (aux.c_str());
            No *vertice1 = new No(id2);
            grafo->adicionaVertice(vertice1);
            aux.clear();
            grafo->arestas.push_back(grafo->getNo(vertice->id)->adicionaNoAdjacente(grafo->getNo(vertice1->id),direcionado,pesoAresta));
        }

        cout << "********* GRAFO CARREGADO **************" << endl;

        if(atoi(argv[3]) != 0)
        {
            grafo->algoritmoGuloso(outfile);
        }

        if(atoi(argv[4]) != 0)
        {
            grafo->algoritmoForcaBruta(outfile);
        }
    }

    return 0;
}
