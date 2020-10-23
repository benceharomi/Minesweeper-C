#include "renderer.h"
#include "debugmalloc.h"

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

void cella_rajzol(SDL_Renderer *renderer, SDL_Texture *cellak, Cella melyik, int x, int y)
{
    SDL_Rect src = { (melyik%12)*BLOCKSIZE,(melyik/12)*BLOCKSIZE, BLOCKSIZE,BLOCKSIZE};
    SDL_Rect dest= { x, y, BLOCKSIZE,BLOCKSIZE};
    SDL_RenderCopy(renderer, cellak, &src, &dest);
}
