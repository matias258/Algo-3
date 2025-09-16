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
https://codeforces.com/group/yuAAIJ8c1R/contest/629197/problem/B

Tienes un string s de n letras del alfabeto latino. Puedes aplicar la siguiente operación una cantidad arbitraría de veces en el string:

Elige un substring (contiguo) de caracteres iguales y bórralo. Luego concatena las partes resultantes. Por ejemplo, en acccad podemos borrar el rango [1,4) y obtener aad.
Calcula la mínima cantidad de operaciones necesaria para eliminar todo el string s.

Input
La primera línea contiene un entero n=|s| (1≤n≤500).
La segunda línea contiene el string s

Output
Imprime un único entero, la mínima cantidad de operaciones necesaria para borrar s

Ejemplo:
Input:
6
aaabbb

Output: 
2

Input:
10
abccabccab
Output:
6
*/

string comprimir_string(string s){
    int repetidos;
    string res;
    for (int i = 0; i < s.size(); i++){
        int j = i;
        while (s[j] == s[j+1]){
            repetidos++;
            j++;
        }
        i = j;
        res += s[i];
    }
    return res;
}


int funcion(int n, string& s, unordered_map<string, int>& memo ){
    // Caso base: eliminé todo el string o me quedó 1 solo
    if (s.size() == 0){
        return 0;
    }
    if (s.size() == 1){
        return 1;
    }

    if (memo.count(s) == true) {    // si la clave existe en memo
        return memo[s];
    }

    int res = INT_MAX / 2;  // lo unico que faltaria es que hiciera overflow la pm

    for (int i = 0; i < s.size(); i++) {
        string left = s.substr(0, i);
        string right = s.substr(i + 1, s.size());

        // Nuevo string sin el que acabo de eliminar (osea s[i])
        string nuevo_string = left + right;
        int costo_agregado = 0; // suma extra por si fin de left e inicio de right comparten misma letra.

        // Si left y right no estan vacios
        // Y si el final de left == inicio de right, (por ejemplo "ab", "bc" -> "abbc")
        // busco eliminar esos 2
        if (!left.empty() && !right.empty() && left.back() == right[0]) {
            nuevo_string = left.substr(0, left.size() - 1) + right.substr(1);
            costo_agregado ++;
        }

        nuevo_string = comprimir_string(nuevo_string);

        int costo = 1 + costo_agregado + funcion(n, nuevo_string, memo);

        res = min(res, costo);
    }

    memo[s] = res;
    return res;
}


/*
// capaz utilizar un dicc como memo? con por ej key = "acbc", value = 3 (min costo)
int main(){
    int n;
    string a;
    unordered_map<string, int> memo;  
    cin >> n;
    cin >> a;

    a = comprimir_string(a);
    int res = funcion(n, a, memo);

    cout << res;
    return 0;
}
*/

int main() {
    // Vector de casos de prueba: {input string, valor esperado}
    unordered_map<string, int> memo;  
    vector<pair<string, int>> casos = {
        {"aaabbb", 2},
        {"abccabccab", 6},
        {"a", 1},             // Comprimido: "a" → 1 operación (caso mínimo n=1)
        {"aa", 1},            // Comprimido: "a" → 1 operación (todo igual)
        {"ab", 2},            // Comprimido: "ab" → 2 operaciones (diferentes, no merge)
        {"aba", 2},           // Comprimido: "aba" → 2 operaciones (merge posible)
        {"abab", 3},          // Comprimido: "abab" → 3 operaciones (alternante, rama profunda)
        {"ababab", 4},        // Comprimido: "ababab" → 4 operaciones (alternante más largo)
        {"abcba", 3},         // Comprimido: "abcba" → 3 operaciones (palíndromo con merges en cascada)
        {"aaddaa", 2},        // Comprimido: "ada" → 2 operaciones (merges con chars diferentes)
        {"abccabccab", 6},    // Comprimido: "abcabcab" → 6 operaciones (ejemplo del problema)
        {"abbbccbbba", 3},    // Comprimido: "abcba" → 3 operaciones (como explicaste, con merges eficientes)
        {"abc", 3},
        {"ababa", 3},
        {"acbdefgh", 8},
        {"abba", 2},             // comprime a "aba" -> 2 operaciones (borrar 'b' luego 'aa')
        {"aabaa", 2},            // comprime a "aba" -> 2 operaciones
        {"aaaaabaaaaa", 2},      // borrar 'b' -> todas las 'a' se juntan -> 2 operaciones
        {"ababa", 3},            // patrón con múltiples 'a' separadas -> 3 operaciones
        {"zzzyzz", 2},           // 'zzz','y','zz' -> borrar 'y' juntea los z -> 2 operaciones
        {"aaabbbcccaaa", 3},     // mezcla de runs que permite merges intermedios
        {"abacaba", 4},
        {"babab", 3},
        {"abzfondob", 7},
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaa", 1},  // 28 'a' → debería dar 1 (bloque entero)
        {"abababababababababababababab", 15}, // alternancia larga (30 letras)
        {"abcabcabcabcabcabcabcabcabc", 18},  // repetición de 'abc' muchas veces
        {"abbaabbaabbaabbaabbaabbaabba", 8},  // repeticiones de 'abba'
        {"rnjgjsqjbmc", 9},
        {"npyzmqytjq", 9}

    };

    // Iterar sobre los casos de prueba
    for (int i = 0; i < casos.size(); i++) {
        string a = casos[i].first;
        int expected = casos[i].second;
        // Comprimir el string
        string b = comprimir_string(a);
        // Calcular resultado (nota: ajusta a funcion(b) si quitaste 'n' en la firma)
        int res = funcion(a.size(), b, memo);  // Usa n = a.size() como en tu código
        // Imprimir resultado con valor esperado
        cout << "a = \"" << a.substr(0, 20) << (a.size() > 20 ? "..." : "") << "\", esperado = " << expected << ", obtenido = " << res << endl;
    }

    return 0;
}