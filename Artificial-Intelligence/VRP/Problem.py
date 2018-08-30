from math import sqrt
import copy
import matplotlib.pyplot as plt
import numpy as np
import sys
from sklearn.cluster import KMeans
from random import randint

class Problem():
	
	def __init__(self, n_vehicles, consumers, weights, v_capacity, warehouse):
		self.n_vehicles = n_vehicles
		self.weights = weights
		# Peso do "consumidor" depósito
		self.weights.insert(0, 0)	
		self.consumers = consumers
		self.consumers.insert(0, warehouse)
		self.v_capacity = v_capacity
		self.warehouse = warehouse
		self.clusters = None
		self.routes = list()
		self.v_weights = []
		self.attended = []
	def get_distance(self, p1, p2):
		return sqrt( ((p2[0] - p1[0]) ** 2) + ((p2[1] - p1[1]) ** 2) )
	
	def get_cost(self, routes):
		cost = 0		
		for r in routes:
			len_route_consumers = len(r)
			if len_route_consumers > 1:				
				for i in range(0, len_route_consumers):				
					if i == len_route_consumers - 1:
						break;
					cost += self.get_distance(self.consumers[r[i]], self.consumers[r[i+1]])		
		return cost
	
	def not_attended_consumer_exists(self):
		for i in range(len(self.consumers)):
			if not i in self.attended:
				return True
		return False

	def get_initial_solution(self):
		costs = list()
		n_vehicles_copy = copy.deepcopy(self.n_vehicles)
		for i in range(50):
			routes = list()
			self.n_vehicles = n_vehicles_copy
			self.attended = list()
			self.v_weights = list()
			while self.not_attended_consumer_exists():			
				kmeans = KMeans(n_clusters=self.n_vehicles)
				kmeans.fit(self.consumers)
				y_kmeans = kmeans.predict(self.consumers)
				
				for i in range(0, self.n_vehicles):
					# Inicializa os pesos de cada veículo
					self.v_weights.append(self.v_capacity)
					# Cria uma lista para cada rota
					routes.append([])
					routes[i].append(0)
					self.attended.append(0)

				for i in range(0, len(routes)):				
					# Ultima posição visitada pelo veículo i
					current_pos = self.consumers[routes[i][-1]]
					while len([j for j in range(len(y_kmeans)) if y_kmeans[j] == i and not j in self.attended]) > 0:					
						# Consumidores da vizinhança i
						neighborhood = [[self.get_distance(current_pos, self.consumers[j]), j] for j in range(len(y_kmeans)) if y_kmeans[j] == i and j not in self.attended]						
						# Armazena a distancia e o indice do consumidor mais proximo da posição atual
						nn = min(neighborhood, key= lambda p: p[0])
						consumer_index = nn[1]						
						# Adiciona o consumidor na rota e na lista de consumidores atendidos
						if self.v_weights[i] - self.weights[consumer_index] >= 0:
							routes[i].append(consumer_index)
							self.attended.append(consumer_index)
							self.v_weights[i] -= self.weights[consumer_index]
						else:
							break
				if self.not_attended_consumer_exists():					
					del kmeans
					del y_kmeans
					self.attended = list()
					self.v_weights = list()
					routes = list()
					self.n_vehicles+= 1
			# Retorno ao depósito
			for r in routes:
				r.append(0)
			costs.append([self.get_cost(routes), routes])
		
		min_cost = min(filter(lambda k: k[0] != 0, costs), key = lambda p: p[0])

		final_routes = min_cost[1]		
		# Lista com os indices já escolhidos para troca em outras iterações
		indexes_already_picked = list()
		
		for j in range(len(final_routes)):
			# O custo da rota j nas rotas finais para comparação com novas configurações
			cost = self.get_cost([final_routes[j]])
			# Copia a rota para não perder os valores originais
			route =  copy.deepcopy(final_routes[j])
			for i in range(250):
				# Seleciona valores de indices para fazer trocas dentro da rota
				r = copy.deepcopy(route)
				x1 = randint(1, len(r) - 2)
				x2 = randint(1, len(r) - 2)
				# Para não desfazer alterações feitas anteriormente
				if (x1,x2) in indexes_already_picked or x1 == x2:
					continue
				# Faz o wap de consumidores na rota e verifica se o custo indivdual da rota diminuiu
				r[x1], r[x2] = r[x2], r[x1]
				new_cost = self.get_cost([r])				
				if new_cost < cost:					
					cost = new_cost
					# Caso o valor do custo seja reduzido, assume a rota como parte da nova solução
					route = r	
					final_routes[j] = r
					indexes_already_picked.append((x1,x2))
		
		# Printa as rotas na saida
		for r in final_routes:			
			print (" ".join(map(str, r)))
		
		# print(self.get_cost(min_cost[1]))

		# Caso queira mostrar o gráfico das rotas, basta inserir um argumento qualquer ao programa
		if (len(sys.argv) > 1 ):
			final_cost = self.get_cost(final_routes)
			print(final_cost)
			for route in min_cost[1]:
				route_consumer_points = [self.consumers[j] for j in [i for i in route]]
				plt.plot( [x[0] for x in route_consumer_points], [x[1] for x in route_consumer_points], linestyle='-', marker='o')			
			plt.show()