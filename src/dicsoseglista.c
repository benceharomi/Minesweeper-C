#include "dicsoseglista.h"
#include "debugmalloc.h"

void kozvetlen(Jatekos *t, int db)   //novekvo sorrendbe rendezi a tombot, hogy jo sorrendben irja ki a nyerteseket
{
    for (int i = 0; i < db-1; ++i)
    {
        int minindex = i;
        for (int j = i+1; j < db; ++j)
            if (t[j].ido < t[minindex].ido)
                minindex = j;

        if (minindex != i)
        {
            int temp = t[minindex].ido;
            char tempnev[10];
            for(int j=0; j<10; ++j)
            {
                tempnev[j]=t[minindex].nev[j];
            }
            t[minindex].ido = t[i].ido;
            for(int j=0; j<10; ++j)
            {
                t[minindex].nev[j]=t[i].nev[j];
            }
            t[i].ido = temp;
            for(int j=0; j<10; ++j)
            {
                t[i].nev[j]=tempnev[j];
            }
        }
    }
}

void dicsoseglista(int ujido)
{
    FILE * fp;
    Jatekos jatekos[100];
    int ido;
    char nev[10];
    char ujnev[10];
    int j=0;

    if( access("save/dicsoseglista", F_OK ) != -1 )
    {
        // ha letezik a fajl, beolvassunk a jelenlegi adatokat
        fp = fopen("save/dicsoseglista", "r+");
        for(; !feof(fp); ++j)
        {
            fscanf(fp,"%s", nev);
            fscanf(fp," %d ", &ido);
            strcpy(jatekos[j].nev,nev);
            jatekos[j].ido=ido;
        }
    }
    else
    {
        // ha nem letezik (mert az elso jatekos jatszik) letrehozzuk a fajlt
        fp = fopen("save/dicsoseglista", "w+");
    }
    printf("Nev:");
    scanf("%s", ujnev);
    strcpy(jatekos[j].nev,ujnev);
    jatekos[j].ido=ujido;
    fprintf(fp,"%-10s",jatekos[j].nev);
    fprintf(fp," %d ",jatekos[j].ido);
    kozvetlen(jatekos,j);
    printf("Nev:      Ido:\n");
    int i=1;
    for(int x=0; x<j+1; ++x,++i)
    {
        printf("%2d. %-10s ", i, jatekos[x].nev);
        int perc=jatekos[x].ido/60;
        int masodperc=jatekos[x].ido;
        if(perc>0)
        {
            masodperc=masodperc-(perc*60);
        }
        printf("%4d perc%4d masodperc", jatekos[x].ido/60, masodperc);
        printf("\n");

    }
    fclose(fp);
}
