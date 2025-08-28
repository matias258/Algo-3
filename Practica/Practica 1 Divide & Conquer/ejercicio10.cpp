#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;

/*
Ejercicio 10 (DistanciaMaxima) ⋆
Dado un arbol binario cualquiera, diseñar un algoritmo de dividir y conquistar que devuelva la maxima
distancia entre dos nodos (es decir, maxima cantidad de ejes a atravesar). El algoritmo no debe hacer recorridos innecesarios sobre el arbol. 
Hint: para saber el camino mas largo de un arbol, posiblemente necesite conocer mas que solo los caminos mas largos de sus subarboles.
*/

// Implementemos un Binary Tree, por ejemplo éste hace un binary search en el Tree.
struct Node{
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Node(int item, Node* p = nullptr)
      : key(item), left(nullptr), right(nullptr), parent(p) {}
};

Node* search(Node* root, int key){
    if (root == NULL || root->key == key){
        return root;
    }
    if (root->key < key){
        return search(root->right, key);
    }
    return search(root->left, key);
}

/*
Pero ahora queremos diseñar algoritmo de dividir y conquistar que devuelva la maxima distancia entre dos nodos (es decir, maxima cantidad de ejes a atravesar).
*/
int DistanciaMaxima(Node* root, int key, int dist){
    if (root == NULL || (root->right == NULL && root->left == NULL)){
        return DistanciaMaxima(root->parent, key, dist - 1);
    }
    dist += 1;
    if (root->right != NULL){
        dist += 1;
        return DistanciaMaxima(root->right, key, dist);
    }
    return DistanciaMaxima(root->right, key, dist);

}

int main() {
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    root->right->left = new Node(60);
    root->right->right = new Node(80);

    cout << "=== Test Search ===" << endl;
    cout << ((search(root, 19) != NULL)? "Found" : "Not Found") << "   // Expected: Not Found" << endl;
    cout << ((search(root, 80) != NULL)? "Found" : "Not Found") << "   // Expected: Found" << endl;
    cout << ((search(root, 50) != NULL)? "Found" : "Not Found") << "   // Expected: Found" << endl;

    cout << "\n=== Test DistanciaMaxima ===" << endl;
    cout << "DistanciaMaxima desde root (50): " << DistanciaMaxima(root, 50, 0) << "   // Expected: 2" << endl;
    cout << "DistanciaMaxima desde nodo 30: " << DistanciaMaxima(root->left, 30, 0) << "   // Expected: 1" << endl;
    cout << "DistanciaMaxima desde nodo 70: " << DistanciaMaxima(root->right, 70, 0) << "   // Expected: 1" << endl;
    cout << "DistanciaMaxima desde nodo 20 (hoja): " << DistanciaMaxima(root->left->left, 20, 0) << "   // Expected: 0" << endl;
    cout << "DistanciaMaxima desde nodo 60 (hoja): " << DistanciaMaxima(root->right->left, 60, 0) << "   // Expected: 0" << endl;

    // Árbol más pequeño
    Node* root2 = new Node(10);
    root2->left = new Node(5);
    root2->right = new Node(15);

    cout << "\n=== Test DistanciaMaxima en arbol chico ===" << endl;
    cout << "DistanciaMaxima desde root2 (10): " << DistanciaMaxima(root2, 10, 0) << "   // Expected: 1" << endl;
    cout << "DistanciaMaxima desde nodo hoja (5): " << DistanciaMaxima(root2->left, 5, 0) << "   // Expected: 0" << endl;

    return 0;
}