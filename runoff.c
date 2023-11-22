#include "cs50.h"
#include "stdio.h"
#include "string.h"

#define MAX_CANDIDATES 9

typedef struct
{
    char* nome;
    int votos;
} Candidato;

typedef struct
{
    char* primeiro;
    char* segundo;
    char* terceiro;
} VotoClassificado;

int encontrarIndiceCandidato(Candidato candidatos[], int numCandidatos, char* nome);
void votar(Candidato candidatos[], int numCandidatos, char* nome, int peso);
char* encontrarVencedorOuSegundoTurno(Candidato candidatos[], int numCandidatos);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s candidato1 candidato2 candidato3 ... candidatoN\n", argv[0]);
        return 1;
    }

    int numCandidatos = argc - 1;

    if (numCandidatos > MAX_CANDIDATES)
    {
        printf("Número máximo de candidatos é %d\n", MAX_CANDIDATES);
        return 2;
    }

    Candidato candidatos[MAX_CANDIDATES];

    for (int i = 0; i < numCandidatos; i++)
    {
        candidatos[i].nome = argv[i + 1];
        candidatos[i].votos = 0;
    }

    int numEleitores;

    do
    {
        printf("Número de eleitores: ");
        numEleitores = get_int(NULL);
    } while (numEleitores < 1);

    VotoClassificado voto;
    for (int i = 0; i < numEleitores; i++)
    {
        printf("\nVoto %d:\n", i + 1);
        printf("Rank 1: ");
        voto.primeiro = get_string(NULL);
        printf("Rank 2: ");
        voto.segundo = get_string(NULL);
        printf("Rank 3: ");
        voto.terceiro = get_string(NULL);

        votar(candidatos, numCandidatos, voto.primeiro, 3);
        votar(candidatos, numCandidatos, voto.segundo, 2);
        votar(candidatos, numCandidatos, voto.terceiro, 1);
    }

    char* resultado = encontrarVencedorOuSegundoTurno(candidatos, numCandidatos);
    printf("\nResultado: %s\n", resultado);

    return 0;
}

int encontrarIndiceCandidato(Candidato candidatos[], int numCandidatos, char* nome)
{
    for (int i = 0; i < numCandidatos; i++)
    {
        if (strcmp(candidatos[i].nome, nome) == 0)
        {
            return i;
        }
    }
    return -1;
}

void votar(Candidato candidatos[], int numCandidatos, char* nome, int peso)
{
    int indice = encontrarIndiceCandidato(candidatos, numCandidatos, nome);
    if (indice != -1)
    {
        candidatos[indice].votos += peso;
    }
}

char* encontrarVencedorOuSegundoTurno(Candidato candidatos[], int numCandidatos)
{
    int primeiroLugar = 0, segundoLugar = 1;

    for (int i = 2; i < numCandidatos; i++)
    {
        if (candidatos[i].votos > candidatos[primeiroLugar].votos)
        {
            segundoLugar = primeiroLugar;
            primeiroLugar = i;
        }
        else if (candidatos[i].votos > candidatos[segundoLugar].votos)
        {
            segundoLugar = i;
        }
    }

    if (candidatos[primeiroLugar].votos > candidatos[segundoLugar].votos)
    {
        return candidatos[primeiroLugar].nome;
    }
    else
    {
        return "Segundo turno";
    }
}
