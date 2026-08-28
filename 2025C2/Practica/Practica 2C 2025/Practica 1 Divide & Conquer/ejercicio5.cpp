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
Ejercicio 5 (PotenciaLogaritmica) ⋆
Encuentre un algoritmo para calcular a^b en tiempo logarıtmico en b. Piense como reutilizar los resultados
ya calculados. Justifique la complejidad del algoritmo dado.
*/

//No sirve, tiene complejidad O(b), es decir que es lineal en b.
int PotenciaLogaritmica(int a, int b, int m){
    if (b <= 1){
        return a;
    }
    else{
        a = a * m;
        return PotenciaLogaritmica(a, b-1, m);
    }
}

int Calcular_Potencia(int a, int b){
    return PotenciaLogaritmica(a, b, a);
}

int PotenciaLogaritmica2(int a, int b){
    
}

int main(){
    cout << "Test 1: " << Calcular_Potencia(3, 5) 
         << " (expected 243)" << endl;

    cout << "Test 2: " << Calcular_Potencia(2, 10) 
         << " (expected 1024)" << endl;

    cout << "Test 3: " << Calcular_Potencia(5, 0) 
         << " (expected 1)" << endl; // cualquier número^0 = 1

    cout << "Test 4: " << Calcular_Potencia(7, 1) 
         << " (expected 7)" << endl;

    cout << "Test 5: " << Calcular_Potencia(10, 2) 
         << " (expected 100)" << endl;

    cout << "Test 6: " << Calcular_Potencia(-2, 3) 
         << " (expected -8)" << endl; // negativo y exponente impar

    cout << "Test 7: " << Calcular_Potencia(-2, 4) 
         << " (expected 16)" << endl; // negativo y exponente par

    return 0;
}