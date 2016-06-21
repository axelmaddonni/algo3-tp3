#!/usr/bin/python
# -*- coding: utf-8 -*-
from scipy import stats
import numpy as np
import matplotlib.pyplot as plt
from sys import argv

calidadg = []
tiempog	 = []
calidad0 = []
tiempo0  = []
calidad1 = []
tiempo1  = []
calidad2 = []
tiempo2	 = []

casos_calidad0 = [(50, 500), (100, 400), (150, 250), (200, 200),
        					(250, 100), (300, 50), (350, 40), (400, 30),
        					(450, 20), (500, 10)]

casos_calidad1 = [(50, 50), (100, 40), (150, 10), (200, 10)]

casos_tiempo0 = [(50, 500), (100, 350), (150, 250), (200, 200),
                 (300, 50), (400, 30)]

casos_tiempo1 = [(50, 30), (100, 30), (150, 10), (200, 10)]


def barplot_calidad0(data_set):
	tamano, cantidad = casos_calidad0[data_set]
	local0 = [calidad0[data_set], calidad0[data_set+1]]
	local1 = [calidad1[data_set], calidad1[data_set+1]]

	dif0 = [vec_diferencia_calidad0(local0[0], data_set),
					vec_diferencia_calidad0(local0[1], data_set+1)]
	dif1 = [vec_diferencia_calidad0(local1[0], data_set),
					vec_diferencia_calidad0(local1[1], data_set+1)]

	Mean0 = [np.mean(dif0[0]), np.mean(dif0[1])]
	Std0 	= [np.std(dif0[0]), np.std(dif0[1])]

	Mean1 = [np.mean(dif1[0]), np.mean(dif1[1])]
	Std1 	= [np.std(dif1[0]), np.std(dif1[1])]

	N = 2

	ind = np.arange(N)  # the x locations for the groups
	width = 0.30       # the width of the bars

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

	ax.legend( (rects1[0], rects2[0]), ('INTERCAMBIAR', 'REMPLAZAR'), loc=0 )

	def autolabel(rects):
	 	# attach some text labels
	 	for rect in rects:
			height = rect.get_height()
			ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.1f'%(round(height,2)),ha='center', va='bottom')

	autolabel(rects1)
	autolabel(rects2)

	plt.savefig('graficos/calidad' + str(data_set) + '.pdf')

def barplot_calidad1(data_set):
	tamano, cantidad = casos_calidad0[data_set]
	local0 = [calidad0[data_set], calidad0[data_set+1]]
	local1 = [calidad1[data_set], calidad1[data_set+1]]
	local2 = [calidad2[data_set], calidad2[data_set+1]]

	dif0 = [vec_diferencia_calidad1(local0[0], data_set), 
					vec_diferencia_calidad1(local0[1], data_set+1)]
	dif1 = [vec_diferencia_calidad1(local1[0], data_set), 
					vec_diferencia_calidad1(local1[1], data_set+1)]
	dif2 = [vec_diferencia_calidad1(local2[0], data_set), 
					vec_diferencia_calidad1(local2[1], data_set+1)]

	Mean0 = [np.mean(dif0[0]), np.mean(dif0[1])]
	Std0 	= [np.std(dif0[0]), np.std(dif0[1])]

	Mean1 = [np.mean(dif1[0]), np.mean(dif1[1])]
	Std1 	= [np.std(dif1[0]), np.std(dif1[1])]

	Mean2 = [np.mean(dif2[0]), np.mean(dif2[1])]
	Std2 	= [np.std(dif2[0]), np.std(dif2[1])]

	N = 2

	ind = np.arange(N)  # the x locations for the groups
	width = 0.3       # the width of the bars

	fig, ax = plt.subplots()
	rects1 = ax.bar(ind, Mean0, width, color='r', yerr=Std0)

	rects2 = ax.bar(ind+width, Mean1, width, color='y', yerr=Std1)

	rects3 = ax.bar(ind+2 * width, Mean2, width, color='b', yerr=Std2)

	# add some text for labels, title and axes ticks
	ax.set_ylabel('#Aristas adicionales promedio')
	ax.set_title(u'Comparación de la cantidad de aristas obtenidas')
	ax.set_xticks(ind+width)
	ax.set_xlabel(u'Tamaño del grafo más grande (#vértices)')
	ax.set_xticklabels( [tamano, tamano+50] )

	ax.set_ylim(bottom=0)

	ax.legend( (rects1[0], rects2[0], rects3[0]), ('INTERCAMBIAR', 'REMPLAZAR', '3-ROTACION'), loc=0 )
	
	def autolabel(rects):
	 	# attach some text labels
	 	for rect in rects:
			height = rect.get_height()
			ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.1f'%(round(height,2)),ha='center', va='bottom')

	autolabel(rects1)
	autolabel(rects2)
	autolabel(rects3)

	plt.savefig('graficos/calidad' + str(data_set) + '.pdf')

