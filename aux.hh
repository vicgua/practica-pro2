/** @file
 * Este archivo contiene definiciones auxiliares (como @em typedefs) que no
 * corresponden a ninguna clase.
 */

#ifndef AUX_HH
#define AUX_HH

#ifndef NO_DIAGRAM
#    include <map>
#    include <string>
#endif // NO_DIAGRAM

using namespace std;

/// Identificador de un producto.
typedef string IdProducto;

/// Inventario, representado como un map [Producto &rarr; cantidad]
typedef map<IdProducto, int> Inventario;

#endif // AUX_HH