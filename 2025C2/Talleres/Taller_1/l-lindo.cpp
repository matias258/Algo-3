#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <string>
using namespace std;

// Recordar:
// char l = 'a'
// char l_dos = l + 1 = 'b'

int es_l_lindo(int size, string s, char l){
    if (s.size() <= 1){     // Caso (1): Si long(s) = 1, entonces si s[0] = 0 --> 1 else 1
        if (l == s[0]){
            return 0;
        }
        else{
            return 1;
        } 
    }

    int medio = s.size() / 2;
    string s_izq;
    string s_der;
    int count_izq = 0;
    int count_der = 0;
    
    for (int i = 0; i < medio; i++){            // parto el string en 2 mitades (divide)
        s_izq.push_back(s[i]);
        s_der.push_back(s[i + medio]);

        // 2 casos posibles: O empiezo a-lindo por subarr derecha, o por subarray izquierda

        // Caso subarray izquierda (cuento cambios necesarios)
        if (s_izq[i] != l){                     
            count_izq++;
        }

        // Caso subarray derecha (cuento cambios necesarios)
        if (s_der[i] != l){
            count_der++;
        }
    }   


    // Hago recursion l+1
    int costo_izq = count_izq + es_l_lindo(s_der.size(), s_der, l+1);
    int costo_der = count_der + es_l_lindo(s_izq.size(), s_izq, l+1);

    if (costo_izq < costo_der){
        return costo_izq;
    }
    else{
        return costo_der;
    }
}

int lindurita(int size, string s){
    return es_l_lindo(size, s, 'a');
}


int main(){
    int n;      // n de casos de prueba
    int size;
    string s;
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> size;
        cin >> s;
        int res = lindurita(size, s);
        cout << res << endl;
    }

    return 0;
}
/*
int main() {
    // Caso 1: string de un solo caracter igual a l
    cout << "Test 1: " << es_l_lindo(1, "a", 'a', 0, 0) << " (esperado: 0)" << endl;

    // Caso 2: string de un solo caracter distinto a l
    cout << "Test 2: " << es_l_lindo(1, "b", 'a', 0, 0) << " (esperado: 1)" << endl;

    // Caso 3: string de dos caracteres iguales a l
    cout << "Test 3: " << es_l_lindo(2, "aa", 'a', 0, 0) << " (esperado: 0)" << endl;

    // Caso 4: string de dos caracteres, uno igual y otro distinto
    cout << "Test 4: " << es_l_lindo(2, "ab", 'a', 0, 0) << " (esperado: 1)" << endl;

    // Caso 5: string de cuatro caracteres, todos iguales a l
    cout << "Test 5: " << es_l_lindo(4, "aaaa", 'a', 0, 0) << " (esperado: 0)" << endl;

    // Caso 6: string de cuatro caracteres, todos distintos a l
    cout << "Test 6: " << es_l_lindo(4, "bbbb", 'a', 0, 0) << " (esperado: 3)" << endl;

    // Caso 7: string de ejemplo del main original
    cout << "Test 7: " << es_l_lindo(8, "aaadcbbb", 'a', 0, 0) << " (esperado: ?)" << endl;

    return 0;
}
*/