/** @file
 * Archivo que define Almacen.
 */
#ifndef ALMACEN_HH
#define ALMACEN_HH

#include <map>
#include <list>
#include <istream>
#include "BinTree.hh"
#include "Sala.hh"

using namespace std;

/** Esquema de una sala, que contiene solo su identificador
 *      y el tamaño de su estantería.
 * Esto es usado para construir el árbol de salas en Almacen::Almacen().
 */
struct EsquemaSala {
    /** Identificador de la sala.
     * @invariant Si inicializado: @c id >= 1. Si @c id == 0, el elemento
     *      se considerará no inicializado.
     */
    int id;
    /** Número de filas de la estantería.
     * @invariant Si inicializado: @c filas > 0.
     */
    int filas;
    /** Número de columnas de la estantería.
     * @invariant Si inicializado: @c columnas > 0.
     */
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
     * @param[in] esquema_salas Lista, en preorden, de las salas, que se utilizará para
     *      construir el árbol de salas.
     * @pre @c num_salas cumple el invariante de @ref num_salas;
     *      @c esquema_salas tiene al menos un elemento inicializado, y la lista forma
     *      un árbol en preorden.
     *      Además, con n = @c esquema_salas.size(),
     *      existe una única sala para cada entero en el rango [1, n].
     */
    Almacen(int num_salas, const list<EsquemaSala>& esquema_salas);

    /** Crea una esquema de las salas a partir de un canal de entrada.
     * @param is Canal de entrada.
     * @param[in,out] esquema_salas Esquema de las salas.
     * @pre @c is contiene un árbol en preorden (=> @c is no está vacío).
     * @post @c A esquema_salas se ha añadido el árbol leído por @c is.
     *      Los EsquemaSala añadidos no se han inicializado.
     */
    static void esquema_desde_stream(istream& is, list<EsquemaSala>& esquema_salas);

    /** Añadir un producto.
     * @param id_producto Identificador del producto.
     * @pre El producto no existe.
     * @post El producto ha sido añadido con 0 unidades.
     */
    void poner_prod(string id_producto);
    
    /** Quitar un producto.
     * @param id_producto Identificador del producto.
     * @pre El producto existe y tiene 0 unidades.
     * @post El producto ha sido eliminado.
     */
    void quitar_prod(string id_producto);

    /** Consultar el número de items que tiene un producto.
     * @param id_producto Identificador del producto.
     * @returns Número de items que tiene el producto.
     * @pre El producto existe.
     */
    int consultar_prod(string id_producto) const;

    /** Obtener una sala.
     * @param id_sala Identificador de la sala.
     * @returns La sala con identificador id_sala.
     * @pre 1 <= @c id_sala <= número de salas
     */
    Sala& sala(int id_sala);

    /** Distribuye los productos por el almacén.
     * 
     * La distribución ocurre de la siguiente forma, comenzando desde la
     * primera sala:
     * 1. Se intentan almacenar todos los productos posibles en la sala.
     * 2. Si no hay suficiente espacio, los n restantes se distribuyen
     *      entre el resto de salas:
     *      - Si hay dos salas a continuación, floor(n / 2) se distribuyen a la sala derecha,
     *          y los ceil(n / 2) restantes, a la izquierda. Ir a 1.
     *      - Si hay una sola sala, se distribuyen a esta.
     *      - Si no hay ninguna sala a continuación, no se pueden almacenar. return += n.
     * 
     * @param id_producto Identificador del producto.
     * @param cantidad Cantidad de items del producto a distribuir.
     * @returns Número de productos que no se han podido almacenar.
     * @post Los productos están distribuidos por el almacén, según
     * la política de distribución; si @e return > 0 => el almacén está lleno.
     */
    int distribuir(string id_producto, int cantidad);

    /** Inventario de los productos.
     * @returns Mapa de (producto &rarr; número de items).
     */
    const map<string, int>& inventario() const;
};

#endif