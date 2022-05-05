#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_video.h"
#include "draw_texture.h"
#include <stdio.h>

Uint32 update(Uint32 n, void *p);

const int width = 960;
const int height = 720;
static SDL_Renderer *pRender = NULL;
static SDL_Window *pWnd = NULL;
static SDL_Texture *pGrid_texture = NULL;
static Grid grid = {0, 0, NULL};
static int go = 1;

int main(int argc, char *argv[]) {
    int delay;
    FILE *fp = fopen("grid.txt", "r");
    if (fp == NULL) {
        printf("hhh");
        return 0;
    }
    // init all data we need
    init_grid(&grid, &delay, fp);
    SDL_Init(SDL_INIT_VIDEO);
    pWnd = SDL_CreateWindow("game of life", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    pRender = SDL_CreateRenderer(pWnd, -1,
        SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
    pGrid_texture = SDL_CreateTexture(pRender, SDL_GetWindowPixelFormat(pWnd),
        SDL_TEXTUREACCESS_TARGET, width, height);
    SDL_ShowWindow(pWnd);

    SDL_TimerID timmer_id = SDL_AddTimer(delay, update, &go);
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
    SDL_DestroyTexture(pGrid_texture);
    SDL_DestroyRenderer(pRender);
    return 0;
}

// will be call after interval
Uint32 update(Uint32 interval, void *p) {
    if (*(int *)p == 0) {
        return 0;
    }
    if (*(int *)p != 2) {
        update_grid(&grid);
    }
    draw_grid_texture(&grid, pRender, pGrid_texture, height);
    SDL_RenderCopy(pRender, pGrid_texture, NULL, NULL);
    SDL_RenderPresent(pRender);
    return interval;
}
