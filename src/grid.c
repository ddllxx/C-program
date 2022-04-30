#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

Grid grid = {0, 0, NULL};
int delay = 0;

int **alloc_grid(const Grid *pGrid);

void init_grid(Grid *pGrid, int *delay, FILE *fp) {
    // fscanf_s(fp, "%d%d%d", &pGrid->row, &pGrid->col, delay);
    fscanf(fp, "%d%d%d", &pGrid->row, &pGrid->col, delay);
    pGrid->gridData = alloc_grid(pGrid);
    for (int i = 0; i < pGrid->row; i++) {
        for (int j = 0; j < pGrid->col; j++) {
            fscanf(fp, "%d", &pGrid->gridData[i][j]);
        }
    }
}

int calc_neighbor(const Grid *pGrid, int i, int j) {
    int sum = 0;
    int start_i = i > 0 ? i - 1 : 0;
    int start_j = j > 0 ? j - 1 : 0;
    int end_i = i < pGrid->row - 1 ? i + 1 : i;
    int end_j = j < pGrid->col - 1 ? j + 1 : j;
    for (int p = start_i; p <= end_i; p++) {
        for (int q = start_j; q <= end_j; q++) {
            sum += pGrid->gridData[p][q];
        }
    }
    return sum;
}

void update_grid(Grid *pGrid) {
    int **new_data = alloc_grid(pGrid);
    for (int i = 0; i < pGrid->row; i++) {
        for (int j = 0; j < pGrid->col; j++) {
            int count_neighbor = calc_neighbor(pGrid, i, j);
            if (count_neighbor <= 1) {
                new_data[i][j] = 0;
            } else if (count_neighbor == 2) {
                new_data[i][j] = pGrid->gridData[i][j];
            } else if (count_neighbor == 3) {
                new_data[i][j] = 1;
            } else {
                new_data[i][j] = 0;
            }
        }
    }
    free_grid(pGrid);
    pGrid->gridData = new_data;
}

int **alloc_grid(const Grid *pGrid) {
    int **data = malloc(pGrid->row * sizeof(int *));
    for (int i = 0; i < pGrid->row; ++i) {
        data[i] = malloc(pGrid->col * sizeof(int));
    }
    return data;
}

void free_grid(Grid *pGrid) {
    for (int i = 0; i < pGrid->row; i++) {
        free(pGrid->gridData[i]);
    }
    free(pGrid->gridData);
}

void output_file(const Grid *pGrid, int delay, const char *filename) {
    FILE * output = fopen(filename, "w+");
    // fopen_s(&output, filename, "w+");
    if (output == NULL) {
        fprintf(stderr, "can't open %s\n", filename);
    }
    fprintf(output, "%d %d %d\n", pGrid->row, pGrid->col, delay);
    for (int i = 0; i < pGrid->row; i++) {
        for (int j = 0; j < pGrid->col; j++) {
            fprintf(output, "%d", pGrid->gridData[i][j]);
            if (j != pGrid->col - 1) {
                fputc(' ', output);
            }
        }
        if (i != pGrid->row - 1) {
            fputs("\n", output);
        }
    }
}

