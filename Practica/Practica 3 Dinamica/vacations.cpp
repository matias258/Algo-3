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

void print_memo_matrix(const vector<vector<int>>& memo) {
    for (int i = 0; i < memo.size(); ++i) {
        for (int j = 0; j < memo[0].size(); ++j) {
            if (memo[i][j] == INT_MAX) {
                cout << "X  ";
            } else {
                cout << memo[i][j] << "  ";
            }
        }
        cout << endl;
    }
}

/*
https://codeforces.com/problemset/problem/698/A

Enunciado
Pepi tiene N días de vacaciones, donde puede hacer actividades:
● Se pueden hacer 2 actividades: gimnasio y competencias.
● Cada día puede tener disponible ninguna, alguna o ambas.
Pepi en cada día puede:
● Hacer una actividad que esté disponible, siempre que no la haya hecho el día
anterior.
● Descansar.
La idea es minimizar la cantidad de días de descanso.
Es un ejercicio de optimización.
*/


vector<int> dias_gym;
vector<int> dias_compe;
// eleccion: 0 -> nada, 1 -> gym, 2 -> compe
int vacations_bt(int d, int n, int eleccion){
    if (d == n) return 0;

    int hacer_compe = INT_MAX;
    int hacer_gym = INT_MAX;
    int hacer_nada = INT_MAX;

    if (eleccion == 1){ // hice gym el dia anterior
        if (find(dias_compe.begin(), dias_compe.end(), d) != dias_compe.end()){
            hacer_compe = vacations_bt(d+1, n, 2);
        }
        hacer_nada = vacations_bt(d+1, n, 0) + 1;
    }
    else if (eleccion == 2){ // hice compe el dia anterior
        if (find(dias_gym.begin(), dias_gym.end(), d) != dias_gym.end()){
            hacer_gym = vacations_bt(d+1, n, 1);
        }
        hacer_nada = vacations_bt(d+1, n, 0) + 1;
    }
    else { // no hice nada el dia anterior
        if (find(dias_compe.begin(), dias_compe.end(), d) != dias_compe.end()){
            hacer_compe = vacations_bt(d+1, n, 2);
        }
        if (find(dias_gym.begin(), dias_gym.end(), d) != dias_gym.end()){
            hacer_gym = vacations_bt(d+1, n, 1);
        }
        hacer_nada  = vacations_bt(d+1, n, 0) + 1; // descansar
    }
    return min(hacer_compe, min(hacer_gym, hacer_nada));
}

// Ahora intentemos por Programacion Dinamica
// Recuerdo eleccion: 0 -> nada, 1 -> gym, 2 -> compe
int vacations_dp(int d, int n, int eleccion, vector<vector<int>>& memo){
    if (d == n) return 0;
    if (memo[d][eleccion] != INT_MAX){
        return memo[d][eleccion];
    }
    int hacer_compe = INT_MAX;
    int hacer_gym = INT_MAX;
    int hacer_nada = INT_MAX;

    // Tengo opcion de hacer gym
    if (find(dias_gym.begin(), dias_gym.end(), d) != dias_gym.end() && eleccion != 1){
        hacer_gym = vacations_dp(d+1, n, 1, memo);
    }
    // Tengo opcion de hacer compe
    if (find(dias_compe.begin(), dias_compe.end(), d) != dias_compe.end() && eleccion != 2){
        hacer_compe = vacations_dp(d+1, n, 1, memo);
    }
    // Siempre puedo no hacer nada
    hacer_nada = vacations_dp(d+1, n, 0, memo) + 1;

    memo[d][eleccion] = min(hacer_gym, min(hacer_compe, hacer_nada));

    return memo[d][eleccion];

}

int main(){
    int n;
    cout << "Ingrese el numero de dias: ";
    cin >> n;

    vector<int> atributos(n);
    cout << "Ingrese los " << n << " atributos separados por espacios (0=nada, 1=compe, 2=gym, 3=ambos):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> atributos[i];
    }

    // Limpiamos los vectores para asegurar que no tengan datos anteriores.
    dias_compe.clear();
    dias_gym.clear();

    // Llenamos los vectores dias_compe y dias_gym.
    for (int i = 0; i < n; ++i){
        if (atributos[i] == 1 || atributos[i] == 3){
            dias_compe.push_back(i);
        }
        if (atributos[i] == 2 || atributos[i] == 3){
            dias_gym.push_back(i);
        }
    }

    // Inicializamos la tabla de memoización con un valor de INT_MAX.
    vector<vector<int>> memo(n, vector<int>(3, INT_MAX));

    // Llamamos a la función de programación dinámica para obtener el resultado.
    // El estado inicial es el día 0, con la opción de "nada" en el día -1.
    int res = vacations_dp(0, n, 0, memo);
    
    // **BUG ARREGLADO:** Imprimimos el resultado final, no los vectores.
    cout << "El numero minimo de dias de descanso es: " << res << endl;
    
    return 0;
}

