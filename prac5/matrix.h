#ifndef MATRIX_H
#define MATRIX_H

#define DIM 8
#define SIZE (DIM*DIM*sizeof(float))

typedef float (* const matrix)[DIM];

void print_matrix(const matrix a);

void prod_matrix(const matrix a, const matrix b, matrix r, int minf, int maxf, int minc, int maxc);

void const_matrix(matrix m, float v);
void save_matrix(const char filename[],const matrix m);
void load_matrix(const char filename[], matrix m);

#endif
