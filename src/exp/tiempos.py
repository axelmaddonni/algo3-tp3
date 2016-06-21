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

try:
    binario = sys.argv[1]
    min_n = int(sys.argv[2])
    max_n = int(sys.argv[3])
    granularidad_n = int(sys.argv[4])
    cuantas_mediciones = int(sys.argv[8])
except:
    "Error leyendo sys.argv"


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
        n2 = 150 #random.randint(50, 200) #random.randint(5, 15) #random.randint(min_n, max_n)
        m2 = 1000 # random.randint(1000, 1050) #random.randint(1, n2 * (n2 - 1) / 2)
        n1 = random.randint(2, 149) #random.randint(min_n, max_n)
        m1 = n1 * (n1 - 1) / 2 #random.randint(1, n1 * (n1 - 1) / 2)
        g1 = grafo_random(n1, m1)

        input_string = generar_string(
                grafo_random(n1, m1), n1,
                grafo_random(n2, m2), n2)
        datos[(n1, m1, n2, m2)].append(
                min([correr_programa(binario, input_string) for _ in range(20)]))

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


def graficar_problema2():
    resultados = defaultdict(list,
            {
                (5, 9, 9, 3): [221.345],
                (5, 3, 10, 25): [327.514],
                (1, 0, 5, 2): [19.329],
                (8, 24, 2, 0): [21.631999999999998],
                (4, 0, 1, 0): [18.851999999999997],
                (4, 0, 4, 3): [20.298000000000002],
                (4, 1, 4, 3): [23.298000000000002],
                (6, 13, 2, 0): [22.557000000000002],
                (5, 7, 4, 0): [21.060000000000002],
                (9, 25, 5, 1): [207.82],
                (9, 20, 4, 1): [187.298000000000002],
                (6, 11, 6, 14): [165.802],
                (7, 12, 7, 14): [230.851999999999997],
            })

    puntos = map(
            lambda (n1, m1, n2, m2) :
                ((4*n1*n2)**(n1+1),
                median(resultados[(n1, m1, n2, m2)]) / (4*n1*n2)**(n1+1)),
            resultados.keys())
    puntos = sorted(puntos, key=lambda tup: tup[0])
    print puntos


    plt.figure()
    plt.title("Algoritmo exacto")
    plt.plot(map(lambda tup: tup[0], puntos),
             map(lambda tup: tup[1], puntos),
            label="Nuestro algoritmo",
            marker=".")
    plt.ylabel("Tiempo (us) / (4n_1n_2)^(n_1+1)")
    plt.xlabel("Tamano de la entrada (4n_1n_2)^(n_1+1)")
    plt.xscale('log')
    plt.yscale('log')
    plt.legend(loc=2)

    plt.savefig("fig.pdf")
    plt.show()


def graficar_problema2_n1fijo():
    resultados = defaultdict(list,
        {(5, 10, 10, 10): [429080.0, 434931.0, 436772.0, 424397.0, 423620.0], (5, 10, 7, 10): [45445.2, 44716.8, 48723.799999999996], (5, 10, 14, 10): [3472010.0, 3473720.0, 3465440.0], (5, 10, 11, 10): [745540.0, 754194.0, 763944.0, 760932.0], (5, 10, 6, 10): [17312.2, 17602.1], (5, 10, 13, 10): [2203830.0, 2126700.0, 2136770.0], (5, 10, 8, 10): [108205.0, 104327.0, 101799.0, 104349.0], (5, 10, 5, 10): [143.48499999999999, 132.69], (5, 10, 15, 10): [5176910.0], (5, 10, 12, 10):
            [1326980.0], (5, 10, 9, 10): [216499.0, 214991.0]})

    puntos = map(
            lambda (n1, m1, n2, m2) : (
                n2,
                median(resultados[(n1, m1, n2, m2)])),
            resultados.keys())

    puntos_dict = {}
    for (n2, tiempos) in puntos:
        puntos_dict[n2] = []
    for (n2, t) in puntos:
        puntos_dict[n2].append(t)

    puntos = sorted(
            map(
                lambda n2: (n2, min(puntos_dict[n2])/1000),
                puntos_dict.keys()),
            key=lambda tup: tup[0])

    print puntos

    plt.figure()
    plt.title("Algoritmo exacto (n_1 = 5)")
    #k = encontrar_k(puntos, lambda x: x**6)
    k1 = 0.0005
    k2 = 0.0004
    plt.plot(map(lambda tup: tup[0], puntos),
             map(lambda tup: tup[1], puntos),
            label="Nuestro algoritmo",
            marker=".")
    plt.plot(map(lambda tup: tup[0], puntos),
            map(lambda tup: k1 * (tup[0]**6), puntos),
             label=str(k1) + "* n_2^6"
             )
    plt.plot(map(lambda tup: tup[0], puntos),
            map(lambda tup: k2 * (tup[0]**6), puntos),
             label=str(k2) + "* n_2^6"
             )
    plt.ylabel("Tiempo (ms)")
    plt.xlabel("Tamano de la entrada (n_2)")
    plt.ylim(0, 5176.9100*1.2)
    plt.legend(loc=2)

    plt.savefig("fig.pdf")
    plt.show()

