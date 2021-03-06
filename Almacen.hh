/** @file
 * Archivo que define Almacen.
 */
#ifndef ALMACEN_HH
#define ALMACEN_HH

#include "Sala.hh"
#include "aux.hh"
#ifndef NO_DIAGRAM
#    include "BinTree.hh"
#    include <istream>
#    include <ostream>
#endif // NO_DIAGRAM

using namespace std;

/** Representación de un almacén. */
class Almacen {
private:
    /** Árbol con la estructura de las salas.
     *
     * Cada nodo contiene el identificador de la sala, y conectado a este, las
     * tres salas a las que se puede acceder (o una, si es una hoja).
     */
    BinTree<IdSala> estructura_salas;
    /// Vector que contiene todas las salas, con la sala n en salas[n-1].
    vector<Sala> salas;
    /** Inventario de todos los productos en el almacén.
     *
     * Un producto puede tener 0 ítems cuando ha sido dado de alta, pero no
     * tiene ningún ítem en ninguna sala.
     */
    Inventario productos;

    /** Leer la estructura del árbol de salas en preorden.
     *
     * @param is
     * Stream desde el que se leerá el árbol.
     *
     * @param[out] tree
     * Árbol de identificadores de salas.
     *
     * @pre
     * Hay un árbol válido en @c is.
     *
     * @post
     * Se han leído elementos de @c is hasta formar un árbol (en preorden, con 0
     * indicando el árbol nulo), que se encuentra en @c tree.
     *
     * @cost
     * Lineal respecto al número de nodos del árbol.
     */
    static void leer_estructura(istream &is, BinTree<IdSala> &tree);

    /** Obtener una sala.
     *
     * @param id_sala
     * Identificador de la sala.
     *
     * @returns
     * La sala con identificador id_sala.
     *
     * @pre
     * 1 <= @c id_sala <= número de salas
     *
     * @cost
     * Constante
     */
    Sala &sala(IdSala id_sala);

    /** Igual que sala(IdSala), pero devuelve una referencia constante. */
    const Sala &sala(IdSala id_sala) const;

    /** Función de inmersión de distribuir().
     *
     * @param tree
     * Árbol que se usará para determinar en qué sala se pondrán los ítems.
     * Este árbol contendrá los identificadores de sala. El árbol puede estar
     * vacío, en cuyo caso no se pondrá ningún ítem.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @param cantidad
     * Cantidad de ítems del producto
     *
     * @returns
     * Número de ítems que no se han podido almacenar.
     *
     * @pre
     * @c id_producto existe (es decir, está en el inventario).
     *
     * @post
     * Los ítems han sido distribuidos por el almacén, según la política de
     * distribución.
     *
     * @cost
     * Lineal respecto a @c cantidad
     */
    int i_distribuir(const BinTree<IdSala> &tree, IdProducto id_producto,
                     int cantidad);

public:
    /** Crea un almacén vacío.
     *
     * @cost
     * Constante
     */
    Almacen();

    /** Añadir un producto.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @retval true
     * El @c id_producto producto ha sido añadido.
     *
     * @retval false
     * El producto @c id_producto ya existe. El objeto no ha sido modificado.
     *
     * @post
     * Si el producto @c id_producto no existía, ha sido añadido con 0 unidades.
     *
     * @cost
     * Logarítmico en la cantidad de productos ya existentes
     */
    bool poner_prod(IdProducto id_producto);

    /** Quitar un producto.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @retval true
     * El producto @c id_producto ha sido eliminado.
     *
     * @retval false
     * El producto @c id_producto no existe o tiene alguna unidad. El objeto no
     * ha sido modificado.
     *
     * @cost
     * Logarítmico en la cantidad de productos
     *
     * @post
     * Si el producto @c id_producto existía y tenía 0 unidades, ha sido
     * eliminado.
     */
    bool quitar_prod(IdProducto id_producto);

