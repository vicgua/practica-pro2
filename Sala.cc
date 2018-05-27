/** @file
 * Implementación de Sala.
 */
#include "Sala.hh"
#ifndef NO_DIAGRAM
#    include <algorithm> // std::sort
#    include <cassert>
#    include <utility> // std::move
#endif

/*------------------+
 | Statics privados |
 +------------------*/

bool Sala::comp_IdProducto(const IdProducto &a, const IdProducto &b) {
    return (not a.empty()) and (b.empty() or (a < b));
}

/*------------------+
 | Métodos privados |
 +------------------*/

void Sala::copia_compactada(Estanteria &dest) const {
    assert(dest.size() >= elementos);
    if (elementos == 0) return;
    Estanteria::const_iterator it_orig = estanteria.begin();
    Estanteria::iterator it_dest = dest.begin();
    int procesados = 0;
    // Invariantes:
    //  - it_orig < estanteria.end; it_dest < dest.end
    //  - [dest.begin, it_dest) no contiene elementos nulos.
    //  - [it_dest, dest.end) contiene solo elementos nulos.
    while (procesados < elementos) {
        assert(it_orig != estanteria.end() and it_dest != dest.end());
        if (not it_orig->empty()) {
            *it_dest = *it_orig;
            ++it_dest;
            ++procesados;
        }
        ++it_orig;
    }
}

/*---------------+
 | Constructores |
 +---------------*/

Sala::Sala() {}

Sala::Sala(int filas, int columnas) {
    assert(filas > 0 and columnas > 0);
    this->filas = filas;
    this->columnas = columnas;
    this->elementos = 0;
    estanteria = Estanteria(filas * columnas, "");
}

/*------------------+
 | Métodos públicos |
 +------------------*/
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
    if (anadidos > 0) inventario[producto] += anadidos;
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
    int nuevo_tamano = filas * columnas;
    if (nuevo_tamano < elementos)
        return false; // No cabrían los elementos actuales
    if (nuevo_tamano <= estanteria.capacity()) {
        // La estantería puede ampliarse / reducirse sin reubicar la estantería
        compactar();
        estanteria.resize(nuevo_tamano, "");
    } else {
        // Compactamos y redimensionamos a la vez, evitando la reubicación de la
        // estantería
        Estanteria nueva_estanteria(nuevo_tamano, "");
        copia_compactada(nueva_estanteria);
        estanteria = move(nueva_estanteria);
    }
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
