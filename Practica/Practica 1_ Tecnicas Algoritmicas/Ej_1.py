# Ej 1 

"""
a. 
Para C = {6, 12, 6} y k = 12,
el conjunto de soluciones candidatas es:
{{6}, {12} (12 o 6 + 6), {6 + 12}} (Todas las combinaciones posibles) (Partes de C)

b. El conjunto de soluciones validas es:
{6 + 6 o 12} (Son las = k)

c. El conjunto de soluciones parciales es:
{6, 12 (6+6 o 12)} (Son todas las que son <= k)

d. Arbol de decisiones:
Árbol de decisiones para C = {6, 12, 6} y k = 12

Raíz (suma = 0, conjunto = {})
├── Incluir 6 (primer elemento)
│   ├── Incluir 12
│   │   ├── Incluir 6 (último)
│   │   │   └── suma = 24, conjunto = {6, 12, 6} (descartado)
│   │   └── No incluir 6
│   │       └── suma = 18, conjunto = {6, 12} (descartado)
│   └── No incluir 12
│       ├── Incluir 6 (último)
│       │   └── suma = 12, conjunto = {6, 6} (válido)
│       └── No incluir 6
│           └── suma = 6, conjunto = {6} (parcial)
├── No incluir 6 (primer elemento)
│   ├── Incluir 12
│   │   ├── Incluir 6 (último)
│   │   │   └── suma = 18, conjunto = {12, 6} (descartado)
│   │   └── No incluir 6
│   │       └── suma = 12, conjunto = {12} (válido)
│   └── No incluir 12
│       ├── Incluir 6 (último)
│       │   └── suma = 6, conjunto = {6} (parcial)
│       └── No incluir 6
│           └── suma = 0, conjunto = {} (parcial)

f.
subset_sum(C, i, j):
    Si i = 0 return j = 0
    Si no, return subset_sum(C, i-1, j) o       (1)
           return subset_sum(C, i-1, j-C[i])    (2)

Vimos en e) que (1) y (2) son True <-> Existe un conjunto válido.
Pero que pasaria si (1) y (2) no son soluciones?
Entonces en la siguiente iteración tendríamos estos 2 codigos:

subset_sum(C, i-1, j):
    Si i = 0 return j = 0
    Si no, return subset_sum(C, i-2, j) o               (1)
           return subset_sum(C, i-2, j-C[i])            (2a)  

subset_sum(C, i-1, j-C[i]):
    Si i = 0 return j = 0
    Si no, return subset_sum(C, i-2, j) o               (1)
           return subset_sum(C, i-2, j-C[i]-C[i-1])     (2b) 

(1) seguira siendo Falso, pues su conjunto esta contenido en el (1) inicial
(2a) = (2) Por lo que tambien sigue siendo falso en nuestra premisa
(2b) Suponiendo que j-C[i]-C[i-1] > 0, como (2b) esta contenido en (2), el abanico de soluciones sigue dando Falso, pues nuestro (2) es falso por premisa.

Luego subset_sum solo puede ser True si se cumple lo mismo que ss(C, k) en el ej e)   

"""
# g. C = {6, 12, 6}, j = 12, i = 3 (C.size())
# Ejemplo de ejecución paso a paso de subset_sum(C, i, j)
# Para C = [6, 12, 6], j = 12, i = 3

# Llamada inicial:
# subset_sum([6, 12, 6], 3, 12)
# i != 0, entonces:
#   subset_sum([6, 12, 6], 2, 12)   # (no tomo el último 6)
#   o
#   subset_sum([6, 12, 6], 2, 6)    # (tomo el último 6, 12-6=6)

# Rama 1: subset_sum([6, 12, 6], 2, 12)
#   i != 0:
#       subset_sum([6, 12, 6], 1, 12)   # (no tomo el 12)
#       o
#       subset_sum([6, 12, 6], 1, 0)    # (tomo el 12, 12-12=0)

#   Rama 1.1: subset_sum([6, 12, 6], 1, 12)
#       i != 0:
#           subset_sum([6, 12, 6], 0, 12)   # (no tomo el primer 6)
#           o
#           subset_sum([6, 12, 6], 0, 6)    # (tomo el primer 6, 12-6=6)
#       Ambos retornan False (no hay subconjunto con suma 12 o 6 usando 0 elementos)

#   Rama 1.2: subset_sum([6, 12, 6], 1, 0)
#       i != 0:
#           subset_sum([6, 12, 6], 0, 0)    # (no tomo el primer 6)
#           o
#           subset_sum([6, 12, 6], 0, -6)   # (tomo el primer 6, 0-6=-6)
#       subset_sum([6, 12, 6], 0, 0) retorna True (caso base: suma 0 con 0 elementos)

#   Por lo tanto, Rama 1 retorna True.

# Rama 2: subset_sum([6, 12, 6], 2, 6)
#   i != 0:
#       subset_sum([6, 12, 6], 1, 6)    # (no tomo el 12)
#       o
#       subset_sum([6, 12, 6], 1, -6)   # (tomo el 12, 6-12=-6)

#   Rama 2.1: subset_sum([6, 12, 6], 1, 6)
#       i != 0:
#           subset_sum([6, 12, 6], 0, 6)    # (no tomo el primer 6)
#           o
#           subset_sum([6, 12, 6], 0, 0)    # (tomo el primer 6, 6-6=0)
#       subset_sum([6, 12, 6], 0, 0) retorna True

#   Por lo tanto, Rama 2 retorna True.

# Como al menos una rama retorna True, subset_sum([6, 12, 6], 3, 12) retorna True.

# Árbol de ejecución de subset_sum([6, 12, 6], 3, 12) ####
# Cada nodo muestra: subset_sum(C, i, j)
# Rama izquierda: NO tomo el elemento actual
# Rama derecha:   SÍ tomo el elemento actual
"""
subset_sum([6, 12, 6], 3, 12)
├── subset_sum([6, 12, 6], 2, 12)        # No tomo el último 6
│   ├── subset_sum([6, 12, 6], 1, 12)    # No tomo el 12
│   │   ├── subset_sum([6, 12, 6], 0, 12)    # No tomo el primer 6 → False
│   │   └── subset_sum([6, 12, 6], 0, 6)     # Tomo el primer 6 → False
│   └── subset_sum([6, 12, 6], 1, 0)     # Tomo el 12
│       ├── subset_sum([6, 12, 6], 0, 0)     # No tomo el primer 6 → True
│       └── subset_sum([6, 12, 6], 0, -6)    # Tomo el primer 6 → False
├── subset_sum([6, 12, 6], 2, 6)         # Tomo el último 6
│   ├── subset_sum([6, 12, 6], 1, 6)     # No tomo el 12
│   │   ├── subset_sum([6, 12, 6], 0, 6)     # No tomo el primer 6 → False
│   │   └── subset_sum([6, 12, 6], 0, 0)     # Tomo el primer 6 → True
│   └── subset_sum([6, 12, 6], 1, -6)    # Tomo el 12
│       ├── subset_sum([6, 12, 6], 0, -6)    # No tomo el primer 6 → False
│       └── subset_sum([6, 12, 6], 0, -12)   # Tomo el primer 6 → False
"""
# Las ramas que llegan a subset_sum(..., 0, 0) retornan True (solución encontrada).
# Si alguna rama retorna True, el resultado final es True.


"""
h)
subset_sum(C, i, j):
    Si j < 0 then return false
    Si i = 0 then return j = 0
    else return subset_sum(C, i-1, j) v subset_sum(C, i-1, j-C[i])

"""