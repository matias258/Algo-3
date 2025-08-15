import itertools
import random

"""
2.
a) Queremos saber cuantos cuadrados habria que generar para encontrar todos los cuadrados magicos para brute force.

Un cuadrado C magico cumple 5 propiedades:
Sea x = Sum(Fila[0]), entonces:
- forall i indice de C, Sum(C[i]) = x
- forall j indice de C, Sum(C[:][j]) = x
- forall k indice de C, Sum(C[k][k]) = x
- forall l indice de C, SUm(C[l][n-l]) = x
- No tiene valores repetidos. Osea que están todos los valores del 1 al n.

Generemos el algoritmo para brute force:
"""
def magic_square_bf(n, square) -> bool:
    target = sum(square[0])
    # Check all rows
    for row in square:
        if sum(row) != target:
            return False
    # Check all columns
    for col in range(n):
        if sum(square[row][col] for row in range(n)) != target:
            return False
    # Check main diagonal
    if sum(square[i][i] for i in range(n)) != target:
        return False
    # Check anti-diagonal
    if sum(square[i][n - i - 1] for i in range(n)) != target:
        return False
    return True

def permutations(n):
    nums = list(range(1, n*n + 1))
    return itertools.permutations(nums, n*n)

def iteration (n) -> int:
    combinations = 0
    for square in permutations(n):
        if (magic_square_bf(n)):
            combinations += 1
    return combinations

"""
# Esto corre todas las permutaciones de una matriz nxn 
if __name__ == "__main__":
    n = int(input("Ingrese el tamaño del cuadrado mágico: "))
    count = 0
    for perm in permutations(n):
        # Convert flat permutation to 2D square
        square = [list(perm[i*n:(i+1)*n]) for i in range(n)]
        count += 1
        print(f"Matriz #{count}:")
        for row in square:
            print(row)
        print()
"""

if __name__ == "__main__":
    n = int(input("Ingrese el tamaño del cuadrado mágico: "))
    cantidad = 0
    for perm in permutations(n):
        # Convertir perm en una matriz 2D antes de pasarla a magic_square_bf
        square = [list(perm[i*n:(i+1)*n]) for i in range(n)]
        if magic_square_bf(n, square):
            cantidad += 1
    print(cantidad)

"""
b) Intentemos por backtracking.

def cuadrado_magico(i, j, S, P):
     
"""