#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

#include <stdio.h>
#include <stdlib.h>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

bool is_connected = false;

void activate_connection() {
    printf("Establishing Connection");
    is_connected = true;
}

void deactivate_connection() {
    printf("Deactivating Connection");
    is_connected = false;
}

std::string format_exception(const std::exception &e) {
    const char *errorTypeID = typeid(e).name();
    const char *errorMessage = e.what();

    std::string formatted_message = "ErrorTypeID: " + std::string(errorTypeID) +
                                    ", ErrorMessage: " + std::string(errorMessage);
    return formatted_message;
}

void print_exception(const std::exception &e) {
    std::string formatted_message = format_exception(e);
    fprintf(stderr, "%s\n", formatted_message.c_str());
}

class DB_Connection {
public:
    DB_Connection() {
        if (is_connected) {
            throw std::runtime_error("Connection already active!");
        }
        activate_connection();
        std::cout << "DB_Connection established.\n";
    }
    ~DB_Connection() {
        if (is_connected) {
            deactivate_connection();
            std::cout << "DB_Connection closed.\n";
        }
    }
};

void print_connection_status() {
    if (is_connected) {
        std::cout << "Heartbeat Check: IsAlive\n";
    } else {
        std::cout << "Heartbeat Check: IsDead\n";
    }
}

int connection_testing() {
    print_connection_status();
    try {
        {
            DB_Connection db1;
            print_connection_status();
        }
        print_connection_status();
        DB_Connection db2;
        print_connection_status();
        DB_Connection db3;
    } catch (const std::exception &e) {
        print_exception(e);
        deactivate_connection();
    }

    print_connection_status();
    return 0;
}

int json_testing() {
    std::string file_path = "/Users/danielsinkin/GitHub_private/learning_cpp/simple_dict.json";

    { // Scope for file reading
        std::ifstream file(file_path);
        if (!file.is_open()) {
            fprintf(stderr, "Failed to open file %s", file_path.c_str());
            return 1;
        }

        json j;
        file >> j;

        std::cout << "Parse JSON data:\n"
                  << j.dump(4) << std::endl;
    }

    return 0;
}

typedef struct
{
    float *data;
    size_t n_row;
    size_t n_col;
} Matrix;

Matrix createMatrix(size_t n_row, size_t n_col) {
    Matrix m;
    m.n_row = n_row;
    m.n_col = n_col;
    m.data = (float *)malloc(n_row * n_col * sizeof(float));
    if (m.data == NULL) {
        fprintf(stderr, "Malloc for matrix failed.\n");
        exit(EXIT_FAILURE);
    }
    for (size_t y = 0; y < n_row; y++) {
        for (size_t x = 0; x < n_col; x++) {
            m.data[y * n_col + n_row] = 0.0f;
        }
    }
    return m;
}

void printMatrix(Matrix *m) {
    for (size_t y = 0; y < m->n_row; y++) {
        printf("[");
        for (size_t x = 0; x < m->n_col; x++) {
            printf("%.2f", m->data[y * m->n_col + x]);
            if (x < m->n_col - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

void freeMatrix(Matrix *m) {
    free(m->data);
    m->data = NULL;
    m->n_row = 0;
    m->n_col = 0;
}

void blockWiseGEMM(Matrix *A, Matrix *B, Matrix *C, size_t block_size) {
    // Check for matrix compatibility
    if (A->n_col != B->n_row) {
        fprintf(stderr, "Incompatible matrices for multiplication.\n");
        exit(EXIT_FAILURE);
    }

    if (C->n_row != A->n_row || C->n_col != B->n_col) {
        fprintf(stderr, "Incompatible dimensions for result matrix.\n");
        exit(EXIT_FAILURE);
    }

    // Perform block-wise matrix multiplication
    for (size_t i = 0; i < A->n_row; i += block_size) {
        for (size_t j = 0; j < B->n_col; j += block_size) {
            for (size_t k = 0; k < A->n_col; k += block_size) {
                for (size_t ii = i; ii < i + block_size && ii < A->n_row; ii++) {
                    for (size_t jj = j; jj < j + block_size && jj < B->n_col; jj++) {
                        float sum = 0.0f;
                        for (size_t kk = k; kk < k + block_size && kk < A->n_col; kk++) {
                            sum += A->data[ii * A->n_col + kk] * B->data[kk * B->n_col + jj];
                        }
                        C->data[ii * C->n_col + jj] += sum;
                    }
                }
            }
        }
    }
}

int main() {
    const size_t n_rows = 5;
    const size_t n_cols = 3;

    Matrix matrix = createMatrix(n_rows, n_cols);

    matrix.data[0] = 1.1f;
    matrix.data[1] = 2.2f;
    matrix.data[2] = 3.3f;
    matrix.data[3] = 4.4f;
    matrix.data[4] = 5.5f;
    matrix.data[5] = 6.6f;
    matrix.data[6] = 7.7f;
    matrix.data[7] = 8.8f;
    matrix.data[8] = 9.9f;
    matrix.data[9] = 10.1f;
    matrix.data[10] = 11.2f;
    matrix.data[11] = 12.3f;
    matrix.data[12] = 13.4f;
    matrix.data[13] = 14.5f;
    matrix.data[14] = 15.6f;

    // Print the matrix
    printMatrix(&matrix);

    freeMatrix(&matrix);

    return 0;
}