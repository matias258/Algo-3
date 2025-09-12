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

/*
Hay n * k cartas, hay k puntajes y n favoritas. puntajes es creciente.
*/

// Me construyo un map con key: numeros de las cartas; values: repeticiones de esos numeros
map<int, int> repes(vector<int> cartas){
    map<int, int> m = {};

    for (size_t i = 0; i < cartas.size(); i++){
        if (m.find(cartas[i]) == m.end()) {
            m[cartas[i]] = 1;
        } else {
            m[cartas[i]]++;
        }
    }
    return m;
}

int cartas(map<int, int> m, vector<int>& favoritas, vector<int>& puntaje, int puntos, vector<int>& todas_cartas, size_t it, size_t cartas_usadas, vector<vector<int>>& memo, int iterar){
    if (it == favoritas.size() || cartas_usadas == todas_cartas.size()){
        return puntos;
    }
    if (memo[it][cartas_usadas] != -1){
        return memo[it][cartas_usadas];
    }

    int maximo = 0;

    if (m[favoritas[it]] > 0){

        m[favoritas[it]] = m[favoritas[it]] - 1; // elimino la que voy a agregar
        // sigo con el mismo jugador
        int puntos_seguir = cartas(m, favoritas, puntaje, puntaje[iterar], todas_cartas, it, cartas_usadas + 1, memo, iterar+1);

        // pasar directamente al prox jugador
        int puntos_pasar = puntaje[cartas_usadas] + cartas(m, favoritas, puntaje, puntos, todas_cartas, it + 1, cartas_usadas, memo, 0);  
        m[favoritas[it]]++; 
        // Tomo el resultado
        maximo = max(puntos_seguir, puntos_pasar);
    }

    // Si no puedo seguir sumando puntos --> Cambio de jugador
    else{
        maximo = max(maximo, cartas(m, favoritas, puntaje, puntos, todas_cartas, it + 1, cartas_usadas, memo, 0));
    }
    memo[it][cartas_usadas] = maximo;
    return maximo;
}


int main(){
        {
        // Si le doy los dos 10 al jugador 1, obtengo 15 pts. 
        // En cambio si doy un 10 al jugador 1 y otro 10 al jugador 3 --> 10 + 10 = 20 > 15 pts
        // Le agrego los dos de 20 al jugador 2 --> 15pts 
        // Obtengo 20 + 15 --> 35
        vector<int> todas_cartas = {10, 10, 20, 20, 99, 98};
        vector<int> favoritas = {10, 20, 10};
        vector<int> puntaje = {10, 15}; 
        map<int,int> m = repes(todas_cartas);
        int n = 3, k = 2;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(m, favoritas, puntaje, 0, todas_cartas, 0, 0, memo, 0);
        cout << "Test 11 -> expected 35, obtenido " << res << endl;
    }
    return 0;
}

/*
int main() {
    int n;
    int k;
    cin >> n >> k;
    
    vector<int> todas_cartas;
    for (int i = 0; i < n * k; i++) {
        int carta;
        cin >> carta;
        todas_cartas.push_back(carta);
    }

    vector<int> favoritas;
    for (int i = 0; i < n; i++) {
        int fav;
        cin >> fav;
        favoritas.push_back(fav);
    }

    vector<int> puntaje;
    for (int i = 0; i < k; i++) {
        int p;
        cin >> p;
        puntaje.push_back(p);
    }

    map<int, int> m = repes(todas_cartas);
    vector<vector<int>> memo(n+1, vector<int>(n, -1));
    int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
    cout << res;
    return 0;
}
*/

