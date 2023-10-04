#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix *m);
Matrix resize_matrix(Matrix *m, int new_rows, int new_cols);
int get_rows(Matrix *m);
int get_cols(Matrix *m);
void save_matrix_to_file(Matrix *m, const char* filename);
Matrix load_matrix_from_file(const char* filename);
void set_element(Matrix *m, int row, int col, double val);
double get_element(Matrix *m, int row, int col);
void print_matrix(Matrix *m);
Matrix add_matrices(Matrix *a, Matrix *b);
Matrix subtract_matrices(Matrix *a, Matrix *b);
Matrix multiply_matrices(Matrix *a, Matrix *b);
Matrix scalar_multiply_matrix(Matrix *m, double scalar);

int main() {
    Matrix m1 = create_matrix(3, 3);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            set_element(&m1, i, j, i + j);

    printf("Matrix m1:\n");
    print_matrix(&m1);

    Matrix m2 = create_matrix(3, 3);
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            set_element(&m2, i, j, 2 * (i + j));

    printf("Matrix m2:\n");
    print_matrix(&m2);

    printf("m1 + m2:\n");
    Matrix sum = add_matrices(&m1, &m2);
    print_matrix(&sum);

    printf("m1 - m2:\n");
    Matrix diff = subtract_matrices(&m1, &m2);
    print_matrix(&diff);

    printf("m1 * m2:\n");
    Matrix product = multiply_matrices(&m1, &m2);
    print_matrix(&product);

    printf("m1 * 5:\n");
    Matrix scal = scalar_multiply_matrix(&m1, 5.0);
    print_matrix(&scal);

    printf("Save m1 to file:\n");
    save_matrix_to_file(&m1,"m.txt");

    printf("m1 getrows(); m1 getcols()\n");
    int rows = get_rows(&m1);
    int cols = get_cols(&m1);
    printf("Rows: %d  Cols: %d\n", rows, cols);

    printf("m1 resize to 5:4\n");
    Matrix resz = resize_matrix(&m1,5,4);
    print_matrix(&resz);

    printf("Load m1 from file:\n");
    Matrix loader = load_matrix_from_file("m.txt");
    print_matrix(&loader);

    free_matrix(&m1);
    free_matrix(&m2);
    free_matrix(&sum);
    free_matrix(&diff);
    free_matrix(&product);
    free_matrix(&scal);
    free_matrix(&resz);
    return 0;
}
// functions
Matrix create_matrix(int rows, int cols) {
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = (double **)malloc(rows * sizeof(double *));
    for(int i = 0; i < rows; i++)
        m.data[i] = (double *)malloc(cols * sizeof(double));
    return m;
}

void free_matrix(Matrix *m) {
    for(int i = 0; i < m->rows; i++)
        free(m->data[i]);
    free(m->data);
}
int get_rows(Matrix *m) { return m->rows; }
int get_cols(Matrix *m) { return m->cols; }
void set_element(Matrix *m, int row, int col, double val) {
    m->data[row][col] = val;
}
double get_element(Matrix *m, int row, int col) {
    return m->data[row][col];
}
void print_matrix(Matrix *m) {
    for(int i = 0; i < m->rows; i++) {
        for(int j = 0; j < m->cols; j++)
            printf("%.2f ", m->data[i][j]);
        printf("\n");
    }
}
Matrix add_matrices(Matrix *a, Matrix *b) {
    Matrix result = create_matrix(a->rows, a->cols);
    for(int i = 0; i < a->rows; i++)
        for(int j = 0; j < a->cols; j++)
            set_element(&result, i, j, get_element(a, i, j) + get_element(b, i, j));
    return result;
}
Matrix subtract_matrices(Matrix *a, Matrix *b) {
    Matrix result = create_matrix(a->rows, a->cols);
    for(int i = 0; i < a->rows; i++)
        for(int j = 0; j < a->cols; j++)
            set_element(&result, i, j, get_element(a, i, j) - get_element(b, i, j));
    return result;
}
Matrix multiply_matrices(Matrix *a, Matrix *b) {
    Matrix result = create_matrix(a->rows, b->cols);
    for(int i = 0; i < a->rows; i++) {
        for(int j = 0; j < b->cols; j++) {
            double sum = 0;
            for(int k = 0; k < a->cols; k++)
                sum += a->data[i][k] * b->data[k][j];
            set_element(&result, i, j, sum);
        }
    }
    return result;
}
Matrix scalar_multiply_matrix(Matrix *m, double scalar) {
    Matrix result = create_matrix(m->rows, m->cols);
    for(int i = 0; i < m->rows; i++)
        for(int j = 0; j < m->cols; j++)
            set_element(&result, i, j, get_element(m, i, j) * scalar);
    return result;
}

Matrix resize_matrix(Matrix *m, int new_rows, int new_cols) {
    Matrix resized = create_matrix(new_rows, new_cols);

    int min_rows = m->rows < new_rows ? m->rows : new_rows;
    int min_cols = m->cols < new_cols ? m->cols : new_cols;

    for(int i = 0; i < min_rows; i++) {
        for(int j = 0; j < min_cols; j++) {
            set_element(&resized, i, j, get_element(m, i, j));
        }
    }
    return resized;
}

void save_matrix_to_file(Matrix *m, const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for writing.\n", filename);
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%d %d\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            fprintf(file, "%.2f ", m->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

Matrix load_matrix_from_file(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open file %s for reading.\n", filename);
        exit(EXIT_FAILURE);
    }
    int rows, cols;
    fscanf(file, "%d %d", &rows, &cols);

    Matrix m = create_matrix(rows, cols);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            fscanf(file, "%lf", &m.data[i][j]);
        }
    }
    fclose(file);
    return m;
}

