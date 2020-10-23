#ifndef RENDERER_H_INCLUDED
#define RENDERER_H_INCLUDED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#define BLOCKSIZE 32

typedef enum Cella {c_ures, c_szam1, c_szam2, c_szam3, c_szam4, c_szam5, c_szam6, c_szam7, c_szam8, c_akna, c_fedett,c_jelzo} Cella;

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer);
void cella_rajzol(SDL_Renderer *renderer, SDL_Texture *cellak, Cella melyik, int x, int y);

#endif // RENDERER_H_INCLUDED
