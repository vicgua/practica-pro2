/// @file

#include "Almacen.hh"
#include "Sala.hh"

#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <vector>

using namespace std;

/// @todo Añadir gestión de errores.
int main() {
    int n;
    cin >> n;
    list<EsquemaSala> esquema_salas;
    
    // Leer el árbol de salas.
    Almacen::esquema_desde_stream(cin, esquema_salas);
    
    // Leer las dimensiones de las salas.
    vector<pair<int, int>> dimensiones_estanterias(n);
    for (int i = 1; i <= n; ++i) {
        int f, c;
        cin >> f >> c;
        dimensiones_estanterias[i - 1] = pair<int, int>(f, c);
    }
    list<EsquemaSala>::iterator it;
    for (it = esquema_salas.begin(); it != esquema_salas.end(); ++it) {
        if (it->id != 0) {
            pair<int, int> d = dimensiones_estanterias[it->id - 1];
            it->filas = d.first;
            it->columnas = d.second;
        }
    }

    // Crear almacén
    Almacen almacen(n, esquema_salas);

    // Procesar instrucciones
    string inst;
    while ((cin >> inst) and (inst != "fin")) {

        if (inst == "poner_prod") {
            string id;
            almacen.poner_prod(id);

        } else if (inst == "quitar_prod") {
            string id;
            almacen.quitar_prod(id);

        } else if (inst == "poner_items") {
            int sala;
            string id;
            int cantidad;
            cin >> sala >> id >> cantidad;
            int sobran = almacen.sala(sala).poner_items(id, cantidad);
            cout << "  " << sobran << endl;

        } else if (inst == "quitar_items") {
            int sala;
            string id;
            int cantidad;
            cin >> sala >> id >> cantidad;
            int faltan = almacen.sala(sala).quitar_items(id, cantidad);
            cout << "  " << faltan << endl;

        } else if (inst == "distribuir") {
            string id;
            int cantidad;
            cin >> id >> cantidad;
            int sobran = almacen.distribuir(id, cantidad);
            cout << "  " << sobran << endl;

        } else if (inst == "compactar") {
            int sala;
            cin >> sala;
            almacen.sala(sala).compactar();

        } else if (inst == "reorganizar") {
            int sala;
            cin >> sala;
            almacen.sala(sala).reorganizar();

        } else if (inst == "redimensionar") {
            int sala;
            int f, c;
            cin >> sala >> f >> c;
            almacen.sala(sala).redimensionar(f, c);

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
            almacen.sala(sala).escribir(cout);

        } else if (inst == "consultar_pos") {
            int sala;
            int f, c;
            string id = almacen.sala(sala).consultar_pos(f, c);
            cout << "  " << id << endl;

        } else if (inst == "consultar_prod") {
            string id;
            cin >> id;
            int num = almacen.consultar_prod(id);
            cout << "  " << num << endl;
        }
    }
}