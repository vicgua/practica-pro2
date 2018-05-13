#!/usr/bin/env python3
# TEST PREPROCESSOR
# Crea un archivo de tests y su solución esperada a partir de un directorio
# de tests. El formato de entrada admite comentarios, un sólo archivo para
# la entrada y la salida esperada, y varios archivos que se juntarán en un
# único archivo final

import argparse
import json
from pathlib import Path

class Sala:
    def __init__(self, id_sala, filas, columnas):
        self.id_sala = id_sala
        self.dimensiones = (filas, columnas)
        self.left = None
        self.right = None
    
    def añadir_sala(self, otra_sala):
        if self.left is None:
            self.left = otra_sala
        elif self.right is None:
            self.right = otra_sala
        else:
            raise ValueError('Intentado conectar una sala a otra completa')
    
    def árbol_salas(self, lista_preorden):
        lista_preorden.append(self.id_sala)
        if self.left is not None:
            self.left.árbol_salas(lista_preorden)
        else:
            lista_preorden.append(0)
        if self.right is not None:
            self.right.árbol_salas(lista_preorden)
        else:
            lista_preorden.append(0)

def procesar_estructura(sala_json, salas_dict):
    id_sala = sala_json['id']
    filas, columnas = sala_json['filas'], sala_json['columnas']
    sala = Sala(id_sala, filas, columnas)
    for s in sala_json.get('conectado a', []):
        sala.añadir_sala(procesar_estructura(s, salas_dict))
    assert id_sala not in salas_dict, 'Sala repetida'
    salas_dict[id_sala] = sala
    return sala

def escribir_estructura(inp, salas, salas_dict):
    inp.write('%d\n' % len(salas_dict))
    salas_preorden = []
    salas.árbol_salas(salas_preorden)
    inp.write('%s\n' % ' '.join(map(str, salas_preorden)))
    for id_sala in range(1, len(salas_dict) + 1):
        # Necesitamos las salas ordenadas
        inp.write('%d %d\n' % salas_dict[id_sala].dimensiones)
    inp.write('\n')

def procesar_test(inp, cor, test):
    for line in test:
        input_line = not line.startswith('  ')
        clean_line = line.split(';', 1)[0].rstrip()
        if not clean_line:
            continue
        if input_line:
            inp.write('%s\n' % clean_line)
        cor.write('%s\n' % clean_line)
    inp.write('\n')

def procesar_meta(meta, base, inp, cor):
    salas_dict = {}
    salas = procesar_estructura(meta['estructura'], salas_dict)
    escribir_estructura(inp, salas, salas_dict)
    for testname in meta['tests']:
        test_file = base / testname
        with test_file.open('r') as test_obj:
            procesar_test(inp, cor, test_obj)
    inp.write('fin')
    cor.write('fin')

parser = argparse.ArgumentParser(
    description='Preprocesador de tests para TreeKEA'
)

parser.add_argument(
    '-o', '--output',
    required=True,
    help=('archivo de salida, sin la extensión.'
          ' Para "-o x", se crearán x.inp y x.out')
)

parser.add_argument(
    'inp_dir',
    help=('directorio de entrada, que contiene un meta.json y'
         ' uno o más tests')
)

args = parser.parse_args()
inp_dir = Path(args.inp_dir)
if not inp_dir.is_dir():
    parser.error('%s no es un directorio' % inp_dir)
metafile = inp_dir / 'meta.json'
if not metafile.is_file():
    parser.error('%s debe contener un archivo meta.json' % inp_dir)

with metafile.open('r') as m:
    meta = json.load(m)

inp_file = Path(args.output + '.inp')
cor_file = Path(args.output + '.cor')
with inp_file.open('w') as inp, cor_file.open('w') as cor:
    procesar_meta(meta, inp_dir, inp, cor)