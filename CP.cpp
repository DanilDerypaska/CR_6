#include <iostream>
#include <vector>

using namespace std;

// Функція для виводу матриці
void printMatrix(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

// Функція для знаходження розв'язку системи рівнянь методом Гаусса
vector<double> solveLinearSystem(vector<vector<double>>& matrix) {
    int n = matrix.size();

    for (int i = 0; i < n; i++) {
        // Знаходимо максимальний елемент в стовпці
        double maxElement = abs(matrix[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < n; k++) {
            if (abs(matrix[k][i]) > maxElement) {
                maxElement = abs(matrix[k][i]);
                maxRow = k;
            }
        }

        // Обмінюємо рядки, щоб максимальний елемент був на діагоналі
        for (int k = i; k < n + 1; k++) {
            double temp = matrix[maxRow][k];
            matrix[maxRow][k] = matrix[i][k];
            matrix[i][k] = temp;
        }

        // Занулюємо елементи нижче діагоналі в поточному стовпці
        for (int k = i + 1; k < n; k++) {
            double ratio = -matrix[k][i] / matrix[i][i];
            for (int j = i; j < n + 1; j++) {
                if (i == j) {
                    matrix[k][j] = 0;
                }
                else {
                    matrix[k][j] += ratio * matrix[i][j];
                }
            }
        }
    }

    // Зворотний хід для знаходження розв'язку
    vector<double> solution(n);
    for (int i = n - 1; i >= 0; i--) {
        solution[i] = matrix[i][n] / matrix[i][i];
        for (int k = i - 1; k >= 0; k--) {
            matrix[k][n] -= matrix[k][i] * solution[i];
        }
    }

    return solution;
}

int main() {
    setlocale(0, "");
    int n; // Розмірність системи рівнянь
    cout << "Введiть розмiрнiсть системи рiвнянь: ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n + 1));

    // Введення коефіцієнтів системи рівнянь
    cout << "Введiть коефiцiєнти системи рiвнянь:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "A[" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
        cout << "B[" << i << "]: ";
        cin >> matrix[i][n];
    }

    // Виведення початкової матриці
    cout << "Початкова матриця:" << endl;
    printMatrix(matrix);

    // Знаходження розв'язку системи рівнянь
    vector<double> solution = solveLinearSystem(matrix);

    // Виведення розв'язку
    cout << "Розв'язок:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "X[" << i << "] = " << solution[i] << endl;
    }

    return 0;
}
