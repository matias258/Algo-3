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
vector<int> aleylosuno(int n, int l, int r){
    vector<int> elementos;

    if (n == 1 || n == 0){
        elementos.push_back(n);
        return elementos;
    }

    int x1, x3 = n/2;
    int x2 = n % 2;


    if (x1 != 1 || x1 != 0){
        return aleylosuno(x1, l, r);
    }
    if (x2 != 1 || x2 != 0){
        return aleylosuno(x2, l, r);
    }
    if (x3 != 1 || x3 != 0){
        return aleylosuno(x3, l, r);
    }

}

int main(){
    int n = 6;
    int l = 3;
    int r = 6;
    vector<int> res = aleylosuno(6, 3, 6);
    printf("el vector final es: ", res);
    
    return 0;
}