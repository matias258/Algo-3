#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <climits>
using namespace std;


long long alfabetico(vector<long long>& c, vector<string>& palabras, vector<string>& palabras_revez, vector<vector<long long>>& memo) {
    for (int i = 0; i < palabras.size(); i++) {

        // Caso 1: no modifico la palabra, eleccion = 0 (string anterior es original)
        if (memo[i][0] != INT_MAX) {
            string palabra_previa;
            if (i > 0) {
                palabra_previa = palabras[i-1];  
            }  

            // Subcaso 1: Usar original actual (costo=0)
            string actual = palabras[i];
            if (i == 0 || palabra_previa <= actual){
                memo[i+1][0] = min(memo[i+1][0], memo[i][0] + 0);
            }

            // Subcaso 2: Usar invertida actual (costo=c[i])
            actual = palabras_revez[i];
            if (i == 0 || palabra_previa <= actual) {
                memo[i+1][1] = min(memo[i+1][1], memo[i][0] + c[i]);
            }
        }

        // Caso 2: eleccion_previa = 1 (invierto el string anterior)
        if (memo[i][1] != INT_MAX) {
            string palabra_previa;
            if (i > 0) {
                palabra_previa = palabras_revez[i-1]; 
            }  

            // Subcaso 1: Usar original actual (costo=0)
            string actual = palabras[i];
            if (i == 0 || palabra_previa <= actual) {
                memo[i+1][0] = min(memo[i+1][0], memo[i][1] + 0);
            }

            // Subcaso 2: Usar invertida actual (costo=c[i])
            actual = palabras_revez[i];
            if (i == 0 || palabra_previa <= actual) {
                memo[i+1][1] = min(memo[i+1][1], memo[i][1] + c[i]);
            }
        }
        
    }
    long long min_costo = min(memo[palabras.size()][0], memo[palabras.size()][1]);
    if (min_costo == INT_MAX){
        return -1;
    }
    else{
        return min_costo;
    }
}


long long gasto_alfabetico(vector<long long> c, vector<string>& palabras) {
    vector<string> palabras_revez = palabras;
    for (int i = 0; i < palabras.size(); i++) {
        reverse(palabras_revez[i].begin(), palabras_revez[i].end());
    }
    vector<vector<long long>> memo(palabras.size()+1, vector<long long>(2, INT_MAX));
    memo[0][0] = 0;
    return alfabetico(c, palabras, palabras_revez, memo);
}
/*
int main(){
    int n;
    cin >> n;
    vector<long long> c(n);
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

