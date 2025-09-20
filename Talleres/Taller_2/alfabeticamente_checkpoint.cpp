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
 
 
int alfa (vector<string>& s, vector<string>& reverse_s, vector<int>& c, int i){
    if (i == s.size() - 1){
        if (s.size() == 1){
            return 0;
        }
        else{
            if (s[i-1] <= s[i-1] || reverse_s[i-1] <= s[i]){
                return 0;
            }
            else{ // hay que darla vuelta
                return c[i];
            }
        }
    }
 
    
    int seguir = INT_MAX / 2;
    int reverse_seguir = INT_MAX / 2;
 
    if (s[i] > s[i+1] && reverse_s[i] > s[i+1] && s[i] > reverse_s[i+1] && reverse_s[i] > reverse_s[i+1]){
        return INT_MAX / 2;
    }
    else{
        if (s[i] < s[i+1]){
            seguir = alfa(s, reverse_s, c, i+1);
            reverse_seguir = c[i] + alfa(s, reverse_s, c, i+1);
        }
        reverse_seguir = c[i] + alfa(s, reverse_s, c, i+1);
    }
    
 
    int res = min(seguir, reverse_seguir);
    return res;
}
 
int alfa_result(vector<string>& s, vector<int>& c){
    vector<string> reverse_s = s; 
    for (int i = 0; i < s.size(); i++) {
            reverse(reverse_s[i].begin(), reverse_s[i].end());
    }
    
    int res = alfa(s, reverse_s, c, 0);
 
    if (res  >= INT_MAX/4){
        return -1;
    }
    return res;
}
 
/*
int main(){
    int n;
    cin >> n;
    vector<int> c(n);
    //vector<vector<int>> memo(n, vector<int>(n, -1)); 
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<string> s(n); 
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
 
 
    cout << alfa_result(s, c);
 
    return;
}
*/

int main(){
    {
        int n = 3;
        vector<int> c = {100, 200, 300};
        vector<string> s = {"abc", "efg", "hij"};


        int res = alfa_result(s, c);
        cout << "Sample 1 -> expected 0, obtenido " << res << endl;  // 0
    }
    {
        int n = 3;
        vector<int> c = {100, 200, 300};
        vector<string> s = {"za", "yb", "xc"};

        int res = alfa_result(s, c);
        cout << "Sample 2 -> expected 300, obtenido " << res << endl;  // 0
    }
    {
        int n = 2;
        vector<int> c = {0, 0};
        vector<string> s = {"casas", "abraza"};
        int res = alfa_result(s, c);
        cout << "Sample 3 -> expected -1, obtenido " << res << endl;  // 0
    }

    // Test 1: Bug Base Case y Dependencia
    {
        vector<int> c = {10, 5};
        vector<string> s = {"ba", "ab"};
        cout << "Test 1: " << alfa_result(s, c) << " // Expected: 5" << endl;
    }

    // Test 2: Overwrite Bug
    {
        vector<int> c = {1, 2, 3};
        vector<string> s = {"aa", "bb", "cc"};
        cout << "Test 2: " << alfa_result(s, c) << " // Expected: 0" << endl;
    }

    // Test 3: Imposibilidad Mal Detectada
    {
        vector<int> c = {0, 0};
        vector<string> s = {"ab", "aa"};
        cout << "Test 3: " << alfa_result(s, c) << " // Expected: -1" << endl;
    }

    // Test 4: Eficiencia (n=10 ya lento, simula con n=5)
    {
        vector<int> c(5, 0);
        vector<string> s = {"a", "b", "c", "d", "e"};
        cout << "Test 4 (n=5): " << alfa_result(s, c) << " // Expected: 0 (but slow)" << endl;
    }

    // Test 5: Dependencia Anterior
    {
        vector<int> c = {0, 0, 1};
        vector<string> s = {"a", "b", "a"};
        cout << "Test 5: " << alfa_result(s, c) << " // Expected: -1" << endl;
    }
    // Test 6: ba <= ab? falso
    {
        vector<int> c = {100, 200, 300};
        vector<string> s = {"ab", "ba", "dddd"};
        cout << "Test 6: " << alfa_result(s, c) << " // Expected: 100" << endl;
    }
    return 0;
}