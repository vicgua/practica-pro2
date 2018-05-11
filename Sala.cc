#include "Sala.hh"
#ifndef NO_DIAGRAM
#    include <algorithm>
#endif

//-----------------
// Métodos privados
//-----------------

int offset_pos(int i, int j) {
    return i * columnas + j;
}

//--------------
// Constructores
//--------------

Sala::Sala() {}

Sala::Sala(int filas, int columnas) {
    this->filas = filas;
    this->columnas = columnas;
    estanteria = Estanteria(filas * columnas, "");
}

//-----------------
// Métodos públicos
//-----------------
int Sala::poner_items(IdProducto producto, int cantidad) {
    int anadidos = 0;
    for (int i = 0; cantidad > 0 and i < estanteria.size(); ++i) {
        if (estanteria[i].empty()) {
            estanteria[i] = producto;
            --cantidad;
            ++anadidos;
            ++elementos;
        }
    }
    inventario[producto] += anadidos;
    return cantidad;
}

int Sala::quitar_items(IdProducto producto, int cantidad) {
    int quitados = 0;
    for (int i = 0; cantidad > 0 and i < estanteria.size(); ++i) {
        if (estanteria[i] == producto) {
            estanteria[i] = "";
            --cantidad;
            ++quitados;
            --elementos;
        }
    }
    Inventario::iterator it = inventario.find(producto);
    it->second -= quitados;
    if (it->second == 0) {
        inventario.erase(it); // Elimina las entradas sin productos
    }
    return cantidad;
}

void Sala::compactar() {
    int i_done = 0;
    int i_op = 0;
    while (i_op < vector.size()) {
        if (not estanteria[i_op].empty()) {
            estanteria[i_done] = estanteria[i_op];
            ++i_done;
        }
        ++i_op;
    }
}


//------------
// Consultores
//------------

IdProducto Sala::consultar_pos(int f, int c) const {
    IdProducto p = estanteria[offset_pos(f - 1, c - 1)];
    if (p.empty())
        return "NULL";
    return p;
}



//----
// I/O
//----

void escribir(ostream &os) const {
    for (int i = filas - 1; i >= 0; --i) {
        os << estanteria[i][0];
        for (int j = 1; j < columnas; ++j) {
            os << ' ' << estanteria[i][j];
        }
        os << endl;
    }
}
