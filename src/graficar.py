import networkx as nx
import matplotlib.pyplot as plt
import fileinput

G=nx.Graph()

for line in fileinput.input():
		if fileinput.isfirstline():
			data = line.split( )
			m = int(data[1])
		if not fileinput.isfirstline():
			numbers = line.split( )
			u = numbers[0]
			v = numbers[1]
			G.add_edge(u,v)
			m = m-1
			if m == 0:
				break

print(list(G.nodes()))
print(list(G.edges()))
nx.draw(G,pos=nx.spring_layout(G)) 
plt.show()
