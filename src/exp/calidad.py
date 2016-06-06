import sys

def correr_programa(binario, archivo):
    p = subprocess.Popen("cat " + archivo + " | " + binario + " | head -n 1",
                         shell = True,
                         stdin=subprocess.PIPE,
                         stderr=subprocess.PIPE, stdout=subprocess.PIPE)
    p.stdin.write(input_string)
    out, err = p.communicate()
    return int(out.split()[1])

def main():
    size = 50
    q = [500, 400, 200, 100, 50, 10]
    ms =[[],  [] , [] , [] , [], []]
    for i in range(6):
        random.seed(i)
        size *= 2
        for j in range(q[i]):
            print i, j
            nombre_archivo = "caso" + str(size) + "_" + str(j) + ".txt"
            nombre_archivo = "casos_random/casos_ahora/" + nombre_archivo
            ms[i].append(correr_programa(binario = sys.argv[1]))
    print ms


main()
