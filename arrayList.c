//
// Created by nava on 02/05/23.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "arrayList.h"

// Variáveis
int ALtamanho = 5;
struct ALregistro *ALlista;
int ALposicao = 0;

BOOLEAN ALadicionar(struct ALregistro *reg, int *nReg)
{
    if(ALposicao == ALtamanho)
    {
        return FALSE;
    }
    else
    {
        strcpy(ALlista[ALposicao].nome, reg->nome);
        strcpy(ALlista[ALposicao].endereco, reg->endereco);
        strcpy(ALlista[ALposicao].telefone, reg->telefone);
        ALlista[ALposicao].excluido = ' ';
        *nReg = ALposicao;
        ALposicao++;
        return TRUE;
    }
}

int ALquantidadeElementos()
{
    return ALposicao;
}

BOOLEAN ALbuscarPorIndice(int indice, struct ALregistro *reg)
{
    if(indice < 0 || indice >= ALposicao)
    {
        return FALSE;
    }
    else
    {
        if(ALlista[indice].excluido == '*')
        {
            return FALSE;
        }
        strcpy(reg->nome, ALlista[indice].nome);
        strcpy(reg->endereco, ALlista[indice].endereco);
        strcpy(reg->telefone, ALlista[indice].telefone);
        return TRUE;
    }
}

BOOLEAN ALbuscarExcluido(int indice, struct ALregistro *reg)
{
    if(indice < 0 || indice >= ALposicao)
    {
        return FALSE;
    }
    else
    {
        if(ALlista[indice].excluido != '*')
        {
            return FALSE;
        }
        strcpy(reg->nome, ALlista[indice].nome);
        strcpy(reg->endereco, ALlista[indice].endereco);
        strcpy(reg->telefone, ALlista[indice].telefone);
        return TRUE;
    }
}

int ALbuscarPorValor(struct ALregistro *reg)
{
    int i;
    for(i = 0; i < ALposicao; i++)
    {
        if(!strcmp(ALlista[i].nome, reg->nome))
        {
            if(ALlista[i].excluido == '*')
            {
                return AL_NAO_ACHEI;
            }
            return i;
        }
    }

    return AL_NAO_ACHEI;
}

void ALexcluirLogico(struct ALregistro *reg)
{
    int indice;

    indice = ALbuscarPorValor(reg);
    if(indice != AL_NAO_ACHEI)
    {
        ALlista[indice].excluido='*';
    }
}

void ALexcluir(struct ALregistro *reg)
{
    int indice;
    int i;

    indice = ALbuscarPorValor(reg);

    if(indice != AL_NAO_ACHEI)
    {
        for(i = indice; i < (ALposicao - 1); i++)
        {
            ALlista[i] = ALlista[i + 1];
        }

        ALposicao--;
    }
}

void ALinicializar()
{
    ALlista = malloc(ALtamanho * sizeof(struct ALregistro));
    if(!ALlista)
    {
        printf("Erro na alocacao de memoria!\n");
        exit(-1);
    }
}

void ALfinalizar()
{
    free(ALlista);
}

void ALexpandir()
{
    int novoTamanho = ALtamanho * 1.5;
    struct ALregistro *aux;
    int i;

    printf("alocando mais memoria!\n");

    aux = malloc(novoTamanho * sizeof(struct ALregistro));
    if(!aux)
    {
        printf("Erro de alocacao de memoria!\n");
        exit(-1);
    }

    for(i = 0; i < ALtamanho; i++)
    {
        aux[i] = ALlista[i];
    }

    free(ALlista);

    ALtamanho = novoTamanho;
    ALlista = aux;
}