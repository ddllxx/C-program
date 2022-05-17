#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_timer.h"
#include "SDL2/SDL_video.h"
#include "draw_texture.h"
#include <stdio.h>

Uint32 update(Uint32 n, void *p);
int init_all(const char *init_file);
int sub_init(void);
void free_all(void);

const int width = 960;
const int height = 720;

static SDL_Renderer *pRender = NULL;
static SDL_Window *pWnd = NULL;
static SDL_Texture *pGrid_texture = NULL;
static SDL_Texture *pTips_texture = NULL;
static Grid grid = {0, 0, NULL};

// change times
static int count = 0;
static int limit = 0;
static int delay = 0;

// status : run next stop
enum Statu {life_next = 1, life_run = 2, life_stop = 3};
static enum Statu go = life_stop;

int main(int argc, char *argv[]) {
    // deal with the args
    if (argc == 5) {
        limit = atoi(argv[1]);
        delay = atoi(argv[2]);
        init_grid2(&grid, atoi(argv[3]), atoi(argv[4]), 0);
        if (sub_init() != 0) {
            free_all();
            printf("error\n");
            return -1;
        }
    } else if (argc == 2) {
        if (init_all(argv[1]) != 0) {
            free_all();
            printf("error\n");
            return -1;
        }
    } else {
        printf("Usage: %s %s", argv[0], "initial status file");
        printf(" OR:\n""%s limit_steps update_interval row col\n", argv[0]);
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
                    go = life_stop;
                } else if (event.key.keysym.sym == SDLK_n) {
                    if (count == limit) {
                        limit = -1;
                    }
                    go = life_next;
                } else if (event.key.keysym.sym == SDLK_r) {
                    if (count == limit) {
                        limit = -1;
                    }
                    go = life_run;
                } else if (event.key.keysym.sym == SDLK_d) {
                    char name[256];
                    sprintf(name, "%s_%d.txt", "shot", count);
                    output_file(&grid, delay, name);
                }
                break;
            case SDL_MOUSEBUTTONDOWN: {
                if (event.button.state != SDL_BUTTON_LEFT) {
                    break;
                }
                int posX = event.button.x;
                int posY = event.button.y;
                if (posX > height || posY > height) {
                    break;
                }
                // bad design, but for convenience
                int index_i = posY / (height / (double)grid.row);
                int index_j = posX / (height / (double)grid.col);
                switch_grid_cell(&grid, index_i, index_j);
                break;
            }
            default:
                break;
            }
        }
    }
    free_all();
    return 0;
}

// will be called after interval
Uint32 update(Uint32 interval, void *p) {
    // detect if output the file
    static int output = 0;
    enum Statu *statu = p;
    if (*statu == life_run) {
        // if (update_grid(&grid) == 0) {
        //     *statu = life_stop;
        // } else {
        //     count++;
        // }
        update_grid(&grid);
        count++;
    } else if (*statu == life_next) {
        // if (update_grid(&grid) != 0) {
        //     count++;
        // }
        update_grid(&grid);
        count++;
        *statu = life_stop;
    } else if (*statu != life_stop) {
        return 0;
    }
    if (count == limit) {
        *statu = life_stop;
        if (!output) {
            output_file(&grid, delay, "output_shot.txt");
            output = 1;
        }
    }
    SDL_SetRenderDrawColor(pRender, 255, 255, 255, 255);
    SDL_RenderClear(pRender);
    SDL_Rect rect = {height, 0, width - height, height};
    SDL_RenderCopy(pRender, pTips_texture, NULL, &rect);
    draw_grid_texture(&grid, pRender, pGrid_texture, height);
    rect.x = 0, rect.y = 0, rect.w = height, rect.h = height;
    SDL_RenderCopy(pRender, pGrid_texture, NULL, &rect);
    SDL_RenderPresent(pRender);
    return interval;
}

int init_all(const char *init_file) {
    FILE *fp = fopen(init_file, "r");
    if (fp == NULL) {
        fprintf(stderr, "can't find %s\n", init_file);
        return -1;
    }
    fscanf(fp, "%d%d", &limit, &delay);
    init_grid(&grid, fp);
    return sub_init();
}

int sub_init(void) {
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
    	return -1;
    }
    return 0;
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
    SDL_Quit();
}
