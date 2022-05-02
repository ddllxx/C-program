#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "draw_texture.h"
#include <stdio.h>

const int width = 800;
const int height = 600;
int main(int argc, char *argv[]) {
    Grid grid;
    int delay;
    FILE *fp = fopen("grid.txt", "r");
    // fopen_s(&fp, "grid2.txt", "r");
    if (fp == NULL) {
        printf("hhh");
        return 0;
    }
    init_grid(&grid, &delay, fp);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *pWnd = SDL_CreateWindow("game of life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    SDL_Renderer *pRender = SDL_CreateRenderer(pWnd, -1, SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
    SDL_Texture *pTexture = SDL_CreateTexture(pRender, SDL_GetWindowSurface(pWnd)->format->format, SDL_TEXTUREACCESS_TARGET, width, height);
    // SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRender, SDL_GetWindowSurface(pWnd));
    SDL_ShowWindow(pWnd);
    draw_texture(&grid, pRender, pTexture);
    SDL_RenderCopy(pRender, pTexture, NULL, NULL);
    SDL_RenderPresent(pRender);
    SDL_Event event;
    int flag = 1;
    while (flag) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                flag = 0;
                break;
            case SDL_KEYDOWN:
                printf("Hello World\n");
                break;
            default:
                break;
            }
        }
    }
    SDL_DestroyWindow(pWnd);
    // SDL_DestroyTexture()
    SDL_DestroyRenderer(pRender);
    return 0;
}
