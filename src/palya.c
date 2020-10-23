#include "palya.h"
#include "debugmalloc.h"

void foglal(int*** palya,Nehezseg n)
{
    int i;
    *palya = malloc(n.magas*sizeof(int *));
    for(i = 0 ; i < n.magas ; i++)
        (*palya)[i] = malloc( n.szeles*sizeof(int) );
}

void felszabadit(int** p, Nehezseg n)
{
    int i;
    for(i = 0 ; i < n.magas ; i++)
        free(p[i]);
    free(p);
}

void aknak_elhelyezese(int** p,Nehezseg n)  //aknak(vagyis 9-esek elhelyezese a palyan
{
    srand(time(NULL));
    for (int i=0; i<n.magas; i++)
    {
        for (int j=0; j<n.szeles; j++)
        {
            p[i][j]=0;
        }
    }
    int db=0;
    while(db!=n.aknaszam)
    {
        int a=rand()%(n.magas);
        int b=rand()%(n.szeles);
        if(p[a][b]!=9)
        {
            p[a][b]=9;
            db=db+1;
        }
    }

}

void kozeli_aknak_szama(int** p,Nehezseg n)   //a kozelben levo aknak meghatarozasa, ahany akna van korulotte azt a szamot irjuk bele a cellaba
{
    for (int i=0; i<n.szeles; i++)
    {
        for (int j=0; j<n.magas; j++)
        {
            if(p[j][i]!=9)
            {
                int szam=0;
                for(int y=-1; y<=1; y=y+1)
                {
                    for(int x=-1; x<=1; x=x+1)
                    {
                        if((i+x)>=0&&(j+y)>=0&&(i+x)<n.szeles&&(j+y)<n.magas)
                        {
                            if(p[j+y][i+x]==9)
                            {
                                szam+=1;
                            }
                        }
                    }
                }
                p[j][i]=szam;
            }
        }
    }
}

bool minden_megtalalva(int** p,Nehezseg n) //a jatek megnyeresenek figyelesere, ha mar csak az aknak felfedetlenek igazat ad vissza
{
    int z=0;
    for(int i=0; i<n.magas; i=i+1)
    {
        for(int j=0; j<n.szeles; j=j+1)
        {
            int a=p[i][j];
            if(a<0)
            {
                z+=1;
            }
        }
    }
    if(z==(n.szeles*n.magas)-n.aknaszam)
    {
        return true;
    }
    else
        return false;
}

void palya_letrehoz(int** p,Nehezseg n)
{
    aknak_elhelyezese(p,n);
    kozeli_aknak_szama(p, n);
}

void felderit(int** p,Nehezseg n,int x, int y)
{
    if (p[y][x] == 0)
    {
        p[y][x]=-9;
        for(int j=-1; j<=1; j=j+1)
        {
            for(int i=-1; i<=1; i=i+1)
            {
                if((i+x)>=0&&(j+y)>=0&&(i+x)<n.szeles&&(j+y)<n.magas)
                {
                    felderit(p,n,(x+i),(j+y));
                }
            }
        }
    }
    else if(p[y][x]!=9&&p[y][x]!=-9)
    {
        if((x)>=0&&(y)>=0&&(x)<n.szeles&&(y)<n.magas)
        {
            if(p[y][x]>=0&&p[y][x]!=9)
            {
                int a=p[y][x];
                p[y][x]=-a;
            }
        }
    }
}

Nehezseg beker()
{
    Nehezseg n;
    printf("Magassag:");
    scanf("%d", &n.magas);
    printf("Szelesseg:");
    scanf("%d", &n.szeles);
    printf("Aknaszam:");
    scanf("%d", &n.aknaszam);
    return n;
}




