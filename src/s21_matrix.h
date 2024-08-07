#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdlib.h>

// - 0 - OK
// - 1 - Error, incorrect matrix
// - 2 - Calculation error
#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

// for cmoparison
#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Creating matrices and cleaning of matrices
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

// Matrix comparison (eq_matrix)
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Adding and subtracting matrices
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Matrix multiplication by scalar (mult_number). Multiplication of two matrices
// (mult_matrix)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Matrix transpose (transpose)
int s21_transpose(matrix_t *A, matrix_t *result);

// Minor of matrix and matrix of algebraic complements (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);

// Matrix determinant
int s21_determinant(matrix_t *A, double *result);

// Inverse of the matrix (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#include "s21_help.h"

#endif