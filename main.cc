/// @file

#include "Almacen.hh"
#include "Sala.hh"
#ifndef NO_DIAGRAM
#    include <iostream>
#    include <map>
#    include <utility>
#    include <vector>
#endif // NO_DIAGRAM

using namespace std;

/** Punto de entrada del programa.
 *
 * main() crea el almacén y contiene el bucle de lectura de instrucciones y
 * escritura de resultados. Las operaciones en sí están definidas e
 * implementadas en las clases Almacen y Sala.
 */
int main() {
    int n;
    cin >> n;

    // Crear almacén
    Almacen almacen;
    almacen.leer(n, cin);

    // Procesar instrucciones
    string inst;
    while ((cin >> inst) and (inst != "fin")) {
        if (inst == "poner_prod") {
            IdProducto id_producto;
            cin >> id_producto;
            cout << inst << ' ' << id_producto << endl;
            bool ok = almacen.poner_prod(id_producto);
            if (not ok) cout << "  error" << endl;

        } else if (inst == "quitar_prod") {
            IdProducto id_producto;
            cin >> id_producto;
            cout << inst << ' ' << id_producto << endl;
            bool ok = almacen.quitar_prod(id_producto);
            if (not ok) cout << "  error" << endl;

        } else if (inst == "poner_items") {
            IdSala id_sala;
            IdProducto id_producto;
            int cantidad;
            cin >> id_sala >> id_producto >> cantidad;
            cout << inst << ' ' << id_sala << ' ' << id_producto << ' '
                 << cantidad << endl;
            if (almacen.existe_producto(id_producto)) {
                int sobran =
                    almacen.poner_items(id_sala, id_producto, cantidad);
                cout << "  " << sobran << endl;
            } else
                cout << "  error" << endl;

        } else if (inst == "quitar_items") {
            IdSala id_sala;
            IdProducto id_producto;
            int cantidad;
            cin >> id_sala >> id_producto >> cantidad;
            cout << inst << ' ' << id_sala << ' ' << id_producto << ' '
                 << cantidad << endl;
            if (almacen.existe_producto(id_producto)) {
                int faltan =
                    almacen.quitar_items(id_sala, id_producto, cantidad);
                cout << "  " << faltan << endl;
            } else
                cout << "  error" << endl;

        } else if (inst == "distribuir") {
            IdProducto id_producto;
            int cantidad;
            cin >> id_producto >> cantidad;
            cout << inst << ' ' << id_producto << ' ' << cantidad << endl;
            int sobran = almacen.distribuir(id_producto, cantidad);
            if (sobran == -1)
                cout << "  error" << endl;
            else
                cout << "  " << sobran << endl;

        } else if (inst == "compactar") {
            IdSala id_sala;
            cin >> id_sala;
            cout << inst << ' ' << id_sala << endl;
            almacen.compactar(id_sala);

        } else if (inst == "reorganizar") {
            IdSala id_sala;
            cin >> id_sala;
            cout << inst << ' ' << id_sala << endl;
            almacen.reorganizar(id_sala);

        } else if (inst == "redimensionar") {
            IdSala id_sala;
            int f, c;
            cin >> id_sala >> f >> c;
            cout << inst << ' ' << id_sala << ' ' << f << ' ' << c << endl;
            bool ok = almacen.redimensionar(id_sala, f, c);
            if (not ok) cout << "  error" << endl;

        } else if (inst == "inventario") {
            cout << inst << endl;
            const map<IdProducto, int> &inventario = almacen.inventario();
            map<IdProducto, int>::const_iterator it;
            for (it = inventario.begin(); it != inventario.end(); ++it) {
                // Los maps están ordenados, así que el resultado
                // saldrá ordenado.
                cout << "  " << it->first << " " << it->second << endl;
            }

        } else if (inst == "escribir") {
            IdSala id_sala;
            cin >> id_sala;
            cout << inst << ' ' << id_sala << endl;
            almacen.escribir(id_sala, cout);

        } else if (inst == "consultar_pos") {
            IdSala id_sala;
            int f, c;
            cin >> id_sala >> f >> c;
            cout << inst << ' ' << id_sala << f << ' ' << c << endl;
            IdProducto id_producto = almacen.consultar_pos(id_sala, f, c);
            cout << "  " << id_producto << endl;

        } else if (inst == "consultar_prod") {
            IdProducto id_producto;
            cin >> id_producto;
            cout << inst << ' ' << id_producto << endl;
            int num = almacen.consultar_prod(id_producto);
            if (num == -1)
                cout << "  error" << endl;
            else
                cout << "  " << num << endl;
        } else {
            cout << "  error" << endl;
        }
    }
}
