#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <cstdio>
using namespace std;

struct Node{
    int key;
    Node* left;
    Node* right;
    Node* parent;
    Node(int item, Node* p = nullptr)
      : key(item), left(nullptr), right(nullptr), parent(p) {}
};

int suma_arbol(Node* root, const vector<int>& f, int piso){
    if (root == nullptr){
        return 0;
    }
    else{
        int ff = f[root->key];
        int pp = piso;
        int suma = f[root->key - 1] * piso;
        int izq = suma_arbol(root->left, f, piso + 1);
        int der = suma_arbol(root->right, f, piso + 1);
       
        return izq + der + suma;
    }
}


int main(){
    // Caso 1: Árbol size 5
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    Node* root1 = new Node(1);
    root1->left = new Node(2, root1);
    root1->right = new Node(3, root1);
    root1->left->left = new Node(4, root1->left);
    root1->left->right = new Node(5, root1->left);

    vector<int> f1 = {4, 3, 7, 1, 2}; // índices: 1..5
    int res1 = suma_arbol(root1, f1, 1);
    cout << "Caso 1 -> Resultado: " << res1 
         << " | Expected: " 
         << f1[0]*1 + f1[1]*2 + f1[2]*2 + f1[3]*3 + f1[4]*3 
         << endl;

    // Liberar
    delete root1->left->left;
    delete root1->left->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    // Caso 2: Árbol con un solo nodo
    //    1
    Node* root2 = new Node(1);
    vector<int> f2 = {10}; 
    int res2 = suma_arbol(root2, f2, 1);
    cout << "Caso 2 -> Resultado: " << res2 
         << " | Expected: " << f2[0]*1 << endl;
    delete root2;

    // Caso 3: Árbol en línea (tipo lista)
    //    1
    //     \
    //      2
    //       \
    //        3
    Node* root3 = new Node(1);
    root3->right = new Node(2, root3);
    root3->right->right = new Node(3, root3->right);

    vector<int> f3 = {1,2,3};
    int res3 = suma_arbol(root3, f3, 1);
    cout << "Caso 3 -> Resultado: " << res3 
         << " | Expected: " << f3[0]*1 + f3[1]*2 + f3[2]*3 << endl;

    delete root3->right->right;
    delete root3->right;
    delete root3;

    // Caso 4: Árbol completo de altura 2
    //        1
    //       / \
    //      2   3
    Node* root4 = new Node(1);
    root4->left = new Node(2, root4);
    root4->right = new Node(3, root4);

    vector<int> f4 = {5, 6, 7};
    int res4 = suma_arbol(root4, f4, 1);
    cout << "Caso 4 -> Resultado: " << res4 
         << " | Expected: " << f4[0]*1 + f4[1]*2 + f4[2]*2 << endl;

    delete root4->left;
    delete root4->right;
    delete root4;

    // Caso 5: Árbol degenerado hacia la izquierda
    //        1
    //       /
    //      2
    //     /
    //    3
    Node* root5 = new Node(1);
    root5->left = new Node(2, root5);
    root5->left->left = new Node(3, root5->left);

    vector<int> f5 = {2,4,6};
    int res5 = suma_arbol(root5, f5, 1);
    cout << "Caso 5 -> Resultado: " << res5 
         << " | Expected: " << f5[0]*1 + f5[1]*2 + f5[2]*3 << endl;

    delete root5->left->left;
    delete root5->left;
    delete root5;

    return 0;
}