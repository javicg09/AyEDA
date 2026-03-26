-ts 10 → tableSize = 10
El número de posiciones de la tabla hash. En este caso 10 casillas.
-fd 1 → función de dispersión:

1 = Módulo (k % tableSize)
2 = Suma de dígitos
3 = Pseudoaleatoria

-hash close/open → tipo de dispersión:

close = dispersión cerrada, usa StaticSequence con exploración
open = dispersión abierta, usa DynamicSequence sin límite

-bs 3 → blockSize = 3 (solo dispersión cerrada)
Cuántos elementos caben en cada posición de la tabla.
-fe 1 → función de exploración (solo dispersión cerrada):

1 = Lineal (i)
2 = Cuadrática (i²)
3 = Doble dispersión (f(k) * i)
4 = Redispersión (f⁽ⁱ⁾(k))