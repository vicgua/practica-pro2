#include "Almacen.hh"
#ifndef NO_DIAGRAM
#    include <list>
#endif

//-----------------
// Statics privados
//-----------------

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

//--------------
// Constructores
//--------------

Almacen::Almacen() {} // Constructor por defecto

//-----------------
// Métodos públicos
//-----------------

bool Almacen::poner_prod(IdProducto id_producto) {
    if (existe_producto(id_producto)) return false;
    productos[id_producto] = 0;
    return true;
}

bool Almacen::quitar_prod(IdProducto id_producto) {
    map<IdProducto, int>::iterator it;
    it = productos.find(id_producto);
    if (it == productos.end()) return false;
    if (it->second > 0) return false;
    productos.erase(it);
    return true;
}

int Almacen::distribuir(IdProducto id_producto, int cantidad) {
    /// @todo Implementar Almacen::distribuir
    (void) id_producto;
    (void) cantidad;
    return -1;
}

//------------
// Consultores
//------------

int Almacen::num_salas() const {
    return this->salas.size();
}

int Almacen::consultar_prod(IdProducto id_producto) const {
    map<IdProducto, int>::const_iterator it;
    it = productos.find(id_producto);
    if (it == productos.end()) return -1;
    return it->second;
}

const map<IdProducto, int> &Almacen::inventario() const {
    return productos;
}

bool Almacen::existe_producto(IdProducto id_producto) const {
    return productos.count(id_producto) > 0;
    // (map::count sólo devuelve 0 si está o 1 si no)
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

//--------------------
// Operaciones de sala
//--------------------

int Almacen::poner_items(int id_sala, IdProducto id_producto, int cantidad) {
    if (not existe_producto(id_producto)) return -1;
    return sala(id_sala).poner_items(id_producto, cantidad);
}

int Almacen::quitar_items(int id_sala, IdProducto id_producto, int cantidad) {
    if (not existe_producto(id_producto)) return -1;
    return sala(id_sala).quitar_items(id_producto, cantidad);
}

void Almacen::compactar(int id_sala) {
    sala(id_sala).compactar();
}

void Almacen::reorganizar(int id_sala) {
    sala(id_sala).reorganizar();
}

bool Almacen::redimensionar(int id_sala, int filas, int columnas) {
    return sala(id_sala).redimensionar(filas, columnas);
}

IdProducto Almacen::consultar_pos(int id_sala, int f, int c) const {
    return sala(id_sala).consultar_pos(f, c);
}