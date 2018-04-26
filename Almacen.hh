/** @file
 * Archivo que define Almacen.
 */
#ifndef ALMACEN_HH
#define ALMACEN_HH

#include "BinTree.hh"
#include "Sala.hh"
#include <istream>
#include <list>
#include <map>

using namespace std;

/** Esquema de una sala, que contiene solo su identificador
 *      y el tamaño de su estantería.
 * Esto es usado para construir el árbol de salas en Almacen::Almacen().
 * Se considera inicializado si: id != 0; filas > 0; columnas > 0.
 */
struct EsquemaSala {
    /// Identificador de la sala.
    int id;
    /// Número de filas de la estantería.
    int filas;
    /// Número de columnas de la estantería.
    int columnas;
};

/** Representación de un almacén. */
class Almacen {
private:
    BinTree<Sala> salas;
    map<string, int> productos;

public:
    /** Número de salas.
     * @invariant @c num_salas > 0;
     *      para cada sala: 1 <= @ref Sala::id "sala.id" <= @c num_salas;
     */
    const int num_salas;

    /** Crea un almacén con las salas especificadas en @c esquema_salas.
     * @param num_salas Número de salas.
     * @param[in] esquema_salas Lista, en preorden, de las salas, que se
     * utilizará para construir el árbol de salas.
     * @pre @c num_salas cumple el invariante de @ref num_salas;
     *      @c esquema_salas tiene al menos un elemento inicializado, y la lista
     *      forma un árbol en preorden. Además, con n = @c esquema_salas.size(),
     *      existe una única sala para cada entero en el rango [1, n].
     */
    Almacen(int num_salas, const list<EsquemaSala> &esquema_salas);

    /** Crea una esquema de las salas a partir de un canal de entrada.
     * @param is Canal de entrada.
     * @param[in,out] esquema_salas Esquema de las salas.
     * @pre @c is contiene un árbol en preorden (&rArr; @c is no está vacío).
     * @post A @c esquema_salas se ha añadido el árbol leído por @c is.
     *      Los EsquemaSala añadidos no se han inicializado.
     */
    static void esquema_desde_stream(istream &is,
                                     list<EsquemaSala> &esquema_salas);

    /** Añadir un producto.
     * @param id_producto Identificador del producto.
     * @post Si el producto no existía, ha sido añadido con 0 unidades.
     * @retval true El producto ha sido añadido.
     * @retval false El producto ya existe. El objeto no ha sido
     *      modificado.
     */
    bool poner_prod(string id_producto);

    /** Quitar un producto.
     * @param id_producto Identificador del producto.
     * @post Si el producto existía y tenía 0 unidades, ha sido eliminado.
     * @retval true El producto ha sido eliminado.
     * @retval false El producto no existe o tiene alguna unidad. El objeto no
     *      ha sido modificado.
     */
    bool quitar_prod(string id_producto);

    /** Consultar el número de items que tiene un producto.
     * @param id_producto Identificador del producto.
     * @returns Número de items que tiene el producto.
     * @retval -1 El producto no existe.
     */
    int consultar_prod(string id_producto) const;

    /** Obtener una sala.
     * @param id_sala Identificador de la sala.
     * @returns La sala con identificador id_sala.
     * @pre 1 <= @c id_sala <= número de salas
     */
    Sala &sala(int id_sala);

    /** Distribuye los productos por el almacén.
     *
     * La distribución ocurre de la siguiente forma, comenzando desde la
     * primera sala:
     * 1. Se intentan almacenar todos los productos posibles en la sala.
     * 2. Si no hay suficiente espacio, los n restantes se distribuyen
     *      entre el resto de salas:
     *      - Si hay dos salas a continuación, floor(n / 2) se distribuyen a la
     * sala derecha, y los ceil(n / 2) restantes, a la izquierda. Ir a 1.
     *      - Si hay una sola sala, se distribuyen a esta.
     *      - Si no hay ninguna sala a continuación, no se pueden almacenar.
     * return += n.
     *
     * @param id_producto Identificador del producto.
     * @param cantidad Cantidad de items del producto a distribuir.
     * @returns Número de productos que no se han podido almacenar.
     * @post Si el producto existe, los items han sido distribuidos por el
     *      almacén, según la política de distribución;
     *      si @e return > 0 &rArr; el almacén está lleno.
     * @retval -1 El producto no existe. El almacén no ha sido modificado.
     */
    int distribuir(string id_producto, int cantidad);

    /** Inventario de los productos.
     * @returns Mapa de [producto &rarr; número de items].
     */
    const map<string, int> &inventario() const;

    /** Comprueba si existe el producto.
     * @param id_producto Identificador del producto
     * @returns Si el producto existe.
     */
    bool existe_producto(string id_producto) const;
};

#endif