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


// ---------- TU CODIGO ----------
string comprimir_string(string s) {
    string res;
    if (s.empty()) return res;
    res.push_back(s[0]);
    for (int i = 1; i < (int)s.size(); i++) {
        if (s[i] != s[i-1]) res.push_back(s[i]);
    }
    return res;
}

int funcion(int n, string& s, unordered_map<string, int>& memo ){
    if (s.size() == 0){
        return 0;
    }
    if (s.size() == 1){
        return 1;
    }

    if (memo.count(s)) {
        return memo[s];
    }

    int res = INT_MAX / 2;

    for (int i = 0; i < s.size(); i++) {
        // Caso 1: elimino s[i] solo
        string left = s.substr(0, i);
        string right = s.substr(i + 1);
        string nuevo_string = left + right;
        int costo = 1 + funcion(n, nuevo_string, memo);
        res = min(res, costo);

        // Caso 2: elimino s[i] y lo engancho con otro s[j]
        for (int j = i + 1; j < s.size(); j++) {
            if (s[i] == s[j]) {
                string middle = s.substr(i + 1, j - i - 1);
                string right2 = s.substr(j);
                int costo_fusion = 1 + funcion(n, middle, memo) + funcion(n, right2, memo);
                res = min(res, costo_fusion);
            }
        }
    }

    memo[s] = res;
    return res;
}



// ---------- SOLUCION CORRECTA (DP O(n^3)) ----------
int dp[505][505];
int solve_dp(const string& s) {
    int n = s.size();
    if (n == 0) return 0;
    for (int i = 0; i < n; i++) dp[i][i] = 1;
    for (int len = 2; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            dp[l][r] = 1 + dp[l+1][r]; // borrar s[l] solo
            for (int k = l+1; k <= r; k++) {
                if (s[l] == s[k]) {
                    int val = (k == l+1 ? 0 : dp[l+1][k-1]) + dp[k][r];
                    dp[l][r] = min(dp[l][r], val);
                }
            }
        }
    }
    return dp[0][n-1];
}

// ---------- TESTING ----------
int main() {
    mt19937 rng(12345);
    uniform_int_distribution<int> dist(0, 25);

    for (int t = 1; t <= 200000; t++) {
        int n = rng() % 12 + 1; // tamaño pequeño para detectar diferencias
        string s;
        for (int i = 0; i < n; i++) s.push_back('a' + dist(rng));

        string comprimido = comprimir_string(s);

        unordered_map<string, int> memo;
        int got = funcion(comprimido.size(), comprimido, memo);
        int expected = solve_dp(comprimido);

        if (got != expected) {
            cout << "Contraejemplo encontrado!\n";
            cout << "s = " << s << "\n";
            cout << "comprimido = " << comprimido << "\n";
            cout << "esperado = " << expected << ", obtenido = " << got << "\n";
            return 0;
        }
    }

    cout << "No se encontraron contraejemplos en 200k tests." << endl;
    return 0;
}