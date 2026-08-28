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

int desordenSort(vector<int> a){
    int counter = 0;
    if (a.size() <= 1){
        return counter;
    }

    int m = a.size() / 2;

    if (a[m - 1] > a[m]){
        counter++;
    }

    vector<int> a_izq;
    for (int i = 0; i < m; i++){
        a_izq.push_back(a[i]);
    }

    vector<int> a_der;
    for (int i = m; i < a.size(); i++){
        a_der.push_back(a[i]);
    }

    int izquierda = desordenSort(a_izq);
    int derecha = desordenSort(a_der);

    return counter + izquierda + derecha;
}

void runTest(const string& nombre, const vector<int>& arr, int esperado) {
    int obtenido = desordenSort(arr);
    cout << nombre << ": " << obtenido << " (expected " << esperado << ")";
    if (obtenido == esperado) {
        cout << " [OK]";
    } else {
        cout << " [FAIL]";
    }
    cout << endl;
}

int main() {
    runTest("Test 1 (vacio)", {}, 0);
    runTest("Test 2 (un elemento)", {5}, 0);
    runTest("Test 3 (ordenado)", {1, 2, 3, 4}, 0);
    runTest("Test 4 (invertido)", {4, 3, 2, 1}, 3);
    runTest("Test 5 (mixto corto)", {2, 1, 3}, 1);
    runTest("Test 6 (mixto)", {3, 1, 2, 0}, 2);

    return 0;
}