    /** Distribuye los productos por el almacén.
     *
     * La distribución ocurre de la siguiente forma, comenzando desde la primera
     * sala:
     * 1. Se intentan almacenar todos los productos posibles en la sala.
     * 2. Si no hay suficiente espacio, los n restantes se distribuyen
     *      entre el resto de salas:
     *      - Si hay dos salas a continuación,
     *          @f$\left \lceil{n / 2} \right \rceil@f$ se distribuyen a la
     *          sala derecha, y los
     *          @f$\left \lfloor{n / 2} \right \rfloor@f$ restantes, a la
     *          izquierda. Ir a 1.
     *      - Si hay una sola sala, se distribuyen a ésta.
     *      - Si no hay ninguna sala a continuación, no se pueden almacenar.
     *          @em return += n.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @param cantidad
     * Cantidad de ítems del producto a distribuir.
     *
     * @returns
     * Número de ítems del producto @c id_producto que no se han podido
     * almacenar.
     *
     * @retval -1
     * El producto @c id_producto no existe. El almacén no ha sido modificado.
     *
     * @post
     * Si el producto @c id_producto existe, los ítems han sido distribuidos por
     * el almacén, según la política de distribución; si @e return > 0 &rArr; el
     * almacén está lleno.
     *
     * @cost
     * Lineal respecto a @c cantidad
     */
    int distribuir(IdProducto id_producto, int cantidad);

    //------------
    // Consultores
    //------------

    /** Número de salas.
     *
     * @invariant
     * @c num_salas > 0; las salas son consecutivas desde 1 hasta el total de
     * salas (es decir, que con n salas, estas tienen identificadores {1, 2,
     * ..., n-1, n})
     *
     * @cost
     * Constante
     */
    int num_salas() const;

    /** Consultar el número de ítems que tiene un producto.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @returns
     * Número de ítems que tiene el producto @c id_producto.
     *
     * @retval -1
     * El producto @c id_producto no existe.
     *
     * @cost
     * Logarítmico en el número de productos
     */
    int consultar_prod(IdProducto id_producto) const;

    /** Inventario de los productos.
     * @param os
     * Stream de salida.
     *
     * @post
     * El contenido del inventario se ha escrito por orden alfabético en @c os
     *
     * @cost
     * Lineal en el número de productos
     */
    void inventario(ostream &os) const;

    /** Lee las salas por un stream.
     *
     * @param is
     * Stream para leer.
     *
     * @pre
     * @c is contiene el número de salas (@em n), un árbol en preorden y las
     * dimensiones de las salas (&rArr; @c is no está vacío); el árbol en @c is
     * tiene @em n nodos, numerados de 1 a @em n.
     *
     * @post
     * El objeto ahora tiene @em n salas con la estructura y dimensiones
     * dadas en @c is.
     *
     * @cost
     * Lineal en el número de salas
     */
    void leer(istream &is);

    //--------------------
    // Operaciones de sala
    //--------------------

    /** Poner un ítem de un producto en una sala.
     *
     * @param id_sala
     * Identificador de la sala.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @param cantidad
     * Cantidad de ítems del producto a añadir como máximo.
     *
     * @returns
     * Cantidad de ítems que no se han podido añadir por falta de espacio.
     *
     * @retval -1
     * El producto @c id_producto no existe.
     *
     * @pre
     * @c cantidad >= 0; 0 < id_sala <= @ref num_salas.
     *
     * @post
     * Si el producto existe, se han añadido
     * min(`cantidad`, espacio libre en la sala) ítems a la sala;
     * si @e return > 0 &rArr; sala llena. Si no existe, no se ha modificado el
     * objeto.
     *
     * @cost
     * Lineal en la cantidad de ítems añadidos, logarítmico en la cantidad de
     * productos del almacén
     *
     * @see
     * Sala::poner_items
     */
    int poner_items(IdSala id_sala, IdProducto id_producto, int cantidad);

