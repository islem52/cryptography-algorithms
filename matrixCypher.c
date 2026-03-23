#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int** create_square_matrix(int dimention){
    int** matrix = (int**)malloc(dimention * sizeof(int*)); //array of row pointers
    for(int i =0 ; i <dimention ; i++){
        matrix[i]= malloc(dimention * sizeof(int));//rows
    }
    return matrix;
}

int** create_matrix(int rows , int columns ){
    int** matrix =(int**)malloc(rows * sizeof(int*));
    for(int i=0;i<rows;i++){
        matrix[i] = (int*)malloc(columns * sizeof(int));
    }
    return matrix;
}

void print_matrix(int** matrix, int rows, int columns){
    for(int i=0;i<rows;i++){
        
        for(int j=0;j<rows;j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void free_matrix(int** matrix, int n){
    for (int i = 0 ; i < n ; i++){
        free(matrix[i]);
    }
    free(matrix);
}

int determinant(int** matrix, int n) {
    if (n == 1) return matrix[0][0]; // Base case for 1x1 matrix

    int det = 0;
    int sign = 1;

    // Temporary matrix for minors
    int** submatrix = create_square_matrix(n - 1);

    for (int col = 0; col < n; col++) {
        // Get the submatrix by excluding the first row and the current column
        for (int i = 1; i < n; i++) {
            int sub_j = 0;
            for (int j = 0; j < n; j++) {
                if (j == col) continue; // Skip the current column
                submatrix[i - 1][sub_j++] = matrix[i][j];
            }
        }

        // Determinant formula: det(A) = somme (-1)^col * A[0][col] * det(submatrix)
        det += sign * matrix[0][col] * determinant(submatrix, n - 1);
        sign = -sign; // Alternate signs for cofactor expansion
    }

    free_matrix(submatrix, n - 1);
    return det;
}

//check if a matrix is invertible(square matrix only)
int matrix_inversible(int** matrix, int rows, int cols) {
    if (rows != cols) {
        printf("Erreur : La matrice n'est pas carrée, donc elle n'est pas inversible.\n");
        return 0;
    }
    int det = determinant(matrix, rows);    
    return (det != 0);
}

int** text_to_matrix(const char* text, int dimension) {
    int length = strlen(text);
    int rows = (length + dimension - 1) / dimension;
    int** matrix = create_matrix(rows, dimension);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < dimension; j++) {
            int index = i * dimension + j;
            if (index < length) {
                char c = toupper(text[index]);  // Convert to uppercase
                matrix[i][j] = (c >= 'A' && c <= 'Z') ? (c - 'A') : 0;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
    return matrix;
}

// int** text_to_matrix(const char* text, int dimension) {
//     int length = strlen(text);
//     int rows = (length + dimension - 1) / dimension;
//     int** matrix = create_matrix(rows, dimension);

//     for (int i = 0; i < rows; i++) {
//         for (int j = 0; j < dimension; j++) {
//             int index = i * dimension + j;
//             matrix[i][j] = (index < length) ? (text[index] - 'A') : 0;
//         }
//     }
//     return matrix;
// }

void matrix_multiplication_mod26(int** result, int** mat1, int** mat2, int rows, int columns, int common_dim) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result[i][j] = 0;
            for (int k = 0; k < common_dim; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
            result[i][j] %= 26;
        }
    }
}




char* matrix_to_text(int** matrix, int rows, int columns) {
    char* text = (char*)malloc(rows * columns + 1);
    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            text[index++] = (char)(matrix[i][j] + 'A');
        }
    }
    text[index] = '\0';
    return text;
}

char* hill_encrypt(const char* plaintext, int** key_matrix, int dimension) {
    int** plaintext_matrix = text_to_matrix(plaintext, dimension);
    int rows = (strlen(plaintext) + dimension - 1) / dimension;
    int** encrypted_matrix = create_matrix(rows, dimension);

    matrix_multiplication_mod26(encrypted_matrix, plaintext_matrix, key_matrix, rows, dimension, dimension);
    char* ciphertext = matrix_to_text(encrypted_matrix, rows, dimension);

    free_matrix(plaintext_matrix, rows);
    free_matrix(encrypted_matrix, rows);
    return ciphertext;
}

int mod_inverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}


void adjugate_matrix(int** matrix, int** adj, int n) {
    if (n == 2) {
        adj[0][0] = matrix[1][1];
        adj[0][1] = -matrix[0][1];
        adj[1][0] = -matrix[1][0];
        adj[1][1] = matrix[0][0];
    }
}

int** inverse_matrix_mod26(int** matrix, int dimension) {
    int det = determinant(matrix, dimension) % 26;
    if (det < 0) det += 26;
    int inv_det = mod_inverse(det, 26);
    if (inv_det == -1) return NULL;

    int** adj = create_square_matrix(dimension);
    adjugate_matrix(matrix, adj, dimension);

    int** inverse = create_square_matrix(dimension);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            inverse[i][j] = (adj[i][j] * inv_det) % 26;
            if (inverse[i][j] < 0) inverse[i][j] += 26;
        }
    }

    free_matrix(adj, dimension);
    return inverse;
}

char* hill_decrypt(const char* ciphertext, int** key_matrix, int dimension) {
    int** inverse_key = inverse_matrix_mod26(key_matrix, dimension);
    if (!inverse_key) {
        printf("Error: Key matrix is not invertible.\n");
        return NULL;
    }
    
    int** ciphertext_matrix = text_to_matrix(ciphertext, dimension);
    int rows = (strlen(ciphertext) + dimension - 1) / dimension;
    int** decrypted_matrix = create_matrix(rows, dimension);

    matrix_multiplication_mod26(decrypted_matrix, ciphertext_matrix, inverse_key, rows, dimension, dimension);
    char* plaintext = matrix_to_text(decrypted_matrix, rows, dimension);

    free_matrix(inverse_key, dimension);
    free_matrix(ciphertext_matrix, rows);
    free_matrix(decrypted_matrix, rows);
    return plaintext;
}


int main(){
    char input[100];
    int choice;
    printf("Choose an option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);
    getchar(); // Consume newline character
    
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character
    
    int** key_matrix = create_square_matrix(2);
    key_matrix[0][0] = 9; key_matrix[0][1] = 4;
    key_matrix[1][0] = 5; key_matrix[1][1] = 7;
    
    if (choice == 1) {
        char* ciphertext = hill_encrypt(input, key_matrix, 2);
        printf("Ciphertext: %s\n", ciphertext);
        free(ciphertext);
    } else if (choice == 2) {
        char* decrypted_text = hill_decrypt(input, key_matrix, 2);
        if (decrypted_text) {
            printf("Decrypted Text: %s\n", decrypted_text);
            free(decrypted_text);
        }
    } else {
        printf("Invalid choice.\n");
    }
    
    free_matrix(key_matrix, 2);
    return 0;
}
