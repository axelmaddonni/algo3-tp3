"""
parametros:
    problema
    granularidad
    ultimo
    cantidad_muestras
"""
import random
import sys
import os
import subprocess
from collections import defaultdict
import cProfile
import copy

import matplotlib.pyplot as plt
import numpy as np
from scipy import stats
import math

binario = sys.argv[1]
min_n = int(sys.argv[2])
max_n = int(sys.argv[3])
granularidad_n = int(sys.argv[4])
min_m = int(sys.argv[5])
max_m = int(sys.argv[6])
granularidad_m = int(sys.argv[7])
cuantas_mediciones = int(sys.argv[8])


def grafo_random(n, m):
    kn = [(i, j) for i in range(n) for j in range(n) if i < j]
    return random.sample(kn, m)

def generar_string(grafo1, n1, grafo2, n2):
    string = ""
    string += str(n1) + " " + str(len(grafo1)) + " "
    string += str(n2) + " " + str(len(grafo2))
    string += "\n"
    for i, j in grafo1:
        string += str(i) + " " + str(j) + "\n"
    for i, j in grafo2:
        string += str(i) + " " + str(j) + "\n"
    return string

def correr_programa(binario, input_string):
    p = subprocess.Popen(binario,
                         shell = True,
                         stdin=subprocess.PIPE,
                         stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    p.stdin.write(input_string)
    out, err = p.communicate()
    return 1000000 * float(err)

def mean(xs):
    if len(xs) == 0:
        return 0.0
    else:
        suma = 0.0
        for x in xs:
            suma += x
        return suma / len(xs)

def median(xs):
    xs.sort()
    return xs[len(xs) / 2]

def mover_n(desde, hasta, granularidad, i):
    datos = {}
    m1 = desde * (desde - 1) / 2
    n2 = random.randint(1, hasta)
    m2 = random.randint(1, n2 * (n2 - 1) / 2 )
    for n1 in range(desde, hasta + 1, granularidad):
        g1 = grafo_random(n1, m1)
        mediciones = []
        for medicion in range(cuantas_mediciones):
            input_string = ""
            if i == 1:
                input_string = generar_string(g1, n1, grafo_random(n2, m2), n2)
            else:
                input_string = generar_string(grafo_random(n2, m2), n2, g1, n1)
            mediciones.append(
                min([correr_programa(binario, input_string) for _ in range(10)]))
        datos[n1] = median(mediciones)
    return datos

def mover_m(desde, hasta, granularidad, i):
    datos = {}
    n1 = 2 * int(math.sqrt(hasta)) + 1
    m2 = random.randint(1, hasta)
    n2 = 2 * int(math.sqrt(m2)) + 1
    for m1 in range(desde, hasta + 1, granularidad):
        g1 = grafo_random(n1, m1)
        mediciones = []
        for medicion in range(cuantas_mediciones):
            input_string = ""
            if i == 1:
                input_string = generar_string(g1, n1, grafo_random(n2, m2), n2)
            else:
                input_string = generar_string(grafo_random(n2, m2), n2, g1, n1)
            mediciones.append(
                min([correr_programa(binario, input_string) for _ in range(10)]))
        datos[m1] = median(mediciones)
    return datos

def general(min_n, max_n, m):
    datos = defaultdict(list)
    for _ in range(m):
        n1 = random.randint(min_n, max_n)
        m1 = random.randint(0, n1 * (n1 - 1) / 2)
        n2 = random.randint(min_n, max_n)
        m2 = random.randint(0, n2 * (n2 - 1) / 2)
        g1 = grafo_random(n1, m1)

        input_string = generar_string(
                grafo_random(n1, m1), n1,
                grafo_random(n2, m2), n2)
        datos[(n1, m1, n2, m2)].append(
                min([correr_programa(binario, input_string) for _ in range(10)]))

    return datos


def graficar(posiciones, datos, f, texto):
    puntos = zip(map(float, posiciones), map(median, datos))
    k = encontrar_k(puntos, lambda n: f(n))
    k *= 1.2
    posiciones_ints = map(int, posiciones)

    plt.figure()
    #plt.subplot(1,2,1)
    plt.plot(posiciones_ints, map(median, datos), label="Nuestro algoritmo")
    plt.plot(posiciones_ints, map(lambda n: k * f(n), posiciones_ints),
            label=str(k)[:5] + " * " + texto)
    plt.ylabel("Tiempo (us)")
    plt.xlabel("Tamano de la entrada")
    plt.legend(loc=2)

    plt.savefig("fig.pdf")
    plt.show()



def encontrar_k(puntos, f):
    ks = []
    for n, tiempo in puntos:
        f_n = 0.0
        try: f_n = f(n)
        except: pass
        print n, f_n

        if f_n == 0.0: continue
        tiempo_normalizado = tiempo / f(n)
        ks.append(tiempo_normalizado)
    return median(ks)

def normalizar(puntos, k, f):
    return [y + (k * f(x) - y) * 0.7 for x, y in puntos]

def main():
    print mover_n(min_n, max_n, granularidad_n, 1)
    print mover_n(min_n, max_n, granularidad_n, 2)
    print mover_m(min_n, max_n, granularidad_n, 1)
    print mover_m(min_n, max_n, granularidad_n, 2)
    print general(min_n, max_n, 2 * (max_n - min_n))

main()
