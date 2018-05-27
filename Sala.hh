/** @file
 * Archivo que define Sala y estructuras auxiliares, como @ref Estanteria,
 * @ref IdProducto e @ref IdSala.
 */

#ifndef SALA_HH
#define SALA_HH

#include "aux.hh"
#ifndef NO_DIAGRAM
#    include <ostream>
#    include <vector>
#endif

using namespace std;

/// Identificador de una sala.
typedef int IdSala;

/** Estantería, representada como un vector de identificadores de productos.
 *
 * Este vector puede ser representado como una matriz, donde la posición @f$ (i,
 * j) @f$ está en la posición @f$ i \cdot N + j @f$ donde @f$ N @f$ es el número
 * de columnas.
 *
 * Se ha escogido este formato ya que simplifica la operación reorganizar() y,
 * en menor medida, redimensionar() y compactar().
 */
typedef vector<IdProducto> Estanteria;

/** Representación de una sala.
 *
 * Cada sala contiene una estantería, de tamaño @em filas x @em columnas, en la
 * que se guardan los productos.
 */
class Sala {
private:
    /** Estantería de la sala, representada como se especifica en @ref
     * Estanteria.
     *
     * @invariant
     * <tt>estanteria.size() == @ref filas * @ref columnas</tt>
     */
    Estanteria estanteria;

    /** Inventario de la sala.
     *
     * Aunque no es estrictamente necesario, el uso de un inventario hace que la
     * operación escribir() vaya notablemente más rápido.
     *
     * @invariant
     * @ref inventario cuenta los ítems actuales de @ref estanteria según el
     * producto. Un producto está en @ref inventario si y sólo si hay al menos
     * una unidad en @ref estanteria.
     */
    Inventario inventario;

    /** Números de elementos en la estantería de la sala.
     * Al igual que @ref inventario, no es necesario, pero agiliza algunas
     * operaciones, especialmente en casos extremos.
     *
     * @invariant
     * Los siguientes son iguales:
     * - El número de ítems no nulos de @ref estanteria.
     * - La suma de los valores de @ref inventario.
     * - El valor de @ref elementos.
     */
    int elementos;

    /** Filas de la estantería de la sala.
     *
     * @invariant
     * filas == estanteria.size() / @ref columnas
     */
    int filas;
    /// Columnas de la estantería de la sala.
    int columnas;

    /** Comparar dos productos, considerando los productos nulos como mayores al
     * resto de productos.
     *
     * Esta función se puede usar como el tercer argumento de std::sort().
     *
     * @param[in] a, b
     * Identificadores de producto a comparar.
     */
    static bool comp_IdProducto(const IdProducto &a, const IdProducto &b);

    /** Copia la estantería actual en otra estantería, compactándola.
     *
     * @param[in,out] dest
     * Vector de destino.
     *
     * @pre
     * @c dest.size() >= @ref elementos
     *
     * @post
     * <tt>dest[0..elementos]</tt> contiene todos los elementos de la estantería
     * actual, en el mismo orden, pero sin espacios entre ellos; el resto del
     * vector no se ha modificado.
     */
    void copia_compactada(Estanteria &dest) const;

public:
    /// Crea una sala vacía.
    Sala();

    /** Crea una sala con un determinado número de filas y columnas.
     *
     * @param filas
     * Filas de la estantería.
     *
     * @param columnas
     * Columnas de la estantería.
     *
     * @pre
     * @c filas > 0; @c columnas > 0.
     */
    Sala(int filas, int columnas);

    /** Poner un ítem de un producto en la sala.
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
     * @pre
     * @c cantidad >= 0; el producto @c id_producto existe.
     *
     * @post
     * Se han añadido min(`cantidad`, espacio libre en la sala) ítems del
     * producto @c id_producto a la sala; si @e return > 0 &rArr; sala llena; @b
     * NO se han añadido los productos al inventario del almacén.
     *
     * @see
     * Almacen::poner_items
     */
    int poner_items(IdProducto id_producto, int cantidad);

    /** Quitar un ítem de un producto de la sala.
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
     * @pre
     * @c cantidad >= 0; el producto @c id_producto existe.
     *
     * @post
     * Se han quitado min(`cantidad`, ítems del producto en la sala) ítems del
     * producto @c id_producto de la sala; si @e return > 0 &rArr; No quedan
     * ítems en la sala; @b NO se han quitado los productos del inventario del
     * almacén.
     *
     * @see
     * Almacen::quitar_items
     */
    int quitar_items(IdProducto id_producto, int cantidad);

    /** Compactar la estantería.
     *
     * Los productos de la estantería se moverán para que no queden
     * huecos vacíos entre ellos, y empiecen desde la primera posición.
     *
     * @post
     * La estantería está compactada.
     *
     * @see
     * Almacen::compactar
     */
    void compactar();

    /** Reorganiza la estantería.
     *
     * Los productos de la estantería se compactan y se ordenan alfabéticamente.
     *
     * @post
     * La estantería está ordenada y compactada.
     *
     * @see
     * compactar,
     * Almacen::reorganizar
     */
    void reorganizar();

    /** Redimensiona la estantería de la sala.
     *
     * @param filas, columnas
     * Nuevas dimensiones de la estantería.
     *
     * @retval true
     * La estantería ha sido redimensionada y compactada. El nuevo tamaño es
     * @c filas x @c columnas.
     *
     * @retval false
     * No se ha podido redimensionar porque los productos actuales no cabrían en
     * el nuevo tamaño. No se ha modificado el objeto.
     *
     * @pre
     * @c filas > 0; @c columnas > 0.
     *
     * @see
     * Almacen::redimensionar
     */
    bool redimensionar(int filas, int columnas);

    /** Consulta el elemento en la posición (f, c).
     *
     * @param f, c
     * Posición del producto.
     *
     * @returns
     * El elemento en (f, c) o @c "NULL" si está vacío.
     *
     * @pre
     * 0 < @c f <= Número de filas; 0 < @c c <= Número de columnas.
     *
     * @see
     * Almacen::consultar_pos
     */
    IdProducto consultar_pos(int f, int c) const;

    /** Escribe la estantería.
     *
     * @param os
     * Stream al que escribir la estantería.
     *
     * @post
     * La estantería se ha escrito a @c os tal y como sería realmente (con el
     * (0, 0) en la esquina inferior izquierda).
     *
     * @see
     * Almacen::escribir
     */
    void escribir(ostream &os) const;
};

#endif // SALA_HH
