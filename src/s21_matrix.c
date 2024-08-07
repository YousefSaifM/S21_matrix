#include "s21_matrix.h"

// Creating matrices
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_code = OK;
  if (result == NULL || rows <= 0 || columns <= 0) {
    return_code = INCORRECT_MATRIX;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      return_code = INCORRECT_MATRIX;
    }
  }
  if (return_code == OK) {
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = (double *)calloc(columns, sizeof(double));
      if (result->matrix[i] == NULL) {
        return_code = INCORRECT_MATRIX;
      }
    }
  }

  return return_code;
}

// cleaning of matrices
void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}

// Matrix comparison
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int return_code = SUCCESS;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    return_code = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return_code = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= 1e-7) {
          return_code = FAILURE;
          break;
        }
      }
    }
  }
  return return_code;
}

// Adding matrices
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    return_code = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return_code = CALCULATION_ERROR;
  } else {
    return_code = s21_create_matrix(A->rows, A->columns, result);
  }
  if (return_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) {
          return_code = CALCULATION_ERROR;
          break;
        }
      }
    }
  }
  return return_code;
}

// subtracting matrices
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    return_code = INCORRECT_MATRIX;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    return_code = CALCULATION_ERROR;
  } else {
    return_code = s21_create_matrix(A->rows, A->columns, result);
  }
  if (return_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        if (!isfinite(result->matrix[i][j])) {
          return_code = CALCULATION_ERROR;
          break;
        }
      }
    }
  }
  return return_code;
}

// Matrix multiplication by scalar
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return_code = INCORRECT_MATRIX;
  } else if (!isfinite(number)) {
    return_code = CALCULATION_ERROR;
  } else {
    return_code = s21_create_matrix(A->rows, A->columns, result);
  }
  if (return_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
        if (!isfinite(result->matrix[i][j])) {
          return_code = CALCULATION_ERROR;
          break;
        }
      }
    }
  }
  return return_code;
}

// Multiplication of two matrices
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      result == NULL) {
    return_code = INCORRECT_MATRIX;
  } else if (A->columns != B->rows) {
    return_code = CALCULATION_ERROR;
  } else {
    return_code = s21_create_matrix(A->rows, B->columns, result);
  }
  if (return_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        double res = 0.0f;
        for (int k = 0; k < A->columns; k++) {
          res += A->matrix[i][k] * B->matrix[k][j];
        }
        result->matrix[i][j] = res;
        if (!isfinite(result->matrix[i][j])) {
          return_code = CALCULATION_ERROR;
          break;
        }
      }
    }
  }
  return return_code;
}

// Matrix transpose
int s21_transpose(matrix_t *A, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return_code = INCORRECT_MATRIX;
  } else {
    return_code = s21_create_matrix(A->columns, A->rows, result);
  }
  if (return_code == OK) {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return return_code;
}

// Minor of matrix and matrix of algebraic complements
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int return_code = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return_code = INCORRECT_MATRIX;
  } else if (A->rows == 1 || A->columns == 1) {
    return_code = CALCULATION_ERROR;
  } else {
    return_code = s21_create_matrix(A->rows, A->columns, result);
  }
  matrix_t tmp = {0};
  if (return_code == OK) {
    return_code = s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);
  }
  if (return_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_copy_minor(A, &tmp, i, j);
        double d = 0;
        return_code = s21_determinant(&tmp, &d);
        result->matrix[i][j] = d * pow(-1, i + j);
      }
    }
  }
  s21_remove_matrix(&tmp);
  return return_code;
}

// Matrix determinant
int s21_determinant(matrix_t *A, double *result) {
  int return_code = OK;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return_code = INCORRECT_MATRIX;
  } else if (!s21_is_square_matrix(A)) {
    return_code = CALCULATION_ERROR;
  }
  if (return_code == OK) {
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else if (A->rows > 2) {
      *result = 0;
      double res = 0, tmp = 0;
      for (int i = 0; i < A->columns; i++) {
        matrix_t *minor = s21_create_minor(0, i, A);
        if (minor == NULL) {
          return_code = INCORRECT_MATRIX;
          break;
        }
        return_code = s21_determinant(minor, &tmp);
        if (return_code == OK) {
          res = pow(-1, i) * A->matrix[0][i] * tmp;
          *result += res;
        }
        s21_remove_matrix(minor);
        free(minor);
        minor = NULL;
      }
    }
  }
  return return_code;
}

// Inverse of the matrix
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_code = OK;
  double determinat = 0.0;
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return_code = INCORRECT_MATRIX;
  } else {
    return_code = s21_determinant(A, &determinat);
  }
  if (return_code == OK && determinat != 0 && s21_is_square_matrix(A)) {
    if (A->rows == 1) {
      return_code = s21_create_matrix(A->rows, A->columns, result);
      if (return_code == OK) {
        result->matrix[0][0] = 1 / A->matrix[0][0];
      }
    } else {
      /////////////////////////////////////
      matrix_t A_T = {0};
      matrix_t A_alg = {0};
      return_code = s21_calc_complements(A, &A_alg);
      if (return_code == OK) {
        return_code = s21_transpose(&A_alg, &A_T);
      }
      if (return_code == OK) {
        return_code = s21_mult_number(&A_T, 1 / determinat, result);
      }
      s21_remove_matrix(&A_alg);
      s21_remove_matrix(&A_T);
      /////////////////////////////////////
    }
  } else if (return_code == OK) {
    return_code = CALCULATION_ERROR;
  }
  return return_code;
}
