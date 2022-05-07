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
static SDL_Texture *pTips_texture = NULL;
static Grid grid = {0, 0, NULL};
static int go = 2;
void free_all();
int main(int argc, char *argv[]) {
    int delay;
    FILE *fp = fopen("grid.txt", "r");
    if (fp == NULL) {
        printf("can't find the initial file: %s\n", "grid.txt");
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
        SDL_TEXTUREACCESS_TARGET, height, height);
    pTips_texture = get_button_texture(pRender);
    if (pRender == NULL || pWnd == NULL || pGrid_texture == NULL || pTips_texture == NULL) {
    	printf("initial failure!\n");
    	return 0;
    }
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
                if (event.key.keysym.sym == SDLK_s) {
                    go = 2;
                } else if (event.key.keysym.sym == SDLK_n) {
                    go = 3;
                } else if (event.key.keysym.sym == SDLK_r) {
                    go = 1;
                } else if (event.key.keysym.sym == SDLK_d) {
                    output_file(&grid, delay, "status_shot.txt");
                }
                break;
            default:
                break;
            }
        }
    }
    free_all();
    SDL_Quit();
    return 0;
}

// will be call after interval
Uint32 update(Uint32 interval, void *p) {
    if (*(int *)p == 0) {
        return 0;
    }
    if (*(int *)p != 2) {
        if (update_grid(&grid) == 0) {
            *(int *)p = 2;
        }
    }
    if (*(int *)p == 3) {
        *(int *)p = 2;
    }
    SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255);
    SDL_RenderClear(pRender);
    SDL_Rect rect = {height + 1, 0, width - height, height};
    SDL_RenderCopy(pRender, pTips_texture, NULL, &rect);
    draw_grid_texture(&grid, pRender, pGrid_texture, height);
    rect.x = 0, rect.y = 0, rect.w = height, rect.h = height;
    SDL_RenderCopy(pRender, pGrid_texture, &rect, &rect);
    SDL_RenderPresent(pRender);
    return interval;
}

void free_all() {
    if (pRender) {
    	SDL_DestroyRenderer(pRender);
    }
    if (pWnd) {
    	SDL_DestroyWindow(pWnd);
    }
    if (pGrid_texture) {
    	SDL_DestroyTexture(pGrid_texture);
    }
    if (pTips_texture) {
    	SDL_DestroyTexture(pTips_texture);
    }
}
