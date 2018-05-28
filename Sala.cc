/** @file
 * Implementación de Sala.
 */
#include "Sala.hh"
#ifndef NO_DIAGRAM
#    include <algorithm> // std::sort, std::min
#    include <cassert>
#endif

/*------------------+
 | Statics privados |
 +------------------*/

bool Sala::comp_IdProducto(const IdProducto &a, const IdProducto &b) {
    return (not a.empty()) and (b.empty() or (a < b));
}

/*---------------+
 | Constructores |
 +---------------*/

Sala::Sala() {}

Sala::Sala(int filas, int columnas) {
    assert(filas > 0 and columnas > 0);
    this->filas = filas;
    this->columnas = columnas;
    elementos = 0;
    estanteria = Estanteria(filas * columnas, "");
}

/*------------------+
 | Métodos públicos |
 +------------------*/
int Sala::poner_items(IdProducto producto, int cantidad) {
    assert(cantidad >= 0);

    // Determina el número de elementos a añadir
    int anadir = min(cantidad, filas * columnas - elementos);
    if (anadir == 0) return cantidad;
    inventario[producto] += anadir;
    elementos += anadir;
    cantidad -= anadir;

    Estanteria::iterator it;
    for (it = estanteria.begin(); anadir > 0; ++it) {
        assert(it != estanteria.end());
        if (it->empty()) {
            *it = producto;
            --anadir;
        }
    }
    return cantidad;
}

int Sala::quitar_items(IdProducto producto, int cantidad) {
    assert(cantidad >= 0);
    Inventario::iterator iit = inventario.find(producto);
    if (iit == inventario.end())
        return cantidad; // No hay ningún ítem en esta sala

    // Determina el número de elementos a quitar
    int quitar = min(cantidad, iit->second);
    cantidad -= quitar;
    iit->second -= quitar;
    elementos -= quitar;

    Estanteria::iterator eit;
    for (eit = estanteria.begin(); quitar > 0; ++eit) {
        assert(eit != estanteria.end());
        if (*eit == producto) {
            *eit = "";
            --quitar;
        }
    }

    if (iit->second == 0) {
        inventario.erase(iit); // Elimina las entradas sin productos
    }
    return cantidad;
}

void Sala::compactar() {
    if (elementos == filas * columnas)
        return; // Estantería llena, no es necesario compactar
    Estanteria::iterator it_done = estanteria.begin();
    Estanteria::iterator it_op = estanteria.begin();
    int procesados = 0;
    // Invariantes:
    //  - it_done <= it_op < end
    //  - [begin, it_done) no contiene elementos nulos (si begin != it_done)
    //  - [it_done, it_op) contiene solo elementos nulos (si it_done != it_op)
    //  - [it_op, end) contiene los elementos no procesados
    while (procesados < elementos) {
        assert(it_op != estanteria.end() and it_done != estanteria.end());
        if (not it_op->empty()) {
            assert(it_op == it_done or *it_done == "");
            swap(*it_op, *it_done);
            ++it_done;
            ++procesados;
        }
        ++it_op;
    }
}

void Sala::reorganizar() {
    sort(estanteria.begin(), estanteria.end(), comp_IdProducto);
}

bool Sala::redimensionar(int filas, int columnas) {
    assert(filas > 0 and columnas > 0);
    int nuevo_tamano = filas * columnas;
    if (nuevo_tamano < elementos)
        return false; // No cabrían los elementos actuales
    compactar();
    estanteria.resize(nuevo_tamano, "");
    this->filas = filas;
    this->columnas = columnas;
    return true;
}

/*-------------+
 | Consultores |
 +-------------*/

IdProducto Sala::consultar_pos(int f, int c) const {
    assert(0 < f and f <= filas);
    assert(0 < c and c <= columnas);
    int i = filas - f;
    int j = c - 1;
    IdProducto p = estanteria[i * columnas + j];
    if (p.empty()) return "NULL";
    return p;
}

/*-----+
 | I/O |
 +-----*/

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
