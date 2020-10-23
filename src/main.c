#include <stdio.h>
#include <stdlib.h>
#include "palya.h"
#include "dicsoseglista.h"
#include "debugmalloc.h"



int main(int argc, char *argv[])
{
    int** p;
    Nehezseg n=beker();
    foglal(&p,n);
    palya_letrehoz(p,n);

    // ablak létrehozása
    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init("Minesweeper", n.szeles*BLOCKSIZE, n.magas*BLOCKSIZE, &window, &renderer);
    // textúra megnyitása
    SDL_Texture *cellak =IMG_LoadTexture(renderer, "res/tiles.jpg");
    if(cellak==NULL)
    {
        SDL_Log("Nem nyithato meg a kepfajl: %s", IMG_GetError());
        exit(1);
    }
    // pálya rajzolása

    for (int i=0; i<n.szeles; i++)
    {
        for (int j=0; j<n.magas; j++)
        {
            cella_rajzol(renderer, cellak, c_fedett, i*BLOCKSIZE, j*BLOCKSIZE);
        }
    }
    clock_t start = clock();

    SDL_RenderPresent(renderer);

    bool quit = false;
    bool minden=false;
    bool revealed=false;
    bool win=false;
    bool jelzo=true;
    int elozox = 0;
    int elozoy = 0;
    while (!quit)
    {
        SDL_Event event;
        SDL_WaitEvent(&event);
        bool tortenes = false;
        switch (event.type)
        {
        case SDL_MOUSEBUTTONDOWN:
            // bal kattintásra történés
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                elozox = event.button.x;
                elozoy = event.button.y;
                int x=elozox/BLOCKSIZE;
                int y=elozoy/BLOCKSIZE;
                //ha a katitintott cella bomba, minden felfedésre kerül
                if(p[y][x]==9)
                {
                    for(int i=0; i<n.magas; ++i)
                    {
                        for(int j=0; j<n.szeles; ++j)
                        {
                            for(int k=0; k<12; ++k)
                            {
                                if(p[i][j]==k)
                                {
                                    cella_rajzol(renderer, cellak, k, j*BLOCKSIZE, i*BLOCKSIZE);
                                }
                            }
                        }
                    }
                    revealed=true;
                }
                //ha ures, akkor a környező aknamentes terület is
                else if(p[y][x]==0)
                {
                    felderit(p,n,x,y);
                    minden_megtalalva(p,n);
                    p[y][x]=-9;
                    for(int i=0; i<n.magas; ++i)
                    {
                        for(int j=0; j<n.szeles; ++j)
                        {
                            for(int k=1; k<9; k++)
                            {
                                if(p[i][j]==-9)
                                {
                                    cella_rajzol(renderer, cellak, 0, j*BLOCKSIZE, i*BLOCKSIZE);
                                }
                                else if(p[i][j]==-k)
                                {
                                    cella_rajzol(renderer, cellak, k, j*BLOCKSIZE, i*BLOCKSIZE);
                                }
                            }
                        }
                    }
                }
                //ha bármi más akkor csak az a cella
                else
                {
                    if(p[y][x]>0)
                    {
                        int a=p[y][x];
                        p[y][x]=-a;
                    }

                    for(int k=0; k<12; ++k)
                    {
                        if(p[y][x]==-k&&p[y][x]!=-9)
                        {
                            cella_rajzol(renderer, cellak, k, x*BLOCKSIZE, y*BLOCKSIZE);
                        }
                    }
                }
                minden=minden_megtalalva(p,n);//ha minden megtalalva akkor a wint ihgazra allitjuk mert megnyerte a jatekos a jatekot
                if(minden)
                {
                    quit=true;
                    win=true;
                }
                tortenes =true;
            }
            //jobb egér kattintásra történes
            else if (event.button.button == SDL_BUTTON_RIGHT)
            {
                elozox = event.button.x;
                elozoy = event.button.y;
                int x=elozox/BLOCKSIZE;
                int y=elozoy/BLOCKSIZE;
                //jelzo lerakasa
                if(p[y][x]>=0&&revealed==false)
                {
                    if(jelzo)
                    {
                        cella_rajzol(renderer, cellak, c_jelzo, x*BLOCKSIZE, y*BLOCKSIZE);
                        jelzo=false;
                    }
                    else
                    {
                        cella_rajzol(renderer, cellak, c_fedett, x*BLOCKSIZE, y*BLOCKSIZE);
                        jelzo=true;
                    }
                }
                tortenes = true;
            }
            break;
        case SDL_QUIT:
            quit = true;
            break;
        }
        if (tortenes)
            SDL_RenderPresent(renderer);

    }


    clock_t end = clock();
    int ido = (int)(end - start) / CLOCKS_PER_SEC;
    if(win)
    {
        SDL_DestroyWindow(window);
        printf("Nyertel!\n");
        dicsoseglista(ido);
    }
    else
    {
        printf("Vesztettel\n");
    }
    SDL_DestroyTexture(cellak);
    SDL_Quit();
    felszabadit(p,n);
    return 0;
}
