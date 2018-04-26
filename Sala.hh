/** @file
 * Archivo que define Sala y estructuras auxiliares, como Estanteria.
 */

#ifndef SALA_HH
#define SALA_HH

#include <ostream>
#include <string>
#include <vector>

using namespace std;

typedef string Producto;

/// Representación de una Estantería como una matriz.
typedef vector<vector<Producto> > Estanteria;

/** Representación de una sala.
 * Cada sala contiene una estantería, de tamaño filas x columnas, en la
 * que se guardan los productos.
 */
class Sala {
private:
    Estanteria estanteria_;
    int contar_elementos() const;

public:
    /**
     * @param id Identificador de la sala.
     * @param filas Filas de la estantería.
     * @param columnas Columnas de la estantería.
     * @pre @c id >= 1; @c filas > 0; @c columnas > 0.
     */
    Sala(int id, int filas, int columnas);

    /** Identificador de la sala.
     * @invariant @c id >= 1
     */
    const int id;

    /** Poner un item de un producto en la sala.
     * @param id_producto Identificador del producto.
     * @param cantidad Cantidad de items del producto a añadir como máximo.
     * @returns Cantidad de items que no se han podido añadir por
     *      falta de espacio.
     * @pre @c cantidad >= 0; el producto existe.
     * @post Se han añadido min(`cantidad`, espacio libre en la sala)
     *      items a la sala; si @e return > 0 &rArr; sala llena.
     */
    int poner_items(string id_producto, int cantidad);

    /** Quitar un item de un producto de la sala.
     * @param id_producto Identificador del producto.
     * @param cantidad Cantidad de items del producto a quitar como máximo.
     * @returns Cantidad de items que no se han podido quitar porque
     *      no habían suficientes en la sala.
     * @pre @c cantidad >= 0; el producto existe.
     * @post Se han quitado min(`cantidad`, items del producto en la sala)
     *      items de la sala; si @e return > 0 &rArr; No quedan items en la sala.
     */
    int quitar_items(string id_producto, int cantidad);

    /** Compactar la estantería.
     * Los productos de la estantería se moverán para que no queden
     * huecos vacíos entre ellos, y empiecen desde la primera posición.
     * @post La estantería está compactada.
     */
    void compactar();

    /** Reorganiza la estantería.
     * Los productos de la estantería se compactan y se ordenan (ver
     * compactar()) alfabéticamente.
     * @post La estantería está ordenada y compactada.
     */
    void reorganizar();

    /** Redimensiona la estantería de la sala.
     * @param filas Nuevo número de filas.
     * @param columnas Nuevo número de columnas
     * @pre Número de productos en la estantería <= @c filas * @c columnas;
     *      @c filas > 0; @c columnas > 0.
     * @retval true La estantería ha sido redimensionada y compactada.
     *      El nuevo tamaño es @c filas x @c columnas.
     * @retval false No se ha podido redimensionar porque los
     *      productos actuales no cabrían en el nuevo tamaño.
     *      No se ha modificado el objeto.
     */
    bool redimensionar(int filas, int columnas);

    /** Consulta el elemento en la posición (f, c).
     * @param f, c    Posición del producto.
     * @returns El elemento en (f, c) o @c "NULL" si está vacío.
     * @pre @c f <= Número de filas; @c c <= Número de columnas.
     */
    string consultar_pos(int f, int c) const;

    /** Escribe la estantería.
     * @param os Stream al que escribir la estantería.
     * @post La estantería se ha escrito a @c os tal y como sería
     *      realmente (con el (0, 0) en la esquina inferior izquierda).
     */
    void escribir(ostream &os) const;
};

#endif // SALA_HH