def barplot_cociente0(data_set):
	tamano1, cantidad1 = casos_tiempo0[data_set]
	tamano2, cantidad2 = casos_tiempo0[data_set+1]
	cLocal0 = [calidad0[data_set], calidad0[data_set+1]]
	cLocal1 = [calidad1[data_set], calidad1[data_set+1]]
	tLocal0 = [tiempo0[data_set], tiempo0[data_set+1]]
	tLocal1 = [tiempo1[data_set], tiempo1[data_set+1]]

	cDif0 = [vec_diferencia_calidad0(cLocal0[0], data_set),
					vec_diferencia_calidad0(cLocal0[1], data_set+1)]
	cDif1 = [vec_diferencia_calidad0(cLocal1[0], data_set),
					vec_diferencia_calidad0(cLocal1[1], data_set+1)]

	tDif0 = [vec_diferencia_tiempos0(tLocal0[0], data_set),
					vec_diferencia_tiempos0(tLocal0[1], data_set+1)]
	tDif1 = [vec_diferencia_tiempos0(tLocal1[0], data_set),
					vec_diferencia_tiempos0(tLocal1[1], data_set+1)]

	dif0 = [[], []]
	dif1 = [[], []]
	for i in xrange(cantidad1):
		dif0[0].append(cDif0[0][i]/tDif0[0][i])
		dif1[0].append(cDif1[0][i]/tDif1[0][i])
	for i in xrange(cantidad2):
		dif0[1].append(cDif0[1][i]/tDif0[1][i])
		dif1[1].append(cDif1[1][i]/tDif1[1][i])

	Mean0 = [np.mean(dif0[0]), np.mean(dif0[1])]
	Std0 	= [np.std(dif0[0]), np.std(dif0[1])]

	Mean1 = [np.mean(dif1[0]), np.mean(dif1[1])]
	Std1 	= [np.std(dif1[0]), np.std(dif1[1])]

	N = 2

	ind = np.arange(N)  # the x locations for the groups
	width = 0.3       # the width of the bars

	fig, ax = plt.subplots()
	rects1 = ax.bar(ind, Mean0, width, color='r', yerr=Std0)

	rects2 = ax.bar(ind+width, Mean1, width, color='y', yerr=Std1)

	# add some text for labels, title and axes ticks
	ax.set_ylabel('#Aristas extra / Tiempo extra (aristas/seg)')
	ax.set_title(u'Comparación relación tiempo-calidad')
	ax.set_xticks(ind+width)
	ax.set_xlabel(u'Tamaño del grafo más grande (#vértices)')
	ax.set_xticklabels( [tamano1, tamano2] )

	ax.set_ylim(bottom=0)

	ax.legend( (rects1[0], rects2[0]), ('INTERCAMBIAR', 'REMPLAZAR'), loc=0 )

	def autolabel(rects):
	 	# attach some text labels
	 	for rect in rects:
			height = rect.get_height()
			ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.1f'%(round(height,2)),ha='center', va='bottom')

	autolabel(rects1)
	autolabel(rects2)

	plt.savefig('graficos/cociente0-' + str(data_set) + '.pdf')

