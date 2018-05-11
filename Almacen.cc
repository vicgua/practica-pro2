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

//-----------------
// Métodos públicos
//-----------------

Sala &Almacen::sala(IdSala id_sala) {
    assert(0 < id_sala and id_sala <= salas.size());
    return salas[id_sala - 1];
}

const Sala &Almacen::sala(IdSala id_sala) const {
    return salas[id_sala - 1];
}

//--------------
// Constructores
//--------------

Almacen::Almacen() {} // Constructor por defecto

//-----------------
// Métodos públicos
//-----------------

bool Almacen::poner_prod(IdProducto id_producto) {
    Inventario::iterator it = productos.find(id_producto);
    if (it != productos.end()) return false;
    productos.insert({id_producto, 0});
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

//----
// I/O
//----

void Almacen::leer(int num_salas, istream &is) {
    leer_estructura(is, this->estructura_salas);
    salas = vector<Sala>(num_salas);
    // Leer el tamaño de las estanterías
    for (int i = 0; i < num_salas; ++i) {
        int filas, columnas;
        is >> filas >> columnas;
        salas[i] = Sala(filas, columnas);
    }
}

void Almacen::escribir(IdSala id_sala, ostream &os) const {
    sala(id_sala).escribir(os);
}

//--------------------
// Operaciones de sala
//--------------------

int Almacen::poner_items(IdSala id_sala, IdProducto id_producto, int cantidad) {
    Inventario::iterator it = productos.find(id_producto);
    if (it == productos.end()) return -1; // El producto no existe
    int sobran = sala(id_sala).poner_items(id_producto, cantidad);
    it->second += cantidad - sobran;
    return sobran;
}

int Almacen::quitar_items(IdSala id_sala, IdProducto id_producto,
                          int cantidad) {
    Inventario::iterator it = productos.find(id_producto);
    if (it == productos.end()) return -1; // El producto no existe
    int faltan = sala(id_sala).quitar_items(id_producto, cantidad);
    it->second -= cantidad - faltan;
    return faltan;
}

void Almacen::compactar(IdSala id_sala) {
    sala(id_sala).compactar();
}

void Almacen::reorganizar(IdSala id_sala) {
    sala(id_sala).reorganizar();
}

bool Almacen::redimensionar(IdSala id_sala, int filas, int columnas) {
    return sala(id_sala).redimensionar(filas, columnas);
}

IdProducto Almacen::consultar_pos(IdSala id_sala, int f, int c) const {
    return sala(id_sala).consultar_pos(f, c);
}
