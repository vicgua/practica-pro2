#include "Sala.hh"

//-----------------
// Métodos privados
//-----------------

int Sala::columnas() const {
    if (filas == 0) return 0;
    return estanteria[0].size();
}

//--------------
// Constructores
//--------------

Sala::Sala() {}

Sala::Sala(int filas, int columnas) {
    this->filas = filas;
    this->columnas = columnas;
    estanteria = Estanteria(filas, vector<IdProducto>(columnas, ""));
}

//-----------------
// Métodos públicos
//-----------------
int Sala::poner_items(IdProducto producto, int cantidad) {
    for (int i = 0; i < filas and cantidad > 0; ++i) {
        for (int j = 0; j < columnas and cantidad > 0; ++j) {
            if (estanteria[i][j].empty()) {
                estanteria[i][j] = producto;
                --cantidad;
                ++elementos;
            }
        }
    }
    return cantidad;
}

int Sala::quitar_items(IdProducto producto, int cantidad) {
    for (int i = 0; i < filas and cantidad > 0; ++i) {
        for (int j = 0; j < columnas and cantidad > 0; ++j) {
            if (estanteria[i][j] == producto) {
                estanteria[i][j] = "";
                --cantidad;
                --elementos;
            }
        }
    }
    return cantidad;
}

void Sala::compactar() {
    int i_done = 0, j_done = 0;
    int i_op = 0, j_op = 0;
    while (i_op < filas) {
        while (j_op < columnas) {
            if (estanteria[i_op][j_op].empty()) {
                // ++O
            } else {
                // ++D
                // ++O
            }
            if (not estanteria[i_op][j_op].empty()) {
                estanteria[i_done][j_done] = estanteria[i_op][j_op];
                ++j_done;
                if (j_done == columnas) {
                    j_done = 0;
                    ++i_done;
                }
            }
            ++j_op;
        }
        j_op = 0;
        ++i_op;
    }
    while (i_done < filas) {
        while (j_done < columnas) {
            estanteria[i_done][j_done] = "";
            ++j_done;
        }
        j_done = 0;
        ++i_done;
    }
}



//------------
// Consultores
//------------

IdProducto Sala::consultar_pos(int f, int c) const {
    IdProducto p = estanteria[f-1][c-1];
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
