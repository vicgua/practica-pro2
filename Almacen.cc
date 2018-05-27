/** @file
 * Implementación de Almacen.
 */
#include "Almacen.hh"
#ifndef NO_DIAGRAM
#    include <list>
#endif

/*------------------+
 | Statics privados |
 +------------------*/

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

/*------------------+
 | Métodos privados |
 +------------------*/

Sala &Almacen::sala(IdSala id_sala) {
    assert(0 < id_sala and id_sala <= salas.size());
    return salas[id_sala - 1];
}

const Sala &Almacen::sala(IdSala id_sala) const {
    assert(0 < id_sala and id_sala <= salas.size());
    return salas[id_sala - 1];
}

int Almacen::i_distribuir(const BinTree<IdSala> &tree, IdProducto id_producto,
                          int cantidad) {
    if (tree.empty()) return cantidad; // Caso base
    int sobran = sala(tree.value()).poner_items(id_producto, cantidad);
    if (sobran == 0) return 0;
    int cantidad_right = sobran / 2;
    int cantidad_left = sobran - cantidad_right;
    int sobran_left = i_distribuir(tree.left(), id_producto, cantidad_left);
    int sobran_right = i_distribuir(tree.right(), id_producto, cantidad_right);
    return sobran_left + sobran_right;
}

/*---------------+
 | Constructores |
 +---------------*/

Almacen::Almacen() {} // Constructor por defecto

/*------------------+
 | Métodos públicos |
 +------------------*/

bool Almacen::poner_prod(IdProducto id_producto) {
    return productos.insert({id_producto, 0}).second;
    // Intenta insertar el producto (con 0 elementos).
    // Si no existe, Inventario::insert lo crea y retorna un pair cuyo segundo
    // elemento es true. Si ya existe, es false, y no modifica el inventario.
}

bool Almacen::quitar_prod(IdProducto id_producto) {
    Inventario::iterator it;
    it = productos.find(id_producto);
    if (it == productos.end()) return false;
    if (it->second > 0) return false;
    productos.erase(it);
    return true;
}

int Almacen::distribuir(IdProducto id_producto, int cantidad) {
    Inventario::iterator it = productos.find(id_producto);
    if (it == productos.end()) return -1; // El producto no existe
    int sobran = i_distribuir(estructura_salas, id_producto, cantidad);
    it->second += cantidad - sobran;
    return sobran;
}

/*-------------+
 | Consultores |
 +-------------*/

int Almacen::num_salas() const {
    return this->salas.size();
}

int Almacen::consultar_prod(IdProducto id_producto) const {
    Inventario::const_iterator it;
    it = productos.find(id_producto);
    if (it == productos.end()) return -1;
    return it->second;
}

/*-----+
 | I/O |
 +-----*/

void Almacen::inventario(ostream &os) const {
    Inventario::const_iterator it;
    for (it = productos.begin(); it != productos.end(); ++it) {
        os << "  " << it->first << " " << it->second << endl;
    }
}

void Almacen::leer(int num_salas, istream &is) {
    leer_estructura(is, estructura_salas);
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

/*---------------------+
 | Operaciones de sala |
 +---------------------*/

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
