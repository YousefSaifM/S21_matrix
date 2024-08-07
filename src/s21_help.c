#include "s21_matrix.h"

// this function is used in "s21_calc_complements()" and
// "s21_is_square_matrix()" functions.
void s21_copy_minor(matrix_t *input, matrix_t *result, int except_row,
                    int except_column) {
  for (int i = 0, result_row = 0; i < input->rows; i++) {
    if (i != except_row) {
      for (int j = 0, result_column = 0; j < input->columns; j++) {
        if (j != except_column) {
          result->matrix[result_row][result_column] = input->matrix[i][j];
          result_column++;
        }
      }
      result_row++;
    }
  }
}

// this is used in "s21_determinant()" and "s21_inverse_matrix()" functions.
int s21_is_square_matrix(matrix_t *A) {
  int return_code = OK;
  if (A == NULL || A->matrix == NULL) {
    return_code = INCORRECT_MATRIX;
  }
  return_code = (A->rows == A->columns) ? 1 : 0;
  return return_code;
}

// this is used in "s21_determinant()" function
matrix_t *s21_create_minor(int y, int x, matrix_t *A) {
  matrix_t *minor = NULL;
  if (A != NULL && A->matrix != NULL) {
    minor = calloc(1, sizeof(matrix_t));
    if (s21_create_matrix(A->rows - 1, A->columns - 1, minor) == OK) {
      s21_copy_minor(A, minor, y, x);
    }
  }
  return minor;
}

// this is used in tests.
void s21_initialize_matrix(matrix_t *A, double start_value,
                           double iteration_step) {
  if (A != NULL && A->matrix != NULL) {
    double value = start_value;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        A->matrix[i][j] = value;
        value += iteration_step;
      }
    }
  }
}
