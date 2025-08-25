#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
using namespace std;

/*
Ejercicio 9 (PotenciaSum) ⋆
Suponga que se tiene un metodo potencia que, dada un matriz cuadrada A de orden 4 × 4 y un numero n,
computa la matriz A^n. Dada una matriz cuadrada A de orden 4 × 4 y un numero natural n que es potencia de
2 (i.e., n = 2k para algun k ≥ 1), desarrollar, utilizando la tecnica de dividir y conquistar y el metodo potencia, un algoritmo que permita calcular
A^1 + A^2 + A^3 + . . . + A^n.
Procure que el algoritmo propuesto aplique el metodo potencia, sume y haga productos de matrices una cantidad estrictamente menor que O(n) veces.
*/

int PotenciaSum(vector<vector<int>> A, int n, int i, int j){
    // Casos Bases:
    if (n % 2 != 0){
        printf("n no es potencia de 2");
        return -1;
    }
    vector<vector<int>> A_NO = {{0, 0}, {0, 0}};
    vector<vector<int>> A_NE = {{0, 0}, {0, 0}};
    vector<vector<int>> A_SO = {{0, 0}, {0, 0}};
    vector<vector<int>> A_SE = {{0, 0}, {0, 0}};
    for (int k = 0; k < 2; k++){
        for (int r = 0; r < 2; r++){
            A_NO[k][r] = A[k][r];
            A_NE[k][r] = A[k+2][r];
            A_SO[k][r] = A[k][r+2];
            A_SE[k][r] = A[k+2][r+2];
        }
    }
    printf("A es: ", A, "\n");
    printf("A_NO es: ", A_NO, "\n");
    printf("A_NE es: ", A_NE, "\n");
    printf("A_SO es: ", A_SO, "\n");
    printf("A_SE es: ", A_SE, "\n");
    return 1;
}

int main() {
    vector<vector<int>> A = {{1, 2, 3, 4}, {2, 9, 5, 6}, {2, 2, 1, 0}, {3, 0, 5, 2}};
    return PotenciaSum(A, 4, 1 ,1);
}
