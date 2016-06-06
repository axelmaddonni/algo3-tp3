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
import copy

import math

def grafo_random(n, m):
    graph = set()
    while len(graph) < m:
        graph.add((random.randint(0,n-1), random.randint(0,n-1)))
    return list(graph)

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


def main():
    size = 50
    q = [500, 400, 200, 100, 50, 10]
    for i in range(6):
        random.seed(i)
        size *= 2
        for j in range(q[i]):
            print i, j
            s = generar_string(
                    grafo_random(
                        size,
                        random.randint(size - 1, size * (size - 1) / 2)),
                    size,
                    grafo_random(
                        size,
                        random.randint(size - 1, size * (size - 1) / 2)),
                    size)
            s2 = generar_string(
                    grafo_random(
                        size,
                        random.randint(size - 1, size * (size - 1) / 2)),
                    size,
                    grafo_random(
                        size,
                        random.randint(size - 1, size * (size - 1) / 2)),
                    size)
            nombre_archivo = "caso" + str(size) + "_" + str(j) + ".txt"
            text_file = open("casos_random/casos_ahora/" + nombre_archivo, "w")
            text_file.write(s)
            text_file.close()
            text_file2 = open("casos_random/casos_despues/" + nombre_archivo, "w")
            text_file2.write(s2)
            text_file2.close()

main()
