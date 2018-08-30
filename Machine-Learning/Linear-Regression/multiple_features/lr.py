from arquivos import readtable, column
import matplotlib.pyplot as plt
import numpy as np

class LinearRegression(object):
	"""docstring for LR"""
	def __init__(self):
		self.alpha = 0.0001
		self.load_training_data("dataset.txt")		

	def load_training_data(self, file_name):
		matrix = readtable(file_name)
		self.x = list()
		self.y = list()
		# Numero de features no dataset		
		self.n = len(matrix[0])
		self.m = len(matrix)
		for row in matrix:
			self.x.append(row[1:self.n - 1])
			self.y.append(row[self.n-1])

	def h(self, weights, x):
		output = 0
		for i in range(0, len(weights)):
			output += sum(weights[i] * x[i])

	def error(self, weights):
		# Vetor de entradas, onde cada posicao de x eh uma vetor de features, x[0] = [f1,f2, f3]
		x = self.x
		# Vetor de saidas, onde cada posicao de y eh uma saida para as features da mesma posicao em x
		y = self.y
		# Numero de entradas
		m = self.m
		# Numero de features
		n = self.n
		error = 0
		for i in range(0, self.m):			
			error += (y[i] - self.h(t0, t1, x[i])) ** 2
		
		return float(error)/float(self.m)

	def gradient(self, t0, t1):
		x = self.x
		y = self.y
		n = float(self.m)

		

if __name__ == "__main__":
	lr = LinearRegression()

	t0, t1 = lr.gradient(0, 0)		
	
	x = lr.training_data[0]
	y = lr.training_data[1]
	print(lr.error(t0,t1))
	plt.show()	
	
	
	
	
