#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Estructura básica del nodo
struct Node {
    int val;
    Node *left, *right;
    Node(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Estructura para devolver dos valores (Altura y Diámetro)
struct Info {
    int h; // Altura
    int d; // Diámetro (distancia máxima)
};

Info resolver(Node* root) {
    if (root == nullptr) return {0, 0};

    Info izq = resolver(root->left);
    Info der = resolver(root->right);

    int altura_actual = 1 + max(izq.h, der.h);
    
    // El diámetro es el máximo entre:
    // 1. El diámetro que pasa por la raíz actual (izq.h + der.h)
    // 2. El máximo diámetro que ya existía en el subárbol izquierdo
    // 3. El máximo diámetro que ya existía en el subárbol derecho
    int diametro_actual = max({izq.h + der.h, izq.d, der.d});

    return {altura_actual, diametro_actual};
}

int DistanciaMaxima(Node* root) {
    return resolver(root).d;
}

int main() {
    // --- TEST 1: Árbol vacío ---
    cout << "Test 1 (Vacio): " << DistanciaMaxima(nullptr) << " (Expected: 0)" << endl;

    // --- TEST 2: Un solo nodo ---
    Node* root2 = new Node(1);
    cout << "Test 2 (Solo raiz): " << DistanciaMaxima(root2) << " (Expected: 0)" << endl;

    // --- TEST 3: Árbol balanceado simple ---
    //      1
    //     / \
    //    2   3
    Node* root3 = new Node(1);
    root3->left = new Node(2);
    root3->right = new Node(3);
    cout << "Test 3 (Balanceado): " << DistanciaMaxima(root3) << " (Expected: 2)" << endl;

    // --- TEST 4: Árbol tipo "Línea" (Degenerado) ---
    //  1 - 2 - 3 - 4
    Node* root4 = new Node(1);
    root4->right = new Node(2);
    root4->right->right = new Node(3);
    root4->right->right->right = new Node(4);
    cout << "Test 4 (Linea): " << DistanciaMaxima(root4) << " (Expected: 3)" << endl;

    // --- TEST 5: El camino más largo NO pasa por la raíz ---
    //           1
    //          / 
    //         2  <-- El diámetro está acá abajo
    //        / \
    //       3   4
    //      /     \
    //     5       6
    Node* root5 = new Node(1);
    root5->left = new Node(2);
    root5->left->left = new Node(3);
    root5->left->right = new Node(4);
    root5->left->left->left = new Node(5);
    root5->left->right->right = new Node(6);
    // Camino: 5 -> 3 -> 2 -> 4 -> 6 (Distancia 4)
    cout << "Test 5 (No pasa por raiz): " << DistanciaMaxima(root5) << " (Expected: 4)" << endl;

    return 0;
}