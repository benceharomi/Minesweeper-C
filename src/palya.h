#ifndef PALYA_H_INCLUDED
#define PALYA_H_INCLUDED
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "renderer.h"


typedef struct Nehezseg
{
    int szeles,magas,aknaszam;
} Nehezseg;
void foglal(int*** p, Nehezseg n);
void aknak_elhelyezese(int** p,Nehezseg n);
void felszabadit(int** p, Nehezseg n);
void kozeli_aknak_szama(int** p,Nehezseg n);
bool minden_megtalalva(int** p,Nehezseg n);
void palya_letrehoz(int** palya,Nehezseg n);
void felderit(int** p,Nehezseg n,int x, int y);
Nehezseg beker();

#endif // PALYA_H_INCLUDED
