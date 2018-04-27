/** @file
 * Archivo que define Almacen.
 */
#ifndef ALMACEN_HH
#define ALMACEN_HH

#include "Sala.hh"
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <istream>
#include <list>
#include <map>
#endif

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
    /** Cómo estan organizadas las salas en el almacén.
     * Cada nodo es el identificador de una sala.
     */
    BinTree<int> estructura_salas;
    vector<Sala> salas;
    map<string, int> productos;
    /** Obtener una sala.
     * @param id_sala Identificador de la sala.
     * @returns La sala con identificador id_sala.
     * @pre 1 <= @c id_sala <= número de salas
     */
    Sala &sala(int id_sala);
    int num_salas_;
    
    /** Crea una esquema de las salas a partir de un canal de entrada.
     * @param is Canal de entrada.
     * @param[in,out] esquema_salas Esquema de las salas.
     * @pre @c is contiene un árbol en preorden (&rArr; @c is no está vacío).
     * @post A @c esquema_salas se ha añadido el árbol leído por @c is.
     *      Los EsquemaSala añadidos no se han inicializado.
     */
    static void esquema_desde_stream(istream &is,
                                     list<EsquemaSala> &esquema_salas);
    


public:
    /** Número de salas.
     * @invariant @c num_salas > 0;
     *      para cada sala: 1 <= @ref Sala::id "sala.id" <= @c num_salas;
     */
    int num_salas() const;

    /// Crea un almacén vacío.
    Almacen();
    
    /* Crea un almacén con las salas especificadas en @c esquema_salas.
     * @param num_salas Número de salas.
     * @param[in] esquema_salas Lista, en preorden, de las salas, que se
     *      utilizará para construir el árbol de salas.
     * @pre @c num_salas cumple el invariante de @ref num_salas;
     *      @c esquema_salas tiene al menos un elemento inicializado, y la lista
     *      forma un árbol en preorden. Además, con n = @c esquema_salas.size(),
     *      existe una única sala para cada entero en el rango [1, n].
     */
    //Almacen(int num_salas, const list<EsquemaSala> &esquema_salas);

    /** Añadir un producto.
     * @param id_producto Identificador del producto.
     * @post Si el producto @c id_producto no existía, ha sido añadido con 0 unidades.
     * @retval true El @c id_producto producto ha sido añadido.
     * @retval false El producto @c id_producto ya existe. El objeto no ha sido
     *      modificado.
     */
    bool poner_prod(string id_producto);

    /** Quitar un producto.
     * @param id_producto Identificador del producto.
     * @retval true El producto @c id_producto ha sido eliminado.
     * @retval false El producto @c id_producto no existe o tiene alguna
     *      unidad. El objeto no ha sido modificado.
     * @post Si el producto @c id_producto existía y tenía 0 unidades,
     *      ha sido eliminado.
     */
    bool quitar_prod(string id_producto);

    /** Poner un item de un producto en una sala.
     * @param id_sala Identificador de la sala.
     * @param id_producto Identificador del producto.
     * @param cantidad Cantidad de items del producto a añadir como máximo.
     * @returns Cantidad de items que no se han podido añadir por
     *      falta de espacio.
     * @pre @c cantidad >= 0; el producto @c id_producto existe; la sala @c id_sala existe.
     * @post Se han añadido min(`cantidad`, espacio libre en la sala)
     *      items a la sala; si @e return > 0 &rArr; sala llena.
     * @see Sala::poner_items
     */
    int poner_items(int id_sala, string id_producto, int cantidad);

    /** Quitar un item de un producto de una sala.
     * @param id_sala Identificador de la sala
     * @param id_producto Identificador del producto.
     * @param cantidad Cantidad de items del producto a quitar como máximo.
     * @returns Cantidad de items que no se han podido quitar porque
     *      no habían suficientes en la sala.
     * @pre @c cantidad >= 0; el producto @c id_producto existe; la sala @c id_sala existe.
     * @post Se han quitado min(`cantidad`, items del producto en la sala)
     *      items de la sala; si @e return > 0 &rArr; No quedan items en la sala.
     * @see Sala::quitar_items
     */
    int quitar_items(int id_sala, string id_producto, int cantidad);
    
    /** Compactar la estantería de una sala.
     * @param sala Identificador de la sala.
     * @pre La sala @c sala existe.
     * @post La estantería de la sala @c sala está compactada.
     * @see Sala::compactar
     */
    void compactar(int sala);
    
    /** Los productos de la estantería de una sala se compactan y se ordenan
     * (ver compactar()) alfabéticamente.
     * @param sala Identificador de la sala.
     * @pre La sala @c sala existe.
     * @post La estantería de la sala @c sala está ordenada y compactada.
     * @see Sala::reorganizar
     */
    void reorganizar(int sala);

    /** Redimensiona la estantería de una sala.
     * @param sala Identificador de la sala.
     * @retval true La estantería de la sala @c sala ha sido redimensionada
     *      y compactada. El nuevo tamaño es @c filas x @c columnas.
     * @retval false No se ha podido redimensionar porque los
     *      productos actuales de la sala @c sala no cabrían en el nuevo
     *      tamaño. No se ha modificado el objeto.
     * @pre La sala @c sala existe.
     * @see Sala::redimensionar
     */
    bool redimensionar(int sala, int filas, int columnas);
    
    /** Consulta el elemento en la posición (f, c).
     * @param sala Identificador de la sala.
     * @param f, c    Posición del producto.
     * @returns El elemento en (f, c) o @c "NULL" si está vacío.
     * @pre @c f <= Número de filas; @c c <= Número de columnas; @c sala existe.
     * @see Sala::consultar_pos
     */
    string consultar_pos(int sala, int f, int c) const;

    
    /** Escribe la estantería.
     * @param sala Identificador de la sala.
     * @param os Stream al que escribir la estantería.
     * @pre La sala @c sala existe.
     * @post La estantería se ha escrito a @c os tal y como sería
     *      realmente (con el (0, 0) en la esquina inferior izquierda).
     * @see Sala::escribir
     */
    void escribir(int sala, ostream &os) const;
    
    /** Consultar el número de items que tiene un producto.
     * @param id_producto Identificador del producto.
     * @returns Número de items que tiene el producto @c id_producto.
     * @retval -1 El producto @c id_producto no existe.
     */
    int consultar_prod(string id_producto) const;

    /** Distribuye los productos por el almacén.
     *
     * La distribución ocurre de la siguiente forma, comenzando desde la
     * primera sala:
     * 1. Se intentan almacenar todos los productos posibles en la sala.
     * 2. Si no hay suficiente espacio, los n restantes se distribuyen
     *      entre el resto de salas:
     *      - Si hay dos salas a continuación,
     *          @f$\left \lfloor{n / 2} \right \rfloor@f$ se distribuyen a la
     *          sala derecha, y los
     *          @f$\left \lceil{n / 2} \right \rceil@f$ restantes, a la izquierda. Ir a 1.
     *      - Si hay una sola sala, se distribuyen a esta.
     *      - Si no hay ninguna sala a continuación, no se pueden almacenar.
     * return += n.
     *
     * @param id_producto Identificador del producto.
     * @param cantidad Cantidad de items del producto a distribuir.
     * @returns Número de items del producto @c id_producto que no se han
     *      podido almacenar.
     * @retval -1 El producto @c id_producto no existe. El almacén no ha
     *      sido modificado.
     * @post Si el producto @c id_producto existe, los items han sido distribuidos
     *      por el almacén, según la política de distribución;
     *      si @e return > 0 &rArr; el almacén está lleno.
     */
    int distribuir(string id_producto, int cantidad);

    /** Inventario de los productos.
     * @returns Mapa de [producto &rarr; número de items].
     */
    const map<string, int> &inventario() const;

    /** Comprueba si existe el producto.
     * @param id_producto Identificador del producto
     * @returns Si el producto @c id_producto existe.
     */
    bool existe_producto(string id_producto) const;
    
    /** Lee las salas por un stream.
     * @param num_salas Número de salas.
     * @param is Stream para leer.
     * @pre @c is contiene un árbol en preorden y @c num_salas dimensiones
     *      (&rArr; @c is no está vacío).
     * @post El objeto ahora tiene @c num_salas salas con la estructura y
     *      dimensiones dadas en @c is.
     */
    void leer(int num_salas, istream& is);
};

#endif
