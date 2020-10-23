#ifndef DICSOSEGLISTA_H_INCLUDED
#define DICSOSEGLISTA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct Jatekos
{
    char nev[10];
    int ido;
} Jatekos;

typedef struct ListaElem
{
    char nev[10];
    int ido;
    struct ListaElem *kov;
} ListaElem;

void kozvetlen(Jatekos *t, int db);
void dicsoseglista(int ujido);

#endif // DICSOSEGLISTA_H_INCLUDED
