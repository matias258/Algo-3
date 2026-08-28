/*
Calcule la complejidad de un algoritmo que utiliza T(n) pasos para una entrada de tamaño n, donde T
cumple:
1) T(n) = T(n − 2) + 5
// ********************** MAL, NO ESTAMOS CALCULANDO UNA FUNCION RECURSIVA ************************
Como T(n) = T(n-2) + 5, entonces a = 1, c <= 1 y f(n) = O(1) = Tita(1), pues T(n) = a*T(n/c) + f(n)
Como n/c = n-2 <-> c = n/n-2 <-> c <= 1
Luego, Caso 2:
f(n) = Tita(1) --> Tita(log^1(1)) = Tita(1), --> T(n) = Tita(n^log1(1) * log(n)) = Tita(log(n))
****************************************************************************************************

Entonces T(n) = T(n − 2) + 5:
Sea O(n), vemos que T(n) esta contenido en O(n):
T(n-2) + 5;
T(n-4) + 5 + 5;
...
T(n-2k) + 5k, donde n-2k = 0
Luego, en el peor caso iteraríamos n veces, obteniendo así que la complejidad es de O(n)

2) T(n) = T(n − 1) + n
T(n-2) + 2n
T(n-3) + 3n
...
T(n-k) + kn, donde en peor caso k = n, luego, nuestra funcion es de la forma:
T(n) = T(n-1) + n, pero T(n-1) = T(n-2) + n-1, reemplazamos:
T(n) = T(n-2) + (n-1) + n, y asi siguiendo llegamos a que:
T(n) = T(0) + 1 + 2 + ... + (n-1) + n = T(0) + Sum(k = 1, n, k) = T(0) + n*(n+1)/2
T(n) = T(0) + (n*n^2)/2 = 1 + (n*n^2)/2--> Luego: T(n) = O(n^2)

3) T(n) = T(n − 1) + √n
T(n) = T(n-1) + √n, pero T(n-1) = T(n-2) + √(n-1), pero T(n-2) = T(n-3) + √(n-2), etc..
Con lo que conseguimos lo siguiente:
T(n) = T(0) + √1 + √2 + √3 + ... + √(n-2) + √(n-1) + √(n) 
T(n) = T(0) + Sum(k = 1, n, √k) = 1 + √(n)*√(n+1)/2  = 1 + √(n*(n+1))(2) = 1 + √(n^2 + n)/2
Usando propiedad de la desigualdad, sabemos que √(n^2 + n) <= √(n^2) + √(n), luego --> √(n^2 + n) <= n + √n
Volviendo: T(n) = 1 + √(n^2 + n)/2 <= 1 + √(n^2) + √(n) = 1 + n + √n --> O(n)
Luego T(n) pertenece a O(n)


4) T(n) = T(n − 1) + n^2
T(n)   = T(n-1) + n^2,      pero 
T(n-1) = T(n-2) + (n-1)^2,  pero
T(n-2) = T(n-3) + (n-2)^2
Conseguimos lo siguiente:
T(n) = T(0) + 1^2 + 2^2 + ... + (n-2)^2 + (n-1)^2 + n^2
Osea: T(n) = 1 + Sum(k=1, n, k^2) = 1 + n(n+1)(2n+1)/2 (formula de la suma de los 1ros n cuadrados)
T(n) tiene un max de orden n^3, luego --> O(n^3)

5) T(n) = 2T(n − 1)
T(n)   = 2T(n-1), pero
T(n-1) = 2T(n-2), pero
T(n-2) = 2T(n-3), etc
--> T(n) = 2*...*2*2*2T(1) = MUlt(k=1, n, 2) * T(1) = 2^n
Obtenemos complejidad O(2^n)

6) T(n) = T(n/2) + n 
Al fin recurrencia
a = 1; c = 2; f(n) = n
Caso 2 (general):
f(n) = O(n) --> Tita(n^log2(1) * log(n)^k) = Tita(log(n)^k), no es mas grande que f(n) = O(n)

Caso 3:
f(n) = O(n) --> Omega(n^log2(1)+e) = Omega(n^e), con e = 1 vemos que se cumple
Luego T(n) = Tita(f(n)) = Tita(n)

7) T(n) = T(n/2) + √n
a = 1; c = 2; f(n) = √n
Caso 2 (general):
f(n) = O(n) --> Tita(n^log2(1) * log(n)^k) = Tita(log(n)^k), no es mas grande que f(n) = O(√n)

Caso 3:
f(n) = O(√n) --> Omega(n^log2(1)+e) = Omega(n^e), con e = 1/2 llegamos a lo mismo:
Omega(n^1/2) = Omega(√n) = O(√n) = f(n), luego f(n) pertenece al Caso 3
Entonces: T(n) = Tita(f(n)) = Tita(√n)

8) T(n) = T(n/2) + n^2
a = 1; c = 2; f(n) = O(n^2)
Como (7) ya era caso 3, y éste es aún más grande, f(n) = O(n^2), apostamos al mismo caso
Omega(n^log2(1)+e) = Omega(n^e), con e = 2 obtenemos lo mismo --> Omega(n^2) = O(n^2) = f(n)
Luego --> T(n) = Tita(n^2)

9) T(n) = 2T(n − 4)
Salimos de recursion un poco:
T(n)   = 2T(n-4), pero
T(n-4) = 2T(n-8), pero
T(n-8) = 2T(n-12), 
T(n)   = 2^k * T(n-4k)  (generalizacion)
Peor caso? cuando n-4k = 0 <-> k = n/4
Entonces, reemplazando: T(n) = 2^(n/4) * T(0), luego la complejidad final es O(2^n)

Otra manera es desarrollar y ver que conseguimos que:
T(n) = Mult(k=1, n, 2)*T(0) donde mod(k, n) = 0
Pero como n->inf, sacarle 1/4 a cada n, es sacarle una constante,
Luego Mult(k=1, n, 2) donde mod(k, n) = 0 <Es Equivalente a> Mult(k=1, n, 2) = 2^n
Conseguimos entonces que T(n) = O(2^n)


10) T(n) = 2T(n/2) + log n
a = 2; c = 2; f(n) = log(n)
Apuesto caso 2:
f(n) = log(n) -> Tita(n^log2(2)) = Tita(1), le erré
Vamos con caso 2 generalizado:
f(n) = log(n) -> Tita(n^log2(2) * log(n)^k) = Tita(log(n)^k), con k = 1 obtenemos lo mismo
Luego f(n) pertenece al Caso 2 generalizado.
Entonces T(n) = Tita(n^log2(2) * log(n)^k+1) = Tita(log(n)^2)

11) T(n) = 3T(n/4)
a = 3; c = 4; f(n) = O(1) 
Caso 1? Veamos:
f(n) = O(n) --> O(n^log4(3)-e), si elijo e = log4(3) obtengo O(1) = f(n), luego f(n) pertenece a Caso 1
Entonces T(n) = Tita(n^log4(3))

12) T(n) = 3T(n/4) + n
a = 3; c = 4; f(n) = O(n)
Me tiro al caso 3:
f(n) = O(n) --> Omega(n^log4(3)+e), sea e = 1-log4(3), obtenemos Omega(n), luego f(n) pertenece al caso 3
Entonces: T(n) = Tita(f(n)) = Tita(n)

Intentar estimar la complejidad para cada ıtem directamente y luego calcularla utilizando el teorema maestro de ser posible. Para simplificar los c´alculos se puede asumir que n es potencia o m´ultiplo de 2 o de 4 seg´un sea conveniente.
*/