    /** Quitar un ítem de un producto de una sala.
     *
     * @param id_sala
     * Identificador de la sala
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @param cantidad
     * Cantidad de ítems del producto a quitar como máximo.
     *
     * @returns
     * Cantidad de ítems que no se han podido quitar porque no habían
     * suficientes en la sala.
     *
     * @retval -1
     * El producto @c id_producto no existe.
     *
     * @pre
     * @c cantidad >= 0; 0 < @c id_sala <= @ref num_salas.
     *
     * @post
     * Si el producto existe, se han quitado
     * min(`cantidad`, ítems del producto en la sala) ítems de la sala;
     * si @e return > 0 &rArr; No quedan ítems en la sala. Si no existe, no se
     * ha modificado el objeto.
     *
     * @cost
     * Lineal en la cantidad de ítems añadidos, logarítmico en la cantidad de
     * productos del almacén
     *
     * @see
     * Sala::quitar_items
     */
    int quitar_items(IdSala id_sala, IdProducto id_producto, int cantidad);

    /** Compactar la estantería de una sala.
     *
     * @param id_sala
     * Identificador de la sala.
     *
     * @pre
     * 0 < @c sala <= @ref num_salas.
     *
     * @post
     * La estantería de la sala @c sala está compactada.
     *
     * @cost
     * Lineal en el tamaño de la estantería de la sala
     *
     * @see
     * Sala::compactar
     */
    void compactar(IdSala id_sala);

    /** Los productos de la estantería de una sala se compactan (ver
     * compactar()) y se ordenan alfabéticamente.
     *
     * @param id_sala
     * Identificador de la sala.
     *
     * @pre
     * 0 < @c id_sala <= @ref num_salas.
     *
     * @post
     * La estantería de la sala @c sala está ordenada y compactada.
     *
     * @see
     * compactar,
     * Sala::reorganizar
     */
    void reorganizar(IdSala id_sala);

    /** Redimensiona la estantería de una sala.
     *
     * @param id_sala
     * Identificador de la sala.
     *
     * @param filas, columnas
     * Nuevas dimensiones del almacén.
     *
     * @retval true
     * La estantería de la sala @c sala ha sido redimensionada y compactada. El
     * nuevo tamaño es @c filas x @c columnas.
     *
     * @retval false
     * No se ha podido redimensionar porque los productos actuales de la sala @c
     * sala no cabrían en el nuevo tamaño. No se ha modificado el objeto.
     *
     * @pre
     * 0 < @c id_sala <= @ref num_salas.
     *
     * @cost
     * Linearítmico, de media, en el tamaño de la estantería de la sala
     *
     * @see
     * Sala::redimensionar
     */
    bool redimensionar(IdSala id_sala, int filas, int columnas);

    /** Consulta el elemento en la posición (f, c).
     *
     * @param id_sala
     * Identificador de la sala.
     *
     * @param f, c
     * Posición del producto.
     *
     * @returns
     * El elemento en (f, c) o @c "NULL" si está vacío.
     *
     * @pre
     * @c f <= Número de filas; @c c <= Número de columnas; 0 < id_sala <=
     * @ref num_salas.
     *
     * @cost
     * Constante
     *
     * @see
     * Sala::consultar_pos
     */
    IdProducto consultar_pos(IdSala id_sala, int f, int c) const;

    /** Escribe la estantería.
     *
     * @param id_sala
     * Identificador de la sala.
     *
     * @param os
     * Stream al que escribir la estantería.
     *
     * @pre
     * 0 < @c id_sala <= @ref num_salas.
     *
     * @post
     * La estantería se ha escrito a @c os tal y como sería realmente (con el
     * (0, 0) en la esquina inferior izquierda).
     *
     * @cost
     * Lineal en el tamaño de la estantería de la sala
     *
     * @see
     * Sala::escribir
     */
    void escribir(IdSala id_sala, ostream &os) const;
};

#endif // ALMACEN_HH
