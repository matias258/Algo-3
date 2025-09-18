#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <bits/stdc++.h>
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

int funcion(int left, int right, vector<vector<int>>& memo, string& s){
    if (left > right)
        return 0;
    if (left == right)
        return 1;
    if (memo[left][right] != 601) 
        return memo[left][right];

    // Eliminamos solo un char
    int res = 1 + funcion(left + 1, right, memo, s);

    // are deleted if any of them matches
    // Si hay algunos vecinos que matchean "abcbc", saco c -> "abbc" (los b matchean)
    // Los eliminamos
    for (int i = left + 1; i <= right; i++) {
        if (s[left] == s[i]){
            int saco_left = funcion(left + 1, i - 1, memo, s);
            int sigo = funcion(i, right, memo, s);
            res = min(res, saco_left + sigo);
        }
            
    }
    return memo[left][right] = res;
}

int main(){
    int n;
    cin >> n;

    string s;
    cin >> s;
    // Como n <= 600, lo max q puede valer algo es 600
    // Y seguro menos porque hay 26 letras (creo?) en el abecedario. Luego es congruente con 26
    vector<vector<int>> memo(n, vector<int>(n, 601));
    int res = funcion(0, n-1, memo, s);
    cout << res;
    return 0;
}
/*
int main() {
    // Vector de casos de prueba: {input string, valor esperado}
    vector<pair<string, int>> casos = {
        {"abbcba", 3},
        {"abzfondob", 7},
        {"aaabbb", 2},
        {"abccabccab", 6},
        {"a", 1},
        {"aa", 1},
        {"ab", 2},
        {"aba", 2},
        {"abab", 3},
        {"ababab", 4},
        {"abcba", 3},
        {"aaddaa", 2},
        {"abccabccab", 6},
        {"abbbccbbba", 3},
        {"abc", 3},
        {"ababa", 3},
        {"acbdefgh", 8},
        {"abba", 2},
        {"aabaa", 2},
        {"aaaaabaaaaa", 2},
        {"ababa", 3},
        {"zzzyzz", 2},
        {"aaabbbcccaaa", 3},
        {"abacaba", 4},
        {"babab", 3},
        {"abzfondob", 7},
        {"aaaaaaaaaaaaaaaaaaaaaaaaaaaa", 1},
        {"abababababababababababababab", 15},
        {"abbaabbaabbaabbaabbaabbaabba", 8},
        {"rnjgjsqjbmc", 9},
        {"npyzmqytjq", 9},
        {"rnsqjbmc", 8}
    };

    // Iterar sobre los casos de prueba
    for (size_t i = 0; i < casos.size(); i++) {
        string a = casos[i].first;
        int expected = casos[i].second;
        // Comprimir el string
        int n = a.size(); // Use compressed string length
        vector<vector<int>> memo(n, vector<int>(n, 601)); // Initialize with -1
        // Calcular resultado
        int res = funcion(0, n - 1, memo, a); // Use compressed string
        // Imprimir resultado con valor esperado
        cout << "a = \"" << a.substr(0, 20) << (a.size() > 20 ? "..." : "") 
             << "\", esperado = " << expected << ", obtenido = " << res << endl;
    }

    return 0;
}
    */