def graficar_problema4():
    resultados = defaultdict(list,
            {
                (49, 513, 12, 42): [67.753],
                (31, 138, 11, 44): [37.772], (8, 12, 10, 8): [18.876], (26, 108, 15, 90): [35.895], (50, 771, 12, 50): [65.49499999999999],
                (47, 889, 11, 34): [52.597], (4, 6, 7, 2): [13.673], (37, 582, 5, 2): [34.304], (29, 322, 6, 4): [31.318], (11, 22, 15, 15): [22.568], (37, 633, 11, 33): [37.685], (35, 56, 10, 40): [35.317], (37, 12, 15, 6): [37.184000000000005], (15, 70, 6, 1): [20.163999999999998], (17, 116, 11, 24): [25.663],
                (47, 506, 8, 2): [61.816], (35, 427, 14, 66): [44.848], (43, 211, 12, 3): [48.364], (47, 806, 15, 70): [59.395], (11, 42, 9, 27): [20.104], (39, 259, 13, 2): [49.089999999999996], (45, 119, 6, 5): [41.632], (37, 577, 14, 2): [39.297], (4, 4, 15, 44): [20.05], (42, 479, 10, 43): [57.333999999999996],
                (24, 157, 15, 103): [34.706], (13, 74, 12, 65): [20.784999999999997], (40, 27, 12, 16): [39.653999999999996], (9, 36, 15, 6): [20.461],
                (14, 14, 14, 85): [23.909000000000002], (41, 346, 7, 18): [50.266000000000005], (18, 136, 5, 9): [20.557], (33, 170, 6, 2): [37.344], (15, 90, 12, 38): [25.329], (44, 575, 9, 10): [57.871], (18, 122, 7, 10): [23.518], (29, 5, 11, 19): [31.041000000000004], (50, 1174, 15, 27): [51.667], (24, 258, 10, 32): [27.192999999999998], (23, 154, 10, 4): [29.663999999999998], (9, 36, 11, 40): [19.197], (8, 17, 14, 21): [21.057],
                (46, 60, 6, 7): [40.814],
                (35, 553, 14, 37): [38.379],
                (20, 25, 6, 11): [22.549],
                (48, 713, 12, 19): [64.303], (36, 186, 15, 101): [46.159000000000006], (27, 151, 11, 23): [35.978], (47, 298, 11, 33): [57.006],
                (34, 293, 12, 29): [46.004999999999995], (39, 59, 11, 20): [39.095], (11, 26, 10, 8): [20.756], (38, 595, 6, 14): [37.738], (38, 127, 6, 15): [37.758],
                (14, 16, 6, 6): [19.028000000000002], (38, 424, 13, 74): [49.794], (14, 4, 11, 7): [20.766000000000002], (12, 31, 6, 11): [19.578000000000003],
                (15, 39, 15, 47): [28.558],
                (9, 4, 10, 14): [18.537], (45, 259, 12, 37): [56.49], (6, 13, 13, 42): [19.441], (29, 32, 7, 5): [31.092], (45, 674, 7, 12): [54.21],
                (49, 618, 12, 5): [67.066], (47, 618, 5, 3): [59.553], (32, 81, 14, 85): [36.379], (13, 67, 8, 24): [19.855], (13, 51, 11, 51): [21.970000000000002], (41, 127, 13, 6): [43.793], (29, 196, 14, 38): [41.998], (9, 27, 5, 7): [15.841999999999999], (45, 437, 11, 47): [60.235],
                (18, 3, 7, 18): [20.288999999999998], (31, 305, 13, 69): [40.516999999999996], (14, 77, 13, 5): [23.445999999999998], (50, 1145, 12, 54): [48.928000000000004], (25, 181, 8, 17): [32.436], (50, 984, 10, 33): [55.827], (4, 6, 12, 31): [17.646], (23, 17, 15, 7): [27.78], (33, 305, 6, 5): [39.791], (48, 938, 9, 16): [51.032000000000004], (30, 92, 11, 5): [34.016], (25, 284, 7, 3): [26.200999999999997], (30, 434, 6, 11): [27.129],
                (44, 920, 12, 4): [41.615],
                (49, 599, 8, 7): [64.83], (39, 166, 13, 53): [46.772], (34, 170, 14, 80): [42.870000000000005],
                (17, 11, 12, 53): [25.006999999999998], (8, 15, 8, 23): [17.615], (34, 109, 11, 34): [39.174], (30, 429, 7, 21): [28.164], (4, 5, 15, 82): [19.569],
                (16, 48, 14, 44): [28.698], (9, 27, 7, 13): [18.619], (28, 271, 12, 24): [37.434000000000005], (47, 21, 10, 27): [43.442], (48, 1033, 6, 7): [44.661]
            })

    puntos = map(
            lambda (n1, m1, n2, m2) :
                (n1**4 * n2,
                median(resultados[(n1, m1, n2, m2)]) / (n1**4 * n2)),
            resultados.keys())
    puntos = sorted(puntos, key=lambda tup: tup[0])
    print puntos


    plt.figure()
    plt.title("Algoritmo goloso")
    plt.plot(map(lambda tup: tup[0], puntos),
             map(lambda tup: tup[1], puntos),
            label="Nuestro algoritmo",
            marker=".")
    plt.ylabel("Tiempo (us) / (n_1^4  n_2)")
    plt.xlabel("Tamano de la entrada (n_1^4  n_2)")
    plt.xscale('log')
    plt.yscale('log')
    plt.legend(loc=2)

    plt.savefig("fig.pdf")
    plt.show()