def barplot_cociente1(data_set):
	tamano1, cantidad1 = casos_tiempo1[data_set]
	tamano2, cantidad2 = casos_tiempo1[data_set+1]
	cLocal0 = [calidad0[data_set], calidad0[data_set+1]]
	cLocal1 = [calidad1[data_set], calidad1[data_set+1]]
	cLocal2 = [calidad2[data_set], calidad2[data_set+1]]
	tLocal0 = [tiempo0[data_set], tiempo0[data_set+1]]
	tLocal1 = [tiempo1[data_set], tiempo1[data_set+1]]
	tLocal2 = [tiempo2[data_set], tiempo2[data_set+1]]

	cDif0 = [vec_diferencia_calidad1(cLocal0[0], data_set),
					vec_diferencia_calidad1(cLocal0[1], data_set+1)]
	cDif1 = [vec_diferencia_calidad1(cLocal1[0], data_set),
					vec_diferencia_calidad1(cLocal1[1], data_set+1)]
	cDif2 = [vec_diferencia_calidad1(cLocal2[0], data_set),
					vec_diferencia_calidad1(cLocal2[1], data_set+1)]

	tDif0 = [vec_diferencia_tiempos1(tLocal0[0], data_set),
					vec_diferencia_tiempos1(tLocal0[1], data_set+1)]
	tDif1 = [vec_diferencia_tiempos1(tLocal1[0], data_set),
					vec_diferencia_tiempos1(tLocal1[1], data_set+1)]
	tDif2 = [vec_diferencia_tiempos1(tLocal2[0], data_set),
					vec_diferencia_tiempos1(tLocal2[1], data_set+1)]

	dif0 = [[], []]
	dif1 = [[], []]
	dif2 = [[], []]
	for i in xrange(cantidad1):
		dif0[0].append(cDif0[0][i]/tDif0[0][i])
		dif1[0].append(cDif1[0][i]/tDif1[0][i])
		dif2[0].append(cDif2[0][i]/tDif2[0][i])
	for i in xrange(cantidad2):
		dif0[1].append(cDif0[1][i]/tDif0[1][i])
		dif1[1].append(cDif1[1][i]/tDif1[1][i])
		dif2[1].append(cDif2[1][i]/tDif2[1][i])

	Mean0 = [np.mean(dif0[0]), np.mean(dif0[1])]
	Std0 	= [np.std(dif0[0]), np.std(dif0[1])]

	Mean1 = [np.mean(dif1[0]), np.mean(dif1[1])]
	Std1 	= [np.std(dif1[0]), np.std(dif1[1])]

	Mean2 = [np.mean(dif2[0]), np.mean(dif2[1])]
	Std2 	= [np.std(dif2[0]), np.std(dif2[1])]

	N = 2

	ind = np.arange(N)  # the x locations for the groups
	width = 0.3       # the width of the bars

	fig, ax = plt.subplots()
	rects1 = ax.bar(ind, Mean0, width, color='r', yerr=Std0)

	rects2 = ax.bar(ind+width, Mean1, width, color='y', yerr=Std1)

	rects3 = ax.bar(ind+2 * width, Mean2, width, color='b', yerr=Std2)

	# add some text for labels, title and axes ticks
	ax.set_ylabel('#Aristas extra / Tiempo extra (aristas/seg)')
	ax.set_title(u'Comparación relación tiempo-calidad')
	ax.set_xticks(ind+width)
	ax.set_xlabel(u'Tamaño del grafo más grande (#vértices)')
	ax.set_xticklabels( [tamano1, tamano2] )

	ax.set_ylim(bottom=0)

	ax.legend( (rects1[0], rects2[0], rects3[0]), ('INTERCAMBIAR', 'REMPLAZAR', '3-ROTACION'), loc=0 )

	def autolabel(rects):
	 	# attach some text labels
	 	for rect in rects:
			height = rect.get_height()
			ax.text(rect.get_x()+rect.get_width()/2., 1.05*height, '%.1f'%(round(height,2)),ha='center', va='bottom')

	autolabel(rects1)
	autolabel(rects2)

	plt.savefig('graficos/cociente1-' + str(data_set) + '.pdf')

