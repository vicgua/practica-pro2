/// @file

#include "Almacen.hh"
#include "Sala.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#endif


using namespace std;

/// @todo Canviar "sala existe" per "1 <= sala <= n"
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
            string id;
            bool ok = almacen.poner_prod(id);
            if (not ok) cout << "  error" << endl;

        } else if (inst == "quitar_prod") {
            string id;
            bool ok = almacen.quitar_prod(id);
            if (not ok) cout << "  error" << endl;

        } else if (inst == "poner_items") {
            int sala;
            string id;
            int cantidad;
            cin >> sala >> id >> cantidad;
            if (almacen.existe_producto(id)) {
                int sobran = almacen.poner_items(sala, id, cantidad);
                cout << "  " << sobran << endl;
            } else
                cout << "  error" << endl;

        } else if (inst == "quitar_items") {
            int sala;
            string id;
            int cantidad;
            cin >> sala >> id >> cantidad;
            if (almacen.existe_producto(id)) {
                int faltan = almacen.quitar_items(sala, id, cantidad);
                cout << "  " << faltan << endl;
            } else
                cout << "  error" << endl;

        } else if (inst == "distribuir") {
            string id;
            int cantidad;
            cin >> id >> cantidad;
            int sobran = almacen.distribuir(id, cantidad);
            if (sobran == -1)
                cout << "  error" << endl;
            else
                cout << "  " << sobran << endl;

        } else if (inst == "compactar") {
            int sala;
            cin >> sala;
            almacen.compactar(sala);

        } else if (inst == "reorganizar") {
            int sala;
            cin >> sala;
            almacen.reorganizar(sala);

        } else if (inst == "redimensionar") {
            int sala;
            int f, c;
            cin >> sala >> f >> c;
            bool ok = almacen.redimensionar(sala, f, c);
            if (not ok) cout << "  error" << endl;

        } else if (inst == "inventario") {
            const map<string, int> &inventario = almacen.inventario();
            map<string, int>::const_iterator it;
            for (it = inventario.begin(); it != inventario.end(); ++it) {
                // Los maps están ordenados, así que el resultado
                // saldrá ordenado.
                cout << "  " << it->first << " " << it->second << endl;
            }

        } else if (inst == "escribir") {
            int sala;
            cin >> sala;
            almacen.escribir(sala, cout);

        } else if (inst == "consultar_pos") {
            int sala;
            int f, c;
            cin >> sala >> f >> c;
            string id = almacen.consultar_pos(sala, f, c);
            cout << "  " << id << endl;

        } else if (inst == "consultar_prod") {
            string id;
            cin >> id;
            int num = almacen.consultar_prod(id);
            if (num == -1)
                cout << "  error" << endl;
            else
                cout << "  " << num << endl;
        }
    }
}
