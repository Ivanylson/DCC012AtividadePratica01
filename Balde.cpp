/**
    UNIVERSIDADE FEDERAL DE JUIZ DE FORA
    INSTITUTO DE CIÊNCIAS EXATAS
    DEPARTAMENTO DA CIẼNCIA DA COMPUTAÇÃO

    TRABALHO DE ESTRUTURA DE DADOS 2(||) - 2020.3 (ERE) - Hash Extensivel
    PROF.DR.MARCELO CANIATO RENHE

    GRUPO:
    IVANYLSON HONORIO GONÇALVES    MAT 201776002


    main.cpp
    *** comando pra rodar ***
    MAC/LINUX:  clear && g++ -std=c++11 main.cpp -o main && ./main
    WINDOWS:    cls & g++ -std=c++11 main.cpp -o main & main.exe

*/

/**Bibliotecas**/
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string.h>
#include <cstdlib>
#include <chrono>
#include <sstream>

/**Classe**/
#include "Balde.h"

using namespace std;

Balde::Balde(int tamM)
{
    this->profundidadeLocal = 0;
    this->tamanhoM = tamM;
}

Balde::Balde(int profundidadeLocal,int tamBalde)
{
    this->profundidadeLocal=profundidadeLocal;
    this->tamBalde=tamBalde;
}

Balde::~Balde() {}

int Balde::getProfundidadeLocal()
{
    return this->profundidadeLocal;
}

int Balde::getTamanhoM()
{
    return this->tamanhoM;
}

string Balde::getPseudoChave(int i)
{
    return this->pseudoChaves[i];
}

void Balde::apagaPseudoChave(int i)
{
    this->imprimeBaldeAleatorio();
    pseudoChaves.erase(pseudoChaves.begin() + i);
    this->imprimeBaldeAleatorio();
}

void Balde::imprimeBaldeAleatorio()
{
    for(int i = 0; i < this->getTamanhoM(); i++)
    {
        cout << "Elemento na pos: " << i+1 << " do balde" << endl;
        if(i < pseudoChaves.size())
            cout << "Com pseudochave: " << this->getPseudoChave(i) << endl;
    }
}

bool Balde::isCheio()
{
    if(this->pseudoChaves.size() < this->getTamanhoM())
    {
        return false;
    }
    return true;
}

void Balde::insere(string pseudoChave)
{
    this->pseudoChaves.push_back(pseudoChave);
}

bool Balde::busca(string pseudoChave)
{
    vector<string>::iterator it;
    it = find (this->pseudoChaves.begin(), this->pseudoChaves.end(), pseudoChave);
    if (it != this->pseudoChaves.end())
    {
        cout << "Elemento repetido\n";
        return true;
    }
    return false;
}

void Balde::atualizaBalde(int profundidadeNova)
{
    this->profundidadeLocal = profundidadeNova;
}



int Balde::gettam()
{
    return tamBalde;

}


int Balde::aumentaProfundidadeLocal()
{

    profundidadeLocal+=profundidadeLocal;
    return profundidadeLocal;
}

string Balde::valores(int i)
{

    return balde[i];

}


int Balde::insereChaveBalde(string psCh)
{

    if(verificaBaldeCheio())
    {
        cout<<"Balde cheio"<<endl;
        return 0;
    }
    else if(balde.empty())
    {
        cout<<"Inserido"<<endl;
        balde.push_back(psCh);
        return 2;

    }
    else if(buscaPseudoch(psCh))
    {
        return -1;
    }
    else
    {
        cout<<"Inserido"<<endl;
        balde.push_back(psCh);
        return 1;
    }


}

void Balde::apaga(string ch)
{

    int index;

    for(int i=0; i<tamBalde; i++)
    {

        if(balde[i]==ch)
        {
            cout<<"Apagada: "<<balde[i];
            index = i;
        }
    }
    cout<<"Apagada: "<<balde[index];
    balde.erase(balde.begin()+index);

}
void Balde::imprimeBalde()
{

    for(int i=0; i<tamBalde; i++)
    {
        cout<<"["<<i<<"] "<<balde[i]<<endl;;
    }
}
bool Balde::verificaBaldeCheio()
{

    if(balde.size()==tamBalde)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool  Balde::buscaPseudoch(string ch)
{


    if(!balde.empty())
    {

        for(int i=0; i<=tamBalde; i++)
        {
            if(balde[i]==ch)
            {
                cout<<"Inserido: "<<balde[i]<<endl;
                return true;
            }
        }
    }
    else
        return false;
    return false;
}
