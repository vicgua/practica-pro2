#include "Almacen.hh"

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