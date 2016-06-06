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
    size = 0
    q = [500, 500, 400, 400, 300, 300, 200, 200, 100, 100]
    for i in range(10):
        random.seed(i)
        size += 50
        for j in range(q[i]):
            print size, j
            n1 = size
            m1 = random.randint(1, n1 * (n1 - 1) / 2)
            n2 = random.randint(n1 / 25, n1)
            m2 = random.randint(1, n2 * (n2 - 1) / 2)
            s = generar_string(
                    grafo_random(n1, m1), n1, grafo_random(n2, m2), n2)
            s2 = generar_string(
                    grafo_random(n1, m1), n1, grafo_random(n2, m2), n2)
            nombre_archivo = "caso" + str(size) + "_" + str(j) + ".txt"
            text_file = open("casos_random/casos_ahora/" + nombre_archivo, "w")
            text_file.write(s)
            text_file.close()
            text_file2 = open(
                    "casos_random/casos_despues/" + nombre_archivo, "w")
            text_file2.write(s2)
            text_file2.close()

main()
