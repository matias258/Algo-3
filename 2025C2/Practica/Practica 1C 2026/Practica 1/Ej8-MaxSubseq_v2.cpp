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

int suma_partes(vector<int> a, int izq, int med, int der){
    int suma = 0;
    int suma_izq = INT_MIN;
    for (int i = med; i >= izq; i--){
        suma+= a[i];
        suma_izq = max(suma, suma_izq);
    }

    suma = 0;
    int suma_der = INT_MIN;
    for (int i = med+1; i <= der; i++){
        suma += a[i];
        suma_der = max(suma, suma_der);
    }

    return suma_izq + suma_der;
}

int maxsubseq(vector<int> a, int izq, int der){
    if (izq == der){
        return a[izq];
    }


    int med = izq + (der - izq) / 2;

    int mitad_izq = maxsubseq(a, izq, med);
    int mitad_der = maxsubseq(a, med + 1, der);
    int mitad_cross = suma_partes(a, izq, med, der);

    return max(mitad_izq, max(mitad_der, mitad_cross));
}



int main() {
    // Caso 1: Ejemplo del enunciado (Mixto)
    vector<int> a1 = {3, -1, 4, 8, -2, 2, -7, 5};
    int res1 = maxsubseq(a1, 0, a1.size() - 1);
    cout << "Test 1 - Mixto: " << res1 << " | Esperado: 14" << endl;

    // Caso 2: Todos positivos
    vector<int> a2 = {1, 2, 3, 4, 5};
    int res2 = maxsubseq(a2, 0, a2.size() - 1);
    cout << "Test 2 - Positivos: " << res2 << " | Esperado: 15" << endl;

    // Caso 3: Todos negativos (debe devolver el menos negativo)
    vector<int> a3 = {-8, -3, -6, -2, -5, -4};
    int res3 = maxsubseq(a3, 0, a3.size() - 1);
    cout << "Test 3 - Negativos: " << res3 << " | Esperado: -2" << endl;

    // Caso 4: Un solo elemento
    vector<int> a4 = {10};
    int res4 = maxsubseq(a4, 0, a4.size() - 1);
    cout << "Test 4 - Un elemento: " << res4 << " | Esperado: 10" << endl;

    // Caso 5: Arreglo vacio
    vector<int> a5 = {};
    if (a5.empty()) {
        cout << "Test 5 - Vacio: Arreglo sin elementos (Omitido)" << endl;
    }

    // Caso 6: El clasico de Kadane
    vector<int> a6 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int res6 = maxsubseq(a6, 0, a6.size() - 1);
    cout << "Test 6 - Clasico: " << res6 << " | Esperado: 6" << endl;

    // Caso 7: Alternados
    vector<int> a7 = {5, -2, 3, -1, 2, -1, 2};
    int res7 = maxsubseq(a7, 0, a7.size() - 1);
    cout << "Test 7 - Alternado: " << res7 << " | Esperado: 8" << endl;

    // Caso 8: Caso extra
    vector<int> a8 = {-5, 6, 3, -1, 4, -2, 2};
    int res8 = maxsubseq(a8, 0, a8.size() - 1);
    cout << "Test 8 - Extra: " << res8 << " | Esperado: 12" << endl;

    return 0;
}