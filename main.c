#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void backtrack(char ***res,
               int *resSize,
               int **map,
               int curr_row,
               int *col,
               int *p_diag,
               int *n_diag,
               int nqueens,
               int level)
{
    if (level == 0) {
        // res = realloc(res, (*resSize + 1) * sizeof(char **));
        res[*resSize] = malloc(nqueens * sizeof(char *));
        for (int i = 0; i < nqueens; i++) {
            res[*resSize][i] = calloc(nqueens + 1, sizeof(char));
            for (int j = 0; j < nqueens; j++)
                res[*resSize][i][j] = (map[i][j] == 0) ? '.' : 'Q';
        }
        (*resSize)++;
        return;
    }

    for (int j = 0; j < nqueens; j++) {
        if (col[j] == 0 && p_diag[curr_row + j] == 0 &&
            n_diag[curr_row - j + nqueens - 1] == 0 && map[curr_row][j] == 0) {
            col[j] = 1;
            p_diag[curr_row + j] = 1;
            n_diag[curr_row - j + nqueens - 1] = 1;
            map[curr_row][j] = 1;
            backtrack(res, resSize, map, curr_row + 1, col, p_diag, n_diag,
                      nqueens, level - 1);
            col[j] = 0;
            p_diag[curr_row + j] = 0;
            n_diag[curr_row - j + nqueens - 1] = 0;
            map[curr_row][j] = 0;
        }
    }
}

char ***solveNQueens(int n, int *returnSize, int **returnColumnSizes)
{
    char ***res = malloc(352 * sizeof(char **));  // 9 queen solution is 352.
    int *col = calloc(n, sizeof(int));
    int *p_diag = calloc(2 * n - 1, sizeof(int)); // pos. slope: right-up left-bottom
    int *n_diag = calloc(2 * n - 1, sizeof(int)); // neg. slope: tight-bottom left-up
    int **map = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        map[i] = calloc(n, sizeof(int));
    *returnSize = 0;

    backtrack(res, returnSize, map, 0, col, p_diag, n_diag, n, n);

    *returnColumnSizes = malloc((*returnSize) * sizeof(int));
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = n;

    free(col);
    free(p_diag);
    free(n_diag);
    for (int i = 0; i < n; i++)
        free(map[i]);
    free(map);
    return res;
}

int main() {
    int n = 4;
    int returnSize;
    int *returnColumnSizes;
    char ***result = solveNQueens(n, &returnSize, &returnColumnSizes);

    printf("Input: n = %d\n", n);
    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            if (j > 0) printf(",");
            printf("\"%s\"", result[i][j]);
        }
        printf("]");
        if (i < returnSize - 1) printf(",");
    }
    printf("]\n");

    n = 1;
    result = solveNQueens(n, &returnSize, &returnColumnSizes);

    printf("Input: n = %d\n", n);
    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("[");
        for (int j = 0; j < n; j++) {
            if (j > 0) printf(",");
            printf("\"%s\"", result[i][j]);
        }
        printf("]");
        if (i < returnSize - 1) printf(",");
    }
    printf("]\n");

    // Free memory
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < n; j++) {
            free(result[i][j]);
        }
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}
