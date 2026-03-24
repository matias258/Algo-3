#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

bool IzquierdaDominante(vector<int> a){
    if (a.size() <= 1){
        return true;
    }

    int medio = a.size() / 2;
    int sumIzq = 0;
    int sumDer = 0;

    vector<int> aIzq;
    vector<int> aDer; 

    for (int i = 0; i < medio; i++){
        sumIzq += a[i];
        aIzq.push_back(a[i]);
    }

    for (int i = medio; i < a.size(); i++){
        sumDer += a[i];
        aDer.push_back(a[i]);
    }
    
    if (sumDer > sumIzq){
        return false;
    }
    else{
        return IzquierdaDominante(aIzq) && IzquierdaDominante(aDer);
    }
}








int main(){
    vector<int> arr1 = {8, 4, 7, 6, 5, 1, 3, 2};     // false -> 0
    vector<int> arr2 = {8, 6, 7, 4, 5, 1, 3, 2};    // true -> 1
    vector<int> arr3 = {1};                         // true -> 1 (caso base tamaño 1)
    vector<int> arr4 = {5, 2};                      // true -> 1 (5 > 2, y ambos subcasos triviales)
    vector<int> arr5 = {2, 5};                      // false -> 0 (2 <= 5)
    vector<int> arr6 = {20, 15, 10, 5, 4, 3, 2, 1}; // true -> 1
    vector<int> arr7 = {1, 2, 3, 4};                // false -> 0 (izquierda 1+2=3 <= derecha 3+4=7)
    vector<int> arr8 = {-1, -2, -3, -4};            // true -> 1
    vector<int> arr9 = {9, 5, 1, 0};                // true -> 1 (14 > 1, y recursivamente también)
    vector<int> arr10 ={50, 40, 30, 20, 10, 9, 8, 7,// true -> 1 (izquierda siempre domina)
                         6, 5, 4, 3, 2, 1, 1, 0};       

    cout << "arr1: " << IzquierdaDominante(arr1) << " (expected 0)" << endl;
    cout << "arr2: " << IzquierdaDominante(arr2) << " (expected 1)" << endl;
    cout << "arr3: " << IzquierdaDominante(arr3) << " (expected 1)" << endl;
    cout << "arr4: " << IzquierdaDominante(arr4) << " (expected 1)" << endl;
    cout << "arr5: " << IzquierdaDominante(arr5) << " (expected 0)" << endl;
    cout << "arr6: " << IzquierdaDominante(arr6) << " (expected 1)" << endl;
    cout << "arr7: " << IzquierdaDominante(arr7) << " (expected 0)" << endl;
    cout << "arr8: " << IzquierdaDominante(arr8) << " (expected 1)" << endl;
    cout << "arr9: " << IzquierdaDominante(arr9) << " (expected 1)" << endl;
    cout << "arr10: " << IzquierdaDominante(arr10) << " (expected 1)" << endl;

    return 0;
}