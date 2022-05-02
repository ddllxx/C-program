#include "draw_texture.h"
#include "SDL2/SDL_render.h"
#include <stdio.h>

extern int height, width;

void draw_texture(const Grid *pGrid, SDL_Renderer *pRender, SDL_Texture *pTexture) {
    SDL_Texture *temp = SDL_GetRenderTarget(pRender);
    SDL_SetRenderTarget(pRender, pTexture);
    SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255);
    SDL_RenderClear(pRender);
    SDL_SetRenderDrawColor(pRender, 0, 0, 0, 255);
    for (int i = 0; i <= pGrid->row; i++) {
        SDL_RenderDrawLine(pRender, 0, height * i / pGrid->row, width, height * i / pGrid->row);
    }
    printf("%d%d\n", pGrid->row, pGrid->col);
    for (int j = 0; j <= pGrid->col; j++) {
        SDL_RenderDrawLine(pRender, width * j / pGrid->col, 0, width * j / pGrid->col, height);
    }
    SDL_RenderPresent(pRender);
    SDL_SetRenderTarget(pRender, temp);
}
