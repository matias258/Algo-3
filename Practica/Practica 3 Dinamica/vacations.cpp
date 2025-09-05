#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;
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

/*
Actividad:
0: Descansar
1: Competencia
2: Gimnasio
*/
// n: # de dias; dia: dia actual; actividad: 'c' compe, 'g': gym, 'd': descansar;
int dias_minimos_descanso(int n, int dia, int ultAct, vector<vector<int>> memo){
    if (dia == n){   // ya vi todos los dias
        return 0;
    }
    if (ultAct == 0){   // Descanso
        memo[dia][ultAct] = 1;
        return dias_minimos_descanso(n, dia + 1, 0, memo);
    }
    if (ultAct == 1){   // Competencia
        memo[dia][ultAct] = 1;
        return dias_minimos_descanso(n, dia + 1, 0, memo);
    }
    return 0;
}


int main() {
    int n;
    cin >> n;                // cantidad de días
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];         // actividades permitidas por día
    }
}
/*
int main() {
    int dias = 6;
    int opciones = 3;
    vector<vector<int>> memo(dias + 1, vector<int>(opciones, 0));
    for (int i = 0; i < dias; i++) {
        for (int j = 0; j < opciones; j++) {
            cout << memo[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
*/
