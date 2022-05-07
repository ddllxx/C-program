#include <stdio.h>

typedef struct Grid {
    int row;
    int col;
    int **gridData;
} Grid;

void init_grid(Grid *pGrid, int *delay, FILE *fp);

int calc_neighbor(const Grid *pGrid, int i, int j);

int update_grid(Grid *pGrid);

void free_grid(Grid *pGrid);

void output_file(const Grid *pGrid, int delay, const char *filename);
