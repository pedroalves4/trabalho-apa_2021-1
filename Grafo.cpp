#include "Grafo.h"
#include "stdio.h"
#include <vector>
#include <algorithm>
#include <stack>
#include <iomanip>
#include <chrono>
#include <random>
#include <map>

using namespace std;

Grafo::Grafo()
{

}

Grafo::~Grafo()
{

}

int Grafo::getGrau()
{
    return grau;
}

void Grafo::setGrau(int val)
{
    grau = val;
}

int Grafo::getOrdem()
{
    return ordem;
}

void Grafo::setOrdem(int val)
{
    ordem = val;
}

void Grafo::matrizAdjacencia(bool direcionado)
{
    int tam = listaNo.size();
    int matriz[tam][tam];
    for(int l = 0 ; l < tam ; l++)
        for(int t = 0 ; t < tam ; t++)
            matriz[l][t] = 0;
    for(int i = 0; i < tam; i++)
    {
        No *elementoi = listaNo[i];
        for(int j = 0; j < tam; j++)
        {
            No *elementoj = listaNo[j];
            if(elementoi->verificaAdjacencia(elementoj))
            {
                matriz[i][j]=1;
                if(direcionado == 1)
                {
                    matriz[j][i] = -1;
                }
            }
            else
            {
                if( i > j )
                {
                    if(matriz[j][i] == 0)
                    {
                        matriz[i][j]=0;
                    }
                }
                else
                {
                    matriz[i][j] = 0;
                }
            }
        }
    }
    for(int i = 0; i < tam; i++)
    {
        if(i == 0)
        {
            cout << "    ";
            for(int i = 0; i < tam; i++)
                cout << " [" << listaNo[i]->id << "] ";
            cout << endl;
        }

        for(int j = 0; j < tam; j++)
        {
            if(j == 0)
                cout << "[" << listaNo[i]->id << "] ";
            cout << " [" << matriz[i][j] << "] ";
        }
        cout << endl;
    }
}
void Grafo::printListaAdjacencia()
{
    int tam = listaNo.size();
    for(int i = 0; i < tam; i++)
    {
        cout << endl;
        No *elemento = listaNo[i];
        vector<No*> adjacentes = elemento->getAdjacentes();
        cout << elemento->id;
        for(int j = 0; j < tam; j++)
        {
            if(elemento->verificaAdjacencia(listaNo[j]))

            {
                cout << " -> " << listaNo[j]->id;
            }
        }
    }
    cout << endl;
}

void Grafo::adicionaVertice(No *no)
{
    if(verificaId(no->id))
    {
        ///cout << "Esse id ja esta sendo utilizado, digite um id valido" << endl;
    }
    else
    {
        listaNo.push_back(no);
        //cout << "****** No adicionado com sucesso *****" << endl;
    }
}

bool Grafo::verificaId(int id)
{
    for(auto no : listaNo)
    {
        if(no->id == id)
        {
            return true;
        }
    }
    return false;
}

No * Grafo::getNo(int id)
{
    if(verificaId(id))
    {
        for(auto no : listaNo)
        {
            if(no->id == id)
                return no;
        }
    }
    return NULL;
}

void Grafo::printNos()
{
    cout << "Lista de vertices do grafo: " << endl;
    for(auto no : listaNo)
    {
        cout << no->id << " ";
    }
    cout << endl;
}

