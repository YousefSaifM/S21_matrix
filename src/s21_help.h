#ifndef S21_HELP_H
#define S21_HELP_H

void s21_copy_minor(matrix_t *A, matrix_t *result, int y, int x);
int s21_is_square_matrix(matrix_t *A);
matrix_t *s21_create_minor(int y, int x, matrix_t *A);

void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step);

#endif