def graficar_problema4_n1fijo():
    resultados = defaultdict(list,
            {
(50, 1000, 115, 1010): [140.732], (50, 1000, 170, 1011): [161.569], (50, 1000, 88, 1003): [109.625], (50, 1000, 145, 1034): [120.97200000000001], (50, 1000, 68, 1043): [83.104], (50, 1000, 121, 1002): [149.53199999999998], (50, 1000, 136, 1043): [107.052], (50, 1000, 120, 1029): [147.57999999999998], (50, 1000, 74, 1021): [91.887], (50, 1000, 64, 1001): [76.411], (50, 1000, 69, 1007): [84.866], (50, 1000, 180, 1004): [173.869], (50, 1000, 69, 1001): [84.371], (50, 1000, 61, 1002): [143.781], (50, 1000, 77, 1043): [96.85], (50, 1000, 186, 1032): [183.39600000000002], (50, 1000, 134, 1033): [105.518], (50, 1000, 112, 1001): [144.499], (50, 1000, 130, 1009): [98.854], (50, 1000, 154, 1024): [133.987], (50, 1000, 125, 1028): [154.911], (50, 1000, 86, 1033): [105.351], (50, 1000, 118, 1046): [145.422], (50, 1000, 96, 1035): [117.97], (50, 1000, 119, 1040): [145.821], (50, 1000, 63, 1031): [139.167], (50, 1000, 76, 1029): [95.931], (50, 1000, 149, 1001): [125.394], (50, 1000, 54, 1050): [110.63199999999999], (50, 1000, 95, 1040): [116.372], (50, 1000, 63, 1044): [139.774], (50, 1000, 88, 1005): [110.884], (50, 1000, 100, 1050): [124.625], (50, 1000, 155, 1002): [135.96300000000002], (50, 1000, 170, 1047): [156.78799999999998], (50, 1000, 177, 1034): [168.71099999999998], (50, 1000, 195, 1001): [125.36], (50, 1000, 64, 1018): [78.53099999999999], (50, 1000, 150, 1042): [128.513], (50, 1000, 98, 1048): [120.631], (50, 1000, 178, 1015): [170.15699999999998], (50, 1000, 95, 1021): [121.133], (50, 1000, 83, 1002): [102.269], (50, 1000, 84, 1050): [106.011], (50, 1000, 171, 1005): [159.643], (50, 1000, 104, 1012): [129.253], (50, 1000, 94, 1039): [117.95599999999999], (50, 1000, 190, 1008): [200.87199999999999], (50, 1000, 151, 1030): [129.981], (50, 1000, 134, 1019): [103.124], (50, 1000, 184, 1039): [186.518], (50, 1000, 62, 1017): [136.696], (50, 1000, 82, 1017): [102.13300000000001], (50, 1000, 79, 1021): [98.786], (50, 1000, 126, 1018): [154.852], (50, 1000, 158, 1039): [137.555], (50, 1000, 104, 1042): [126.78999999999999], (50, 1000, 88, 1011): [109.825], (50, 1000, 195, 1037): [124.379], (50, 1000, 78, 1035): [97.73299999999999], (50, 1000, 180, 1024): [173.867], (50, 1000, 93, 1015): [115.59400000000001], (50, 1000, 182, 1027): [176.245], (50, 1000, 136, 1022): [106.65], (50, 1000, 191, 1018): [196.03799999999998], (50, 1000, 150, 1012): [127.06800000000001], (50, 1000, 119, 1030): [149.35999999999999], (50, 1000, 107, 1022): [132.56199999999998], (50, 1000, 51, 1026): [106.893], (50, 1000, 200, 1033): [129.714], (50, 1000, 189, 1026): [191.152], (50, 1000, 85, 1020): [106.49199999999999], (50, 1000, 58, 1041): [123.93699999999998], (50, 1000, 122, 1031): [150.041], (50, 1000, 108, 1017): [132.568], (50, 1000, 108, 1006): [133.96], (50, 1000, 130, 1030): [98.44800000000001], (50, 1000, 107, 1047): [133.621], (50, 1000, 134, 1012): [105.435], (50, 1000, 177, 1012): [169.316], (50, 1000, 67, 1012): [81.13799999999999], (50, 1000, 164, 1042): [146.369], (50, 1000, 103, 1024): [125.59299999999999], (50, 1000, 84, 1025): [105.226], (50, 1000, 60, 1048): [132.688], (50, 1000, 177, 1003): [168.436], (50, 1000, 61, 1041): [145.612], (50, 1000, 110, 1032): [135.14000000000001], (50, 1000, 57, 1028): [121.32], (50, 1000, 188, 1044): [192.852], (50, 1000, 95, 1025): [118.512], (50, 1000, 113, 1029): [139.546], (50, 1000, 140, 1050): [113.544], (50, 1000, 200, 1007): [133.886], (50, 1000, 55, 1041): [114.88], (50, 1000, 94, 1043): [117.17999999999999], (50, 1000, 172, 1043): [160.44299999999998], (50, 1000, 172, 1046): [161.481], (50, 1000, 98, 1039): [119.715], (50, 1000, 122, 1042): [149.334]})

    puntos = map(
            lambda (n1, m1, n2, m2) : (
                n2,
                median(resultados[(n1, m1, n2, m2)])),
            resultados.keys())

    puntos_dict = {}
    for (n2, tiempos) in puntos:
        puntos_dict[n2] = []
    for (n2, t) in puntos:
        puntos_dict[n2].append(t)

    puntos = sorted(
            map(
                lambda n2: (n2, min(puntos_dict[n2])/1000),
                puntos_dict.keys()),
            key=lambda tup: tup[0])

    print puntos

    plt.figure()
    plt.title("Algoritmo goloso (n_1 = 50)")
    #k = encontrar_k(puntos, lambda x: x**6)
    k1 = 0.00045
    k2 = 0.00035
    plt.plot(map(lambda tup: tup[0], puntos),
             map(lambda tup: tup[1], puntos),
            label="Nuestro algoritmo",
            marker=".")
    plt.plot(map(lambda tup: tup[0], puntos),
            map(lambda tup: k1 * (tup[0]) + 0.12, puntos),
             label=str(k1) + "* n_2"
             )
    plt.plot(map(lambda tup: tup[0], puntos),
            map(lambda tup: k2 * (tup[0]) + 0.05, puntos),
             label=str(k2) + "* n_2"
             )
    plt.ylabel("Tiempo (ms)")
    plt.xlabel("Tamano de la entrada (n_2)")
    plt.legend(loc=2)

    plt.savefig("fig.pdf")
    plt.show()

