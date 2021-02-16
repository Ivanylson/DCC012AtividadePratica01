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

/**Bibliotecas padrao**/
#include <iostream>
#include <fstream>
#include <string.h>
#include <map>
#include <cmath>
#include <bitset>

/**Classe**/
#include "Diretorio.h"
#include "Balde.h"


using namespace std;


Diretorio::Diretorio(int numeroDeBits, int tamanhoM)
{
    /**Aleatorio e normal*/
    this->profundidadeGlobal = 1;
    this->tamanhoBits = numeroDeBits;
    this->tamanhoDoBalde=tamanhoM;

    vector<Balde*> conjuntoDeBaldesAleatorios;
    for (int i = 0; i < 2; i++)
    {
        Balde* novoBaldeAleatorio = new Balde(tamanhoM);
        this->conjuntoDeBaldesAleatorios.push_back(novoBaldeAleatorio);
    }

    Balde *novoBalde=new Balde(0,tamanhoDoBalde);

    for(int i=0; i<1<<profundidadeGlobal; i++)
    {
        baldes.push_back(novoBalde);

    }
}

int Diretorio::getTamanhoDiretorio()
{
    return this->conjuntoDeBaldesAleatorios.size();
}

void Diretorio::inserePseudoChave(string pseudoChave)
{
    int indiceBalde = std::stoi(pseudoChave.substr(0, this->profundidadeGlobal), nullptr, 2);
    int diretorioLocal = this->conjuntoDeBaldesAleatorios[indiceBalde]->getProfundidadeLocal();

    int diretorioGlobal = this->profundidadeGlobal;
    diretorioGlobal++;
    //cout << "Diretorio Global: " << diretorioGlobal << endl;

    if(!this->conjuntoDeBaldesAleatorios[indiceBalde]->isCheio())
    {
        this->conjuntoDeBaldesAleatorios[indiceBalde]->insere(pseudoChave);
    }
    else
    {
        if(diretorioLocal > diretorioGlobal)
        {
            cout << "Implementaçao errada\n";
        }
        if(diretorioLocal == diretorioGlobal)
        {
            if(diretorioGlobal <= this->tamanhoBits)
            {
                this->duplicaDiretorioPseudoChave();
            }
            else
            {
                cout << "Essa pseudochave não pode ser inserida, o diretório não pode mais ser duplicado" << endl;
                return;
            }
        }
        this->divideBaldesPseudoChave(indiceBalde);
        this->inserePseudoChave(pseudoChave);
    }

}

bool Diretorio::buscaPseudoChave(string pseudoChave)
{
    int indiceBalde = std::stoi(pseudoChave.substr(0, this->profundidadeGlobal), nullptr, 2); //Acesso ao indice do Balde por binario
    if (indiceBalde < pow(2,this->profundidadeGlobal))
    {
        this->conjuntoDeBaldesAleatorios[indiceBalde]->busca(pseudoChave);
    }
    return false;
}

void Diretorio::divideBaldesPseudoChave(int indiceDoBalde)
{
    int profundidadeNova = this->conjuntoDeBaldesAleatorios[indiceDoBalde]->getProfundidadeLocal() + 1;
    int novoTamanhoM = this->conjuntoDeBaldesAleatorios[indiceDoBalde]->getTamanhoM();
    Balde* novoBalde = new Balde(novoTamanhoM);

    this->conjuntoDeBaldesAleatorios[indiceDoBalde]->atualizaBalde(profundidadeNova);
    novoBalde->atualizaBalde(profundidadeNova);
    int tempNovoIndicePraDelecao;

    //percorre o balde original
    for (int i = 0; i < novoTamanhoM; i++)
    {
        //pega a pseudochave no balde original
        string pseudoChaveAtual = this->conjuntoDeBaldesAleatorios[indiceDoBalde]->getPseudoChave(i);
        cout << "\nPseudo Chave Atual:" << pseudoChaveAtual << endl;

        //redistribui as chaves, colocando como novoIndice a pseudoChave de acordo com a profundidadeGlobal
        int novoIndice = std::stoi(pseudoChaveAtual.substr(0, this->profundidadeGlobal), nullptr, 2);
        cout << "\n Novo Indice:" << novoIndice << std::endl;

        //se o novo indice for diferente do indice que ja tinha, coloca no novo Balde
        if(novoIndice != indiceDoBalde)
        {
            tempNovoIndicePraDelecao = novoIndice;
            novoBalde->insere(move(pseudoChaveAtual));
            //coloca o novo Balde no balde de novoIndice
            this->conjuntoDeBaldesAleatorios[novoIndice] = novoBalde;
        }
    }
    //limpa o balde original
    for (int i = 0, delecoes = 0; i < novoTamanhoM - delecoes;)
    {
        string pseudoChaveAtual = this->conjuntoDeBaldesAleatorios[indiceDoBalde]->getPseudoChave(i);
        int novoIndice = std::stoi(pseudoChaveAtual.substr(0, this->profundidadeGlobal), nullptr, 2);
        if(novoIndice == tempNovoIndicePraDelecao)
        {
            conjuntoDeBaldesAleatorios[indiceDoBalde]->apagaPseudoChave(i);
            delecoes++;
        }
        else
            i++;
    }
}

