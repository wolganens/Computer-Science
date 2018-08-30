import sys
# Pilha
class Stack(object):	
	def __init__(self):
		self.queue = list()
	
	def push(self, index):
		self.queue.insert(0, index)

class TSP(object):
	"""docstring for TSP"""
	def __init__(self, distances, src, target):
		self.distances = distances
		self.src = src
		self.target = target
		self.visited = set()
		self.n = len(self.distances)
	
	def is_goal_state(self, state):
		return state == self.target
	
	def h(self, state):		
		return self.distances[state][self.target]
	
	def sucessors(self, state):		
		neighbors = [i for i in range(self.n) if i != state and not i in self.visited]
		return sorted(neighbors, key = lambda x : self.h(x))
		
def main():
	count = 0
	distances = list()	
	grafo = dict()
	with open('grafo.txt', 'r') as f:
		pass			
	with open('distancias.txt', 'r') as f:
		for line in f:
			distances.append([int(d) for d in line.split()])
	
	print("Digite a origem: ")
	src = int(input())
	print("Digite o destino: ")
	target = int(input())

	tsp = TSP(distances, src, target)
	s = Stack()
	s.push(src)
	
	if tsp.is_goal_state(src):
		print("Estado final!")
		sys.exit(0)

	while len(s.queue) > 0:
		state = s.queue.pop()
		
		if tsp.is_goal_state(state):
			print("Estado final!")
			print([v for v in tsp.visited])
			sys.exit(0)
		
		tsp.visited.add(state)
		
		for sucessor in tsp.sucessors(state):
			s.push(sucessor)
if __name__ == '__main__':
	main()