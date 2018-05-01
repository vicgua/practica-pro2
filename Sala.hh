/** @file
 * Archivo que define Sala y estructuras auxiliares, como @ref Estanteria y @ref
 * Producto.
 */

#ifndef SALA_HH
#define SALA_HH

#ifndef NO_DIAGRAM
#    include <ostream>
#    include <string>
#    include <vector>
#endif

using namespace std;

/** Representación de un producto.
 * Este es representado por su identificador.
 */
typedef string Producto;

/// Representación de una Estantería como una matriz.
typedef vector<vector<Producto> > Estanteria;

/** Representación de una sala.
 *
 * Cada sala contiene una estantería, de tamaño @em filas x @em columnas, en la
 * que se guardan los productos.
 */
class Sala {
private:
    Estanteria estanteria_;
    int elementos;

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

    /** Poner un item de un producto en la sala.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @param cantidad
     * Cantidad de items del producto a añadir como máximo.
     *
     * @returns
     * Cantidad de items que no se han podido añadir por falta de espacio.
     *
     * @pre
     * @c cantidad >= 0; el producto @c id_producto existe.
     *
     * @post
     * Se han añadido min(`cantidad`, espacio libre en la sala) items del
     * producto @c id_producto a la sala; si @e return > 0 &rArr; sala llena; @b
     * NO se han añadido los productos al inventario del almacén.
     *
     * @see
     * Almacen::poner_items
     */
    int poner_items(string id_producto, int cantidad);

    /** Quitar un item de un producto de la sala.
     *
     * @param id_producto
     * Identificador del producto.
     *
     * @param cantidad
     * Cantidad de items del producto a quitar como máximo.
     *
     * @returns
     * Cantidad de items que no se han podido quitar porque no habían
     * suficientes en la sala.
     *
     * @pre
     * @c cantidad >= 0; el producto @c id_producto existe.
     *
     * @post
     * Se han quitado min(`cantidad`, items del producto en la sala) items del
     * producto @c id_producto de la sala; si @e return > 0 &rArr; No quedan
     * items en la sala; @b NO se han quitado los productos del inventario del
     * almacén.
     *
     * @see
     * Almacen::quitar_items
     */
    int quitar_items(string id_producto, int cantidad);

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
     * 0 <= @c f <= Número de filas; 0 <= @c c <= Número de columnas.
     *
     * @see
     * Almacen::consultar_pos
     */
    string consultar_pos(int f, int c) const;

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
