"""
parametros:
    1. Ubicacion del binario
"""
import sys
import subprocess

binario = sys.argv[1]


"""def grafo_completo(n):
	res = ""
	for i in range(0,n):
		for j in range (i+1,n):
			res+=str(i)+" "+str(j) + "\n"
   	return res"""

# La definicion de ciclo es para n mayor o igual a 3
def grafo1(n):
    #completo
    return (n, [(i, j) for i in range(n) for j in range(n) if i < j])

def grafo2(n):
    aristas = []
    for i in range(n+1):
        aristas.append((0,i+1))
    for i in range(n):
        for j in range(n):
            if i < j:
                aristas.append((i+n+2, j+n+2))
    aristas.append((0, n+2))
    return (2*n+2, aristas)


def generar_string(n):
    g1 = grafo1(n)
    g2 = grafo2(n)

    s = str(g1[0]) + " " + str(len(g1[1])) + " " + str(g2[0]) + " " + str(len(g2[1]))  + "\n"
    for x in g1[1]:
        s += str(x[0]) + " " + str(x[1]) + "\n"
    for x in g2[1]:
        s += str(x[0]) + " " + str(x[1]) + "\n"
    return s


def correr_programa(binario, input_string):
    p = subprocess.Popen(binario,
            shell = True,
            stdin=subprocess.PIPE,
            stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    p.stdin.write(input_string)
    output_string, err = p.communicate()
    return int((output_string.splitlines()[0]).split()[1])


def main(binario):
    resultados = []
    for n in range(3, 100):
        solucion = correr_programa(binario, generar_string(n))
        resultados.append((n * (n-1) / 2, solucion))
    print resultados


main(binario)

