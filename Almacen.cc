#include "Almacen.hh"
#ifndef NO_DIAGRAM
#include <list>
#endif

// Statics privados
void Almacen::esquema_desde_stream(istream &is,
                                   list<EsquemaSala> &esquema_salas) {
    EsquemaSala sala;
    is >> sala.id;
    esquema_salas.push_back(sala);
    if (sala.id == 0)
        // Árbol nulo
        return;
    // Subárbol derecho
    esquema_desde_stream(is, esquema_salas);
    // Subárbol izquierdo
    esquema_desde_stream(is, esquema_salas);
}

// Statics
void Almacen::leer(int num_salas, istream &is) {
    (void)num_salas; // Temporal fins implementació
    (void)is;
    this->num_salas_ = num_salas;
    list<EsquemaSala> esquema_salas;
    //esquema_desde_stream(cin, esquema_salas);
    //estructura_salas
}