void Diretorio::duplicaDiretorioPseudoChave()
{
    this->profundidadeGlobal += 1;
    int tamanhoDir = this->getTamanhoDiretorio();
    vector<Balde*> duplicata {2*tamanhoDir};
    for (int i = 0; i < tamanhoDir; i++)
    {
        duplicata[2*i] = move(this->conjuntoDeBaldesAleatorios[i]);
        duplicata[2*i+1] = move(this->conjuntoDeBaldesAleatorios[i]);
    }
    this->conjuntoDeBaldesAleatorios = duplicata;
}

void Diretorio::imprimeDiretorioAleatorio()
{
    cout << "Profundidade global: " << this->profundidadeGlobal << endl;
    for(int i = 0; i < this->conjuntoDeBaldesAleatorios.size(); i++)
    {
        cout << "\nElementos no balde de indice " << i << " e endereço " << conjuntoDeBaldesAleatorios.at(i) <<  " e profundidade " << this->conjuntoDeBaldesAleatorios[i]->getProfundidadeLocal() << endl;
        this->conjuntoDeBaldesAleatorios[i]->imprimeBaldeAleatorio();
    }
}

int Diretorio::calculaNumBaldes()
{
    int nBaldes = 1;
    for(int i = 1; i < this->conjuntoDeBaldesAleatorios.size(); i++)
    {
        if(this->conjuntoDeBaldesAleatorios[i] != this->conjuntoDeBaldesAleatorios[i-1])
        {
            nBaldes++;
        }
    }
    return nBaldes;
}
/****/

void Diretorio::inserirChave(string chave)
{
    cout<<"Chave: "<<chave<<endl;
    string bitEsquerda = chave.substr(0,profundidadeGlobal);

    cout<<"Bits Esquerda "<<bitEsquerda<<endl;

    int index = std::stoi(bitEsquerda, 0, 2);
    cout<<"Index: "<<index<<endl;

    int test=baldes[index]->insereChaveBalde(chave);
    cout<<endl;


    if(test==0)
    {

        if(baldes[index]->getProfundidadeLocal()==profundidadeGlobal)
        {
            cout<<"Diretorio Cheio"<<endl;
            particionaDiretorio();
            duplicaBalde(index,chave);

        }
        else if(baldes[index]->getProfundidadeLocal()<profundidadeGlobal)
        {
            cout<<"Duplicando Balde apenas"<<endl;
            duplicaBalde(index,chave);
        }
    }
}
int Diretorio::getIndice(int indiceDoBalde, int profundidadetGlobal)
{
    return indiceDoBalde^(1<<profundidadetGlobal-1);

}
void Diretorio::particionaDiretorio()
{
//Aumenta a profunidade global;
    profundidadeGlobal++;
    for(int i = 0 ; i < 1<<(profundidadeGlobal-1); i++ )
    {
        //desloca o diretorio de acordo com os bits da profundidadeGlobal
        baldes.push_back(baldes[i]);
    } //adciona o valor no Balde na posicao i
}
void Diretorio::duplicaBalde(int indice,string chave)
{
    int i=getIndice(indice,profundidadeGlobal);
    int index1=min(indice,i);
    int index2=max(indice,i);

    cout<<"Index1: "<<index1<<endl;
    cout<<"Index2: "<<index2<<endl;

    baldes[indice]->imprimeBalde();

    //Crias dois novos baldes
    Balde *novo1=new Balde(baldes[indice]->getProfundidadeLocal(),tamanhoDoBalde);
    Balde *novo2=new Balde(baldes[indice]->getProfundidadeLocal(),tamanhoDoBalde);

    novo1->insereChaveBalde(chave);
    string bitEsquerda = chave.substr(0,profundidadeGlobal);

    int tam = novo1->gettam();
    for(int i=1; i<tam; i++)
    {

        string s=baldes[indice]->valores(i);
        cout<<" "<<s<<endl;
        string bitEsquerdaS = s.substr(0,profundidadeGlobal);

        if(bitEsquerdaS.compare(bitEsquerdaS))
        {
            novo1->insereChaveBalde(s);
        }
        else
        {
            novo2->insereChaveBalde(s);
        }
    }

    cout<<"Balde 1:"<<endl;

    novo1->imprimeBalde();

    cout<<"Balde 2:"<<endl;
    novo2->imprimeBalde();


    //Associa os novos baldes com os index correpondentes as suas chaves  no diretorio
    string s1 = novo1->valores(1);
    string bitEsquerdaB1 = s1.substr(0,profundidadeGlobal);
    int indexCorrespondeB1 = std::stoi(bitEsquerdaB1, 0, 2);

    cout<<"S1: "<<s1<<endl;
    cout<<"Index Balde 1: "<<indexCorrespondeB1<<endl;

    string s2 = novo2->valores(1);
    string bitEsquerdaB2 = s2.substr(0,profundidadeGlobal);
    int indexCorrespondeB2 = std::stoi(bitEsquerdaB2, 0, 2);

    cout<<"S2: "<<s2<<endl;
    cout<<"Index Balde 2: "<<indexCorrespondeB2<<endl;


    baldes[indexCorrespondeB1]=novo1;
    baldes[indexCorrespondeB2]=novo2;

    //Aumenta a profundidade dos baldes
    baldes[indexCorrespondeB1]->aumentaProfundidadeLocal();
    baldes[indexCorrespondeB2]->aumentaProfundidadeLocal();
}
void Diretorio::imprimeDiretorio()
{
    cout<<endl;
    for(int i=0; i<baldes.size(); i++)
    {
        cout<<"Index: "<<i<<endl;
        baldes[i]->imprimeBalde();
    }
}
