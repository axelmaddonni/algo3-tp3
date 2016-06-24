#!/usr/bin/python
# -*- coding: utf-8 -*-
from scipy import stats
import numpy as np
import matplotlib.pyplot as plt
from sys import argv

calidadG = []
tiempoG  = []
calidadL = []
tiempoL  = []
calidadT = []
tiempoT  = []


casos_calidad0 = [(50, 60), (100, 35), (150, 20), (200, 10),
                  (250, 10), (300, 10)]

casos_tiempo0 = [(50, 60), (100, 35), (150, 20), (200, 10),
                  (250, 10), (300, 10)]


def barplot_calidad0(data_set):
  tamano, cantidad = casos_calidad0[data_set]
  local = [calidadL[data_set], calidadL[data_set+1]]
  tabu = [calidadT[data_set], calidadT[data_set+1]]


  Mean0 = [np.mean(local[0]), np.mean(local[1])]
  Std0  = [np.std(local[0]), np.std(local[1])]

  Mean1 = [np.mean(tabu[0]), np.mean(tabu[1])]
  Std1  = [np.std(tabu[0]), np.std(tabu[1])]


  N = 2

  ind = np.arange(N)  # the x locations for the groups
  width = 0.3      # the width of the bars

  fig, ax = plt.subplots()

  rects1 = ax.bar(ind, Mean0, width, color='r', yerr=Std0)

  rects2 = ax.bar(ind+width, Mean1, width, color='y', yerr=Std1)

  # add some text for labels, title and axes ticks
  ax.set_ylabel('#Aristas extra')
  ax.set_title(u'Comparación de la cantidad de aristas obtenidas')
  ax.set_xticks(ind+width)
  ax.set_xlabel(u'Tamaño del grafo más grande (#vértices)')
  ax.set_xticklabels( [tamano, tamano+50] )

  ax.set_ylim(bottom=0)

  ax.legend( (rects1[0], rects2[0]), ('Local', 'Tabu'), loc=2 )

  def autolabel(rects):
    # attach some text labels
    for rect in rects:
      height = rect.get_height()
      ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.1f'%(round(height,2)),ha='center', va='bottom')

  autolabel(rects1)
  autolabel(rects2)

  plt.savefig('graficos/calidad' + str(data_set) + '.pdf')



def barplot_tiempo0(data_set):
  tamano, cantidad = casos_tiempo0[data_set]
  local = [tiempoL[data_set], tiempoL[data_set+1]]
  tabu = [tiempoT[data_set], tiempoT[data_set+1]]


  Mean0 = [np.mean(local[0]), np.mean(local[1])]
  Std0  = [np.std(local[0]), np.std(local[1])]

  Mean1 = [np.mean(tabu[0]), np.mean(tabu[1])]
  Std1  = [np.std(tabu[0]), np.std(tabu[1])]


  N = 2

  ind = np.arange(N)  # the x locations for the groups
  width = 0.3      # the width of the bars

  fig, ax = plt.subplots()

  rects1 = ax.bar(ind, Mean0, width, color='r', yerr=Std0)

  rects2 = ax.bar(ind+width, Mean1, width, color='y', yerr=Std1)

  # add some text for labels, title and axes ticks
  ax.set_ylabel('Tiempo extra (seg)')
  ax.set_title(u'Comparación del tiempo necesario')
  ax.set_xticks(ind+width)
  ax.set_xlabel(u'Tamaño del grafo más grande (#vértices)')
  ax.set_xticklabels( [tamano, tamano+50] )

  ax.set_ylim(bottom=0)

  ax.legend( (rects1[0], rects2[0]), ('Local', 'Tabu'), loc=2 )

  def autolabel(rects):
    # attach some text labels
    for rect in rects:
      height = rect.get_height()
      ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.2f'%(round(height,2)),ha='center', va='bottom')

  autolabel(rects1)
  autolabel(rects2)

  plt.savefig('graficos/tiempo' + str(data_set) + '.pdf')

