import sys
import subprocess

def correr_programa(binario, archivo):
    comando = binario + " < "  + archivo
    p = subprocess.Popen(comando,
                         shell = True,
                         stdin=subprocess.PIPE,
                         stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    out, err = p.communicate()
    return int(out.split()[1])

def main():
    size = 50
    casos = [(50, 500), (100, 500), (150, 400), (200, 400),
             (250, 300), (300, 300), (350, 200), (400, 200),
             (450, 100), (500, 100)]
    ms = []
    for tam, corridas in casos:
        lista = []
        for i in range(corridas):
            print tam, corridas
            nombre_archivo = "caso" + str(tam) + "_" + str(i) + ".txt"
            nombre_archivo = "exp/casos_random/casos_ahora/" + nombre_archivo
            aristas = correr_programa(sys.argv[1], nombre_archivo)
            print aristas
            lista.append(aristas)
        ms.append(lista)
    print ms


main()
