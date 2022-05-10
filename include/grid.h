#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#define ERREXIR(message) do {\
    fprintf(stderr, message);\
    exit(EXIT_FAILURE);\
} while (0)
typedef struct Grid {
    int row;
    int col;
    int **gridData;
} Grid;

void init_grid(Grid *pGrid, FILE *fp);

int calc_neighbor(const Grid *pGrid, int i, int j);

int update_grid(Grid *pGrid);

void free_grid(Grid *pGrid);

void output_file(const Grid *pGrid, int delay, const char *filename);
