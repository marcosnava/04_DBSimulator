//
// Created by nava on 02/05/23.
//
#include <stdio.h>
#include <string.h>
#include "listaDuplamenteLigada.h"

struct LLno *LLregInicio;
struct LLno *LLregFim;
struct LLno *LLaux;
struct LLno *LLregAnterior;
struct LLno *LLnovo;
struct LLno *LLregAtual;

void LLinicializar()
{
    LLregInicio = NULL;
    LLregFim = NULL;
}

void LLfinalizar()
{
    if(LLregInicio != NULL)
    {
        LLfinalizarElemento(LLregInicio);
    }
}

void LLfinalizarElemento(struct LLno *elemento)
{
    if(elemento->proximo != NULL)
    {
        LLfinalizarElemento(elemento->proximo);
    }
    free(elemento);
}

struct LLno *LLnovoNo(char *nome, int reg)
{
    struct LLno *p;
    p = malloc(sizeof (struct LLno));
    if(!p)
    {
        printf("Nao tem memoria!\n");
        exit(-1);
    }

    strcpy(p->nome, nome);
    p->reg = reg;
    p->proximo = NULL;
    p->anterior = NULL;

    return p;
}

void LLadicionar(char *nome, int reg)
{
    LLnovo = LLnovoNo(nome, reg);

    if(LLregInicio == NULL)
    {
        LLregInicio = LLnovo;
        LLregFim = LLnovo;
    }
    else
    {
        if(strcmp(LLnovo->nome, LLregInicio->nome) < 0)
        {
            LLadicionarNoInicio();
        }
        else
        {
            LLaux = LLregInicio;
            while(strcmp(LLaux->nome, LLnovo->nome) <=0 && LLaux->proximo != NULL)
            {
                LLaux = LLaux->proximo;
            }
            if(strcmp(LLnovo->nome, LLaux->nome) > 0)
            {
                LLadicionarNoFim();
            }
            else
            {
                LLadicionarNoMeio();
            }
        }
    }
}

void LLadicionarNoInicio()
{
    LLnovo->proximo = LLregInicio;
    LLregInicio->anterior = LLnovo;
    LLregInicio = LLnovo;
}

void LLadicionarNoMeio()
{
    LLregAnterior = LLaux->anterior;

    LLregAnterior->proximo = LLnovo;
    LLnovo->proximo = LLaux;

    LLaux->anterior = LLnovo;
    LLnovo->anterior = LLregAnterior;
}

void LLadicionarNoFim()
{
    LLaux->proximo = LLnovo;
    LLnovo->anterior = LLaux;
    LLregFim = LLnovo;
}

void LLexcluir(char *nome)
{
    if(LLregInicio != NULL)
    {
        if(!strcmp(LLregInicio->nome, nome))
        {
            LLexcluirNoInicio();
        }
        else
        {
            LLaux = LLregInicio;
            while(strcmp(LLaux->nome, nome) != 0 && LLaux->proximo != NULL)
            {
                LLaux = LLaux->proximo;
            }
            if(!strcmp(LLaux->nome, nome)) {
                if (LLaux->proximo == NULL) {
                    LLexcluirNoFim();
                } else {
                    LLexcluirNoMeio();
                }
            }
        }
    }
}

void LLexcluirNoInicio()
{
    if(LLregInicio->proximo == NULL)
    {
        free(LLregInicio);
        LLregInicio = NULL;
        LLregFim = NULL;
    }
    else
    {
        LLaux = LLregInicio;
        LLregInicio = LLregInicio->proximo;
        LLregInicio->anterior = NULL;

        free(LLaux);
    }
}

void LLexcluirNoMeio()
{
    struct LLno *proximo = NULL;
    proximo = LLaux->proximo;
    LLregAnterior = LLaux->anterior;

    LLregAnterior->proximo = proximo;
    proximo->anterior = LLregAnterior;

    free(LLaux);
}

void LLexcluirNoFim()
{
    LLregAnterior = LLaux->anterior;
    LLregAnterior->proximo = NULL;
    LLregFim = LLregAnterior;

    free(LLaux);
}

void LLprimeiro()
{
    LLregAtual = LLregInicio;
}

void LLultimo()
{
    LLregAtual = LLregFim;
}

struct LLno *LLregistroAtual()
{
    return LLregAtual;
}

BOOLEAN LLproximo()
{
    if(LLregAtual->proximo == NULL)
    {
        return FALSE;
    }
    LLregAtual = LLregAtual->proximo;
    return TRUE;
}

BOOLEAN LLanterior()
{
    if(LLregAtual->anterior == NULL)
    {
        return FALSE;
    }
    LLregAtual = LLregAtual->anterior;
    return TRUE;
}