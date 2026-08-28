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

int suma_max_cruzada(const vector<int>& a, int izq, int m, int der) {
    int suma_izq = INT_MIN;
    int suma = 0;
    
    // Vamos desde el medio hacia la IZQUIERDA
    for (int i = m; i >= izq; i--) { 
        suma += a[i];
        if (suma > suma_izq) suma_izq = suma;
    }

    int suma_der = INT_MIN;
    suma = 0;

    // Vamos desde el medio+1 hacia la DERECHA
    for (int i = m + 1; i <= der; i++) { 
        suma += a[i];
        if (suma > suma_der) suma_der = suma;
    }

    return suma_izq + suma_der;
}

int maxSubArray(const vector<int>& a, int izq, int der) {
    // Caso base: un solo elemento
    if (izq == der) {
        return a[izq];
    }
    
    int m = izq + (der - izq) / 2;
    
    int max_izq = maxSubArray(a, izq, m);
    int max_der = maxSubArray(a, m + 1, der);
    int max_cruzado = suma_max_cruzada(a, izq, m, der);
    
    return max(max_izq, max(max_der, max_cruzado));
}


int main() {
    // Caso 1: Ejemplo del enunciado (Mixto)
    vector<int> a1 = {3, -1, 4, 8, -2, 2, -7, 5};
    int res1 = maxSubArray(a1, 0, a1.size() - 1);
    cout << "Test 1 - Mixto: " << res1 << " | Esperado: 14" << endl;

    // Caso 2: Todos positivos
    vector<int> a2 = {1, 2, 3, 4, 5};
    int res2 = maxSubArray(a2, 0, a2.size() - 1);
    cout << "Test 2 - Positivos: " << res2 << " | Esperado: 15" << endl;

    // Caso 3: Todos negativos (debe devolver el menos negativo)
    vector<int> a3 = {-8, -3, -6, -2, -5, -4};
    int res3 = maxSubArray(a3, 0, a3.size() - 1);
    cout << "Test 3 - Negativos: " << res3 << " | Esperado: -2" << endl;

    // Caso 4: Un solo elemento
    vector<int> a4 = {10};
    int res4 = maxSubArray(a4, 0, a4.size() - 1);
    cout << "Test 4 - Un elemento: " << res4 << " | Esperado: 10" << endl;

    // Caso 5: Arreglo vacio
    vector<int> a5 = {};
    if (a5.empty()) {
        cout << "Test 5 - Vacio: Arreglo sin elementos (Omitido)" << endl;
    }

    // Caso 6: El clasico de Kadane
    vector<int> a6 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res6 = maxSubArray(a6, 0, a6.size() - 1);
    cout << "Test 6 - Clasico: " << res6 << " | Esperado: 6" << endl;

    // Caso 7: Alternados
    vector<int> a7 = {5, -2, 3, -1, 2, -1, 2};
    int res7 = maxSubArray(a7, 0, a7.size() - 1);
    cout << "Test 7 - Alternado: " << res7 << " | Esperado: 8" << endl;

    // Caso 8: Caso extra
    vector<int> a8 = {-5, 6, 3, -1, 4, -2, 2};
    int res8 = maxSubArray(a8, 0, a8.size() - 1);
    cout << "Test 8 - Extra: " << res8 << " | Esperado: 12" << endl;

    return 0;
}