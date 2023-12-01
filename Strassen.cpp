#include <iostream>
#include <vector>

using namespace std;

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] + B[i][j];

    return result;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i][j] = A[i][j] - B[i][j];

    return result;
}

// Function to multiply two matrices using Strassen's algorithm
vector<vector<int>> strassenMatrixMultiplication(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();

    // Base case: If the matrices are 1x1, perform a simple multiplication
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // Divide matrices into four submatrices
    int mid = n / 2;

    vector<vector<int>> A11(mid, vector<int>(mid, 0));
    vector<vector<int>> A12(mid, vector<int>(mid, 0));
    vector<vector<int>> A21(mid, vector<int>(mid, 0));
    vector<vector<int>> A22(mid, vector<int>(mid, 0));

    vector<vector<int>> B11(mid, vector<int>(mid, 0));
    vector<vector<int>> B12(mid, vector<int>(mid, 0));
    vector<vector<int>> B21(mid, vector<int>(mid, 0));
    vector<vector<int>> B22(mid, vector<int>(mid, 0));

    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + mid];
            A21[i][j] = A[i + mid][j];
            A22[i][j] = A[i + mid][j + mid];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + mid];
            B21[i][j] = B[i + mid][j];
            B22[i][j] = B[i + mid][j + mid];
        }

    // Recursive steps
    vector<vector<int>> P1 = strassenMatrixMultiplication(A11, subtractMatrices(B12, B22));
    vector<vector<int>> P2 = strassenMatrixMultiplication(addMatrices(A11, A12), B22);
    vector<vector<int>> P3 = strassenMatrixMultiplication(addMatrices(A21, A22), B11);
    vector<vector<int>> P4 = strassenMatrixMultiplication(A22, subtractMatrices(B21, B11));
    vector<vector<int>> P5 = strassenMatrixMultiplication(addMatrices(A11, A22), addMatrices(B11, B22));
    vector<vector<int>> P6 = strassenMatrixMultiplication(subtractMatrices(A12, A22), addMatrices(B21, B22));
    vector<vector<int>> P7 = strassenMatrixMultiplication(subtractMatrices(A11, A21), addMatrices(B11, B12));

    // Calculate the four quadrants of the result matrix
    vector<vector<int>> C11 = subtractMatrices(addMatrices(addMatrices(P5, P4), P6), P2);
    vector<vector<int>> C12 = addMatrices(P1, P2);
    vector<vector<int>> C21 = addMatrices(P3, P4);
    vector<vector<int>> C22 = subtractMatrices(subtractMatrices(addMatrices(P5, P1), P3), P7);

    // Combine the four quadrants into the result matrix
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < mid; i++)
        for (int j = 0; j < mid; j++) {
            result[i][j] = C11[i][j];
            result[i][j + mid] = C12[i][j];
            result[i + mid][j] = C21[i][j];
            result[i + mid][j + mid] = C22[i][j];
        }

    return result;
}

int main() {
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};

    cout << "Matrix A:" << endl;
    for (const auto& row : A) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    cout << "\nMatrix B:" << endl;
    for (const auto& row : B) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    // Perform Strassen's Matrix Multiplication
    vector<vector<int>> result = strassenMatrixMultiplication(A, B);

    cout << "\nResult Matrix:" << endl;
    for (const auto& row : result) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }

    return 0;
}