/*
int main(){ // vacations dynamic programming
    // --- Caso de Prueba 1: Actividades Alternas ---
    dias_gym = {2, 3};
    dias_compe = {1, 2};
    int n_case1 = 4;
    vector<vector<int>> memo1(n_case1, vector<int>(3, INT_MAX));
    int res1 = vacations_dp(0, n_case1, 0, memo1);

    cout << "Test 1: Actividades Alternas" << endl;
    cout << "Resultado Esperado: 2 | Resultado Obtenido: " << res1 << endl;
    cout << "---" << endl;
    cout << "Matriz Memo:" << endl;
    print_memo_matrix(memo1);
    cout << endl;

    // --- Caso de Prueba 2: Solo un tipo de actividad ---
    dias_gym = {0, 2};
    dias_compe = {};
    int n_case2 = 3;
    vector<vector<int>> memo2(n_case2, vector<int>(3, INT_MAX));
    int res2 = vacations_dp(0, n_case2, 0, memo2);
    
    cout << "Test 2: Solo Gimnasio Disponible" << endl;
    cout << "Resultado Esperado: 1 | Resultado Obtenido: " << res2 << endl;
    cout << "---" << endl;
    cout << "Matriz Memo:" << endl;
    print_memo_matrix(memo2);
    cout << endl;

    // --- Caso de Prueba 3: Descanso Obligatorio ---
    dias_gym = {0, 3};
    dias_compe = {1, 4};
    int n_case3 = 5;
    vector<vector<int>> memo3(n_case3, vector<int>(3, INT_MAX));
    int res3 = vacations_dp(0, n_case3, 0, memo3);

    cout << "Test 3: Dia de Descanso Obligatorio" << endl;
    cout << "Resultado Esperado: 1 | Resultado Obtenido: " << res3 << endl;
    cout << "---" << endl;
    cout << "Matriz Memo:" << endl;
    print_memo_matrix(memo3);
    cout << endl;

    // --- Caso de Prueba 4: Sin Actividades ---
    dias_gym = {};
    dias_compe = {};
    int n_case4 = 2;
    vector<vector<int>> memo4(n_case4, vector<int>(3, INT_MAX));
    int res4 = vacations_dp(0, n_case4, 0, memo4);

    cout << "Test 4: Sin Actividades Disponibles" << endl;
    cout << "Resultado Esperado: 2 | Resultado Obtenido: " << res4 << endl;
    cout << "---" << endl;
    cout << "Matriz Memo:" << endl;
    print_memo_matrix(memo4);
    cout << endl;

    // --- Caso de Prueba 4: Test 1 Codeforces ---
    dias_compe = {0, 1};
    dias_gym = {1, 2};
    int n_case5 = 4;
    vector<vector<int>> memo5(n_case5, vector<int>(3, INT_MAX));
    int res5 = vacations_dp(0, n_case5, 0, memo5);

    cout << "Test 5: Test 1 de Codeforces" << endl;
    cout << "Resultado Esperado: 2 | Resultado Obtenido: " << res5 << endl;
    cout << "---" << endl;
    cout << "Matriz Memo:" << endl;
    print_memo_matrix(memo5);
    cout << endl;

    return 0;
}
*/

/*
int main() {    // vacations backtracking
    

    // --- Test Case 1: Simple Alternating Activities ---
    dias_gym = {1, 3};
    dias_compe = {0, 2};
    int n_case1 = 4;
    int res1 = vacations_bt(0, n_case1, 0);
    cout << "Test 1: Alternating Activities" << endl;
    cout << "Expected: 0 | Result: " << res1 << endl;
    cout << "---" << endl;

    // --- Test Case 2: Consecutive Same Activity ---
    dias_gym = {0, 2};
    dias_compe = {3, 4};
    int n_case2 = 5;
    int res2 = vacations_bt(0, n_case2, 0);
    cout << "Test 2: Consecutive Same Activity" << endl;
    cout << "Expected: 2 | Result: " << res2 << endl;
    cout << "---" << endl;
    
    // --- Test Case 3: Only One Activity Type Available ---
    dias_gym = {0, 2};
    dias_compe = {};
    int n_case3 = 3;
    int res3 = vacations_bt(0, n_case3, 0);
    cout << "Test 3: Only One Activity Type" << endl;
    cout << "Expected: 1 | Result: " << res3 << endl;
    cout << "---" << endl;
    
    // --- Test Case 4: No Activities Available ---
    dias_gym = {};
    dias_compe = {};
    int n_case4 = 2;
    int res4 = vacations_bt(0, n_case4, 0);
    cout << "Test 4: No Activities" << endl;
    cout << "Expected: 2 | Result: " << res4 << endl;
    cout << "---" << endl;

    return 0;
}
*/