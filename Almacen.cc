#include "Almacen.hh"
#ifndef NO_DIAGRAM
#    include <list>
#endif

// Statics privados
void Almacen::leer_estructura(istream &is, BinTree<int> &tree) {
    int n;
    is >> n;
    if (n == 0) {
        // Caso base: Árbol vacío
        tree = BinTree<int>();
        return;
    }
    BinTree<int> left, right;
    leer_estructura(is, left);
    leer_estructura(is, right);
    tree = BinTree<int>(n, left, right);
}

// Métodos públicos
int Almacen::num_salas() const {
    return this->salas.size();
}

void Almacen::leer(int num_salas, istream &is) {
    leer_estructura(is, this->estructura_salas);
    this->salas = vector<Sala>(num_salas);
    // Leer el tamaño de las estanterías
    for (int i = 0; i < num_salas; ++i) {
        int filas, columnas;
        is >> filas >> columnas;
        this->salas[i] = Sala(filas, columnas);
    }
}