def graficar_problema4_n2fijo():
    resultados = defaultdict(list,
        {
            (74, 2701, 150, 1000): [117.53699999999999], (104, 5356, 150, 1000): [158.56], (142, 10011, 150, 1000): [181.86100000000002, 182.077], (90, 4005, 150, 1000): [138.41, 137.70000000000002], (108, 5778, 150, 1000): [165.87199999999999], (118, 6903, 150, 1000): [185.77, 186.691], (143, 10153, 150, 1000): [184.29399999999998], (42, 861, 150, 1000): [106.00800000000001], (66, 2145, 150, 1000): [110.801], (55, 1485, 150, 1000): [124.43799999999999,
                122.06099999999999], (52, 1326, 150, 1000): [116.586], (125, 7750, 150, 1000): [198.354], (122, 7381, 150, 1000): [193.115, 192.799], (128, 8128, 150, 1000): [158.918], (9, 36, 150, 1000): [81.47500000000001, 81.966], (7, 21, 150, 1000): [81.125], (141, 9870, 150, 1000): [178.149], (111, 6105, 150, 1000): [174.257, 174.369], (97, 4656, 150, 1000): [150.27700000000002, 144.06099999999998], (76, 2850, 150, 1000): [119.92999999999999], (149, 11026, 150, 1000):
            [195.72299999999998, 195.351], (48, 1128, 150, 1000): [109.882, 111.265], (93, 4278, 150, 1000): [142.713, 141.59099999999998, 142.55800000000002, 142.836], (101, 5050, 150, 1000): [154.862], (113, 6328, 150, 1000): [176.514], (54, 1431, 150, 1000): [120.639], (35, 595, 150, 1000): [98.974, 99.47699999999999], (94, 4371, 150, 1000): [144.051], (38, 703, 150, 1000): [102.511, 103.148], (144, 10296, 150, 1000): [187.42499999999998, 186.73100000000002],
            (25, 300, 150, 1000): [89.787], (61, 1830, 150, 1000): [124.71], (24, 276, 150, 1000): [88.489], (17, 136, 150, 1000): [88.79599999999999, 86.562], (3, 3, 150, 1000): [77.509, 79.159, 78.198], (64, 2016, 150, 1000): [107.642], (119, 7021, 150, 1000): [187.947, 188.749], (33, 528, 150, 1000): [96.312], (85, 3570, 150, 1000): [131.81900000000002], (87, 3741, 150, 1000): [134.869], (20, 190, 150, 1000): [88.54100000000001], (14, 91, 150, 1000): [83.251], (49, 1176,
                150, 1000): [112.79499999999999], (146, 10585, 150, 1000): [190.118, 188.503], (109, 5886, 150, 1000): [169.077], (8, 28, 150, 1000): [80.55799999999999], (28, 378, 150, 1000): [93.245], (80, 3160, 150, 1000): [124.281], (89, 3916, 150, 1000): [135.787], (83, 3403, 150, 1000): [127.71200000000002, 129.454], (70, 2415, 150, 1000): [112.86, 115.382, 114.342], (43, 903, 150, 1000): [107.236], (22, 231, 150, 1000): [89.82700000000001], (132, 8646,
                    150, 1000): [165.856], (10, 45, 150, 1000): [82.915], (140, 9730, 150, 1000): [178.709], (21, 210, 150, 1000): [88.281], (23, 253, 150, 1000): [88.80199999999999], (57, 1596, 150, 1000): [121.648], (15, 105, 150, 1000): [85.271, 84.994], (41, 820, 150, 1000): [104.677, 103.809], (5, 10, 150, 1000): [78.82300000000001, 79.50099999999999, 79.52300000000001], (82, 3321, 150, 1000): [127.24399999999999, 128.22899999999998], (45, 990, 150, 1000): [108.067], (117,
                        6786, 150, 1000): [184.274], (116, 6670, 150, 1000): [182.17499999999998], (107, 5671, 150, 1000): [164.835, 160.705], (37, 666, 150, 1000): [99.81599999999999], (26, 325, 150, 1000): [89.329], (50, 1225, 150, 1000): [113.718]})
    puntos = map(
            lambda (n1, m1, n2, m2) : (
                n1,
                median(resultados[(n1, m1, n2, m2)])),
            resultados.keys())

    puntos_dict = {}
    for (n1, tiempos) in puntos:
        puntos_dict[n1] = []
    for (n1, t) in puntos:
        puntos_dict[n1].append(t)

    puntos = sorted(
            map(
                lambda n1: (n1, min(puntos_dict[n1])/1000),
                puntos_dict.keys()),
            key=lambda tup: tup[0])

    print puntos

    plt.figure()
    plt.title("Algoritmo goloso (n_2 = 150)")
    #k = encontrar_k(puntos, lambda x: x**6)
    k1 = 0.0000000004
    plt.plot(map(lambda tup: tup[0], puntos),
             map(lambda tup: tup[1], puntos),
            label="Nuestro algoritmo",
            marker=".")
    plt.plot(map(lambda tup: tup[0], puntos),
            map(lambda tup: k1 * (tup[0]**4) + 0.14, puntos),
             label=str(k1) + " * n_1^4"
             )
    plt.ylabel("Tiempo (ms)")
    plt.xlabel("Tamano de la entrada (n_1)")
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
    #print general(min_n, max_n, 100)
    graficar_problema4_n2fijo()

main()
