#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

// n = numero
// l, r = rango de la r (osea un i j)
// dado n, vamos a querer descomponerlo en 3 valores:
// 1. n/2; 
// 2. n mod 2; 
// 3. n/2;
// Repetimos con los nuevos valores (1.,2.,3.) hasta obtener 1s y 0s
// Contamos cuantos 1s hay en la última iteración, dentro del rango l r
int last_row_2(int n, int izq, int der, int tamaño, int sum){

    if (n == 1){
        sum ++;
    }
    //Jugar con el tamaño y las cotas izq y der, no esta nada terminado.
    if (tamaño < der - izq){
        return last_row_2(n/2, izq )
    }

    return last_row_2(n/2, izq, der-1, tamaño + 1, sum) + last_row_2()
}

int aleylosuno(int n, int l, int r){
    int sum = 0;

    
    return sum;
}
/*
int main(){
    
    int n, l, r;
    cin >> n;
    cin >> l;
    cin >> r;
    

    cout << last_row_2(10, 2, 4);
    return 0;
}
*/

int main(){
    // Test 1
    int res1 = aleylosuno(6, 3, 6);
    cout << "Test 1 -> Resultado: " << res1 << " | Expected: 3" << endl;

    // Test 2
    int res2 = aleylosuno(5, 1, 5);
    cout << "Test 2 -> Resultado: " << res2 << " | Expected: 4" << endl;

    // Test 3
    int res3 = aleylosuno(4, 2, 4);
    cout << "Test 3 -> Resultado: " << res3 << " | Expected: 1" << endl;

    // Test 4
    int res4 = aleylosuno(7, 1, 7);
    cout << "Test 4 -> Resultado: " << res4 << " | Expected: 7" << endl;

    // Test 5
    int res5 = aleylosuno(8, 1, 15);
    cout << "Test 5 -> Resultado: " << res5 << " | Expected: 8" << endl;

    int res6 = aleylosuno(9, 4, 11);
    cout << "Test 6 -> Resultado: " << res6 << " | Expected: 5" << endl;
    return 0;
}