def barplot_cociente0(data_set):
  tamano0, cantidad0 = casos_tiempo0[data_set]
  tamano1, cantidad1 = casos_tiempo0[data_set+1]
  clocal = [calidadL[data_set], calidadL[data_set+1]]
  tlocal = [tiempoL[data_set], tiempoL[data_set+1]]
  ctabu = [calidadT[data_set], calidadT[data_set+1]]
  ttabu = [tiempoT[data_set], tiempoT[data_set+1]]

  local = [[], []]
  tabu = [[], []]

  for i in xrange(cantidad0):
    local[0].append(clocal[0][i]/(tlocal[0][i]/60))
    tabu[0].append(ctabu[0][i]/(ttabu[0][i]/60))

  for i in xrange(cantidad1):
    local[1].append(clocal[1][i]/(tlocal[1][i]/60))
    tabu[1].append(ctabu[1][i]/(ttabu[1][i]/60))

  Mean0 = [np.mean(local[0]), np.mean(local[1])]
  Std0  = [np.std(local[0]), np.std(local[1])]

  Mean1 = [np.mean(tabu[0]), np.mean(tabu[1])]
  Std1  = [np.std(tabu[0]), np.std(tabu[1])]


  N = 2

  ind = np.arange(N)  # the x locations for the groups
  width = 0.3      # the width of the bars

  fig, ax = plt.subplots()

  rects1 = ax.bar(ind, Mean0, width, color='r', yerr=Std0)

  rects2 = ax.bar(ind+width, Mean1, width, color='y', yerr=Std1)

  # add some text for labels, title and axes ticks
  ax.set_ylabel('#Aristas extra / Tiempo extra (aristas/min)')
  ax.set_title(u'Comparación del tiempo necesario')
  ax.set_xticks(ind+width)
  ax.set_xlabel(u'Tamaño del grafo más grande (#vértices)')
  ax.set_xticklabels( [tamano0, tamano1] )

  ax.set_ylim(bottom=0)

  ax.legend( (rects1[0], rects2[0]), ('Local', 'Tabu'), loc=2 )

  def autolabel(rects):
    # attach some text labels
    for rect in rects:
      height = rect.get_height()
      ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.2f'%(round(height,2)),ha='center', va='bottom')

  autolabel(rects1)
  autolabel(rects2)

  plt.savefig('graficos/cociente' + str(data_set) + '.pdf')

def parsear_archivo(f, lista):
  fobj = open(f, "r")
  contenido = fobj.read()
  fobj.close()
  aux = contenido.split("]")
  aux = [(s.strip(' [,]\n')).split(', ') for s in aux]
  while [''] in aux:
    aux.remove([''])
  for l in aux:
    aux2 = []
    #print l
    for s in l:
      aux2.append(float(s))
    lista.append(aux2)

def vec_diferencia_calidad0(l1, i):
  lista = []
  tamano, cant = casos_calidad0[i]
  for j in xrange(cant):
    lista.append(l1[j] - calidadG[i][j])
  return lista

def vec_diferencia_tiempo0(l1, i):
  lista = []
  tamano, cant = casos_tiempo0[i]
  for j in xrange(cant):
    lista.append(l1[j] - tiempoG[i][j])
  return lista



def main():
  #parsear_archivo("test.in", calidadg)
  #print calidadg
  parsear_archivo("resultados/calidad/despues/greedy.out", calidadG)
  parsear_archivo("resultados/tiempo/despues/greedy.out", tiempoG)
  parsear_archivo("resultados/calidad/despues/local_0.out", calidadL)
  parsear_archivo("resultados/tiempo/despues/local_0.out", tiempoL)
  parsear_archivo("resultados/calidad/despues/tabu.out", calidadT)
  parsear_archivo("resultados/tiempo/despues/tabu.out", tiempoT)

  for i in xrange(len(calidadL)):
    calidadL[i] = vec_diferencia_calidad0(calidadL[i], i)
    calidadT[i] = vec_diferencia_calidad0(calidadT[i], i)
    tiempoL[i] = vec_diferencia_tiempo0(tiempoL[i], i)
    tiempoT[i] = vec_diferencia_tiempo0(tiempoT[i], i)

  barplot_calidad0(0)
  barplot_calidad0(2)
  barplot_calidad0(4)

  barplot_tiempo0(0)
  barplot_tiempo0(2)
  barplot_tiempo0(4)

  barplot_cociente0(0)
  barplot_cociente0(2)
  barplot_cociente0(4)

main()