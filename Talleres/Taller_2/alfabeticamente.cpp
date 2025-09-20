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


int alfa(vector<string>& s, vector<string>& reverse_s, vector<int>& c, int i, int estado, vector<vector<int>>& memo){
    // Caso base: última palabra
    if (i == s.size() - 1) {
        if (estado == 0) {
            return 0;        // sin invertir
        } else {
            return c[i];     // invertida
        }
    }

    if (memo[i][estado] < INT_MAX/2){
        return memo[i][estado];
    }

    string actual;
    int costo;

    if (estado == 0) {
        actual = s[i];
        costo = 0;
    } 
    else{
        actual = reverse_s[i];
        costo = c[i];
    }

    // Pa que no haga ¡kaboom!
    int res = INT_MAX / 2;

    // Caso 1: Puedo seguir --> estado = 0
    if (actual <= s[i+1]) {
        res = min(res, costo + alfa(s,reverse_s, c, i+1, 0, memo));
    }

    // Caso 2: Tengo que dar vuelta la palabra --> estado = 1
    if (actual <= reverse_s[i+1]) {
        res = min(res, costo + alfa(s,reverse_s, c, i+1, 1, memo));
    }

    memo[i][estado] = res;

    return memo[i][estado];
}
 
int alfa_result(vector<string>& s, vector<int>& c){
    vector<string> reverse_s = s; 

    // mejor prevenir que curar 
    vector<vector<int>> memo1(s.size(), vector<int>(2, INT_MAX/2));
    vector<vector<int>> memo2(s.size(), vector<int>(2, INT_MAX/2));

    for (int i = 0; i < s.size(); i++) {
            reverse(reverse_s[i].begin(), reverse_s[i].end());
    }
    
    // Comienzo con la 1ra palabra como viene
    int res1 = alfa(s, reverse_s, c, 0, 0, memo1);

    // Comienzo con la 1ra palabra invertida
    int res2 = alfa(s, reverse_s, c, 0, 1, memo2); 

    int res = min(res1, res2);
 
    if (res >= INT_MAX/4){
        return -1;
    }
    return res;
}

int main() {
    // Test cases with expected outputs
    vector<tuple<vector<string>, vector<int>, int, string>> tests = {
        {{"dcba", "bcda", "abcd", "cdab"}, {1, 2, 3, 4}, -1, "Impossible to form non-decreasing sequence"},
        {{"abc"}, {5}, 0, "Single string, no reversal needed"},
        {{"ba", "ab"}, {1, 1}, 1, "Two strings, one reversal makes it non-decreasing"},
        {{"abc", "abc", "abc"}, {1, 1, 1}, 0, "Equal strings, no reversal needed"},
        {{"a", "b", "c"}, {1000000, 1000000, 1000000}, 0, "Already non-decreasing, large costs"},
        {{"", ""}, {1, 1}, 0, "Empty strings, no reversal needed"},
        {{"ba", "ab", "ba", "ab", "ba"}, {1, 1, 1, 1, 1}, 2, "Alternating pattern, multiple reversals"},
        {{"cba", "abc", "bca"}, {1, 1, 1}, 1, "Test memoization with multiple valid paths"},
        {{"z", "a", "z"}, {1, 1, 1}, -1, "Impossible: middle string too small"},
        {{"abc", "xyz", "abc"}, {1, 1, 1}, -1, "Impossible: second string too large"},
        {{"aaa", "aba", "aab"}, {1, 1, 1}, 1, "Close strings, one reversal needed"},
        {{"zyx", "zyx", "zyx", "zyx"}, {1000000, 1000000, 1000000, 1000000}, 0, "All equal strings, high costs"},
        {{"aa", "ba", "ab"}, {15, 10, 5}, 5, "Decreasing costs, optimal reverse at i=2"}
    };

    for (int i = 0; i < tests.size(); ++i) {
        auto& [strings, costs, expected, description] = tests[i];
        cout << "Test Case " << i + 1 << " (" << description << "):" << endl;
        cout << "Input: n = " << strings.size() << ", strings = [";
        for (int j = 0; j < strings.size(); ++j) {
            cout << "\"" << strings[j] << "\"" << (j < strings.size() - 1 ? ", " : "");
        }
        cout << "], costs = [";
        for (int j = 0; j < costs.size(); ++j) {
            cout << costs[j] << (j < costs.size() - 1 ? ", " : "");
        }
        cout << "]" << endl;
        
        int result = alfa_result(strings, costs);
        cout << "Output: " << result << ", Expected: " << expected;
        if (result == expected) {
            cout << " [PASS]" << endl;
        } else {
            cout << " [FAIL]" << endl;
        }
        cout << endl;
    }
    return 0;
}

/*
int main(){
    int n;
    cin >> n;
    vector<int> c(n); 
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<string> s(n); 
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }


    cout << alfa_result(s, c);

    return 0;
}
    
*/