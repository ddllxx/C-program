#include "draw_texture.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_stdinc.h"
#include "SDL2/SDL_surface.h"
#include <stdio.h>


// draw the grid
void draw_grid_texture(const Grid *pGrid, SDL_Renderer *pRender, SDL_Texture *pTexture, int size) {
    if (pGrid == NULL || pRender == NULL || pTexture == NULL || size <= 0) {
        ERREXIR("error NULL pointer");
    }
    int height = size;
    int width = size;
    // save the environment
    SDL_Texture *temp = SDL_GetRenderTarget(pRender);
    Uint8 old_r, old_g, old_b, old_a;
    SDL_GetRenderDrawColor(pRender, &old_r, &old_g, &old_b, &old_a);

    // clean the texture
    SDL_SetRenderTarget(pRender, pTexture);
    SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255);
    SDL_RenderClear(pRender);

    // draw grid
    SDL_SetRenderDrawColor(pRender, 255, 128, 0, 255);
    for (int i = 0; i <= pGrid->row; i++) {
        SDL_RenderDrawLine(pRender, 0, height * i / pGrid->row, width, height * i / pGrid->row);
    }

    for (int j = 0; j <= pGrid->col; j++) {
        SDL_RenderDrawLine(pRender, width * j / pGrid->col - 1, 0, width * j / pGrid->col - 1, height);
    }

    // draw cells
    SDL_SetRenderDrawColor(pRender, 0, 0, 0, 255);
    for (int i = 0; i < pGrid->row; i++) {
        for (int j = 0; j < pGrid->col; j++) {
            if (pGrid->gridData[i][j]) {
                SDL_Rect rect = {j * width / pGrid->col + 1, i * height / pGrid->row + 1,
                    width / pGrid->col - 2, height / pGrid->row - 2};
                SDL_RenderFillRect(pRender, &rect);
            }
        }
    }
    // recover
    SDL_RenderPresent(pRender);
    SDL_SetRenderDrawColor(pRender, old_r, old_g, old_b, old_a);
    SDL_SetRenderTarget(pRender, temp);
}

SDL_Texture *get_button_texture(SDL_Renderer *pRender) {
    if (pRender == NULL) {
        ERREXIR("error NULL pointer");
    }
    SDL_Surface *pSurf = SDL_LoadBMP("./resources/tips.bmp");
    SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(pRender, pSurf);
    SDL_FreeSurface(pSurf);
    return tempTexture;
}