/*
int main() { 

    {
        vector<int> todas_cartas = {1,1,2,2}; // 4 cartas
        vector<int> favoritas = {1,1};        // 2 jugadores
        vector<int> puntaje = {10,20};        // h1=10, h2=20
        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 2;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);

        // Mejor reparto: un jugador recibe las dos '1' -> h2=20, otro h0=0 -> total 20
        cout << "Ejemplo 2 -> expected 20, obtenido " << res << endl;
    }
    
    // ======================
    // Ejemplo 1 (original)
    // ======================
    {
        vector<int> todas_cartas = {
            1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5, 1,2,3,4,5
        }; // 25 cartas
        vector<int> favoritas = {1,2,3,4,5};
        vector<int> puntaje = {10,20,30,40,50}; // h1..h5 (h1 != 0)
        map<int,int> m = repes(todas_cartas);
        int n = 5, k = 5;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // cada jugador recibe 5 de su favorito -> h5 = 50 -> total = 5 * 50 = 250
        cout << "Ejemplo 1 -> expected 250, obtenido " << res << endl;
    }


    // ======================
    // Ejemplo 3 (CORREGIDO: n=3, k=4 -> 12 cartas)
    // ======================
    {
        vector<int> todas_cartas;
        for (int i = 0; i < 4; ++i) { todas_cartas.push_back(1); }
        for (int i = 0; i < 4; ++i) { todas_cartas.push_back(2); }
        for (int i = 0; i < 4; ++i) { todas_cartas.push_back(3); }
        vector<int> favoritas = {1,2,3};
        vector<int> puntaje = {100,110,120,130}; // h1..h4
        map<int,int> m = repes(todas_cartas);
        int n = 3, k = 4;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // Podemos dar a cada jugador las 4 cartas de su favorito -> h4 = 130
        // total = 3 * 130 = 390
        cout << "Ejemplo 3 (corregido) -> expected 390, obtenido " << res << endl;
    }

    // ======================
    // Extra 1: todos los jugadores mismo favorito
    // n=2, k=4 -> 8 cartas
    // ======================
    {
        vector<int> todas_cartas = {5,5,5,5, 5,5,5,5}; // 8 cartas (todas '5')
        vector<int> favoritas = {5,5};
        vector<int> puntaje = {5,15,40,80}; // h1..h4
        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 4;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // Cada jugador recibe 4 veces su favorito -> h4 = 80 -> total = 160
        cout << "Extra 1 -> expected 160, obtenido " << res << endl;
    }

    // ======================
    // Extra 2: no hay coincidencias con favoritos
    // n=1, k=4 -> todas cartas '7', favorito distinto
    // ======================
    {
        vector<int> todas_cartas = {7,7,7,7};
        vector<int> favoritas = {1};
        vector<int> puntaje = {5,10,20,30}; // h1..h4
        map<int,int> m = repes(todas_cartas);
        int n = 1, k = 4;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // Ninguna carta coincide -> total = 0
        cout << "Extra 2 -> expected 0, obtenido " << res << endl;
    }

    // ======================
    // Extra 3: k=1, favoritos distintos
    // n=3, k=1 -> 3 cartas
    // ======================
    {
        vector<int> todas_cartas = {1,2,3};
        vector<int> favoritas = {1,2,3};
        vector<int> puntaje = {10}; // h1=10
        map<int,int> m = repes(todas_cartas);
        int n = 3, k = 1;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // Cada jugador recibe exactamente 1 de su favorito -> 3 * 10 = 30
        cout << "Extra 3 -> expected 30, obtenido " << res << endl;
    }

    // ======================
    // Tests adicionales para depuración (casos pequeños y borde)
    // ======================

    // Test 1: 1 jugador, 1 carta, coincide
    {
        vector<int> todas_cartas = {7};
        vector<int> favoritas = {7};
        vector<int> puntaje = {12}; // h1=12
        map<int,int> m = repes(todas_cartas);
        int n = 1, k = 1;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 1 -> expected 12, obtenido " << res << endl;
    }

    // Test 2: 1 jugador, 1 carta, no coincide
    {
        vector<int> todas_cartas = {5};
        vector<int> favoritas = {7};
        vector<int> puntaje = {9}; // h1=9
        map<int,int> m = repes(todas_cartas);
        int n = 1, k = 1;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 2 -> expected 0, obtenido " << res << endl;
    }

    // Test 3: 2 jugadores, k=1, favoritos distintos
    {
        vector<int> todas_cartas = {1,2};
        vector<int> favoritas = {1,2};
        vector<int> puntaje = {11}; // h1=11
        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 1;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 3 -> expected 22, obtenido " << res << endl;
    }

    // Test 4: 2 jugadores, k=1, ambos quieren '1' pero hay solo una '1'
    {
        vector<int> todas_cartas = {1,9};
        vector<int> favoritas = {1,1};
        vector<int> puntaje = {13}; // h1=13
        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 1;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 4 -> expected 13, obtenido " << res << endl;
    }

    // Test 5: 2 jugadores, k=2, favoritos distintos
    {
        vector<int> todas_cartas = {1,1,2,2};
        vector<int> favoritas = {1,2};
        vector<int> puntaje = {6,17}; // h1=6, h2=17
        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 2;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // cada uno recibe sus 2 favoritas -> 17 + 17 = 34
        cout << "Test 5 -> expected 34, obtenido " << res << endl;
    }

    // Test 6: 2 jugadores, k=3, cartas variadas
    {
        vector<int> todas_cartas = {1,1,2,2,3,3}; // 6 cartas
        vector<int> favoritas = {1,2};
        vector<int> puntaje = {5,14,33}; // h1=5, h2=14, h3=33
        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 3;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // cada jugador puede conseguir 2 favoritas -> h2=14 + h2=14 = 28
        cout << "Test 6 -> expected 28, obtenido " << res << endl;
    }

    // Test 7: 
    {
        vector<int> todas_cartas = {1,1,1, 5};
        vector<int> favoritas = {1,1};
        vector<int> puntaje = {10,25}; // h1=10, h2=25

        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 2;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        // cada jugador puede conseguir 2 favoritas -> h2=14 + h2=14 = 28
        cout << "Test 7 -> expected 35, obtenido " << res << endl;
    }

    // Test 8: Ningun favorito
    {
        vector<int> todas_cartas = {1,1,1,1,1,1,1,1,1,1}; // 10
        vector<int> favoritas = {1,1};
        vector<int> puntaje = {100,101, 102, 103, 105};

        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 5;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 8 -> expected 210, obtenido " << res << endl;
    }

    {   // Test 9
        vector<int> todas_cartas = {1,1,1,1,1,1,1,1,1,1}; // 10
        vector<int> favoritas = {1,1};
        vector<int> puntaje = {100,101,102,103,104}; 

        map<int,int> m = repes(todas_cartas);
        int n = 2, k = 5;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 9 -> expected 208, obtenido " << res << endl;
    }

    {
        vector<int> todas_cartas = {};
        vector<int> favoritas = {};
        vector<int> puntaje = {}; 

        map<int,int> m = repes(todas_cartas);
        int n = 0, k = 0;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 10 -> expected 0, obtenido " << res << endl;
    }

    {
        // Si le doy los dos 10 al jugador 1, obtengo 15 pts. 
        // En cambio si doy un 10 al jugador 1 y otro 10 al jugador 3 --> 10 + 10 = 20 > 15 pts
        // Le agrego los dos de 20 al jugador 2 --> 15pts 
        // Obtengo 20 + 15 --> 35
        vector<int> todas_cartas = {10, 10, 20, 20, 99, 98};
        vector<int> favoritas = {10, 20, 10};
        vector<int> puntaje = {10, 15}; 
        map<int,int> m = repes(todas_cartas);
        int n = 3, k = 2;
        vector<vector<int>> memo(n+1, vector<int>(k+1, -1));
        int res = cartas(n, k, m, favoritas, puntaje, 0, 0, memo);
        cout << "Test 11 -> expected 35, obtenido " << res << endl;
    }

    

    return 0;
}
*/