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
Merge Sort para Python

def merge_sort ( arr ):
    if len ( arr ) <= 1:
        return arr
    medio = len ( arr ) // 2 
    mitad_izq = merge_sort ( arr [: medio ])
    mitad_der = merge_sort ( arr [ medio :])
    return merge ( mitad_izq , mitad_der )

def merge ( izq , der ):
    mergeados = []
    i = j = 0

    while i < len ( izq ) and j < len ( der ):
        if izq [i] < der [j ]:
            mergeados . append ( izq [ i ])
            i += 1
        else :
            mergeados . append ( der [ j ])
            j += 1

    mergeados . extend ( izq [ i :])
    mergeados . extend ( der [ j :])
    return mergeados

*/
// Esta haciendo mal el merge
vector<int> merge (vector<int> izq, vector<int> der){
    vector<int> mergeados;
    int i, j = 0;

    while (i < izq.size() && j < der.size()){
        if (izq[i] < der[j]){
            mergeados.push_back(izq[i]);
            i++;
        }
        else {
            mergeados.push_back(der[i]);
            j++; 
        }
        
    }
    for (int k = i; k < izq.size(); k++){
        mergeados.push_back(izq[k]);
    }
    for (int l = j; l < der.size(); l++){
        mergeados.push_back(der[l]);
    }
    return mergeados;
}


vector<int> merge_sort(vector<int> arr){
    if (arr.size() <= 1){
        return arr;
    }
    int medio = arr.size(); 
    vector<int>mitad_izq;
    vector<int>mitad_der; 
    for (int k = 0; k < arr.size() / 2; k++){
        mitad_izq.push_back(arr[k]);
    }
    for (int k = arr.size() / 2; k < arr.size(); k++){
        mitad_der.push_back(arr[k]);
    }
    return merge(mitad_izq, mitad_der);
}

int main(){

    vector<int> arr = {1, 6, 2, 2, 8, 34};
    vector<int> sorted_arr = merge_sort(arr);

    cout << "The Sorted array elements are: ";
    for (int i = 0; i < sorted_arr.size(); i++) {
        cout << sorted_arr[i] << ' ';
    }
    return 0;
}