/**
 * Função principal do algoritmo forca bruta, esse algoritmo coloca o nó atual em uma lista e para cada nó do grafo, verifica se sua lista de nós adjacentes está contida nessa lista.
 @return void
*/
void Grafo::algoritmoForcaBruta(ofstream& arquivoDeSaida)
{
	vector<No*> nosCandidatos = listaNo; ///A lista de candidatos inicialmente corresponde a todos os vertices do grafo
	int maiorSolucao = 0;
	vector<No*>* solucaoForcaBruta = new vector<No*>;
	vector<No*> nosAdjacentes;

	chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < nosCandidatos.size(); i++)
	{
		No* candidatoAtual = nosCandidatos[i];  ///Pega o primeiro da lista
		solucaoForcaBruta->push_back(candidatoAtual);
		for (int j = 0; j < nosCandidatos.size(); j++)
		{
			if (nosCandidatos[i]->id != nosCandidatos[j]->id)
			{
				std::sort(nosCandidatos[j]->nosAdjacentes.begin(), nosCandidatos[j]->nosAdjacentes.end());
				std::sort(solucaoForcaBruta->begin(), solucaoForcaBruta->end());

				std::set_intersection(nosCandidatos[j]->nosAdjacentes.begin(), nosCandidatos[j]->nosAdjacentes.end(),
					solucaoForcaBruta->begin(), solucaoForcaBruta->end(), std::back_inserter(nosAdjacentes));
				if (nosAdjacentes.size() == 0)
				{
					solucaoForcaBruta->push_back(nosCandidatos[j]);
				}
			}

			nosAdjacentes.clear();
		}

		maiorSolucao = solucaoForcaBruta->size() > maiorSolucao ? solucaoForcaBruta->size() : maiorSolucao;
		solucaoForcaBruta->clear();
	}

	chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
	auto elapsed = finish - start;
	float tempo = elapsed.count() / 1000000000;

	printSolucaoForcaBruta(maiorSolucao, arquivoDeSaida, tempo);
}

/**
 * Imprime a solução encontrada pelo algoritmo força bruta
 * @param inteiro que representa o tamanho da solução
 * @return void
*/
void Grafo::printSolucaoForcaBruta(int solucao, ofstream& arquivoDeSaida, float tempo)
{
	arquivoDeSaida << solucao << "," << tempo;
	arquivoDeSaida << "\n";
}

void Grafo::algoritmoForcaBruta()
{
	vector<No*> nosCandidatos = listaNo; ///A lista de candidatos inicialmente corresponde a todos os vertices do grafo
	int maiorSolucao = 0;
	vector<No*>* solucaoForcaBruta = new vector<No*>;
	vector<No*> nosAdjacentes;

	for (int i = 0; i < nosCandidatos.size(); i++)
	{
		No* candidatoAtual = nosCandidatos[i];  ///Pega o primeiro da lista
		solucaoForcaBruta->push_back(candidatoAtual);
		for (int j = 0; j < nosCandidatos.size(); j++)
		{
			if (nosCandidatos[i]->id != nosCandidatos[j]->id)
			{
				std::sort(nosCandidatos[j]->nosAdjacentes.begin(), nosCandidatos[j]->nosAdjacentes.end());
				std::sort(solucaoForcaBruta->begin(), solucaoForcaBruta->end());

				std::set_intersection(nosCandidatos[j]->nosAdjacentes.begin(), nosCandidatos[j]->nosAdjacentes.end(),
					solucaoForcaBruta->begin(), solucaoForcaBruta->end(), std::back_inserter(nosAdjacentes));
				if (nosAdjacentes.size() == 0)
				{
					solucaoForcaBruta->push_back(nosCandidatos[j]);
				}
			}

			nosAdjacentes.clear();
		}

		maiorSolucao = solucaoForcaBruta->size() > maiorSolucao ? solucaoForcaBruta->size() : maiorSolucao;
		solucaoForcaBruta->clear();
	}

	printSolucaoForcaBruta(maiorSolucao);
}

void Grafo::printSolucaoForcaBruta(int solucao)
{
	cout << "Cardinalidade da solucao forca bruta: " << solucao << endl;
}