def lineplot_crecimiento():
	Means0 = []
	Stds0 = []
	Means1 = []
	Stds1 = []
	tamanos = []

	for i in xrange(len(casos_calidad0)):
		tamano, cantidad = casos_calidad0[i]
		tamanos.append(tamano)
		local0 = calidad0[i]
		local1 = calidad1[i]

		dif0 = vec_diferencia_calidad0(local0, i)
		dif1 = vec_diferencia_calidad0(local1, i)

		Means0.append(np.mean(dif0))
		Stds0.append(np.std(dif0))
		Means1.append(np.mean(dif1))
		Stds1.append(np.std(dif1))

	fig, ax = plt.subplots()

	plt.plot(tamanos, Means0, 'ro')
	rects1 = ax.errorbar(tamanos, Means0, yerr=Stds0)

	plt.plot(tamanos, Means1, 'ro')
	rects2 = ax.errorbar(tamanos, Means1, yerr=Stds1)

	#ax.set_yscale('log', basey=2)
	ax.set_ylabel('#Aristas extra')
	ax.set_title(u'Crecimiento de las soluciones')
	ax.set_xlabel(u'Tamaño del grafo más grande (#vértices)')
	ax.legend( (rects1[0], rects2[0]), ('INTERCAMBIAR', 'REMPLAZAR'), loc=1 )

	plt.savefig('graficos/crecimiento.pdf')

def parsear_archivo(f, lista):
	fobj = open(f, "r")
	contenido = fobj.read()
	fobj.close()
	aux = contenido.split("]")
	aux =	[(s.strip(' [,]\n')).split(', ') for s in aux]
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
		lista.append(l1[j] - calidadg[i][j])
	return lista

def vec_diferencia_calidad1(l1, i):
	lista = []
	tamano, cant = casos_calidad1[i]
	for j in xrange(cant):
		lista.append(l1[j] - calidadg[i][j])
	return lista

def vec_diferencia_tiempos0(l1, i):
	lista = []
	tamano, cant = casos_tiempo0[i]
	for j in xrange(cant):
		lista.append(l1[j] - tiempog[i][j])
	return lista

def vec_diferencia_tiempos1(l1, i):
	lista = []
	tamano, cant = casos_tiempo1[i]
	for j in xrange(cant):
		lista.append(l1[j] - tiempog[i][j])
	return lista


def main():
	#parsear_archivo("test.in", calidadg)
	#print calidadg
	parsear_archivo("resultados/calidad/greedy.out", calidadg)
	parsear_archivo("resultados/tiempo/greedy.out", tiempog)
	parsear_archivo("resultados/calidad/local_0.out", calidad0)
	parsear_archivo("resultados/tiempo/local_0.out", tiempo0)
	parsear_archivo("resultados/calidad/local_1.out", calidad1)
	parsear_archivo("resultados/tiempo/local_1.out", tiempo1)
	parsear_archivo("resultados/calidad/local_2.out", calidad2)
	parsear_archivo("resultados/tiempo/local_2.out", tiempo2)
	''' Hasta aca anda todo bien ''' 
	barplot_calidad1(0)
	barplot_calidad1(2)
	barplot_calidad0(4)
	barplot_calidad0(6)
	barplot_calidad0(8)
	barplot_cociente0(0)
	barplot_cociente0(2)
	barplot_cociente0(4)
	barplot_cociente1(2)
	lineplot_crecimiento()


main()