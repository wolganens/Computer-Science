from arquivos import readtable, column
import matplotlib.pyplot as plt
import numpy as np

class LinearRegression(object):
	"""docstring for LR"""
	def __init__(self):
		self.alpha = 0.001
		self.load_training_data("dataset.txt")
		self.m = len(self.training_data[0])				

	def load_training_data(self, file_name):
		matrix = readtable(file_name)
		self.training_data = (column(matrix, 1), column(matrix, 2))

	def h(self, t0, t1, x):
		return t0 + t1 * x

	def error(self, t0,t1):
		x = self.training_data[0]
		y = self.training_data[1]
		
		error = 0
		
		for i in range(0, self.m):			
			error += (y[i] - self.h(t0, t1, x[i])) ** 2
		
		return float(error)/float(self.m)

	def gradient(self, t0, t1):
		x = self.training_data[0]
		y = self.training_data[1]
		n = float(self.m)
		
		t0_gradient = 0
		t1_gradient = 0
		error = self.error(t0, t1)
		prev_error = error + 1
		
		while prev_error > error:			
			for i in range(0, self.m):			
				t0_gradient = (y[i] - self.h(t1, t1, x[i]))
				t1_gradient = (y[i] - self.h(t0, t1, x[i])) * x[i]			
			
			t0_gradient = - (2/float(n)) * t0_gradient
			t1_gradient = - (2/float(n)) * t1_gradient

			t0 += -(self.alpha * t0_gradient)
			t1 += - (self.alpha * t1_gradient)
			prev_error = error		
			error = self.error(t0,t1)		
		return [t0, t1]		

		

if __name__ == "__main__":
	lr = LinearRegression()

	t0, t1 = lr.gradient(0, 0)		
	x = lr.training_data[0]
	y = lr.training_data[1]

	plt.scatter(x, y)
	a, b = np.polyfit(np.array(x), np.array(y), deg=1)
	
	f = lambda x: t1*x + t0
	d = np.array([min(x),max(y)])
	plt.plot(d,f(d), c="orange", label="fit line between min and max")		
	plt.show()
