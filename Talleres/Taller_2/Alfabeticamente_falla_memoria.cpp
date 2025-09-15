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
Link: https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/A

Juan tiene n strings de letras minúsculas del alfabeto inglés. 
Quiere ordenarlas alfabéticamente, pero no tiene permitido cambiarlas de lugar. Lo único que puede hacer es dar vuelta algunas de ellas (dar vuelta un string s es leerlo de atrás para adelante). Dos palabras iguales consecutivas se consideran ordenadas. Para dar vuelta el string i tiene que gastar ci unidades de energía. Él quiere minimizar la cantidad de energía que necesita gastar para que las palabras queden en orden alfabético. 

Input:
La primera línea del input contiene un entero n (2≤n≤100.000 ), la cantidad de palabras. 
La siguiente línea contiene los n enteros ci (0≤ci≤109 ). 
Las últimas n líneas contienen cada uno de los strings a ordenar. 
La longitud total de estos strings es menor o igual a 100.000 caracteres. 

Output: 
Si es imposible invertir algunas (posiblemente 0) de las strings para que queden ordenadas alfabéticamente, imprimir -1. 
En caso contrario, imprimir la mínima cantidad de energía que Juan necesita gastar para lograr su objetivo.
*/

long long alfabetico(vector<long long>& c, vector<string>& palabras, 
                    vector<string>& palabras_revez) {
    if (palabras.size() == 0) return 0;

    // Memo: memo[i][eleccion] = costo mínimo para primeros i strings, con string anterior en estado eleccion
    vector<vector<long long>> memo(palabras.size() + 1, vector<long long>(2, INT_MAX));
    memo[0][0] = 0;  // Dummy inicial (no hay string anterior)

    // Iterar sobre i (progreso)
    for (int i = 0; i < palabras.size(); i++) {

        // Caso 1: no modifico la palabra, eleccion = 0 (string anterior es original)
        if (memo[i][0] != INT_MAX) {
            string palabras_ordenadas;
            if (i > 0) {
                palabras_ordenadas = palabras[i-1];  // Original anterior
            }  // Para i=0, no se usa (vacío)

            // Subcaso 1: Usar original actual (curr_state=0, costo=0)
            string actual = palabras[i];
            if (i == 0 || palabras_ordenadas <= actual) {
                memo[i+1][0] = min(memo[i+1][0], memo[i][0] + 0);
            }

            // Subcaso 2: Usar invertida actual (curr_state=1, costo=c[i])
            actual = palabras_revez[i];
            if (i == 0 || palabras_ordenadas <= actual) {
                memo[i+1][1] = min(memo[i+1][1], memo[i][0] + c[i]);
            }
        }

        // Caso 2: eleccion_previa = 1 (string anterior es invertido)
        if (memo[i][1] != LLONG_MAX / 2) {
            string palabras_ordenadas;
            if (i > 0) {
                palabras_ordenadas = palabras_revez[i-1];  // Invertido anterior
            }  // Para i=0, no se usa (vacío)

            // Subcaso 1: Usar original actual (curr_state=0, costo=0)
            string actual = palabras[i];
            if (i == 0 || palabras_ordenadas <= actual) {
                memo[i+1][0] = min(memo[i+1][0], memo[i][1] + 0);
            }

            // Subcaso 2: Usar invertida actual (curr_state=1, costo=c[i])
            actual = palabras_revez[i];
            if (i == 0 || palabras_ordenadas <= actual) {
                memo[i+1][1] = min(memo[i+1][1], memo[i][1] + c[i]);
            }
        }
    }

    long long min_costo = min(memo[palabras.size()][0], memo[palabras.size()][1]);
    return (min_costo == INT_MAX ? -1 : min_costo);
}

long long gasto_alfabetico(vector<long long> c, vector<string>& palabras) {
    vector<string> palabras_revez = palabras;
    for (int i = 0; i < palabras.size(); i++) {
        reverse(palabras_revez[i].begin(), palabras_revez[i].end());
    }
    return alfabetico(c, palabras, palabras_revez);
}


/*
int main(){
    int n;
    cin >> n;
    vector<int> c(n);
    vector<vector<int>> memo(n, vector<int>(n, -1));
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<string> palabras(n);
    for (int i = 0; i < n; i++) {
        cin >> palabras[i];
    }
    cout << gasto_alfabetico(c, palabras) << endl;
    return 0;
}
*/



int main() {
    // Test sample 1: Ya ordenado
    {
        int n = 3;
        vector<long long> c = {100, 200, 300};
        vector<string> palabras = {"abc", "efg", "hij"};
        long long res = gasto_alfabetico(c, palabras);
        cout << "Sample 1 -> expected 0, obtenido " << res << endl;  // 0
    }

    // Test sample 2: "za", "yb", "xc" -> Lógicamente 100, pero sample dice 300 (posible error en judge)
    {
        int n = 3;
        vector<long long> c = {100, 200, 300};
        vector<string> palabras = {"za", "yb", "xc"};
        long long res = gasto_alfabetico(c, palabras);  // Da 300
        cout << "Sample 2 -> expected 300, obtenido " << res << endl;  // 0
    }

    // Test sample 3: Imposible
    {
        int n = 2;
        vector<long long> c = {0, 0};
        vector<string> palabras = {"casas", "abraza"};
        long long res = gasto_alfabetico(c, palabras);
        cout << "Sample 3 -> expected -1, obtenido " << res << endl;  // -1
    }

    // Tus tests originales (ajustados)
    {
        int n = 1;
        vector<long long> c = {5};
        vector<string> palabras = {"cba"};
        long long res = gasto_alfabetico(c, palabras);
        cout << "Test 11 -> expected 0, obtenido " << res << endl;  // 0 (n=1 trivial)
    }

    {
        int n = 2;
        vector<long long> c = {10, 5};
        vector<string> palabras = {"ba", "ab"};
        long long res = gasto_alfabetico(c, palabras);
        cout << "Test 15 (óptimo) -> expected 5, obtenido " << res << endl;  // 5 (invertir segundo)
    }

    // Más tests que rompen versiones buggy
    {
        int n = 2;
        vector<long long> c = {0, 0};
        vector<string> palabras = {"bc", "ab"};
        long long res = gasto_alfabetico(c, palabras);
        cout << "Test 12 (imposible) -> expected -1, obtenido " << res << endl;  // -1
    }

    // Solapamiento, para testear si memo funciona y ahorra calcular valores
    {
        int n = 2;
        vector<long long> c = {100, 200};
        vector<string> palabras = {"ab", "ba"};
        long long res = gasto_alfabetico(c, palabras);
        cout << "Test 13 -> expected 0, obtenido " << res << endl;  // 0
    }

    return 0;
}

