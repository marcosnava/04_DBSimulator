#include <stdio.h>
#include <string.h>
#include "arrayList.h"
#include "listaDuplamenteLigada.h"
#include "arvoreBinaria.h"

// Variaveis
struct ALregistro registro;

// Constantes
enum
{
    OP_NAO_SELECIONADA = 0,
    OP_ADICIONAR,
    OP_EXCLUIR,
    OP_LOCALIZAR,
    OP_LISTAR_FISICO,
    OP_LISTAR_LOGICO_CRESCENTE,
    OP_LISTAR_LOGICO_DECRESCENTE,
    OP_REORGANIZAR_INDICES,
    OP_SAIR,
};

// Protótipos
void inicializar();
void finalizar();
void adicionar(struct ALregistro reg);
void excluir(struct ALregistro reg);
void localizar(struct ALregistro reg);
void listarFisico();
void listarLogicoCrescente();
void listarLogicoDecrescente();
void reorganizarIndices();
int menu();

int main() {
    int opcao = OP_NAO_SELECIONADA;
    char nome[101];
    char endereco[101];
    char telefone[21];

    inicializar();

    while(opcao != OP_SAIR)
    {
        opcao = menu();
        switch(opcao)
        {
            case OP_ADICIONAR:
                printf("Digite o nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                printf("Digite o endereco: ");
                fgets(endereco, 100, stdin);
                endereco[strcspn(endereco, "\n")] = 0;

                printf("Digite o telefone: ");
                fgets(telefone, 20, stdin);
                telefone[strcspn(telefone, "\n")] = 0;

                strcpy(registro.nome, nome);
                strcpy(registro.endereco, endereco);
                strcpy(registro.telefone, telefone);

                adicionar(registro);
                break;
            case OP_EXCLUIR:
                printf("Digite o nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                strcpy(registro.nome, nome);

                excluir(registro);
                break;
            case OP_LOCALIZAR:
                printf("Digite o nome: ");
                fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = 0;

                strcpy(registro.nome, nome);

                localizar(registro);
                break;
            case OP_LISTAR_FISICO:
                listarFisico();
                break;
            case OP_LISTAR_LOGICO_CRESCENTE:
                listarLogicoCrescente();
                break;
            case OP_LISTAR_LOGICO_DECRESCENTE:
                listarLogicoDecrescente();
                break;
            case OP_REORGANIZAR_INDICES:
                reorganizarIndices();
                break;
            case OP_SAIR:
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    finalizar();

    return 0;
}

void inicializar()
{
    ALinicializar();
    LLinicializar();
    ABinicializar();
}

void finalizar()
{
    ALfinalizar();
    LLfinalizar();
    ABfinalizar(ABinicio);
}

int menu()
{
    int op;

    printf("%d - Adicionar\n", OP_ADICIONAR);
    printf("%d - Excluir\n", OP_EXCLUIR);
    printf("%d - Localizar\n", OP_LOCALIZAR);
    printf("%d - Listar ordem Fisica\n", OP_LISTAR_FISICO);
    printf("%d - Listar ordem Logica Crescente\n", OP_LISTAR_LOGICO_CRESCENTE);
    printf("%d - Listar ordem Logica Decrescente\n", OP_LISTAR_LOGICO_DECRESCENTE);
    printf("%d - Reorganizar Indices\n", OP_REORGANIZAR_INDICES);
    printf("%d - Sair\n", OP_SAIR);
    printf("Selecione sua opcao: ");
    scanf("%d", &op);
    scanf("%*c");

    return op;
}

void adicionar(struct ALregistro reg)
{
    BOOLEAN deuCerto = FALSE;
    int nRegistro = 0;

    struct ABno *no = ABlocalizar(ABinicio, reg.nome);

    if(no != NULL)
    {
        printf("Registro ja existe!\n");
    }
    else {

        // adicionar no array list
        deuCerto = ALadicionar(&registro, &nRegistro);
        if (!deuCerto) {
            ALexpandir();
            ALadicionar(&registro, &nRegistro);
        }

        // adicionar na lista duplamente ligada
        LLadicionar(reg.nome, nRegistro);

        // adicionar na árvore binária
        ABadicionar(ABinicio, ABnovoNo(reg.nome, nRegistro));
    }
}

void excluir(struct ALregistro reg)
{
    // excluir no array list
    ALexcluirLogico(&reg);

    // excluir na lista duplamente ligada
    LLexcluir(reg.nome);

    // excluir na árvore binária
    ABexcluir(reg.nome);
}

void localizar(struct ALregistro reg)
{
    struct ABno *no = NULL;
    no = ABlocalizar(ABinicio, reg.nome);
    if(no == NULL)
    {
        printf("Registro nao localizado!\n");
    }
    else
    {
        if(ALbuscarPorIndice(no->reg, &registro))
        {
            printf("Registro.: %d\n", no->reg);
            printf("Nome.....: %s\n", registro.nome);
            printf("Endereco.: %s\n", registro.endereco);
            printf("Telefone.: %s\n", registro.telefone);
        }
    }
}

void listarFisico()
{
    printf("Listagem por ordem de cadastro:\n");
    int i;
    for(i = 0; i < ALquantidadeElementos(); i++)
    {
        if(ALbuscarPorIndice(i, &registro)) {
            printf("Registro.: %d\n", i);
            printf("Nome.....: %s\n", registro.nome);
            printf("Endereco.: %s\n", registro.endereco);
            printf("Telefone.: %s\n\n", registro.telefone);
        }
    }
    printf("FIM DO ARQUIVO\n");
}

void listarLogicoCrescente()
{
    printf("Listar Ordem Crescente\n");
    LLprimeiro();
    do {
        if(LLregAtual != NULL)
        {
            ALbuscarPorIndice(LLregAtual->reg, &registro);
            printf("Registro.: %d\n", LLregAtual->reg);
            printf("Nome.....: %s\n", LLregAtual->nome);
            printf("Endereco.: %s\n", registro.endereco);
            printf("Telefone.: %s\n\n", registro.telefone);
        }
    } while(LLproximo());
}

void listarLogicoDecrescente()
{
    printf("Listar Ordem Decrescente\n");
    LLultimo();
    do {
        if(LLregAtual != NULL)
        {
            ALbuscarPorIndice(LLregAtual->reg, &registro);
            printf("Registro.: %d\n", LLregAtual->reg);
            printf("Nome.....: %s\n", LLregAtual->nome);
            printf("Endereco.: %s\n", registro.endereco);
            printf("Telefone.: %s\n\n", registro.telefone);
        }
    } while(LLanterior());
}

void reorganizarIndices()
{
    LLfinalizar();
    ABfinalizar(ABinicio);

    LLinicializar();
    ABinicializar();

    int i;
    for(i = 0; i < ALquantidadeElementos(); i++)
    {
        if(ALbuscarExcluido(i, &registro)) {
            ALexcluir(&registro);
        }
    }

    for(i = 0; i < ALquantidadeElementos(); i++)
    {
        if(ALbuscarPorIndice(i, &registro)) {
            LLadicionar(registro.nome, i);
            ABadicionar(ABinicio, ABnovoNo(registro.nome, i));
        }
    }
}