/**
 * Função principal do algoritmo guloso, que busca os vértices de menores graus para minimizar a redução da lista de vértices candidatos a cada iteração
 * @param referencia do arquivo onde sera escrita o resultado da execucao
 * @return void
*/
void Grafo::algoritmoGuloso(ofstream &arquivoDeSaida)
{
    vector<No*> *solucaoGulosa = new vector<No*>;
    vector<No*> nosCandidatos = listaNo;
    vector<int> idsDosNosSolucao;

    chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    while(!nosCandidatos.empty())
    {
        No* candidatoAtual = getNoDeMenorGrau(nosCandidatos);
        solucaoGulosa->push_back(candidatoAtual);
        nosCandidatos = atualizaNosCandidatos(candidatoAtual, nosCandidatos);
        idsDosNosSolucao.push_back(candidatoAtual->id);
    }

    chrono::high_resolution_clock::time_point finish = std::chrono::high_resolution_clock::now();
    auto elapsed = finish - start;
    float tempo = elapsed.count()/1000000000;

    printSolucaoGulosa(idsDosNosSolucao, arquivoDeSaida, tempo);
}

/**
 * Remove da lista de candidatos aqueles que são adjacentes ao último selecionado
 * @param candidatoSelecionado ultimo candidato adicionado à solução
 * @param nosCandidatos vetor de candidatos, que será atualizado pela função
 * @return nosCandidatos
*/
vector<No*> Grafo::atualizaNosCandidatos(No* candidatoSelecionado, vector<No*> nosCandidatos)
{
    for(unsigned int a = 0; a < nosCandidatos.size(); a++) ///tira o ultimo candidato selecionado da lista de candidatos
    {
        if(nosCandidatos[a]->id == candidatoSelecionado->id)
            nosCandidatos.erase(nosCandidatos.begin() + a);
    }

    vector<No*> adjacentesAoSelecionado = candidatoSelecionado->nosAdjacentes;

    for(unsigned int i = 0; i < nosCandidatos.size(); i++) /// o conjunto deve ser independente: nao pode conter elementos adjacentes!
    {
        for(unsigned int j = 0; j < adjacentesAoSelecionado.size(); j++)
        {
            if(nosCandidatos[i]->id == adjacentesAoSelecionado[j]->id)
            {
                nosCandidatos.erase(nosCandidatos.begin() + i);
            }
        }
    }
    return nosCandidatos;
}

/**
 * Retorna o vértice de menor grau dentre aqueles que estão na lista de candidatos
 * @param nosCandidatos
 * @return noMenorGrau
*/
No* Grafo::getNoDeMenorGrau(vector<No*> nosCandidatos)
{
    No* noMenorGrau = nosCandidatos[0];
    for(auto candidato : nosCandidatos)
    {
        if(candidato->getGrau() < noMenorGrau->getGrau())
            noMenorGrau = candidato;
    }
    return noMenorGrau;
}

/**
 * Imprime a solução encontrada pelo algoritmo guloso
 * @param solucao vetor contendo os id's dos nós da solução
 * @return void
*/
void Grafo::printSolucaoGulosa(vector<int> solucao, ofstream &arquivoDeSaida, float tempo)
{
    arquivoDeSaida << solucao.size() << "," << tempo;
    arquivoDeSaida << "\n";
}

void Grafo::algoritmoGuloso()
{
    vector<No*> *solucaoGulosa = new vector<No*>;
    vector<No*> nosCandidatos = listaNo;
    vector<int> idsDosNosSolucao;

    while(!nosCandidatos.empty())
    {
        No* candidatoAtual = getNoDeMenorGrau(nosCandidatos);   ///O melhor candidato � o n� de menor grau
        solucaoGulosa->push_back(candidatoAtual);
        nosCandidatos = atualizaNosCandidatos(candidatoAtual, nosCandidatos);
        idsDosNosSolucao.push_back(candidatoAtual->id);
    }

    printSolucaoGulosa(idsDosNosSolucao);
}

void Grafo::printSolucaoGulosa(vector<int> solucao)
{
    cout << "Cardinalidade da solucao gulosa: " << solucao.size() << endl;
}





