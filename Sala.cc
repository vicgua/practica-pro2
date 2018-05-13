#include "Sala.hh"
#ifndef NO_DIAGRAM
#    include <algorithm> // std::sort
#    include <cassert>
#    include <utility> // std::move
#endif

//-----------------
// Statics privados
//-----------------

bool Sala::comp_IdProducto(const IdProducto &a, const IdProducto &b) {
    if (a.empty()) return false;
    if (b.empty()) return true;
    return a < b;
}

//--------------
// Constructores
//--------------

Sala::Sala() {}

Sala::Sala(int filas, int columnas) {
    assert(filas > 0 and columnas > 0);
    this->filas = filas;
    this->columnas = columnas;
    this->elementos = 0;
    estanteria = Estanteria(filas * columnas, "");
}

//-----------------
// Métodos públicos
//-----------------
int Sala::poner_items(IdProducto producto, int cantidad) {
    if (elementos == filas * columnas)
        return cantidad; // No cabe ningún ítem en esta sala
    int anadidos = 0;
    for (int i = 0; cantidad > 0 and i < estanteria.size(); ++i) {
        if (estanteria[i].empty()) {
            estanteria[i] = producto;
            --cantidad;
            ++anadidos;
            ++elementos;
        }
    }
    if (anadidos > 0) {
        inventario[producto] += anadidos;
    }
    return cantidad;
}

int Sala::quitar_items(IdProducto producto, int cantidad) {
    Inventario::iterator it = inventario.find(producto);
    if (it == inventario.end())
        return cantidad; // No hay ningún ítem en esta sala
    int quitados = 0;
    for (int i = 0; cantidad > 0 and i < estanteria.size(); ++i) {
        if (estanteria[i] == producto) {
            estanteria[i] = "";
            --cantidad;
            ++quitados;
            --elementos;
        }
    }
    it->second -= quitados;
    if (it->second == 0) {
        inventario.erase(it); // Elimina las entradas sin productos
    }
    return cantidad;
}

void Sala::compactar() {
    int i_done = 0;
    int i_op = 0;
    while (i_op < estanteria.size()) {
        if (not estanteria[i_op].empty()) {
            estanteria[i_done] = estanteria[i_op];
            ++i_done;
        }
        ++i_op;
    }
    while (i_done < estanteria.size()) {
        estanteria[i_done] = "";
        ++i_done;
    }
}

void Sala::reorganizar() {
    sort(estanteria.begin(), estanteria.end(), comp_IdProducto);
}

bool Sala::redimensionar(int filas, int columnas) {
    int nuevo_tamano = filas * columnas;
    if (nuevo_tamano < elementos) return false;
    Estanteria nueva_est(nuevo_tamano, "");
    int ni = 0;
    for (int i = 0; i < estanteria.size(); ++i) {
        if (not estanteria[i].empty()) {
            nueva_est[ni] = estanteria[i];
            ++ni;
        }
    }
    estanteria = move(nueva_est);
    this->filas = filas;
    this->columnas = columnas;
    return true;
}

//------------
// Consultores
//------------

IdProducto Sala::consultar_pos(int f, int c) const {
    assert(0 < f and f <= filas);
    assert(0 < c and c <= columnas);
    int i = filas - f;
    int j = c - 1;
    IdProducto p = estanteria[i * columnas + j];
    if (p.empty()) return "NULL";
    return p;
}

//----
// I/O
//----

void Sala::escribir(ostream &os) const {
    for (int i = filas - 1; i >= 0; --i) {
        os << ' ';
        for (int j = 0; j < columnas; ++j) {
            IdProducto id_producto = estanteria[i * columnas + j];
            if (id_producto.empty()) {
                os << " NULL";
            } else {
                os << ' ' << id_producto;
            }
        }
        os << endl;
    }
    Inventario::const_iterator it = inventario.begin();
    os << "  " << elementos << endl;
    while (it != inventario.end()) {
        os << "  " << it->first << ' ' << it->second << endl;
        ++it;
    }
}
