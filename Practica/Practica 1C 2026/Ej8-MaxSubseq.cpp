#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <climits>
using namespace std;

int maxCrossingSum(vector<int>& arr, int l, int m, int h) {
    // 1. Buscar la suma máxima hacia la izquierda del medio
    int suma = 0;
    int max_izq = -1e9; // Un número muy chico (infinito negativo)
    for (int i = m; i >= l; i--) {
        suma += arr[i];
        if (suma > max_izq) max_izq = suma;
    }

    // 2. Buscar la suma máxima hacia la derecha del medio
    suma = 0;
    int max_der = -1e9;
    for (int i = m + 1; i <= h; i++) {
        suma += arr[i];
        if (suma > max_der) max_der = suma;
    }

    return max_izq + max_der;
}

int maxSubArray(vector<int>& arr, int l, int h) {
    if (l == h) return arr[l]; 

    int m = (l + h) / 2;

    return max(maxSubArray(arr, l, m), max(maxSubArray(arr, m + 1, h), maxCrossingSum(arr, l, m, h)));
}

int maxSubArray(vector<int>& arr) {
    if (arr.empty()) {
        return INT_MIN;
    }
    return maxSubArray(arr, 0, static_cast<int>(arr.size()) - 1);
}

void runTest(const string& name, vector<int> arr, int expected) {
    int got = maxSubArray(arr);
    cout << name << ": " << got << " (expected " << expected << ")";
    if (got == expected) {
        cout << " [OK]";
    } else {
        cout << " [FAIL]";
    }
    cout << endl;
}

int main() {

    runTest("Test 1 (mixto)", {3, -1, 4, 8, -2, 2, -7, 5}, 14);
    runTest("Test 2 (positivos)", {1, 2, 3, 4, 5}, 15);
    runTest("Test 3 (negativos)", {-8, -3, -6, -2, -5, -4}, -2);
    runTest("Test 4 (un elemento)", {10}, 10);
    runTest("Test 5 (vacio)", {}, INT_MIN);
    runTest("Test 6 (clasico)", {-2, 1, -3, 4, -1, 2, 1, -5, 4}, 6);
    runTest("Test 7 (alternado)", {5, -2, 3, -1, 2, -1, 2}, 8);
    runTest("Test 8 (queseyo)", {-5, 6, 3, -1, 4, -2, 2}, 12);

    return 0;
}