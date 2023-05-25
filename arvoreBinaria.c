//
// Created by nava on 18/05/23.
//

#include <stdio.h>
#include <string.h>
#include "arvoreBinaria.h"

// Variáveis
struct ABno *ABinicio;
struct ABno *ABanterior = NULL;

void ABinicializar()
{
    ABinicio = NULL;
}

void ABfinalizar(struct ABno *elemento)
{
    if(ABinicio != NULL)
    {
        printf("Excluindo %s\n", elemento->nome);
        if(elemento->esquerda != NULL)
        {
            ABfinalizar(elemento->esquerda);
        }
        if(elemento->direita != NULL)
        {
            ABfinalizar(elemento->direita);
        }
        free(elemento);
    }
}

struct ABno *ABnovoNo(char *nome, int reg)
{
    struct ABno *p;

    p = malloc(sizeof(struct ABno));
    if(!p)
    {
        printf("Erro fatal! Nao existe memoria disponivel!\n");
        exit(-1);
    }

    p->esquerda = NULL;
    p->direita = NULL;
    p->reg = reg;
    strcpy(p->nome, nome);

    return p;
}

void ABadicionar(struct ABno *aonde, struct ABno *novo)
{
    if(ABinicio == NULL)
    {
        ABinicio = novo;
    }
    else
    {
        if(strcmp(novo->nome, aonde->nome) > 0)
        {
            // ABadicionar a direita
            if(aonde->direita == NULL)
            {
                aonde->direita = novo;
            }
            else
            {
                ABadicionar(aonde->direita, novo);
            }
        }
        else
        {
            // ABadicionar a esquerda
            if(aonde->esquerda == NULL)
            {
                aonde->esquerda = novo;
            }
            else
            {
                ABadicionar(aonde->esquerda, novo);
            }
        }
    }
}

struct ABno *ABlocalizar(struct ABno *aonde, char *nome)
{
    if(ABinicio == NULL)
    {
        return NULL;
    }
    if(!strcmp(aonde->nome, nome))
    {
        return aonde;
    }
    else
    {
        ABanterior = aonde;
        if(strcmp(nome, aonde->nome) > 0)
        {
            // ABlocalizar à direita
            if(aonde->direita == NULL)
            {
                return NULL;
            }
            else
            {
                return ABlocalizar(aonde->direita, nome);
            }
        }
        else
        {
            // ABlocalizar à esquerda
            if(aonde->esquerda == NULL)
            {
                return NULL;
            }
            else
            {
                return ABlocalizar(aonde->esquerda, nome);
            }
        }
    }
}

void ABexcluir(char *nome)
{
    if(ABinicio == NULL)
    {
        return;
    }
    else
    {
        struct ABno *aux;
        aux = ABlocalizar(ABinicio, nome);
        printf("Localizei %s\n", aux->nome);
        if(aux == NULL)
        {
            return;
        }
        else
        {
            if(aux == ABinicio)
            {
                ABinicio = NULL;
            }
            else {
                if (strcmp(aux->nome, ABanterior->nome) > 0) {
                    ABanterior->direita = NULL;
                } else {
                    ABanterior->esquerda = NULL;
                }
            }
            if(aux->esquerda != NULL) {
                ABadicionar(ABinicio, aux->esquerda);
            }
            if(aux->direita != NULL)
            {
                ABadicionar(ABinicio, aux->direita);
            }
            free(aux);

        }
    }
}