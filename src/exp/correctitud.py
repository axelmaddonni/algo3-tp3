"""
parametros:
    1. Ubicacion del binario
    2. Cantidad de tests, arrancando con ciclos de tamano 3 hasta lo que se le indique
"""
import sys
import subprocess

binario = sys.argv[1]
cuantas_mediciones = int(sys.argv[2])


"""def grafo_completo(n):
	res = ""
	for i in range(0,n):
		for j in range (i+1,n):
			res+=str(i)+" "+str(j) + "\n"
   	return res"""

# La definicion de ciclo es para n mayor o igual a 3
def grafo_ciclo(n):
	res = ""
	for i in range(0,n-1):
		res += str(i)+" "+str(i+1) + "\n"
	res += str(n-1)+" "+str(0) + "\n"  	
	return res

def grafo_test(n):
	res = str(0)+" "+str(1) + "\n"
	for i in range(0,n-2):
		res+= str(i*3+1)+" "+str(i*3+2) + "\n"
		res+= str(i*3+1)+" "+str(i*3+3) + "\n"
		res+= str(i*3+1)+" "+str(i*3+4) + "\n"
   	return res

"""
Ejemplo con n = 6		
  2 5 8 11
0-1-4-7-10-13
  3 6 9 12
"""

def correr_programa(binario, input_string):
    p = subprocess.Popen(binario,
                         shell = True,
                         stdin=subprocess.PIPE,
                         stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    p.stdin.write(input_string)
    output_string, err = p.communicate()
    return output_string


def main(binario, cuantas_mediciones):
	resultados = []
	for i in range(3,cuantas_mediciones+3):
		grafos = str(i) + " " + str(i) + " "
		grafos += str(i+(i-2)*2) + " " + str(i-1+(i-2)*2) + "\n"
		grafos += grafo_ciclo(i)
		grafos += grafo_test(i)
		solucion = correr_programa(binario, grafos)
		# Agarro el segundo numero de la primer fila de la salida del programa, 
		# el cual es siempre la cantidad de aristas del isomorfismo
		aristas_isomorfismo = [numero for numero in [fila for fila in solucion.split('\n')][0].split(' ')][1]
		resultados.append(aristas_isomorfismo)
	print "Lo que da es:\n" + ', '.join(str(i) for i in resultados)
	print "Lo que deberia dar es:\n" + ', '.join(str(i) for i in range(2,cuantas_mediciones+2))

main(binario, cuantas_mediciones)


