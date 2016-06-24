import sys
import subprocess

def correr_programa(binario, archivo):
    comando = binario + " < "  + archivo
    p = subprocess.Popen(comando,
                         shell = True,
                         stdin=subprocess.PIPE,
                         stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    out, err = p.communicate()
    data = out.split()
    return [int(data[0]), float(data[1])]

def main():
    size = 50
    casos = [(50, 50), (100, 40), (150, 10), (200, 10),
             (250, 50), (300, 40), (350, 20), (400, 15)]
        casos = []
    calidades = []
    tiempos = []
    for tam, corridas in casos:
        lista1 = []
        lista2 = []
        for i in range(corridas):
            print sys.argv[1], ":", tam, i+1, "/", corridas
            nombre_archivo = "caso" + str(tam) + "_" + str(i) + ".txt"
            nombre_archivo = "exp/casos_random/casos_ahora/" + nombre_archivo
            aristas, tiempo = correr_programa(sys.argv[1], nombre_archivo)
            lista1.append(aristas)
            lista2.append(tiempo)
        calidades.append(lista1)
        tiempos.append(lista2)
    
    f = open(sys.argv[2], 'w')
    print >> f , calidades
    f.close();

    f = open(sys.argv[3], 'w')
    print >> f , tiempos
    f.close();

main()
